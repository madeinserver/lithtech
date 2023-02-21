#include "bdefs.h"
#include "ltrendermgr_impl.h"
#include "render.h"

//IClientFileMgr
#include "client_filemgr.h"
static IClientFileMgr *client_file_mgr;
define_holder(IClientFileMgr, client_file_mgr);

#include "ilteffectshadermgr.h"
static ILTEffectShaderMgr* ilt_effectshader_mgr;
define_holder(ILTEffectShaderMgr, ilt_effectshader_mgr);

#include "iltrendertargetmgr.h"
static ILTRenderTargetMgr* ilt_rendertarget_mgr;
define_holder(ILTRenderTargetMgr, ilt_rendertarget_mgr);


//instantiate our implementation class
define_interface(CLTRenderMgr, ILTRenderMgr);

void CLTRenderMgr::Init()
{

}

void CLTRenderMgr::Term()
{
	r_GetRenderStruct()->FreeDefaultData(DEFD_RENDER_TARGET);
}

LTRESULT CLTRenderMgr::AddEffectShader (const char *pFileName, 
								  int EffectShaderID, 
								  const uint32 *pVertexElements, 
								  uint32 VertexElementsSize, 
								  HEFFECTPOOL EffectPoolID)
{
	if (!pFileName)
	{
		RETURN_ERROR(1, CLTRenderMgr::AddEffectShader, LT_INVALIDPARAMS);
	}

	FileRef ref;
	ref.m_FileType = FILE_ANYFILE;
	ref.m_pFilename = pFileName;
	ILTStream *pStream = client_file_mgr->OpenFile(&ref);
	if (!pStream)
	{
		RETURN_ERROR(3, CLTRenderMgr::AddEffectShader, LT_NOTFOUND);
	}

	if(!ilt_effectshader_mgr->AddEffectShader(pStream, pFileName, EffectShaderID, pVertexElements, VertexElementsSize, EffectPoolID))
	{
		// Close the file.
		if (pStream != NULL)
		{
			pStream->Release();
			pStream = NULL;
		}

		return LT_ERROR;
	}
	

	// Close the file.
	if (pStream != NULL)
	{
		pStream->Release();
		pStream = NULL;
	}

	return LT_OK;
}

LTEffectShader* CLTRenderMgr::GetEffectShader(int EffectShaderID)
{
	return ilt_effectshader_mgr->GetEffectShader(EffectShaderID);
}

LTRESULT CLTRenderMgr::CreateEffectPool (HEFFECTPOOL EffectPoolID)
{
	bool bSuccess = ilt_effectshader_mgr->AddEffectPool(EffectPoolID);
	if(bSuccess)
	{
		return LT_OK;
	}

	return LT_ERROR;
}

LTRESULT CLTRenderMgr::CreateRenderTarget(uint32 nWidth, uint32 nHeight, ERenderTargetFormat eRenderTargetFormat, EStencilBufferFormat eStencilBufferFormat, HRENDERTARGET hRenderTarget)
{
	LTRESULT hr = ilt_rendertarget_mgr->AddRenderTarget(nWidth, nHeight, eRenderTargetFormat, eStencilBufferFormat, hRenderTarget);
	return hr;
}

LTRESULT CLTRenderMgr::InstallRenderTarget(HRENDERTARGET hRenderTarget)
{
	IRenderTarget* pRenderTarget = ilt_rendertarget_mgr->GetRenderTarget(hRenderTarget);
	if(pRenderTarget)
	{
		if(pRenderTarget->InstallOnDevice() == LT_OK)
		{
			ilt_rendertarget_mgr->SetCurrentRenderTargetHandle(hRenderTarget);
			return LT_OK;
		}
	}

	return LT_ERROR;
}

LTRESULT CLTRenderMgr::RemoveRenderTarget(HRENDERTARGET hRenderTarget)
{
	return ilt_rendertarget_mgr->RemoveRenderTarget(hRenderTarget);
}

LTRESULT CLTRenderMgr::StretchRectRenderTargetToBackBuffer(HRENDERTARGET hRenderTarget)
{

	IRenderTarget* pRenderTarget = ilt_rendertarget_mgr->GetRenderTarget(hRenderTarget);
	if(pRenderTarget)
	{
		HBACKBUFFER pBackBuffer = INVALID_BACK_BUFFER;
		if (!r_GetRenderStruct()->GetBackBuffer(&pBackBuffer))
			return LT_ERROR;

		LTRESULT hr = pRenderTarget->StretchRectToSurface(pBackBuffer); //g_Device.m_pDefaultRenderTarget

		r_GetRenderStruct()->ReleaseBackBuffer(pBackBuffer);

		return hr;
	}

	return LT_ERROR;
}

LTRESULT CLTRenderMgr::GetRenderTargetDims(HRENDERTARGET hRenderTarget, uint32& nWidth, uint32 nHeight)
{
	IRenderTarget* pRenderTarget = ilt_rendertarget_mgr->GetRenderTarget(hRenderTarget);
	if(pRenderTarget)
	{
		const RenderTargetParams params = pRenderTarget->GetRenderTargetParams();
		nWidth = params.Width;
		nHeight = params.Height;

		return LT_OK;
	}

	return LT_ERROR;
}

LTRESULT CLTRenderMgr::StoreDefaultRenderTarget()
{
	r_GetRenderStruct()->SaveDefaultData(DEFD_RENDER_TARGET);
	r_GetRenderStruct()->SaveDefaultData(DEFD_DEPTH_BUFFER);

	return LT_OK;
}

LTRESULT CLTRenderMgr::RestoreDefaultRenderTarget()
{
	if (!r_GetRenderStruct()->RestoreDefaultData(DEFD_RENDER_TARGET))
		return LT_ERROR;

	if (!r_GetRenderStruct()->RestoreDefaultData(DEFD_DEPTH_BUFFER))
		return LT_ERROR;

	ilt_rendertarget_mgr->SetCurrentRenderTargetHandle(INVALID_RENDER_TARGET);

	return LT_OK;
}


LTRESULT CLTRenderMgr::SnapshotCurrentFrame()
{
	return r_GetRenderStruct()->SnapshotCurrentFrame();
}

LTRESULT CLTRenderMgr::SaveCurrentFrameToPrevious()
{
	return r_GetRenderStruct()->SaveCurrentFrameToPrevious();
}

LTRESULT CLTRenderMgr::UploadCurrentFrameToEffect(LTEffectShader* pEffect, const char* szParam)
{
	return r_GetRenderStruct()->UploadCurrentFrameToEffect(pEffect, szParam);
}

LTRESULT CLTRenderMgr::UploadPreviousFrameToEffect(LTEffectShader* pEffect, const char* szParam)
{
	return r_GetRenderStruct()->UploadPreviousFrameToEffect(pEffect, szParam);
}
