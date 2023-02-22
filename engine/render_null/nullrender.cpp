
#include <windows.h>
#include "ltbasedefs.h"
#include "ltbasetypes.h"
#include "ltrenderstruct.h"
#include "iltrender.h"
#include "ltcolorops.h"
#include "ltmodule.h"
#include <malloc.h>
#include <string.h>

typedef uint32 DDWORD;

typedef struct DIB_BMI256_struct
{
	BITMAPINFOHEADER	hdr;
	RGBQUAD				colors[256];
} DIB_BMI;

typedef struct NullBuf_t
{
	DDWORD			m_Width, m_Height;
	unsigned short	m_Data[1];
} NullBuf;



DIB_BMI g_bmi;
HWND g_hWnd = NULL;
HBITMAP g_hBitmap = NULL;
void *g_pDibBytes = NULL;
DWORD g_DibWidth, g_DibHeight, g_DibPitchBytes;
bool g_bInOptimized2D=false;
bool g_bIn3D=false;


// ---------------------------------------------------------------- //
// Internal functions.
// ---------------------------------------------------------------- //

int nr_Init(struct RenderStructInit *pInit)
{
	RECT screenRect, wndRect;
	HDC hDC;

	

	pInit->m_RendererVersion = LTRENDER_VERSION;
	g_hWnd = (HWND)pInit->m_hWnd;
	
	// Size the window to how they want it.
	GetWindowRect(GetDesktopWindow(), &screenRect);
	
	// Setup the client rectangle.
	wndRect.left = 0;//((screenRect.right - screenRect.left) - pInit->m_Mode.m_Width) / 2;
	wndRect.top = 0;//((screenRect.right - screenRect.left) - pInit->m_Mode.m_Width) / 2;
	wndRect.right = 0;//wndRect.left + pInit->m_Mode.m_Width;
	wndRect.bottom = 0;//wndRect.top + pInit->m_Mode.m_Height;

	// Figure out the full window coordinates given the client coordinates.
	AdjustWindowRect(&wndRect, WS_OVERLAPPEDWINDOW, FALSE);

	SetWindowPos(g_hWnd, 0, wndRect.left, wndRect.top, wndRect.right-wndRect.left,
		wndRect.bottom-wndRect.top, SWP_NOREPOSITION);

	
	// Create our DIB buffer for the 'screen'.
	hDC = GetDC(NULL);
	if(hDC)
	{
		memset(&g_bmi.hdr, 0, sizeof(BITMAPINFOHEADER));

		g_bmi.hdr.biSize         = sizeof(BITMAPINFOHEADER);
		g_bmi.hdr.biWidth        = pInit->m_Mode.m_Width;
		g_bmi.hdr.biHeight       = -((int)pInit->m_Mode.m_Height);
		g_bmi.hdr.biBitCount     = 16;
		g_bmi.hdr.biPlanes       = 1;
		g_bmi.hdr.biCompression  = BI_RGB;
		g_bmi.hdr.biSizeImage    = 0L;
		g_bmi.hdr.biClrUsed      = 0;
		g_bmi.hdr.biClrImportant = 0;

		g_hBitmap = CreateDIBSection(hDC, (BITMAPINFO*)&g_bmi, DIB_PAL_COLORS, (void**)&g_pDibBytes, NULL, 0);
		if(g_hBitmap)
		{
			g_DibWidth = pInit->m_Mode.m_Width;
			g_DibHeight = pInit->m_Mode.m_Height;
			g_DibPitchBytes = g_DibWidth * 2;
		}

		ReleaseDC(NULL, hDC);
	}

	return RENDER_OK;
}


void nr_Term(bool bFullTerm)
{
	g_hWnd = 0;

	if(g_hBitmap)
	{
		DeleteObject(g_hBitmap);
		g_hBitmap = 0;
	}
	
	g_pDibBytes = NULL;
}


void nr_BindTexture(SharedTexture *pTexture, bool bTextureChanged)
{
}


void nr_UnbindTexture(SharedTexture *pTexture)
{
}


