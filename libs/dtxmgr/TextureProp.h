//------------------------------------------------------------------
//
//  FILE      : TextureProp.h
//
//  PURPOSE   :	Texture properties structure
//
//  COPYRIGHT : (c) 2003 Touchdown Entertainment, Inc. All rights reserved.
//
//------------------------------------------------------------------

#ifndef __TEXTUREPROP_H__
#define __TEXTUREPROP_H__
#pragma once

#include "dtxmgr.h"

// OLD Defs
class TextureData;

#define TPROP_FLAGS					(1<<0)
#define TPROP_GROUP					(1<<2)
#define TPROP_NUMMIPMAPS			(1<<3)
#define TPROP_FULLBRITES			(1<<4)
#define TPROP_PREFER4444			(1<<5)
#define TPROP_PREFER16BIT			(1<<6)
#define TPROP_COMMANDSTRING			(1<<7)
#define TPROP_DATAFORMAT			(1<<8)
#define TPROP_NONS3TCMIPMAPOFFSET	(1<<9)
#define TPROP_UIMIPMAPOFFSET		(1<<10)
#define TPROP_TEXTUREPRIORITY		(1<<11)
#define TPROP_DETAILTEXTURESCALE	(1<<12)
#define TPROP_DETAILTEXTUREANGLE	(1<<13)
#define TPROP_PREFER5551			(1<<14)
#define TPROP_32BITSYSCOPY			(1<<15)
#define TPROP_NOSYSCACHE			(1<<16)


class TextureProp
{
public:

	TextureProp()
		: m_pTexture(LTNULL),
		  m_bFullBrights(LTFALSE),
		  m_b32BitSysCopy(LTFALSE),
		  m_bPrefer4444(LTFALSE),
		  m_bPrefer5551(LTFALSE),
		  m_bPrefer16Bit(LTFALSE),
		  m_bNoSysCache(LTFALSE),
		  m_TextureFlags(0),
		  m_TextureGroup(0),
		  m_nMipmaps(0),
		  m_NonS3TCMipmapOffset(0),
		  m_AlphaCutoff(0),
		  m_AverageAlpha(0),
		  m_UIMipmapOffset(0),
		  //m_BPPIdent(BPP_32),
		  //m_TempBPPIdent(BPP_32),
		  m_TexturePriority(0),
		  m_DetailTextureScale(0.0f),
		  m_DetailTextureAngle(0),
		  m_Initted(false)
	{
	}

	~TextureProp();

	// initialize
	bool		Init(const char *pFilename, int nFileHandle);
	bool		Save(const char *pFilename, int nFileHandle);
	bool		New(unsigned short nWidth, unsigned short nHeight, unsigned short nMips);
	bool		Resize(unsigned short nWidth, unsigned short nHeight);
	void		GetDims(unsigned short &nWidth, unsigned short &nHeight);
	bool		GetTextureRGBAData(void* pBuffer, int nMaxBufferSize);
	void*		GetDataBuffer();
	bool		ConvertToFormat(int nBPPIdent);

	void		RebuildMipMaps();
	void		FillMembers();
	void		StoreMembers();

	// terminate
	void		Term();

public:

	// Texture to use in the preview window.
	// If this is NULL, there won't be a preview window.
	// This texture is deleted automatically when the window is closed.
	TextureData*	m_pTexture;

	LTBOOL			m_bFullBrights;
	LTBOOL			m_b32BitSysCopy;
	LTBOOL			m_bPrefer4444;
	LTBOOL			m_bPrefer5551;
	LTBOOL			m_bPrefer16Bit;
	LTBOOL			m_bNoSysCache;
	uint32			m_TextureFlags;
	uint32			m_TextureGroup;
	uint32			m_nMipmaps;
	uint32			m_NonS3TCMipmapOffset;
	int				m_AlphaCutoff;
	int				m_AverageAlpha;
	int				m_UIMipmapOffset;
	char			m_CommandString[DTX_COMMANDSTRING_LEN];
	int				m_BPPIdent;
	int				m_TempBPPIdent;
	uint32			m_TexturePriority;
	float			m_DetailTextureScale;
	int16			m_DetailTextureAngle;

	bool			m_Initted;
};



#endif // __TEXTUREPROP_H__
