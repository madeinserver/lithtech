
//-------------------------------------------------------------------
//
//   MODULE    : ILTEFFECTSHADERMGR.H
//
//   PURPOSE   : defines an abstract to the effect shader manager
//
//   CREATED   : 2/2023
//
//   COPYRIGHT : (C) 2023  Made In SErver
//
//-------------------------------------------------------------------

#ifndef ILTEFFECTSHADERMGR_H
#define ILTEFFECTSHADERMGR_H

#include "ltbasedefs.h"
#include "ltmodule.h"
#include "iltstream.h"

class ILTEffectShaderMgr : public IBase
{
public:
	//set the interface version number
	interface_version(ILTEffectShaderMgr, 0);

	virtual ~ILTEffectShaderMgr() {}

	virtual void						Term() = 0;

	// add a effect shader
	virtual bool						AddEffectShader(ILTStream* pStream,
		const char* ShaderName,
		int ShaderID,
		const uint32* pVertexElements,
		uint32 VertexElementsSize,
		HEFFECTPOOL EffectPoolID) = 0;

	// remove a effect shader
	virtual void						RemoveEffectShader(int ShaderID) = 0;

	// remove all effect shaders
	virtual void						RemoveAllEffectShaders() = 0;

	// effect shader access
	virtual LTEffectShader* GetEffectShader(int ShaderID) = 0;

	// frees all the device shader handles
	virtual void						FreeDeviceObjects() = 0;

	// recreates all the shaders. This is necessary when the device changes.
	virtual void						RecreateEffectShaders() = 0;

	virtual bool						AddEffectPool(HEFFECTPOOL EffectPoolID) = 0;
	virtual bool						RemoveEffectPool(HEFFECTPOOL EffectPoolID) = 0;
	virtual void*						GetEffectPool(HEFFECTPOOL EffectPoolID) = 0;
};

#endif