HRENDERCONTEXT nr_CreateContext()
{
	HRENDERCONTEXT p;
	LT_MEM_TRACK_ALLOC(p = (HRENDERCONTEXT)LTMemAlloc(1),LT_MEM_TYPE_RENDERER);
	return p;
}


void nr_DeleteContext(HRENDERCONTEXT hContext)
{
	if(hContext)
	{
		LTMemFree(hContext);
	}
}


void nr_Clear(LTRect *pRect, DDWORD flags, LTRGBColor& ClearColor)
{
	BYTE *pCurLine, *pEndLine;

	if(g_pDibBytes && g_hBitmap)
	{
		pCurLine = (BYTE*)g_pDibBytes;
		pEndLine = pCurLine + g_DibHeight*g_DibPitchBytes;
		while(pCurLine != pEndLine)
		{
			memset(pCurLine, 0, g_DibPitchBytes);
			pCurLine += g_DibPitchBytes;
		}
	}
}


int nr_RenderScene(struct SceneDesc *pScene)
{
	return 0;
}


void nr_RenderCommand(int argc, char **argv)
{
}


void* nr_GetHook(char *pHook)
{
	return 0;
}


void nr_SwapBuffers(uint flags)
{
	BOOL ret;
	HDC hDC;
	
	if(g_hBitmap && g_hWnd && g_pDibBytes)
	{
		hDC = GetDC(g_hWnd);
		if(hDC)
		{
			ret = StretchDIBits(hDC,
					 0, 0, g_DibWidth, g_DibHeight,
					 0, 0, g_DibWidth, g_DibHeight,
					 g_pDibBytes, (BITMAPINFO*)&g_bmi, DIB_RGB_COLORS, SRCCOPY);
			
			ReleaseDC(g_hWnd, hDC);
		}
	}
}

HLTBUFFER nr_CreateSurface(int width, int height)
{
	NullBuf *pBuf;

	LT_MEM_TRACK_ALLOC(pBuf = (NullBuf*)LTMemAlloc(sizeof(NullBuf) + ((width*height)-1) * sizeof(unsigned short)),LT_MEM_TYPE_RENDERER);
	if(pBuf)
	{
		pBuf->m_Width = width;
		pBuf->m_Height = height;
		return (HLTBUFFER)pBuf;
	}
	else
	{
		return LTNULL;
	}
}


void nr_DeleteSurface(HLTBUFFER hSurf)
{
	if(hSurf)
	{
		LTMemFree(hSurf);
	}
}


void nr_GetSurfaceInfo(HLTBUFFER hSurf, DDWORD *pWidth, DDWORD *pHeight)
{
	NullBuf *pBuf;

	pBuf = (NullBuf*)hSurf;
	
	if(pWidth) *pWidth = pBuf->m_Width;
	if(pHeight) *pHeight = pBuf->m_Height;
//	if(pPitchBytes) *pPitchBytes = pBuf->m_Width*2;
}


void* nr_LockSurface(HLTBUFFER hSurf, uint32& Pitch)
{
	NullBuf *pBuf;

	pBuf = (NullBuf*)hSurf;
	return pBuf->m_Data;
}


void nr_UnlockSurface(HLTBUFFER hSurf)
{
}


bool nr_LockScreen(int left, int top, int right, int bottom, void **pData, long *pPitch)
{
	BYTE *pStartLine;

	if(!g_pDibBytes)
		return LTFALSE;

	pStartLine = (BYTE*)g_pDibBytes;
	pStartLine += (DWORD)top * g_DibPitchBytes + (DWORD)(left << 1);
	*pData = pStartLine;
	*pPitch = g_DibPitchBytes;
	return LTTRUE;
}


void nr_UnlockScreen()
{
}


void nr_MakeScreenShot(const char *pFilename)
{
}


bool nr_Start3D()
{
	g_bIn3D = TRUE;
	return LTTRUE;
}


bool nr_End3D()
{
	g_bIn3D = FALSE;
	return LTTRUE;
}


bool nr_IsIn3D()
{
	return g_bIn3D;
}


bool nr_StartOptimized2D()
{
	g_bInOptimized2D = TRUE;
	return LTTRUE;
}


