#include "stdafx.h"
#include "iltsound.h"

//! CNulSoundSys

class CNulSoundSys : public ILTSoundSys
{
public:
	CNulSoundSys( ) {}
	virtual ~CNulSoundSys( ) {}

public:
	virtual bool		Init( );
	virtual void		Term( );

public:
	virtual void*		GetDDInterface( uint uiDDInterfaceId );

public:
	// system wide functions
	virtual void		Lock( void );
	virtual void		Unlock( void );
	virtual int32			Startup( void );
	virtual void		Shutdown( void );
	virtual uint32			MsCount( void );
	virtual int32			SetPreference( uint32 uiNumber, int32 siValue );
	virtual int32			GetPreference( uint32 uiNumber );
	virtual void		MemFreeLock( void* ptr );
	virtual void*		MemAllocLock( uint32 uiSize );
	virtual char*		LastError( void );

	// digital sound driver functions
	virtual int32			WaveOutOpen( LHDIGDRIVER* phDriver, PHWAVEOUT* pphWaveOut, int32 siDeviceId, LWAVEFORMAT* pWaveFormat );
	virtual void		WaveOutClose( LHDIGDRIVER hDriver );
	virtual void		SetDigitalMasterVolume( LHDIGDRIVER hDig, int32 siMasterVolume );
	virtual int32			GetDigitalMasterVolume( LHDIGDRIVER hDig );
	virtual int32			DigitalHandleRelease( LHDIGDRIVER hDriver );
	virtual int32			DigitalHandleReacquire( LHDIGDRIVER hDriver );

#ifdef USE_EAX20_HARDWARE_FILTERS
	virtual bool		SetEAX20Filter(bool bEnable, LTSOUNDFILTERDATA* pFilterData);
	virtual bool		SupportsEAX20Filter();
	virtual bool		SetEAX20BufferSettings(LHSAMPLE hSample, LTSOUNDFILTERDATA* pFilterData);
#endif

	// 3d sound provider functions
	virtual void		Set3DProviderMinBuffers(uint32 uiMinBuffers);
	virtual int32		Open3DProvider(LHPROVIDER hLib);
	virtual void		Close3DProvider(LHPROVIDER hLib);
	virtual void		Set3DProviderPreference(LHPROVIDER hLib, char* sName, void* pVal);
	virtual void		Get3DProviderAttribute(LHPROVIDER hLib, char* sName, void* pVal);
	virtual int32		Enumerate3DProviders(LHPROENUM* phNext, LHPROVIDER* phDest, char** psName);

	// 3d listener functions
	virtual LH3DPOBJECT	Open3DListener( LHPROVIDER hLib );
	virtual void		Close3DListener( LH3DPOBJECT hListener );
	virtual void		SetListenerDoppler(LH3DPOBJECT hListener, float fDoppler);
	virtual void		CommitDeferred();

	// 3d sound object functions
	virtual void		Set3DPosition( LH3DPOBJECT hObj, float fX, float fY, float fZ);
	virtual void		Set3DVelocityVector( LH3DPOBJECT hObj, float fDX_per_ms, float fDY_per_ms, float fDZ_per_ms );
	virtual void		Set3DOrientation( LH3DPOBJECT hObj, float fX_face, float fY_face, float fZ_face, float fX_up, float fY_up, float fZ_up );
	virtual void		Set3DUserData( LH3DPOBJECT hObj, uint32 uiIndex, int32 siValue );
	virtual void		Get3DPosition( LH3DPOBJECT hObj, float* pfX, float* pfY, float* pfZ);
	virtual void		Get3DVelocity( LH3DPOBJECT hObj, float* pfDX_per_ms, float* pfDY_per_ms, float* pfDZ_per_ms );
	virtual void		Get3DOrientation( LH3DPOBJECT hObj, float* pfX_face, float* pfY_face, float* pfZ_face, float* pfX_up, float* pfY_up, float* pfZ_up );
	virtual int32			Get3DUserData( LH3DPOBJECT hObj, uint32 uiIndex);

