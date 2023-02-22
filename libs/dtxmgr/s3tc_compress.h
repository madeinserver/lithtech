
// This module performs S3 texture compression.
#ifndef __S3TC_COMPRESS_H__
#define __S3TC_COMPRESS_H__

	#include "dtxmgr.h"

	class S3TC_Compressor
	{
	public:

		// Do the compression.  This uses the S3TC compressor which is awesome.
		LTRESULT CompressUsingLibrary();


	public:

		// The format you want the compressed data to be in.
		// Either BPP_S3TC_DXT1 or BPP_S3TC_DXT3.
		BPPIdent	m_Format;

		// The input data.
		void	*m_pData;
		uint32	m_Width;
		uint32	m_Height;
		long	m_Pitch;
		PFormat	m_DataFormat;

		// This stuff is allocated and filled in with the output data.
		// You are responsible for freeing it (if Compress or CompressUsingLibrary return LT_OK).
		void	*m_pOutData;
		uint32	m_OutDataSize;

	
	protected:

		FormatMgr	m_FormatMgr;


	protected:

		void	CreateBlock(uint32 xBlock, uint32 yBlock, 
			uint32 nBlocksX, uint32 nBlocksY,
			int32 rVariance, int32 gVariance, int32 bVariance,
			uint32 blockSize, LTBOOL bAlpha, uint32 &errorMeasure);
		
	};


	// Converts the texture info the format you specify.
	// If any of the texture's mipmaps are not a multiple of 4 and you try to convert 
	// to a compressed format, it will just chop those mipmaps off.
	LTBOOL ConvertTextureData(TextureData *pData, BPPIdent bpp);


#endif
