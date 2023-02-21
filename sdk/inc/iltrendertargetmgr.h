
//-------------------------------------------------------------------
//
//   MODULE    : ILTRENDERTARGETMGR.H
//
//   PURPOSE   : defines an abstract to the render target manager
//
//   CREATED   : 2/2023
//
//   COPYRIGHT : (C) 2023  Made In SErver
//
//-------------------------------------------------------------------

#ifndef ILTRENDERTARGETRMGR_H
#define ILTRENDERTARGETRMGR_H

#include "ltbasedefs.h"
#include "ltmodule.h"
#include "iltrendermgr.h"

struct RenderTargetParams
{
	int						Width;
	int						Height;
	ERenderTargetFormat		RT_Format;
	EStencilBufferFormat	DS_Format;
};

class IRenderTarget
{
public:
	virtual				~IRenderTarget() {}

	virtual LTRESULT	Init(int nWidth, int nHeight, ERenderTargetFormat eRTFormat, EStencilBufferFormat eDSFormat) = 0;
	virtual LTRESULT	Term() = 0;
	virtual LTRESULT	Recreate() = 0;
	virtual LTRESULT	InstallOnDevice() = 0;
	virtual const RenderTargetParams& GetRenderTargetParams() = 0;
	virtual LTRESULT	StretchRectToSurface(HBACKBUFFER pBackBuffer) = 0;
};

class ILTRenderTargetMgr : public IBase
{
public:
	//set the interface version number
	interface_version(ILTRenderTargetMgr, 0);

	virtual								~ILTRenderTargetMgr() {}

	virtual LTRESULT					Init() = 0;
	virtual LTRESULT					Term() = 0;

	virtual LTRESULT					AddRenderTarget(int Width, int Height, ERenderTargetFormat eRTFormat, EStencilBufferFormat eDSFormat, HRENDERTARGET hRenderTarget);
	virtual IRenderTarget*				GetRenderTarget(HRENDERTARGET hRenderTarget) = 0;
	virtual LTRESULT					RemoveRenderTarget(HRENDERTARGET hRenderTarget) = 0;
	virtual void						SetCurrentRenderTargetHandle(HRENDERTARGET hRenderTarget) = 0;
	virtual HRENDERTARGET				GetCurrentRenderTargetHandle();
	virtual void						FreeDeviceObjects() = 0;
	virtual void						RecreateRenderTargets() = 0;

};

#endif
