// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__FD67504D_D265_4C7D_9845_56DC0914F5A5__INCLUDED_)
#define AFX_STDAFX_H__FD67504D_D265_4C7D_9845_56DC0914F5A5__INCLUDED_

#ifdef _WIN32
	#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
	#include <Windows.h>
#endif

#include "lithtech.h"
#include "ltinteger.h"

// Helpful error output routines.
#define dsi_ConsolePrint dsi_PrintToConsole
extern void dsi_PrintToConsole(const char* pMsg, ...);    // From dsys_interface.h
extern void dsi_OnReturnError(int err);

#endif // !defined(AFX_STDAFX_H__FD67504D_D265_4C7D_9845_56DC0914F5A5__INCLUDED_)