	// 3d sound sample functions
	virtual LH3DSAMPLE Allocate3DSampleHandle(LHPROVIDER hLib);
	virtual void		Release3DSampleHandle(LH3DSAMPLE hS);
	virtual void		Stop3DSample(LH3DSAMPLE hS);
	virtual void		Start3DSample(LH3DSAMPLE hS);
	virtual void		Resume3DSample(LH3DSAMPLE hS);
	virtual void		End3DSample(LH3DSAMPLE hS);
	virtual int32		Init3DSampleFromAddress(LH3DSAMPLE hS, void* pStart, uint32 uiLen, LWAVEFORMATEX* pWaveFormat, int32 siPlaybackRate, LTSOUNDFILTERDATA* pFilterData);
	virtual int32		Init3DSampleFromFile(LH3DSAMPLE hS, void* pFile_image, int32 siBlock, int32 siPlaybackRate, LTSOUNDFILTERDATA* pFilterData);
	virtual int32		Get3DSampleVolume(LH3DSAMPLE hS);
	virtual void		Set3DSampleVolume(LH3DSAMPLE hS, int32 siVolume);
	virtual uint32		Get3DSampleStatus(LH3DSAMPLE hS);
	virtual void		Set3DSampleMsPosition(LHSAMPLE hS, int32 siMilliseconds);
	virtual int32		Set3DSampleInfo(LH3DSAMPLE hS, LTSOUNDINFO* pInfo);
	virtual void		Set3DSampleDistances(LH3DSAMPLE hS, float fMax_dist, float fMin_dist);
	virtual void		Set3DSamplePreference(LH3DSAMPLE hSample, char* sName, void* pVal);
	virtual void		Set3DSampleLoopBlock(LH3DSAMPLE hS, int32 siLoop_start_offset, int32 siLoop_end_offset, bool bEnable);
	virtual void		Set3DSampleLoop(LH3DSAMPLE hS, bool bLoop);
	virtual void		Set3DSampleObstruction(LH3DSAMPLE hS, float fObstruction);
	virtual float		Get3DSampleObstruction(LH3DSAMPLE hS);
	virtual void		Set3DSampleOcclusion(LH3DSAMPLE hS, float fOcclusion) ;
	virtual float		Get3DSampleOcclusion(LH3DSAMPLE hS);

	// 2d sound sample functions
	virtual LHSAMPLE	AllocateSampleHandle(LHDIGDRIVER hDig);
	virtual void		ReleaseSampleHandle(LHSAMPLE hS);
	virtual void		InitSample(LHSAMPLE hS);
	virtual void		StopSample(LHSAMPLE hS);
	virtual void		StartSample(LHSAMPLE hS);
	virtual void		ResumeSample(LHSAMPLE hS);
	virtual void		EndSample(LHSAMPLE hS);
	virtual void		SetSampleVolume(LHSAMPLE hS, int32 siVolume);
	virtual void		SetSamplePan(LHSAMPLE hS, int32 siPan);
	virtual int32		GetSampleVolume(LHSAMPLE hS);
	virtual int32		GetSamplePan(LHSAMPLE hS);
	virtual void		SetSampleUserData(LHSAMPLE hS, uint32 uiIndex, int32 siValue);
	virtual void		GetDirectSoundInfo(LHSAMPLE hS, PTDIRECTSOUND* ppDS, PTDIRECTSOUNDBUFFER* ppDSB);
	virtual void		SetSampleReverb(LHSAMPLE hS, float fReverb_level, float fReverb_reflect_time, float fReverb_decay_time);
	virtual int32		InitSampleFromAddress(LHSAMPLE hS, void* pStart, uint32 uiLen, LWAVEFORMATEX* pWaveFormat, int32 siPlaybackRate, LTSOUNDFILTERDATA* pFilterData);
	virtual int32		InitSampleFromFile(LHSAMPLE hS, void* pFile_image, int32 siBlock, int32 siPlaybackRate, LTSOUNDFILTERDATA* pFilterData);
	virtual void		SetSampleLoopBlock(LHSAMPLE hS, int32 siLoop_start_offset, int32 siLoop_end_offset, bool bEnable);
	virtual void		SetSampleLoop(LHSAMPLE hS, bool bLoop);
	virtual void		SetSampleMsPosition(LHSAMPLE hS, int32 siMilliseconds);
	virtual int32		GetSampleUserData(LHSAMPLE hS, uint32 uiIndex);
	virtual uint32		GetSampleStatus(LHSAMPLE hS);

