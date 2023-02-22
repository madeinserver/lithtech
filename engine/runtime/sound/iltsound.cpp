//	===========================================================================

#include "iltsound.h"
#include "ltsysnode.h"
#include "string.h"

// ============================================================================

#ifdef USE_DX8_SOFTWARE_FILTERS

// filter support
void LTFILTERCHORUS::SetParam( const char* pszParam, float fValue )
{
	if ( !strcmp( pszParam, "Delay" ) )
	{
		fDelay = fValue;				
		uiFilterParamFlags |= SET_CHORUS_DELAY;
	}
	else if ( !strcmp( pszParam, "Depth" ) )
	{
		fDepth = fValue;				
		uiFilterParamFlags |= SET_CHORUS_DEPTH;
	}
	else if ( !strcmp( pszParam, "Feedback" ) )
	{
		fFeedback = fValue;				
		uiFilterParamFlags |= SET_CHORUS_FEEDBACK;
	}
	else if ( !strcmp( pszParam, "Frequency" )	)
	{
		fFrequency = fValue;				
		uiFilterParamFlags |= SET_CHORUS_FREQUENCY;
	}
	else if ( !strcmp( pszParam, "WetDryMix" ) )
	{
		fWetDryMix = fValue;				
		uiFilterParamFlags |= SET_CHORUS_WETDRYMIX;
	}
	else if ( !strcmp( pszParam, "Phase" ) )
	{
		lPhase = (int) fValue;				
		uiFilterParamFlags |= SET_CHORUS_PHASE;
	}
	else if ( !strcmp( pszParam, "Waveform" ) )
	{
		lWaveform = (int) fValue;				
		uiFilterParamFlags |= SET_CHORUS_WAVEFORM;
	}
}

void LTFILTERCOMPRESSOR::SetParam( const char* pszParam, float fValue )
{
	if ( !strcmp( pszParam, "Attack" ) )
	{
		fAttack = fValue;
		uiFilterParamFlags |= SET_COMPRESSOR_ATTACK;
	}
	else if ( !strcmp( pszParam, "Gain" ) )
	{
		fGain = fValue;
		uiFilterParamFlags |= SET_COMPRESSOR_GAIN;
	}
	else if ( !strcmp( pszParam, "Predelay" ) )
	{
		fPredelay = fValue;
		uiFilterParamFlags |= SET_COMPRESSOR_PREDELAY;
	}
	else if ( !strcmp( pszParam, "Ratio" ) )
	{
		fRatio = fValue;
		uiFilterParamFlags |= SET_COMPRESSOR_RATIO;
	}
	else if ( !strcmp( pszParam, "Release" ) )
	{
		fRelease = fValue;
		uiFilterParamFlags |= SET_COMPRESSOR_RELEASE;
	}
	else if ( !strcmp( pszParam, "Threshold" ) )
	{
		fThreshold = fValue;
		uiFilterParamFlags |= SET_COMPRESSOR_THRESHOLD;
	}
}

void LTFILTERDISTORTION::SetParam( const char* pszParam, float fValue )
{
	if ( !strcmp( pszParam, "Edge" ) )
	{
   		fEdge = fValue;
	   	uiFilterParamFlags |= SET_DISTORTION_EDGE;
	}
    else if ( !strcmp( pszParam, "Gain" ) )
    {
    	fGain = fValue;
    	uiFilterParamFlags |= SET_DISTORTION_GAIN;
    }
    else if ( !strcmp( pszParam, "PostEQBandwidth" ) )
    {
   		fPostEQBandwidth = fValue;
		uiFilterParamFlags |= SET_DISTORTION_POSTEQBANDWIDTH;
	}
	else if ( !strcmp( pszParam, "PostEQCenterFreq" ) )
	{
   		fPostEQCenterFrequency = fValue;
   		uiFilterParamFlags |= SET_DISTORTION_POSTEQCENTERFREQ;
	}
	else if ( !strcmp( pszParam, "PreLowpassCutoff" ) )
	{
   		fPreLowpassCutoff = fValue;
	   	uiFilterParamFlags |= SET_DISTORTION_PRELOWPASSCUTOFF;
    }
}

