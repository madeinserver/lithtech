#ifndef __WAVE_H__
#define __WAVE_H__

#ifndef __ILTSOUND_H__
#include "iltsound.h"
#endif

#ifdef USE_DIRECTMUSIC
// for adding DirectMusic header info
#ifndef __DMUSICI_H__
#define __DMUSICI_H__
#include <dmusici.h>
#endif

#ifndef __DMUSICF_H__
#define __DMUSICF_H__
#include <dmusicf.h>
#endif
#endif

//	===========================================================================
#ifdef USE_ABSTRACT_SOUND_INTERFACES
//	===========================================================================

#ifndef WAVE_FORMAT_IMA_ADPCM
#define WAVE_FORMAT_IMA_ADPCM	0x0011
#endif

#ifndef WAVE_FORMAT_PCM
#define WAVE_FORMAT_PCM			1
#endif

#ifndef WAVE_MAPPER
#define	WAVE_MAPPER				((uint32)-1)
#endif

#ifndef MAKEFOURCC
#define MAKEFOURCC(ch0, ch1, ch2, ch3)								\
		((uint32)(uint8)(ch0) | ((uint32)(uint8)(ch1) << 8) |		\
		((uint32)(uint8)(ch2) << 16) | ((uint32)(uint8)(ch3) << 24))
#endif

#ifndef mmioFOURCC
#define mmioFOURCC(w,x,y,z) MAKEFOURCC(w,x,y,z)
#endif

//	===========================================================================
#else
//	===========================================================================

//	===========================================================================
#endif
//	===========================================================================

class ILTStream;
class SSBufStream;

// Defines used with CLithSoundFormat::m_dwSoundBufferFlags
// Compressed sound files default to decompressing the file as it plays.  These files cannot
// be used for true 3d sounds.
#define	SOUNDBUFFERFLAG_STREAM				(1<<0)		// Buffer used for streaming sound
#define SOUNDBUFFERFLAG_DECOMPRESSONLOAD	(1<<1)		// Decompress the file when loaded.
#define SOUNDBUFFERFLAG_DECOMPRESSATSTART	(1<<2)		// Decompress the whole when first played.

#define WAVE_FORMAT_MPEGLAYER3	85

#define FOURCC uint32

// defs from dmusici.h

#ifndef DMUS_WAVEF_OFF
#define DMUS_WAVEF_OFF          0x01
#endif

#ifndef DMUS_WAVEF_STREAMING
#define DMUS_WAVEF_STREAMING    0x02
#endif

#ifndef DMUS_WAVEF_NOINVALIDATE
#define DMUS_WAVEF_NOINVALIDATE 0x04
#endif

#ifndef DMUS_WAVEF_NOPREROLL
#define DMUS_WAVEF_NOPREROLL    0x08
#endif

#ifndef DMUS_WAVEF_IGNORELOOPS
#define DMUS_WAVEF_IGNORELOOPS  0x20
#endif


struct WAVEHEADER_cuepoint
{
	uint32		m_dwName;
	uint32		m_dwPosition;
	FOURCC		m_fccChunk;
	uint32		m_dwChunkStart;
	uint32		m_dwBlockStart;
	uint32		m_dwSampleOffset;
};

struct WAVEHEADER_cue
{
	uint32					m_dwNumCuePoints;
	WAVEHEADER_cuepoint *	m_pCuePoints;
};

struct WAVEHEADER_ltxt
{
	uint32		m_dwName;
	uint32		m_dwSampleLength;
	uint32		m_dwPurpose;
	uint16		m_wCountry;
	uint16		m_wLanguage;
	uint16		m_wDialect;
	uint16		m_wCodePage;
};

struct WAVEHEADER_lith
{
	uint32 m_dwSoundBufferFlags;
	float m_fPitchMod;
};

typedef LONGLONG REFERENCE_TIME_lith;

struct DMUS_IO_WAVE_HEADER_lith {
	REFERENCE_TIME_lith  rtReadAhead;
	DWORD     dwFlags;
};

struct WAVEHEADER_dmus
{
	LTBOOL		m_bStream;
	DMUS_IO_WAVE_HEADER_lith m_dmusWavHeader;
};

struct CCuePoint
{
	LTBOOL		m_bValid;
	uint32		m_dwName;
	uint32		m_dwPosition;
	uint32		m_dwLength;
};

struct CWaveHeader
{
	LTWAVEFORMATEX				m_WaveFormat;
	uint32						m_dwDataPos;
	uint32						m_dwDataSize;
	uint32						m_dwSamples;
	WAVEHEADER_lith				m_lith;
	WAVEHEADER_dmus				m_dmus;
	CCuePoint					m_CuePoint;
};


LTBOOL GetWaveInfo( ILTStream &inStream, CWaveHeader &waveHeader );
LTBOOL WriteWave( SSBufStream &inStream, ILTStream &outStream, CWaveHeader &waveHeader );


#endif // __WAVE_H__