	// old 2d sound stream functions
	virtual LHSTREAM	OpenStream( char* sFilename, uint32 nOffset, LHDIGDRIVER hDig, char* sStream, int32 siStream_mem );
	virtual void		SetStreamLoop(LHSTREAM hStream, bool bLoop);
	virtual void		SetStreamPlaybackRate( LHSTREAM hStream, int32 siRate );
	virtual void		SetStreamMsPosition( LHSTREAM hS, int32 siMilliseconds );
	virtual void		SetStreamUserData( LHSTREAM hS, uint32 uiIndex, int32 siValue);
	virtual int32			GetStreamUserData( LHSTREAM hS, uint32 uiIndex);

	// new 2d sound stream functions
	//virtual LHSTREAM	OpenStream( streamBufferParams_t* pStreamBufferParams );
	virtual void		CloseStream( LHSTREAM hStream );
	virtual void		StartStream( LHSTREAM hStream );
	virtual void		PauseStream( LHSTREAM hStream, int32 siOnOff );
	virtual void		ResetStream( LHSTREAM hStream );
	virtual void		SetStreamVolume( LHSTREAM hStream, int32 siVolume );
	virtual void		SetStreamPan( LHSTREAM hStream, int32 siPan );
	virtual int32		GetStreamVolume( LHSTREAM hStream );
	virtual int32		GetStreamPan( LHSTREAM hStream );
	virtual uint32		GetStreamStatus( LHSTREAM hStream );
	virtual int32		GetStreamBufferParam( LHSTREAM hStream, uint32 uiParam );
	virtual void		ClearStreamBuffer( LHSTREAM hStream, bool bClearStreamDataQueue = true);
	virtual bool		QueueStreamData( LHSTREAM, uint8* pucPCMSoundData, uint uiNumBytes );
	virtual	int32		GetStreamDataQueueSize( LHSTREAM hStream );
	virtual int32		GetStreamCount( );

	// wave file decompression functons
	virtual int32			DecompressADPCM( LTSOUNDINFO* pInfo, void** ppOutData, uint32* puiOutSize );
	virtual int32			DecompressASI( void* pInData, uint32 uiInSize, char* sFilename_ext, void** ppWav, uint32* puiWavSize, LTLENGTHYCB fnCallback );


	// Gets the ticks spent in sound thread.
	virtual uint32		GetThreadedSoundTicks();

	virtual bool		HasOnBoardMemory();

public:
	static CNulSoundSys m_NulSoundSys;
	static char*		m_pcNulSoundSysDesc;
};

//	===========================================================================
//	CNulSoundSys methods

bool CNulSoundSys::Init( )
{
	return true;
}

void CNulSoundSys::Term( )
{
}

void* CNulSoundSys::GetDDInterface( uint uiDDInterfaceId )
{
	return NULL;
}

// system wide functions
void CNulSoundSys::Lock( void ) 
{ 
}

void CNulSoundSys::Unlock( void ) 
{ 
}

int32	CNulSoundSys::Startup( void ) 
{ 
	return 0; 
}

void CNulSoundSys::Shutdown( void ) 
{ 
}

uint32	CNulSoundSys::MsCount( void ) 
{ 
	return 0; 
}

int32	CNulSoundSys::SetPreference( uint32 uiNumber, int32 siValue ) 
{ 
	return 0; 
}

int32	CNulSoundSys::GetPreference( uint32 uiNumber ) 
{ 
	return 0; 
}

void CNulSoundSys::MemFreeLock( void* ptr ) 
{ 
	LTMemFree( ptr );
}

void* CNulSoundSys::MemAllocLock( uint32 uiSize ) 
{ 
	void* p;
	LT_MEM_TRACK_ALLOC(p = LTMemAlloc( uiSize ),LT_MEM_TYPE_SOUND);
	return p;
}

char* CNulSoundSys::LastError( void ) 
{ 
	return "no error";
}

// digital sound driver functions
int32	CNulSoundSys::WaveOutOpen( LHDIGDRIVER* phDriver, PHWAVEOUT* pphWaveOut, int32 siDeviceId, LWAVEFORMAT* pWaveFormat ) 
{ 
	return 0; 
}

void CNulSoundSys::WaveOutClose( LHDIGDRIVER hDriver ) 
{ 
}

void CNulSoundSys::SetDigitalMasterVolume( LHDIGDRIVER hDig, int32 siMasterVolume ) 
{ 
}

int32	CNulSoundSys::GetDigitalMasterVolume( LHDIGDRIVER hDig ) 
{ 
	return 0; 
}

int32	CNulSoundSys::DigitalHandleRelease( LHDIGDRIVER hDriver ) 
{ 
	return 0; 
}