void LTFILTERECHO::SetParam( const char* pszParam, float fValue )
{
	if ( !strcmp( pszParam, "Feedback" ) )
	{
		fFeedback = fValue;
		uiFilterParamFlags |= SET_ECHO_FEEDBACK;
	}
	else if ( !strcmp( pszParam, "LeftDelay" ) )
	{
		fLeftDelay = fValue;
		uiFilterParamFlags |= SET_ECHO_LEFTDELAY;
	}
	else if ( !strcmp( pszParam, "RightDelay" ) )
	{
		fRightDelay = fValue;
		uiFilterParamFlags |= SET_ECHO_RIGHTDELAY;
	}
	else if ( !strcmp( pszParam, "PanDelay" ) )
	{
		lPanDelay = (int) fValue;
		uiFilterParamFlags |= SET_ECHO_PANDELAY;
	}
}

void LTFILTERFLANGE::SetParam( const char* pszParam, float fValue )
{
	if ( !strcmp( pszParam, "Delay" ) )
	{
		fDelay = fValue;
		uiFilterParamFlags |= SET_FLANGE_DELAY;
	}
	else if ( !strcmp( pszParam, "Depth" ) )
	{
		fDepth = fValue;
		uiFilterParamFlags |= SET_FLANGE_DEPTH;
	}
	else if ( !strcmp( pszParam, "Feedback" ) )
	{
		fFeedback = fValue;
		uiFilterParamFlags |= SET_FLANGE_FEEDBACK;
	}
	else if ( !strcmp( pszParam, "Frequency" ) )
	{
		fFrequency = fValue;
		uiFilterParamFlags |= SET_FLANGE_FREQUENCY;
	}
	else if ( !strcmp( pszParam, "WetDryMix" ) )
	{
		fWetDryMix = fValue;
		uiFilterParamFlags |= SET_FLANGE_WETDRYMIX;
	}
	else if ( !strcmp( pszParam, "Phase" ) )
	{
		lPhase = (int) fValue;
		uiFilterParamFlags |= SET_FLANGE_PHASE;
	}
	else if ( !strcmp( pszParam, "Waveform" ) )
	{
		lWaveform = (int) fValue;
		uiFilterParamFlags |= SET_FLANGE_WAVEFORM;
	}
}

void LTFILTERPARAMEQ::SetParam( const char* pszParam, float fValue )
{
	if ( !strcmp( pszParam, "Bandwidth" ) )
	{
		fBandwidth = fValue;
		uiFilterParamFlags |= SET_PARAMEQ_BANDWIDTH;
	}
	else if ( !strcmp( pszParam, "Center" ) )
	{
		fCenter = fValue;
		uiFilterParamFlags |= SET_PARAMEQ_CENTER;
	}
	else if ( !strcmp( pszParam, "Gain" ) )
	{
		fGain = fValue;
		uiFilterParamFlags |= SET_PARAMEQ_GAIN;
	}
}

void LTFILTERREVERB::SetParam( const char* pszParam, float fValue )
{
	if ( !strcmp( pszParam, "DecayHFRatio" ) )
	{
		fDecayHFRatio = fValue;
		uiFilterParamFlags |= SET_REVERB_DECAYHFRATIO;
	}
	else if ( !strcmp( pszParam, "DecayTime" ) )
	{
		fDecayTime = fValue;
		uiFilterParamFlags |= SET_REVERB_DECAYTIME;
	}
	else if ( !strcmp( pszParam, "Density" ) )
	{
		fDensity = fValue;
		uiFilterParamFlags |= SET_REVERB_DENSITY;
	}
	else if ( !strcmp( pszParam, "Diffusion" ) )
	{
		fDiffusion = fValue;
		uiFilterParamFlags |= SET_REVERB_DIFFUSION;
	}
	else if ( !strcmp( pszParam, "HFReference" ) )
	{
		fHFReference = fValue;
		uiFilterParamFlags |= SET_REVERB_HFREFERENCE;
	}
	else if ( !strcmp( pszParam, "ReflectionsDelay" ) )
	{
		fReflectionsDelay = fValue;
		uiFilterParamFlags |= SET_REVERB_REFLECTIONSDELAY;
	}
	else if ( !strcmp( pszParam, "ReverbDelay" ) )
	{
		fReverbDelay = fValue;
		uiFilterParamFlags |= SET_REVERB_REVERBDELAY;
	}
	else if ( !strcmp( pszParam, "RoomRolloffFactor" ) )
	{
		fRoomRolloffFactor = fValue;
		uiFilterParamFlags |= SET_REVERB_ROOMROLLOFFFACTOR;
	}
	else if ( !strcmp( pszParam, "Reflections" ) )
	{
		lReflections = (int) fValue;
		uiFilterParamFlags |= SET_REVERB_REFLECTIONS;
	}
	else if ( !strcmp( pszParam, "Reverb" ) )
	{
		lReverb = (int) fValue;
		uiFilterParamFlags |= SET_REVERB_REVERB;
	}
	else if ( !strcmp( pszParam, "Room" ) )
	{
		lRoom = (int) fValue;
		uiFilterParamFlags |= SET_REVERB_ROOM;
	}
	else if ( !strcmp( pszParam, "RoomHF" ) )
	{
		lRoomHF = (int) fValue;
		uiFilterParamFlags |= SET_REVERB_ROOMHF;
	}
}

