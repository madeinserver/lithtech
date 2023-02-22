
#ifndef __LTPFORMAT_H__
#define __LTPFORMAT_H__

#include "ltpvalue.h"

inline bool IsFormatCompressed(BPPIdent eType)
{
	return (eType == BPP_S3TC_DXT1) || (eType == BPP_S3TC_DXT3) || (eType == BPP_S3TC_DXT5);
}


// Pixel format.
class PFormat
{
public:

	// Use these to set it up.  It will precalculate some data so it's best to 
	// initialize a PFormat and keep it around.
	// (virtual so renderers don't have to link it in..)  
	virtual void Init(BPPIdent bpp, uint32 aMask, uint32 rMask, uint32 gMask, uint32 bMask);

	// Initialize with the PValue format.  This format is BY FAR the fastest format to
	// convert to/from.
	void        InitPValueFormat();

	BPPIdent    GetType() const { return m_eType; }
	uint32		GetBitsPerPixel() const { return m_nBPP; }
	uint32		GetBytesPerPixel() const { return m_nBPP / 8; }
	bool	    IsCompressed() const { return IsFormatCompressed(m_eType); }

	bool	    IsSameFormat(PFormat* pOther) const;

	uint32		GetNumPixelBytes() const;


	// Info specified.
public:

	// Tells how many bits per pixel and if it's palettized.
	BPPIdent	m_eType;
	BPPIdent	m_nBPP;		// Bits per pixel.


	// Precalculated stuff.
public:

	uint32		m_Masks[NUM_COLORPLANES];
	uint32		m_nBits[NUM_COLORPLANES];		// Bit counts for each plane.
	uint32		m_FirstBits[NUM_COLORPLANES];	// Tells at which bit the color plane starts.
};

extern uint32 g_PixelBytes[NUM_BIT_TYPES];

#endif