void nr_EndOptimized2D()
{
	g_bInOptimized2D = FALSE;
}


bool nr_IsInOptimized2D()
{
	return g_bInOptimized2D;
}


bool nr_OptimizeSurface(HLTBUFFER hBuffer, DDWORD transparentColor)
{
	return LTFALSE;
}


void nr_UnoptimizeSurface(HLTBUFFER hBuffer)
{
}


bool nr_QueryDeletePalette(struct DEPalette_t *pPalette)
{
	return LTTRUE;
}


void nr_ReadConsoleVariables()
{
}


LTBOOL nr_SetMasterPalette(SharedTexture *pTexture)
{
	return FALSE;
}


bool nr_GetScreenFormat(PFormat *pFormat)
{
	pFormat->Init(BPP_16, 0, RGB555_RMASK, RGB555_GMASK, RGB555_BMASK);
	return true;
}

LTObject* nr_ProcessAttachment(LTObject* pParent, LTAttachment* pAttachment)
{
	return pParent;
}

// Get a shared texture from a file name  (returns NULL on failure)
SharedTexture* nr_GetSharedTexture(const char* pFilename) { return NULL; }

// Gets the texture in memory (guaranteed to be in memory until the next 
// call to GetTexture).  
HTEXTUREDATA nr_GetTexture(SharedTexture* pTexture) { return NULL; }

// Gets the texture's file name
const char* nr_GetTextureName(const SharedTexture* pTexture) { return NULL; }

// Force it to free this texture.
void            nr_FreeTexture(SharedTexture* pTexture) {}

// Runs a string in the console.  The render drivers usually use this
// so they can get HLTPARAMs right away and not have to check for
// them all the time.
void            nr_RunConsoleString(char* pString) {}

// Print a string in the console.           
void            nr_ConsolePrint(char* pMsg, ...) {}

// Gets a parameter from the game (something that can be set from the console).
// Returns NULL if the parameter doesn't exist.
HLTPARAM nr_GetParameter(char* pName) { return NULL; }

// Gets the value of a parameter .. returns 0/NULL if you pass in NULL.
float           nr_GetParameterValueFloat(HLTPARAM hParam) { return 0.0f; }
char* nr_GetParameterValueString(HLTPARAM hParam) { return NULL; }

// Increments the object frame code.  This is needed for portals.
uint32 nr_IncObjectFrameCode() { return 0; }
uint32 nr_GetObjectFrameCode() { return 0; }

// Returns a texture frame code that is guaranteed to not be set in 
// any SharedTextures.  The renderer is expected to set this frame code on
// any SharedTextures that it uses while rendering so the engine can know
// if a texture was viewed or not.
uint16 nr_IncCurTextureFrameCode() { return 0; }

void* nr_GetDevice() {
	return NULL;
} 

DDFormat nr_GetTextureDDFormat1(BPPIdent BPP, uint32 iFlags) { return 0; }
bool            nr_QueryDDSupport(PFormat* Format) { return false; }
bool            nr_GetTextureDDFormat2(BPPIdent BPP, uint32 iFlags, PFormat* pFormat) { return false; }
bool            nr_ConvertTexDataToDD(uint8* pSrcData, PFormat* SrcFormat, uint32 SrcWidth, uint32 SrcHeight, uint8* pDstData, PFormat* DstFormat, BPPIdent eDstType, uint32 nDstFlags, uint32 DstWidth, uint32 DstHeight)
{
	return false;
}


//called to set a texture for the draw primitive
void            nr_DrawPrimSetTexture(SharedTexture* pTexture) {}
void            nr_DrawPrimDisableTextures() {}

bool            nr_SetOptimized2DBlend(LTSurfaceBlend blend) { return false; }
bool            nr_GetOptimized2DBlend(LTSurfaceBlend& blend) { return false; }
bool            nr_SetOptimized2DColor(HLTCOLOR color) { return false; }
bool            nr_GetOptimized2DColor(HLTCOLOR& color) { return false; }

void            nr_BlitToScreen(BlitRequest* pRequest) {}
bool            nr_WarpToScreen(BlitRequest* pRequest) { return false; }

