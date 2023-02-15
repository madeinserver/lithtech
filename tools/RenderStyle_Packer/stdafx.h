// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__F8D95047_DC20_11D0_9A2C_00C04FD7D17B__INCLUDED_)
#define AFX_STDAFX_H__F8D95047_DC20_11D0_9A2C_00C04FD7D17B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include "ltbasetypes.h"

typedef struct DXGI_JPEG_DC_HUFFMAN_TABLE
{
    uint8 CodeCounts[12];
    uint8 CodeValues[12];
} DXGI_JPEG_DC_HUFFMAN_TABLE;

typedef struct DXGI_JPEG_AC_HUFFMAN_TABLE
{
    uint8 CodeCounts[16];
    uint8 CodeValues[162];
} DXGI_JPEG_AC_HUFFMAN_TABLE;

typedef struct DXGI_JPEG_QUANTIZATION_TABLE
{
    uint8 Elements[64];
} DXGI_JPEG_QUANTIZATION_TABLE;



#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <d3d9.h>
#include <d3dx9.h>
#include <windows.h>
#include <assert.h>

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__F8D95047_DC20_11D0_9A2C_00C04FD7D17B__INCLUDED_)
