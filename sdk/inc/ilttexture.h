#ifndef __ILTTEXTURE_H__
#define __ILTTEXTURE_H__

#include "iltclientfilemgr.h"

enum ELinkedTex
{
	eLinkedTex_EnvMap,			// The environment map of this texture
	eLinkedTex_Detail,			// The detail texture of this texture
	eLinkedTex_BumpMap,			// The bumpmap of this texture
	eLinkedTex_EffectTexture1,	// The effect texture 1 of this texture
	eLinkedTex_EffectTexture2,	// The effect texture 2 of this texture
	eLinkedTex_EffectTexture3,	// The effect texture 1 of this texture
	eLinkedTex_EffectTexture4,	// The effect texture 2 of this texture
};

class ILTTexture
{
public:
	virtual uint16 GetFlags() const = 0;
	virtual void SetFlags(uint16 flags) = 0;

	virtual uint16 GetRefCount() const = 0;
	virtual void SetRefCount(uint16 count) = 0;

	virtual ILTTexture* GetLinkedTexture(ELinkedTex eTexture) = 0;
	virtual const ILTTexture* GetLinkedTexture(ELinkedTex eTexture) const = 0;

	virtual void SetLinkedTexture(ELinkedTex eTexture, ILTTexture* pTexture) = 0;
	virtual void SetTextureInfo(uint32 nWidth, uint32 nHeight, const PFormat& Format) = 0;
	virtual void GetTextureInfo(uint32& nWidth, uint32& nHeight, PFormat& Format) const = 0;

	virtual FileIdentifier* GetFile() = 0;
	virtual void SetFile(FileIdentifier* pFile) = 0;

	virtual TextureData* GetEngineData() = 0;
	virtual void SetEngineData(TextureData* pData) = 0;

	virtual void* GetRenderData() = 0;
	virtual void SetRenderData(void* pData) = 0;

};

#endif