void			nr_MakeCubicEnvMap(const char* pszPrefix, uint32 nSize, const SceneDesc& InSceneDesc) {}


// Get the current render info
void            nr_GetRenderInfo(RenderInfoStruct* pStruct) {}

// Blit from the screen.

void            nr_BlitFromScreen(BlitRequest* pRequest) {}

// Creating RenderObjects...
HRENDEROBJECT nr_CreateRenderObject(RENDER_OBJECT_TYPES ObjectType) { return NULL; }
bool            nr_DestroyRenderObject(HRENDEROBJECT pObject) { return false; }

// Load rendering data from the specified stream
bool			nr_LoadWorldData(ILTStream* pStream) { return false; }

// Change the color of a lightgroup in the currently loaded world
// Returns false if a world isn't loaded
bool			nr_SetLightGroupColor(uint32 nID, const LTVector& vColor) { return false; }

// Change/query the state of an occluder in the currently loaded world
// Returns LT_NOTFOUND if the ID isn't found or LT_NOTINWORLD if a world isn't loaded
LTRESULT nr_SetOccluderEnabled(uint32 nID, bool bEnabled) { return LT_ERROR; }
LTRESULT nr_GetOccluderEnabled(uint32 nID, bool* pEnabled) { return LT_ERROR; }

// Accessing texture effect variables
uint32 nr_GetTextureEffectVarID(const char* pszEffectGroup, uint32 nStage) { return 0; }
bool			nr_SetTextureEffectVar(uint32 nVarID, uint32 nVar, float fValue) { return false; }

// Access to the different object groups
bool			nr_IsObjectGroupEnabled(uint32 nGroup) { return false; }
void			nr_SetObjectGroupEnabled(uint32 nGroup, bool bEnable) {}
void			nr_SetAllObjectGroupEnabled() {}

// Access to the render style map used when rendering the glow effect
bool			nr_AddGlowRenderStyleMapping(const char* pszSource, const char* pszMapTo) { return false; }
bool			nr_SetGlowDefaultRenderStyle(const char* pszFile) { return false; }
bool			nr_SetNoGlowRenderStyle(const char* pszFile) { return false; }

int             nr_GetFrameStats(LTRendererStats& refStats) { return 0; }
bool            nr_GetBackBuffer(HBACKBUFFER* pBackBuffer) { return false; }
void            nr_ReleaseBackBuffer(HBACKBUFFER pBackBuffer) {}

bool            nr_SaveDefaultData() { return false; }
bool            nr_RestoreDefaultData() { return false; }
void            nr_FreeDefaultData() {}
LTRESULT nr_GetDeviceCaps(LTGraphicsCaps* caps) { return LT_ERROR; }
LTRESULT nr_SnapshotCurrentFrame() { return LT_ERROR; }
LTRESULT nr_SaveCurrentFrameToPrevious() { return LT_ERROR; }
LTRESULT nr_UploadCurrentFrameToEffect(LTEffectShader* pEffect, const char* szParam) { return LT_ERROR; }
LTRESULT nr_UploadPreviousFrameToEffect(LTEffectShader* pEffect, const char* szParam) { return LT_ERROR; }
void            nr_SetConsoleView() {}
void            nr_UnsetConsoleView() {}
void            nr_SetConsoleTextRenderMode() {}
void            nr_UnsetConsoleTextRenderMode() {}

void nr_SetMatrixInfo(uint32 i, LTMatrix mtx, void* pOut)
{

}

void nr_FreeMatrix(void* pData)
{

}

void nr_AllocateMatrix(uint32 nNumNodes, void** pOut)
{

}

class NullRenderSys : public ILTRenderSys
{
public:
	bool Init() { return true; }
	void Term() {}

