
#include "bdefs.h"
#include "dtxmgr.h"
#include "render.h"
#include "ltpixelformat.h"
#include "dtxmgr.h"

extern FormatMgr g_FormatMgr;
static int g_dtxInMemSize = 0;

//Texture groups, used to control offsetting of Mip Maps when they are loaded, thus allowing
//us to not waste any memory loading mips higher than those that we are going to use. Note that
//this define needs to match the one in the engine vars code. This is ugly, but there is no
//shared header.
#define MAX_TEXTURE_GROUPS 4
extern int32	g_CV_TextureMipMapOffset;
extern int32	g_CV_TextureGroupOffset[MAX_TEXTURE_GROUPS];

// Based on the value of bSkip, it either memset()s the memory to 0 or reads it from the file.
void dtx_ReadOrSkip(
	LTBOOL bSkip,
	ILTStream* pStream,
	int32 nFileHandle,
	void* pData,
	uint32 dataLen)
{
	if (bSkip)
	{
		memset(pData, 0, dataLen);
		pStream->SeekTo(pStream->GetPos() + dataLen);
	}
	else
	{
		pStream->Read(pData, dataLen);
	}
}

LTRESULT dtx_Create(ILTStream *pStream, TextureData **ppOut, uint32& nBaseWidth, uint32& nBaseHeight)
{
	TextureData *pRet;
	uint32 allocSize, textureDataSize;
	

	DtxHeader hdr;
	STREAM_READ(hdr);
	if (hdr.m_ResType != LT_RESTYPE_DTX) 
		RETURN_ERROR(1, dtx_Create, LT_INVALIDDATA);

	// Correct version and valid data?
	if (hdr.m_Version != CURRENT_DTX_VERSION) 
		RETURN_ERROR(1, dtx_Create, LT_INVALIDVERSION);

	if (hdr.m_nMipmaps == 0 || hdr.m_nMipmaps > MAX_DTX_MIPMAPS) 
		RETURN_ERROR(1, dtx_Create, LT_INVALIDDATA);

	
	//figure out the dimensions that we are going to want our texture to start out at
	uint32 nMipOffset = (uint32)LTMAX(0, g_CV_TextureMipMapOffset);
	if(hdr.GetTextureGroup() < MAX_TEXTURE_GROUPS)
	{
		nMipOffset = (uint32)LTMAX(0, g_CV_TextureMipMapOffset + g_CV_TextureGroupOffset[hdr.GetTextureGroup()]);
	}

	//clamp our mipmap offset to the number of mipmaps that we actually have
	nMipOffset = LTMIN(hdr.m_nMipmaps - 1, nMipOffset);

	nBaseWidth  = hdr.m_BaseWidth;
	nBaseHeight = hdr.m_BaseHeight;

	//now we need to determine our dimensions
	uint32 nTexWidth  = hdr.m_BaseWidth  / (1 << nMipOffset);
	uint32 nTexHeight = hdr.m_BaseHeight / (1 << nMipOffset);
	uint32 nNumMips	  = hdr.m_nMipmaps - nMipOffset;

	// I'm supporting converts to DD texture formats (the sys mem copy will be in DD format - so it's fast copy & minimal mem storage).

	PFormat DstFormat;

	BPPIdent TexFormat = hdr.GetBPPIdent();

	bool bConvertToDDFormat = true;

	// Need to get the DD format (we're going to store it in memory in the DD format)...
	if(!r_GetRenderStruct()->GetTextureDDFormat2(hdr.GetBPPIdent(),hdr.m_IFlags,&DstFormat))
		RETURN_ERROR(1, dtx_Create, LT_INVALIDFILE); 

	// If they're the same, just blip on out...
	BPPIdent SrcBppIdent = hdr.GetBPPIdent();
	if (DstFormat.GetType() == SrcBppIdent) 
		bConvertToDDFormat = false;
	if (hdr.m_IFlags & DTX_NOSYSCACHE) 
		bConvertToDDFormat = false;
	if (hdr.m_IFlags & DTX_32BITSYSCOPY) 
		bConvertToDDFormat = false;

	//determine what format we are going to be using
	if(bConvertToDDFormat)
		TexFormat = DstFormat.GetType();

	pRet = dtx_Alloc(TexFormat, nTexWidth, nTexHeight, nNumMips, &allocSize, &textureDataSize,hdr.m_IFlags);
	if (!pRet) 
		RETURN_ERROR(1, dtx_Create, LT_OUTOFMEMORY); 


	if (bConvertToDDFormat) 
	{ 
		pRet->m_PFormat = DstFormat; 
	}
	else 
	{ 
		dtx_SetupDTXFormat2(pRet->m_Header.GetBPPIdent(), &pRet->m_PFormat); 
	}

	pRet->m_pSharedTexture = LTNULL;
	uint8 iBppBefore = pRet->m_Header.m_Extra[2];
	memcpy(&pRet->m_Header, &hdr, sizeof(DtxHeader));
	if (bConvertToDDFormat) 
		pRet->m_Header.m_Extra[2] = iBppBefore;	// Restore the Bpps (because we might have asked for a different one)...

	//restore the width, height, and mipmaps
	pRet->m_Header.m_BaseWidth  = nTexWidth;
	pRet->m_Header.m_BaseHeight = nTexHeight;
	pRet->m_Header.m_nMipmaps	= nNumMips;

	// Alloc a tmp buffer to read in the source image...
	uint8* pTmpBuffer = NULL; 
	TextureMipData *pMip = &pRet->m_Mips[0];

	if (bConvertToDDFormat) 
	{
		uint32 size = CalcImageSize(hdr.GetBPPIdent(), pMip->m_Width, pMip->m_Height);
		LT_MEM_TRACK_ALLOC(pTmpBuffer = new uint8[size],LT_MEM_TYPE_TEXTURE);
		
		if (!pTmpBuffer) 
			return false; 
	}

	// Read in mipmap data....
	uint32 iTexturesInRow = 1;
	if (hdr.m_IFlags & DTX_CUBEMAP) 
		iTexturesInRow = 6;

	for (uint32 iTex = 0; iTex < iTexturesInRow; ++iTex) 
	{
		uint32 nWidth  = hdr.m_BaseWidth;
		uint32 nHeight = hdr.m_BaseHeight;

		for (uint32 iMipmap=0; iMipmap < hdr.m_nMipmaps; iMipmap++) 
		{
			//determine whether or not we want to read in this mip map or not
			bool bSkipImageData = true;

			uint8* pTmpBufferPtr = pTmpBuffer;
			TextureMipData *pMip = NULL;
			uint8* pMipData		 = NULL;

			//see if we want to actually read in this mipmap
			if(iMipmap >= nMipOffset)
			{
				pMip			= &pRet->m_Mips[iMipmap - nMipOffset];
				pMipData		= pMip->m_Data;
				bSkipImageData	= false;
			}

			pMipData += CalcImageSize(TexFormat, nWidth, nHeight) * iTex; 

			uint32 size = CalcImageSize(hdr.GetBPPIdent(), nWidth, nHeight);
			if (bConvertToDDFormat) 
			{
				dtx_ReadOrSkip(bSkipImageData, pStream, 0, pTmpBuffer, size); 
			}
			else 
			{
				dtx_ReadOrSkip(bSkipImageData, pStream, 0, pMipData, size); 
			}

			if (bConvertToDDFormat && !bSkipImageData) 
			{
				// Convert the mip to DD format...
				PFormat SrcFormat; 
				if (hdr.GetBPPIdent() == BPP_32) 
				{ 
					SrcFormat.Init(hdr.GetBPPIdent(),0xFF000000,0x00FF0000,0x0000FF00,0x000000FF); 
				}
				else 
				{ 
					SrcFormat.Init(hdr.GetBPPIdent(),0x0,0x0,0x0,0x0); 
				}

				r_GetRenderStruct()->ConvertTexDataToDD(pTmpBuffer, &SrcFormat, nWidth, nHeight,
														pMipData,&DstFormat,hdr.GetBPPIdent(), hdr.m_IFlags, nWidth, nHeight);

				pTmpBufferPtr = pTmpBuffer; 
			} 

			nWidth /= 2;
			nHeight /= 2;
		} 
		if ((hdr.m_IFlags & DTX_CUBEMAP) && (iTex==0)) 
		{
			DtxSection DtxSectHeader;
			pStream->Read(&DtxSectHeader, sizeof(SectionHeader)); 
		} 
	} 

	if (pTmpBuffer) 
	{ 
		delete[] pTmpBuffer; 
		pTmpBuffer = NULL; 
	}

	//don't bother loading in the sections
	pRet->m_Header.m_nSections = 0;

	// Check the error status.
	if (pStream->ErrorStatus() != LT_OK) 
	{
		dtx_Destroy(pRet);
		RETURN_ERROR(1, dtx_Create, LT_INVALIDDATA); 
	}

	*ppOut = pRet;
	return LT_OK;
}

