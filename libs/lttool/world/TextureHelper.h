#pragma once

#include <atlstr.h>

int NumColorsWithAlpha(TextureData* pData, uint8* alpha);
bool FillTextureWithPcx(LoadedBitmap* pcx, TextureData* dtx);
BOOL SavePcxAsTexture(LoadedBitmap* pPcx, DStream* pStream, DWORD textureFlags);
BOOL SaveDtxAsTga(DStream* pDtxFile, CAbstractIO& outFile);
BOOL SaveDtxAs8Bit(DStream* pDtxFile, CAbstractIO& outFile, CString* pFilename, bool retainHeader = false);