	void Setup(LTRenderStruct* pStruct)
	{
		pStruct->ProcessAttachment = nr_ProcessAttachment;
		pStruct->GetSharedTexture = nr_GetSharedTexture;
		pStruct->GetTexture = nr_GetTexture;
		pStruct->GetTextureName = nr_GetTextureName;
		pStruct->FreeTexture = nr_FreeTexture;
		pStruct->RunConsoleString = nr_RunConsoleString;
		pStruct->ConsolePrint = nr_ConsolePrint;
		pStruct->GetParameter = nr_GetParameter;
		pStruct->GetParameterValueFloat = nr_GetParameterValueFloat;
		pStruct->GetParameterValueString = nr_GetParameterValueString;
		pStruct->IncObjectFrameCode = nr_IncObjectFrameCode;
		pStruct->GetObjectFrameCode = nr_GetObjectFrameCode;
		pStruct->IncCurTextureFrameCode = nr_IncCurTextureFrameCode;

		pStruct->Init = nr_Init;
		pStruct->Term = nr_Term;
		pStruct->GetDevice = nr_GetDevice;

		pStruct->BindTexture = nr_BindTexture;
		pStruct->UnbindTexture = nr_UnbindTexture;
		pStruct->GetTextureDDFormat1 = nr_GetTextureDDFormat1;
		pStruct->QueryDDSupport = nr_QueryDDSupport;
		pStruct->GetTextureDDFormat2 = nr_GetTextureDDFormat2;
		pStruct->ConvertTexDataToDD = nr_ConvertTexDataToDD;

		pStruct->DrawPrimSetTexture = nr_DrawPrimSetTexture;
		pStruct->DrawPrimDisableTextures = nr_DrawPrimDisableTextures;

		pStruct->CreateContext = nr_CreateContext;
		pStruct->DeleteContext = nr_DeleteContext;

		pStruct->Clear = nr_Clear;

		pStruct->Start3D = nr_Start3D;
		pStruct->End3D = nr_End3D;
		pStruct->IsIn3D = nr_IsIn3D;

		pStruct->StartOptimized2D = nr_StartOptimized2D;
		pStruct->EndOptimized2D = nr_EndOptimized2D;
		pStruct->IsInOptimized2D = nr_IsInOptimized2D;
		pStruct->SetOptimized2DBlend = nr_SetOptimized2DBlend;
		pStruct->GetOptimized2DBlend = nr_GetOptimized2DBlend;
		pStruct->SetOptimized2DColor = nr_SetOptimized2DColor;
		pStruct->GetOptimized2DColor = nr_GetOptimized2DColor;

		pStruct->RenderScene = nr_RenderScene;

		pStruct->RenderCommand = nr_RenderCommand;

		pStruct->SwapBuffers = nr_SwapBuffers;

		pStruct->GetScreenFormat = nr_GetScreenFormat;

		pStruct->CreateSurface = nr_CreateSurface;
		pStruct->DeleteSurface = nr_DeleteSurface;

		pStruct->GetSurfaceInfo = nr_GetSurfaceInfo;

		pStruct->LockScreen = nr_LockScreen;
		pStruct->UnlockScreen = nr_UnlockScreen;

		pStruct->OptimizeSurface = nr_OptimizeSurface;
		pStruct->UnoptimizeSurface = nr_UnoptimizeSurface;

		pStruct->LockSurface = nr_LockSurface;
		pStruct->UnlockSurface = nr_UnlockSurface;

		pStruct->BlitToScreen = nr_BlitToScreen;
		pStruct->WarpToScreen = nr_WarpToScreen;

		pStruct->MakeScreenShot = nr_MakeScreenShot;

		pStruct->MakeCubicEnvMap = nr_MakeCubicEnvMap;

		pStruct->ReadConsoleVariables = nr_ReadConsoleVariables;

		pStruct->GetRenderInfo = nr_GetRenderInfo;

		pStruct->BlitFromScreen = nr_BlitFromScreen;

		pStruct->CreateRenderObject = nr_CreateRenderObject;
		pStruct->DestroyRenderObject = nr_DestroyRenderObject;

		pStruct->LoadWorldData = nr_LoadWorldData;

		pStruct->SetLightGroupColor = nr_SetLightGroupColor;

		pStruct->SetOccluderEnabled = nr_SetOccluderEnabled;
		pStruct->GetOccluderEnabled = nr_GetOccluderEnabled;

		pStruct->GetTextureEffectVarID = nr_GetTextureEffectVarID;
		pStruct->SetTextureEffectVar = nr_SetTextureEffectVar;

		pStruct->IsObjectGroupEnabled = nr_IsObjectGroupEnabled;
		pStruct->SetObjectGroupEnabled = nr_SetObjectGroupEnabled;
		pStruct->SetAllObjectGroupEnabled = nr_SetAllObjectGroupEnabled;

		pStruct->AddGlowRenderStyleMapping = nr_AddGlowRenderStyleMapping;
		pStruct->SetGlowDefaultRenderStyle = nr_SetGlowDefaultRenderStyle;
		pStruct->SetNoGlowRenderStyle = nr_SetNoGlowRenderStyle;

		pStruct->GetFrameStats = nr_GetFrameStats;
		pStruct->GetBackBuffer = nr_GetBackBuffer;
		pStruct->ReleaseBackBuffer = nr_ReleaseBackBuffer;

		pStruct->SaveDefaultRenderTarget = nr_SaveDefaultData;
		pStruct->RestoreDefaultRenderTarget = nr_RestoreDefaultData;
		pStruct->FreeDefaultRenderTarget = nr_FreeDefaultData;
		pStruct->GetDeviceCaps = nr_GetDeviceCaps;
		pStruct->SnapshotCurrentFrame = nr_SnapshotCurrentFrame;
		pStruct->SaveCurrentFrameToPrevious = nr_SaveCurrentFrameToPrevious;
		pStruct->UploadCurrentFrameToEffect = nr_UploadCurrentFrameToEffect;
		pStruct->UploadPreviousFrameToEffect = nr_UploadPreviousFrameToEffect;

		pStruct->SetConsoleView = nr_SetConsoleView;
		pStruct->UnsetConsoleView = nr_UnsetConsoleView;
		pStruct->SetConsoleTextRenderMode = nr_SetConsoleTextRenderMode;
		pStruct->UnsetConsoleTextRenderMode = nr_UnsetConsoleTextRenderMode;

		pStruct->AllocateMatrix = nr_AllocateMatrix;
		pStruct->FreeMatrix = nr_FreeMatrix;
		pStruct->SetMatrixInfo = nr_SetMatrixInfo;
	}