int32	CNulSoundSys::DigitalHandleReacquire( LHDIGDRIVER hDriver ) 
{ 
	return 0; 
}

// 3d sound provider functions
void CNulSoundSys::Set3DProviderMinBuffers(uint32 uiMinBuffers)
{

}

int32 CNulSoundSys::Open3DProvider( LHPROVIDER hLib ) 
{ 
	return 0; 
}

void CNulSoundSys::Close3DProvider( LHPROVIDER hLib ) 
{ 
}

void CNulSoundSys::Set3DProviderPreference( LHPROVIDER hLib, char* sName, void* pVal ) 
{ 
}

void CNulSoundSys::Get3DProviderAttribute( LHPROVIDER hLib, char* sName, void* pVal ) 
{ 
}

int32	CNulSoundSys::Enumerate3DProviders( LHPROENUM* phNext, LHPROVIDER* phDest, char** psName) 
{ 
	return 0; 
}

#ifdef USE_EAX20_HARDWARE_FILTERS
bool CNulSoundSys::SetEAX20Filter(bool bEnable, LTSOUNDFILTERDATA* pFilterData)
{
	return false;
}

bool CNulSoundSys::SupportsEAX20Filter()
{
	return false;
}

bool CNulSoundSys::SetEAX20BufferSettings(LHSAMPLE hSample, LTSOUNDFILTERDATA* pFilterData)
{
	return false;
}
#endif

// 3d listener functions
LH3DPOBJECT	CNulSoundSys::Open3DListener( LHPROVIDER hLib ) 
{ 
	return NULL;
}

void CNulSoundSys::SetListenerDoppler(LH3DPOBJECT hListener, float fDoppler)
{

}

void CNulSoundSys::CommitDeferred()
{

}

void CNulSoundSys::Close3DListener( LH3DPOBJECT hListener ) 
{ 
}

// 3d sound object functions
void CNulSoundSys::Set3DPosition( LH3DPOBJECT hObj, float fX, float fY, float fZ) 
{ 
}

void CNulSoundSys::Set3DVelocityVector( LH3DPOBJECT hObj, float fDX_per_ms, float fDY_per_ms, float fDZ_per_ms ) 
{ 
}

void CNulSoundSys::Set3DOrientation( LH3DPOBJECT hObj, float fX_face, float fY_face, float fZ_face, float fX_up, float fY_up, float fZ_up ) 
{ 
}

void CNulSoundSys::Set3DUserData( LH3DPOBJECT hObj, uint32 uiIndex, int32 siValue ) 
{ 
}

void CNulSoundSys::Get3DPosition( LH3DPOBJECT hObj, float* pfX, float* pfY, float* pfZ) 
{ 
}

void CNulSoundSys::Get3DVelocity( LH3DPOBJECT hObj, float* pfDX_per_ms, float* pfDY_per_ms, float* pfDZ_per_ms ) 
{ 
}

void CNulSoundSys::Get3DOrientation( LH3DPOBJECT hObj, float* pfX_face, float* pfY_face, float* pfZ_face, float* pfX_up, float* pfY_up, float* pfZ_up ) 
{ 
}

int32	CNulSoundSys::Get3DUserData( LH3DPOBJECT hObj, uint32 uiIndex) 
{ 
	return 0; 
}

// 3d sound sample functions
LH3DSAMPLE CNulSoundSys::Allocate3DSampleHandle( LHPROVIDER hLib ) 
{ 
	return NULL;
}

void CNulSoundSys::Release3DSampleHandle( LH3DSAMPLE hS ) 
{ 
}

void CNulSoundSys::Stop3DSample( LH3DSAMPLE hS ) 
{ 
}

void CNulSoundSys::Start3DSample( LH3DSAMPLE hS ) 
{ 
}

void CNulSoundSys::Resume3DSample( LH3DSAMPLE hS ) 
{ 
}

void CNulSoundSys::End3DSample( LH3DSAMPLE hS ) 
{ 
}

int32 CNulSoundSys::Init3DSampleFromAddress(LH3DSAMPLE hS, void* pStart, uint32 uiLen, LWAVEFORMATEX* pWaveFormat, int32 siPlaybackRate, LTSOUNDFILTERDATA* pFilterData)
{
	return 0;
}

int32 CNulSoundSys::Init3DSampleFromFile(LH3DSAMPLE hS, void* pFile_image, int32 siBlock, int32 siPlaybackRate, LTSOUNDFILTERDATA* pFilterData)
{
	return 0;
}

