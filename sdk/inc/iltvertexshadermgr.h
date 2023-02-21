
//-------------------------------------------------------------------
//
//   MODULE    : ILTVERTEXSHADERMGR.H
//
//   PURPOSE   : defines an abstract to the vertex shader manager
//
//   CREATED   : 2/2023
//
//   COPYRIGHT : (C) 2023  Made In SErver
//
//-------------------------------------------------------------------

#ifndef ILTVERTEXSHADERMGR_H
#define ILTVERTEXSHADERMGR_H

#include "ltbasedefs.h"
#include "ltmodule.h"
#include "iltstream.h"

class ILTVertexShaderMgr : public IBase
{
public:
	//set the interface version number
	interface_version(ILTVertexShaderMgr, 0);

	virtual ~ILTVertexShaderMgr() {}

	virtual void						Term() = 0;

	// add a vertex shader
	virtual bool						AddVertexShader(ILTStream* pStream, const char* ShaderName, int ShaderID,
		const void* pVertexElements, uint32 VertexElementsSize,
		bool bCompileShader) = 0;

	// remove a vertex shader
	virtual void						RemoveVertexShader(int ShaderID) = 0;

	// remove all vertex shaders
	virtual void						RemoveAllVertexShaders() = 0;

	// vertex shader access
	virtual LTVertexShader* GetVertexShader(int ShaderID) = 0;

	// frees all the device shader handles
	virtual void						FreeDeviceObjects() = 0;

	// recreates all the shaders. This is necessary when the device changes.
	virtual void						RecreateVertexShaders() = 0;

	// sets the shader constants
	virtual bool						SetVertexShaderConstants(LTVertexShader* pShader) = 0;

	// installs the specified shader into the device
	virtual bool						InstallVertexShader(LTVertexShader* pShader) const = 0;

	// uninstalls any currently installed shaders
	virtual void						UninstallVertexShader() const = 0;
};

#endif
