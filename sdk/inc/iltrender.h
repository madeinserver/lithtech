//-------------------------------------------------------------------
//
//   MODULE    : ILTRENDER.H
//
//   PURPOSE   : Render abstractions
//
//   CREATED   : 2/21
//
//   COPYRIGHT : (C) 2023 Made In Server developers
//
//-------------------------------------------------------------------
#ifndef __ILTRENDER_H__
#define __ILTRENDER_H__

#include "ltbasedefs.h"
#include "ltrenderstruct.h"
#include "ltsysnode.h"

class ILTRenderSys
{
protected:
	ILTRenderSys() {}
	virtual ~ILTRenderSys() {}

public:
	virtual bool Init() = 0;
	virtual void Term() = 0;

	virtual void Setup(LTRenderStruct* render) = 0;
	virtual RMode* GetSupportedModes() = 0;
	virtual void FreeModeList(RMode* pModes) = 0;
};

#endif