int32 CNulSoundSys::Get3DSampleVolume(LH3DSAMPLE hS)
{
	return 0;
}

void CNulSoundSys::Set3DSampleVolume( LH3DSAMPLE hS, int32 siVolume ) 
{ 
}

void CNulSoundSys::Set3DSampleMsPosition(LHSAMPLE hS, int32 siMilliseconds)
{

}

uint32	CNulSoundSys::Get3DSampleStatus( LH3DSAMPLE hS ) 
{ 
	return 0; 
}


int32	CNulSoundSys::Set3DSampleInfo( LH3DSAMPLE hS, LTSOUNDINFO* pInfo ) 
{ 
	return 0; 
}

void CNulSoundSys::Set3DSampleDistances( LH3DSAMPLE hS, float fMax_dist, float fMin_dist ) 
{ 
}

void CNulSoundSys::Set3DSampleLoopBlock(LH3DSAMPLE hS, int32 siLoop_start_offset, int32 siLoop_end_offset, bool bEnable)
{

}

void CNulSoundSys::Set3DSampleLoop(LH3DSAMPLE hS, bool bLoop)
{

}

void CNulSoundSys::Set3DSamplePreference( LH3DSAMPLE hSample, char* sName, void* pVal ) 
{ 
}

void CNulSoundSys::Set3DSampleObstruction( LH3DSAMPLE hS, float fObstruction ) 
{ 
}

float CNulSoundSys::Get3DSampleObstruction( LH3DSAMPLE hS ) 
{ 
	return 0; 
}

void CNulSoundSys::Set3DSampleOcclusion( LH3DSAMPLE hS, float fOcclusion ) 
{ 
}

float CNulSoundSys::Get3DSampleOcclusion( LH3DSAMPLE hS ) 
{ 
	return 0; 
}

// 2d sound sample functions
LHSAMPLE CNulSoundSys::AllocateSampleHandle( LHDIGDRIVER hDig ) 
{ 
	return NULL;
}

void CNulSoundSys::ReleaseSampleHandle( LHSAMPLE hS ) 
{ 
}

void CNulSoundSys::InitSample( LHSAMPLE hS ) 
{ 
}

void CNulSoundSys::StopSample( LHSAMPLE hS ) 
{ 
}

void CNulSoundSys::StartSample( LHSAMPLE hS )
{
}

void CNulSoundSys::ResumeSample( LHSAMPLE hS ) 
{ 
}

void CNulSoundSys::EndSample( LHSAMPLE hS )
{
}

void CNulSoundSys::SetSampleVolume( LHSAMPLE hS, int32 siVolume ) 
{ 
}

void CNulSoundSys::SetSamplePan( LHSAMPLE hS, int32 siPan ) 
{ 
}

int32	CNulSoundSys::GetSampleVolume( LHSAMPLE hS ) 
{ 
	return 0; 
}

int32	CNulSoundSys::GetSamplePan( LHSAMPLE hS ) 
{ 
	return 0; 
}

void CNulSoundSys::SetSampleUserData( LHSAMPLE hS, uint32 uiIndex, int32 siValue ) 
{ 
}

uint32 CNulSoundSys::GetSampleStatus(LHSAMPLE hS)
{
	return 0;
}

void CNulSoundSys::GetDirectSoundInfo( LHSAMPLE hS, PTDIRECTSOUND* ppDS, PTDIRECTSOUNDBUFFER* ppDSB ) 
{ 
}

void CNulSoundSys::SetSampleReverb( LHSAMPLE hS, float fReverb_level, float fReverb_reflect_time, float fReverb_decay_time ) 
{ 
}

int32 CNulSoundSys::InitSampleFromAddress(LHSAMPLE hS, void* pStart, uint32 uiLen, LWAVEFORMATEX* pWaveFormat, int32 siPlaybackRate, LTSOUNDFILTERDATA* pFilterData)
{
	return 0;
}

int32 CNulSoundSys::InitSampleFromFile(LHSAMPLE hS, void* pFile_image, int32 siBlock, int32 siPlaybackRate, LTSOUNDFILTERDATA* pFilterData)
{
	return 0;
}

void CNulSoundSys::SetSampleLoopBlock(LHSAMPLE hS, int32 siLoop_start_offset, int32 siLoop_end_offset, bool bEnable)
{

}

