
#ifndef __PIXELFORMAT_T_H__
#define __PIXELFORMAT_T_H__

    #ifndef __LTPVALUE_H__
	#include "ltpvalue.h"
    #endif

	#include "ltpixelformat.h"


	// 0-8 inclusive.
	#define NUM_SCALE_TABLES	9


	// ConvertRequest flags.
		// If this is set, the contents of the source are converted to the dest's bit
		// format and OR'd with the destination.
		#define CR_LOGICAL_OR	(1<<0)


	class FormatMgr;


	// This is what is used to represent a color value in a particular format.
	union GenericColor
	{
		uint32	dwVal;
		uint16	wVal;
		uint8	bVal;
	};
				  


	char* GetBPPString(BPPIdent ident);



	// A palette color.
	struct RPaletteColor
	{
		union
		{
			struct 
			{
				unsigned char	a, r, g, b;
			} rgb;
			
			uint32 dword;
		};
	};


	// Helper for debugging..
	template<class T, uint32 size>
	class SafeArray
	{
	public:

		T&	operator[](uint32 index)
		{
			return Get(index);
		}

		T&	Get(uint32 index)
		{
			ASSERT(index < size);
			return m_Array[index];
		}

		T*	GetArray() {return m_Array;}

	private:

		T	m_Array[size];		
	};
	

	typedef SafeArray<uint8, 256> ScaleFrom8Table;

	// Passed to FormatMgr::ConvertPixels.
	#define ConvertRequest FMConvertRequest
	class FMConvertRequest
	{
	public:
		
					FMConvertRequest();
		
		LTBOOL		IsValid() const;
		

	// The caller MUST fill all these in.
	// m_pSrcFormat and m_pDestFormat are set in the constructor and you can use
	// the defaults if you want or change them.
	// These values remain UNCHANGED on output.
	public:

		PFormat			*m_pSrcFormat;
		uint8			*m_pSrc;
		long			m_SrcPitch;
		// This must be set if the source format is 8-bit.
		RPaletteColor	*m_pSrcPalette;

		PFormat		*m_pDestFormat;
		uint8		*m_pDest;
		long		m_DestPitch;
		
		uint32		m_Width;
		uint32		m_Height;
		uint32		m_Flags; // Combination of CR_ flags.

	// The converter fills these in itself.
	public:

		PFormat		m_DefaultSrcFormat;
		PFormat		m_DefaultDestFormat;
	};


	// Passed to FormatMgr::DrawRect.
	class FMRectRequest
	{
	public:

					FMRectRequest();

		LTBOOL		IsValid();


	// You must set these befure calling DrawRect.
	// m_pDestFormat will be set to m_pDefaultDestFormat automatically so you 
	// can use that if you want.
	public:

		PFormat		*m_pDestFormat;
		uint8		*m_pDest;
		long		m_DestPitch;

		// This rectangle does NOT include the right and bottom pixels.
		// So if you wanted a 1 pixel rect it should be:
		// left=0
		// top=0
		// right=1
		// bottom=1
		LTRect		m_Rect;
		PValue		m_Color; // Fill color.


	public:

		PFormat		m_DefaultFormat;
	};


	class FormatMgr
	{
	public:
					FormatMgr();
		
		
		// Convert a block of pixels between color formats.
		// flags is a combination of the CONVERT_ flags.
		LTRESULT	ConvertPixels(const FMConvertRequest *pRequest);
		
		// Fill in a rectangle.
		LTRESULT	FillRect(FMRectRequest *pRequest);

		// Gets the value in the PFormat's format.
		// (ie: out would equal red in pFormat's format if the input PValue was red).
		LTRESULT	PValueToFormatColor(PFormat *pFormat, PValue in, GenericColor &out);
		LTRESULT	PValueFromFormatColor(PFormat *pFormat, GenericColor in, PValue &out);


	protected:

		void		InitScaleTables();


	public:

		// The internal format used for 32-bit pixel conversion.
		PFormat		m_32BitFormat;

		// Used for S3TC formats.
		PFormat		m_RGB565Format;
		
		// Tables to convert from X bits to 8 bits and back (scales the ranges uniformly).
		SafeArray<ScaleFrom8Table, NUM_SCALE_TABLES>	m_ScaleFrom8;
		uint8		*m_ScaleTo8[NUM_SCALE_TABLES];

		uint8		m_0to8[(1<<0)];
		uint8		m_1to8[(1<<1)];
		uint8		m_2to8[(1<<2)];
		uint8		m_3to8[(1<<3)];
		uint8		m_4to8[(1<<4)];
		uint8		m_5to8[(1<<5)];
		uint8		m_6to8[(1<<6)];
		uint8		m_7to8[(1<<7)];
		uint8		m_8to8[(1<<8)];
	};


	// Calculates the size of an image in the specified format.
	uint32 CalcImageSize(BPPIdent bpp, uint32 width, uint32 height);
	
	// Returns a string representing the BPPIdent.
	char* GetBPPString(BPPIdent ident);

	// Returns the size of each block in the texture (either 8 or 16, depending on if 
	// which DXT format it is).
	uint32 GetBlockSize(BPPIdent ident);
	
	// Color block is always 8 bytes.
	inline uint32 GetColorBlockSize(BPPIdent bpp) {return 8;}
	inline uint32 GetAlphaBlockSize(BPPIdent bpp) {return 8;}
	

#endif