#endif

#ifdef USE_EAX20_HARDWARE_FILTERS

void LTFILTERREVERB::SetParam( const char* pszParam, float fValue )
{
	if ( !strcmp( pszParam, "DecayHFRatio" ) )
	{
		fDecayHFRatio = fValue;
		uiFilterParamFlags |= SET_REVERB_DECAYHFRATIO;
	}
	else if ( !strcmp( pszParam, "DecayTime" ) )
	{
		fDecayTime = fValue;
		uiFilterParamFlags |= SET_REVERB_DECAYTIME;
	}
	else if ( !strcmp( pszParam, "Size" ) )
	{
		fSize = fValue;
		uiFilterParamFlags |= SET_REVERB_SIZE;
	}
	else if ( !strcmp( pszParam, "Diffusion" ) )
	{
		fDiffusion = fValue;
		uiFilterParamFlags |= SET_REVERB_DIFFUSION;
	}
	else if ( !strcmp( pszParam, "AirAbsorptionHF" ) )
	{
		fAirAbsorptionHF = fValue;
		uiFilterParamFlags |= SET_REVERB_AIRABSORPTIONHF;
	}
	else if ( !strcmp( pszParam, "ReflectionsDelay" ) )
	{
		fReflectionsDelay = fValue;
		uiFilterParamFlags |= SET_REVERB_REFLECTIONSDELAY;
	}
	else if ( !strcmp( pszParam, "ReverbDelay" ) )
	{
		fReverbDelay = fValue;
		uiFilterParamFlags |= SET_REVERB_REVERBDELAY;
	}
	else if ( !strcmp( pszParam, "RoomRolloffFactor" ) )
	{
		fRoomRolloffFactor = fValue;
		uiFilterParamFlags |= SET_REVERB_ROOMROLLOFFFACTOR;
	}
	else if ( !strcmp( pszParam, "Reflections" ) )
	{
		lReflections = (int) fValue;
		uiFilterParamFlags |= SET_REVERB_REFLECTIONS;
	}
	else if ( !strcmp( pszParam, "Reverb" ) )
	{
		lReverb = (int) fValue;
		uiFilterParamFlags |= SET_REVERB_REVERB;
	}
	else if ( !strcmp( pszParam, "Room" ) )
	{
		lRoom = (int) fValue;
		uiFilterParamFlags |= SET_REVERB_ROOM;
	}
	else if ( !strcmp( pszParam, "RoomHF" ) )
	{
		lRoomHF = (int) fValue;
		uiFilterParamFlags |= SET_REVERB_ROOMHF;
	}
	else if ( !strcmp( pszParam, "Direct" ) )
	{
		lDirect = (int) fValue;
		uiFilterParamFlags |= SET_REVERB_DIRECT;
	}
	else if ( !strcmp( pszParam, "Environment" ) )
	{
		lEnvironment = (int) fValue;
		uiFilterParamFlags |= SET_REVERB_ENVIRONMENT;
	}
}

#endif