void CNulSoundSys::SetSampleLoop(LHSAMPLE hS, bool bLoop)
{

}

void CNulSoundSys::SetSampleMsPosition( LHSAMPLE hS, int32 siMilliseconds ) 
{ 
}

int32	CNulSoundSys::GetSampleUserData( LHSAMPLE hS, uint32 uiIndex ) 
{ 
	return 0; 
}

// old 2d sound stream functions
LHSTREAM CNulSoundSys::OpenStream( char* sFilename, uint32 nOffset, LHDIGDRIVER hDig, char* sStream, int32 siStream_mem ) 
{ 
	return NULL;
}

void CNulSoundSys::SetStreamLoop( LHSTREAM hStream, bool bLoop ) 
{ 
}

void CNulSoundSys::SetStreamPlaybackRate( LHSTREAM hStream, int32 siRate ) 
{ 
}

void CNulSoundSys::SetStreamMsPosition( LHSTREAM hS, int32 siMilliseconds ) 
{ 
}

void CNulSoundSys::SetStreamUserData( LHSTREAM hS, uint32 uiIndex, int32 siValue) 
{ 
}

int32	CNulSoundSys::GetStreamUserData( LHSTREAM hS, uint32 uiIndex) 
{ 
	return 0; 
}

// new 2d sound stream functions
//LHSTREAM CNulSoundSys::OpenStream( streamBufferParams_t* pStreamBufferParams )
//{
//	return NULL;
//}

void CNulSoundSys::CloseStream( LHSTREAM hStream ) 
{ 
}

void CNulSoundSys::StartStream( LHSTREAM hStream ) 
{ 
}

void CNulSoundSys::PauseStream( LHSTREAM hStream, int32 siOnOff ) 
{ 
}

void CNulSoundSys::ResetStream( LHSTREAM hStream )
{
}

void CNulSoundSys::SetStreamVolume( LHSTREAM hStream, int32 siVolume ) 
{ 
}

void CNulSoundSys::SetStreamPan( LHSTREAM hStream, int32 siPan ) 
{ 
}

int32	CNulSoundSys::GetStreamVolume( LHSTREAM hStream ) 
{ 
	return 0; 
}

int32	CNulSoundSys::GetStreamPan( LHSTREAM hStream ) 
{ 
	return 0; 
}

uint32 CNulSoundSys::GetStreamStatus( LHSTREAM hStream )
{
	return 0;
}

int32 CNulSoundSys::GetStreamBufferParam( LHSTREAM hStream, uint32 uiParam )
{
	return 0;
}

void CNulSoundSys::ClearStreamBuffer( LHSTREAM hStream, bool bClearStreamDataQueue )
{
}

bool CNulSoundSys::QueueStreamData( LHSTREAM, uint8* pucPCMSoundData, uint uiNumBytes )
{
	return false;
}

int32 CNulSoundSys::GetStreamDataQueueSize( LHSTREAM hStream )
{
	return 0;
}

int32 CNulSoundSys::GetStreamCount( )
{
	return 0;
}

// wave file decompression functons
int32	CNulSoundSys::DecompressADPCM( LTSOUNDINFO* pInfo, void** ppOutData, uint32* puiOutSize ) 
{ 
	return 0; 
}

int32	CNulSoundSys::DecompressASI( void* pInData, uint32 uiInSize, char* sFilename_ext, void** ppWav, uint32* puiWavSize, LTLENGTHYCB fnCallback ) 
{ 
	return 0; 
}

uint32 CNulSoundSys::GetThreadedSoundTicks() { return 0; }

bool CNulSoundSys::HasOnBoardMemory() { return false; }

//	===========================================================================

CNulSoundSys CNulSoundSys::m_NulSoundSys;
char* CNulSoundSys::m_pcNulSoundSysDesc = "*** null sound driver ***";

extern "C"
{
	LTMODULE_EXPORT char*			SoundSysDesc( );
	LTMODULE_EXPORT ILTSoundSys*	SoundSysMake( );
}

char* SoundSysDesc( )
{
	return CNulSoundSys::m_pcNulSoundSysDesc;
}

ILTSoundSys* SoundSysMake( )
{
	return &CNulSoundSys::m_NulSoundSys;
}

#ifdef _WIN32
bool WINAPI DllMain( HANDLE hModule, DWORD ul_reason_for_call, LPVOID lpReserved )
{
    return true;
}
#endif
