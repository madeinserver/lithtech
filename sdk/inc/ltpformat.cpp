#include "ltbasedefs.h"
#include "ltpformat.h"

uint32 g_PixelBytes[NUM_BIT_TYPES] = { 1, 1, 2, 4, 0, 0, 0, 1 };		//! added 1 at the end for BPP_32P -- jyl


// Figures out where the bits start and end.  left is the MSB, right is the LSB.
// (left will be a greater number than right).
static void GetMaskBounds(uint32 mask, uint32* pLeft, uint32* pRight)
{
	uint32 testMask, i;

	// Starting with 1, find out where the mask starts.
	*pRight = 0;
	testMask = 1;
	for (i = 0; i < 32; i++)
	{
		if (testMask & mask)
			break;

		testMask <<= 1;
		(*pRight)++;
	}

	// Now find where it ends.
	*pLeft = *pRight;
	for (i = 0; i < 32; i++)
	{
		if (!(testMask & mask))
			break;

		testMask <<= 1;
		(*pLeft)++;
	}
}

static void SetBitCountAndRightShift(PFormat* pFormat, uint32 iPlane)
{
	uint32 left, right;

	GetMaskBounds(pFormat->m_Masks[iPlane], &left, &right);
	pFormat->m_nBits[iPlane] = left - right;
	pFormat->m_FirstBits[iPlane] = right;
}

void PFormat::Init(BPPIdent Type, uint32 aMask, uint32 rMask, uint32 gMask, uint32 bMask)
{

	m_eType = Type;
	m_nBPP = (BPPIdent)(g_PixelBytes[m_eType] * 8);
	m_Masks[CP_ALPHA] = aMask;
	m_Masks[CP_RED] = rMask;
	m_Masks[CP_GREEN] = gMask;
	m_Masks[CP_BLUE] = bMask;

	for (uint32 i = 0; i < NUM_COLORPLANES; i++)
	{
		SetBitCountAndRightShift(this, i);
	}
}


void PFormat::InitPValueFormat()
{
	Init(BPP_32, PVALUE_ALPHAMASK, PVALUE_REDMASK, PVALUE_GREENMASK, PVALUE_BLUEMASK);
}

bool PFormat::IsSameFormat(PFormat* pOther) const
{
	return
		m_eType == pOther->m_eType &&
		m_nBPP == pOther->m_nBPP &&
		m_Masks[0] == pOther->m_Masks[0] &&
		m_Masks[1] == pOther->m_Masks[1] &&
		m_Masks[2] == pOther->m_Masks[2] &&
		m_Masks[3] == pOther->m_Masks[3];
}

uint32 PFormat::GetNumPixelBytes() const
{
	return g_PixelBytes[m_nBPP];
}
