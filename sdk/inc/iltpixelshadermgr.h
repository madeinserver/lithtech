
//-------------------------------------------------------------------
//
//   MODULE    : ILTPIXELSHADERMGR.H
//
//   PURPOSE   : defines an abstract to the pixel shader manager
//
//   CREATED   : 2/2023
//
//   COPYRIGHT : (C) 2023  Made In SErver
//
//-------------------------------------------------------------------

#ifndef ILTPIXELSHADERMGR_H
#define ILTPIXELSHADERMGR_H

#include "ltbasedefs.h"
#include "ltmodule.h"
#include "iltstream.h"

class ILTPixelShaderMgr : public IBase
{
public:
	//set the interface version number
	interface_version(ILTPixelShaderMgr, 0);

	virtual ~ILTPixelShaderMgr() {}

	virtual void						Term() = 0;

	// add a pixel shader from file
	virtual bool						AddPixelShader(ILTStream* pStream, const char* ShaderName, int ShaderID, bool bCompileShader) = 0;

	// remove a pixel shader
	virtual void						RemovePixelShader(int ShaderID) = 0;

	// remove all pixel shaders
	virtual void						RemoveAllPixelShaders() = 0;

	// pixel shader access
	virtual LTPixelShader* GetPixelShader(int ShaderID) = 0;

	// frees all the device shader handles
	virtual void						FreeDeviceObjects() = 0;

	// recreates all the shaders. This is necessary when the device changes.
	virtual void						RecreateVertexShaders() = 0;

	// sets the shader constants
	virtual bool						SetPixelShaderConstants(LTPixelShader* pShader) = 0;

	// installs the specified shader into the device
	virtual bool						InstallPixelShader(LTPixelShader* pShader) const = 0;

	// uninstalls any currently installed shaders
	virtual void						UninstallPixelShader() const = 0;
};

#endif
