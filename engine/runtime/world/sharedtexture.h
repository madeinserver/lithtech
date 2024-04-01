#ifndef _SHAREDTEXTURE_H_
#define _SHAREDTEXTURE_H_

#include "Ilttexture.h"

// SharedTexture flags.  The m_RefCount member is shared by the flags and the refcount.
#define ST_TAGGED           0x8000  // Used by client when freeing unused textures.
#define ST_VALIDTEXTUREINFO 0x4000  // Used to determine if the width, height, format info on the texture is valid
#define ST_REFCOUNTMASK     0x3FFF

// Forward declaration of the file identifier class
struct FileIdentifier;

// Different types of textures determined from their command string
enum ESharedTexType
{
	eSharedTexType_Single,							// No detail texture or environment map
	eSharedTexType_Detail,							// Detail Texture
	eSharedTexType_EnvMap,							// Environment map
	eSharedTexType_EnvMapAlpha,					// Environment map blended with the alpha channel
	eSharedTexType_EnvBumpMap,						// Environment map with an underlying bumpmap
	eSharedTexType_EnvBumpMap_NoFallback,		// Environment map with bumpmap, but falls back to normal texturing instead of environment map
	eSharedTexType_DOT3BumpMap,					// DOT3 bumpmap 
	eSharedTexType_DOT3EnvBumpMap,					// DOT3 bump map with environment map
	eSharedTexType_Effect
};

class SharedTexture : public ILTTexture
{
public:

	enum {	NUM_LINKED_TEXTURES = 4 };

    SharedTexture()
    {
        m_pEngineData		= NULL;
        m_pRenderData		= NULL;
        m_Link.m_pData		= this;
        m_pFile				= NULL;
        m_RefCount			= 0;
		m_eTexType			= eSharedTexType_Single;
		m_nShaderID			= 0;

		for(uint32 nCurrLinkedTex = 0; nCurrLinkedTex < NUM_LINKED_TEXTURES; nCurrLinkedTex++)
			m_pLinkedTexture[nCurrLinkedTex] = NULL;
   }

    inline uint16   GetFlags() const				{return (uint16)(m_RefCount & ~ST_REFCOUNTMASK);}
    inline void     SetFlags(uint16 flags)			{ASSERT(!(flags & ST_REFCOUNTMASK)); m_RefCount &= ST_REFCOUNTMASK; m_RefCount |= (flags & ~ST_REFCOUNTMASK);}

    inline uint16   GetRefCount() const 			{return (uint16)(m_RefCount & ST_REFCOUNTMASK);}
    inline void     SetRefCount(uint16 count)		{ASSERT(!(count & ~ST_REFCOUNTMASK)); m_RefCount &= ~ST_REFCOUNTMASK; m_RefCount |= (count & ST_REFCOUNTMASK);}


	//gets the specified linked texture
	SharedTexture*			GetLinkedTexture(ELinkedTex eTexture)							{ return m_pLinkedTexture[GetTextureID(eTexture)]; }
	const SharedTexture*	GetLinkedTexture(ELinkedTex eTexture) const						{ return m_pLinkedTexture[GetTextureID(eTexture)]; }

	//sets the specified linked texture
	void					SetLinkedTexture(ELinkedTex eTexture, SharedTexture* pTexture)	{ m_pLinkedTexture[GetTextureID(eTexture)] = pTexture; }

	//sets the info associated with the texture
	void					SetTextureInfo(uint32 nWidth, uint32 nHeight, const PFormat& Format)
	{
		SetFlags(GetFlags() | ST_VALIDTEXTUREINFO);
		m_nWidth	= nWidth;
		m_nHeight	= nHeight;
		m_Format	= Format;
	}

	//accesses the texture info. This should never be called, the r_GetTextureInfo should
	//be used instead since that will appropriately handle loading the texture if it has not
	//been yet
	void					GetTextureInfo(uint32& nWidth, uint32& nHeight, PFormat& Format) const
	{
		assert((GetFlags() & ST_VALIDTEXTUREINFO) != 0);
		nWidth	= m_nWidth;
		nHeight = m_nHeight;
		Format	= m_Format;
	}

public:

    void				*m_pEngineData;
    void				*m_pRenderData;
    LTLink				m_Link;

    FileIdentifier		*m_pFile;		// File identifier so the client can load it.
    ESharedTexType		m_eTexType;		// Determines the type of this texture
	int					m_nShaderID;	// Effect shader ID (0 for none)

protected:

	//given a texture type, it will map it into an index in the linked texture list
	static uint32 GetTextureID(ELinkedTex eTexture)
	{
		switch(eTexture)
		{
		//since no shared texture type involves a detail texture AND an evnmap, we can throw
		//those into the same link
		case eLinkedTex_EnvMap:
		case eLinkedTex_Detail:
		case eLinkedTex_EffectTexture1:
			return 0;
			break;
		case eLinkedTex_BumpMap:
		case eLinkedTex_EffectTexture2:
			return 1;
			break;
		case eLinkedTex_EffectTexture3:
			return 2;
			break;
		case eLinkedTex_EffectTexture4:
			return 3;
			break;
		default:
			assert(!"Invalid linked texture type specified");
			return 0;
			break;
		}
	}				

	// Appropriately linked textures defined by the shared texture type
    SharedTexture		*m_pLinkedTexture[NUM_LINKED_TEXTURES];		

	// Ref count and flags.
    uint16				m_RefCount;			

	//information about the texture surface. Only valid after the texture data has been loaded
	//at least once, this can be determined by checking the ST_VALIDTEXTUREINFO flag
	uint16				m_nWidth;
	uint16				m_nHeight;
	PFormat				m_Format;
};

#endif