	RMode* GetSupportedModes()
	{
		RMode* pMode;

		LT_MEM_TRACK_ALLOC(pMode = new RMode, LT_MEM_TYPE_RENDERER);
		if (pMode)
		{
			LTStrCpy(pMode->m_Description, "NullRender: (debug renderer)", sizeof(pMode->m_Description));
			LTStrCpy(pMode->m_InternalName, "NullRender", sizeof(pMode->m_InternalName));

			pMode->m_Width = 640;
			pMode->m_Height = 480;
			pMode->m_BitDepth = 32;
			pMode->m_bHWTnL = true;
			pMode->m_pNext = LTNULL;

			return pMode;
		}
		else
		{
			return LTNULL;
		}
	}


	void FreeModeList(RMode* pModes)
	{
		//	free(pModes);
		RMode* pCur = pModes;
		while (pCur) {
			RMode* pNext = pCur->m_pNext;
			LTMemFree(pCur);
			pCur = pNext;
		}
	}

public:
	static NullRenderSys m_NulSys;
	static char* m_pcNulSysDesc;
};

// ---------------------------------------------------------------- //
// DLL export functions.
// ---------------------------------------------------------------- //

NullRenderSys NullRenderSys::m_NulSys;
char* NullRenderSys::m_pcNulSysDesc = "*** null render driver ***";

extern "C"
{
	LTMODULE_EXPORT char* RenderSysDesc();
	LTMODULE_EXPORT ILTRenderSys* RenderSysMake();
}

char* RenderSysDesc()
{
	return NullRenderSys::m_pcNulSysDesc;
}

ILTRenderSys* RenderSysMake()
{
	return &NullRenderSys::m_NulSys;
}

#ifdef _WIN32
bool WINAPI DllMain(HANDLE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	return true;
}
#endif
