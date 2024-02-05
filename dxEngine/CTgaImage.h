// See comment at end for file info
#ifndef _CTGAIMAGE
#define _CTGAIMAGE

#include "standard.h"

class CTgaHeader
{
public:

	BYTE idLength;        // 00h  Size of Image ID field 

	BYTE colorMapType;    // 01h  Color map type 

	BYTE imageType;       // 02h  Image type code 

	WORD cMapStart;       // 03h  Color map origin 
	WORD cMapLength;      // 05h  Color map length 
	BYTE cMapDepth;       // 07h  Depth of color map entries 

	WORD xOffset;         // 08h  X origin of image 
	WORD yOffset;         // 0Ah  Y origin of image 

	WORD width;           // 0Ch  Width of image 
	WORD height;          // 0Eh  Height of image 

	BYTE pixelDepth;      // 10h  Image pixel size 

	// bit 0-3 contain the number of attribute bits per pixel; bits are found only for 16 and 32 bit
	// bit 4 left or right
	// bit 5 top or bottom
	// bit 6-7 are unused
	BYTE imageDescriptor;

	CTgaHeader()
	{
		memset(this, 0x00, sizeof(CTgaHeader));
	}
};

class CTgaFooter
{
public:

	DWORD extensionOffset;	// Extension Area Offset 
	DWORD developerOffset;	// Developer Directory Offset 

	CHAR signature[18];		// TGA Signature 

	CTgaFooter()
	{
		memset(this, 0x00, sizeof(CTgaFooter));
	}

	VOID ReadValues(FILE* f)
	{
		fread_s(&extensionOffset, sizeof(DWORD), sizeof(DWORD), 1, f);
		fread_s(&developerOffset, sizeof(DWORD), sizeof(DWORD), 1, f);
		fread_s(&signature, sizeof(CHAR) * 18, sizeof(CHAR), 18, f);
	}
};

class CTgaTag
{
public:

	WORD tagNumber;	// ID Number of the tag 

	DWORD offset;	// Offset location of the tag data 

	DWORD size;		// Size of the tag data in bytes 

	CTgaTag()
	{
		memset(this, 0x00, sizeof(CTgaTag));
	}
};

class CTgaExtension
{
public:

	WORD Size;                   // Extension Size 

	CHAR AuthorName[41];         // Author Name 
	CHAR AuthorComment[324];     // Author Comment 

	WORD StampMonth;             // Date/Time Stamp: Month 
	WORD StampDay;               // Date/Time Stamp: Day 
	WORD StampYear;              // Date/Time Stamp: Year 
	WORD StampHour;              // Date/Time Stamp: Hour 
	WORD StampMinute;            // Date/Time Stamp: Minute 
	WORD StampSecond;            // Date/Time Stamp: Second 

	CHAR JobName[41];            // Job Name/ID 
	WORD JobHour;                // Job Time: Hours 
	WORD JobMinute;              // Job Time: Minutes 
	WORD JobSecond;              // Job Time: Seconds 

	CHAR SoftwareId[41];         // Software ID 

	WORD VersionNumber;          // Software Version Number 
	BYTE VersionLetter;          // Software Version Letter 

	DWORD KeyColor;              // Key Color 

	WORD PixelNumerator;         // Pixel Aspect Ratio 
	WORD PixelDenominator;       // Pixel Aspect Ratio 

	WORD GammaNumerator;         // Gamma Value 
	WORD GammaDenominator;       // Gamma Value 

	DWORD ColorOffset;           // Color Correction Offset 
	DWORD StampOffset;           // Postage Stamp Offset 
	DWORD ScanOffset;            // Scan-Line Table Offset 

	BYTE AttributesType;         // Attributes Types 

	CTgaExtension()
	{
		memset(this, 0x00, sizeof(CTgaExtension));
	}
};

class CTgaColorCorrectionTable
{
public:

	SHORT A;

	SHORT R;
	SHORT G;
	SHORT B;

	CTgaColorCorrectionTable()
	{
		memset(this, 0x00, sizeof(CTgaColorCorrectionTable));
	}
};

class BGRA
{
public:

	BYTE B;
	BYTE G;
	BYTE R;

	BYTE A;

	friend bool operator == (const BGRA& p1, const BGRA& p2)
	{
		return ((p1.B == p2.B) && (p1.G == p2.G) && (p1.R == p2.R) && (p1.A == p2.A));
	}

	friend bool operator != (const BGRA& p1, const BGRA& p2)
	{
		return !(p1 == p2);
	}

	BGRA()
	{
		memset(this, 0x00, sizeof(BGRA));
	}
};

class RGBA
{
public:

	BYTE R;
	BYTE G;
	BYTE B;

	BYTE A;

	friend bool operator == (const RGBA& p1, const RGBA& p2)
	{
		return ((p1.A == p2.A) && (p1.R == p2.R) && (p1.G == p2.G) && (p1.B == p2.B));
	}

	friend bool operator != (const RGBA& p1, const RGBA& p2)
	{
		return !(p1 == p2);
	}

	RGBA()
	{
		memset(this, 0x00, sizeof(RGBA));
	}
};

class BGR
{
public:

	BYTE B;
	BYTE G;
	BYTE R;

	friend bool operator == (const BGR& p1, const BGR& p2)
	{
		return ((p1.B == p2.B) && (p1.G == p2.G) && (p1.R == p2.R));
	}

	friend bool operator != (const BGR& p1, const BGR& p2)
	{
		return !(p1 == p2);
	}

	BGR()
	{
		memset(this, 0x00, sizeof(BGR));
	}
};

#undef RGB

class RGB
{
public:

	BYTE R;
	BYTE G;
	BYTE B;

	friend bool operator == (const RGB& p1, const RGB& p2)
	{
		return ((p1.R == p2.R) && (p1.G == p2.G) && (p1.B == p2.B));
	}

	friend bool operator != (const RGB& p1, const RGB& p2)
	{
		return !(p1 == p2);
	}

	RGB()
	{
		memset(this, 0x00, sizeof(RGB));
	}
};

//
//compression packet
//
//byte 1
//bit 7			1 for compressed byte(s)
//bit 6 - 0 	count 0 - 127 and add 1
//
//8 bit
//byte 2		value 0 - 255
//
//32 bit
//byte 2,3,4,5	value 0 - 255

class RLEPacket
{
public:

	BYTE count;

	RLEPacket()
	{
		memset(this, 0x00, sizeof(RLEPacket));
	}

	VOID ReadCount(FILE* f)
	{
		fread_s(&count, sizeof(BYTE), sizeof(BYTE), 1, f);
	}

	BOOL IsEncoded()
	{
		if (count & 128)
		{
			return TRUE;
		}

		return FALSE;
	}

	BYTE GetCount()
	{
		// remove the RLE bit
		BYTE c = count << 1;

		c = c >> 1;

		// add 1 for RLE packets
		c += 1;

		return c;
	}
};

class RLEPacket8 : public RLEPacket
{
public:

	BYTE value;

	RLEPacket8()
	{
		memset(this, 0x00, sizeof(RLEPacket8));
	}

	VOID ReadValue(FILE* f)
	{
		fread_s(&value, sizeof(BYTE), sizeof(BYTE), 1, f);
	}
};

class RLEPacket24 : public RLEPacket
{
public:

	BGR value;

	RLEPacket24()
	{
		memset(this, 0x00, sizeof(RLEPacket24));
	}

	VOID ReadValue(FILE* f)
	{
		fread_s(&value, sizeof(BGR), sizeof(BGR), 1, f);
	}
};

class RLEPacket32 : public RLEPacket
{
public:

	BGRA value;

	RLEPacket32()
	{
		memset(this, 0x00, sizeof(RLEPacket32));
	}

	VOID ReadValue(FILE* f)
	{
		fread_s(&value, sizeof(BGRA), sizeof(BGRA), 1, f);
	}
};

class CTgaImage
{
public:

	CTgaHeader* header;

	CTgaFooter* footer;

	CTgaExtension* extension;

	BGR colorTable[256];

	BYTE imageDescription[256];

	INT size8;
	INT size24;
	INT size32;

	BYTE* pixels8;
	BYTE* pixels24;
	BYTE* pixels32;

	BOOL isInitialized;

	CTgaImage();

	~CTgaImage();

	CTgaImage(const CHAR* f);

	BOOL Load();

	VOID Flip();

	VOID DumpHeader();

	VOID DumpFooter();

	VOID DumpColorMap();

	VOID DumpRawPixels8();
	VOID DumpRawPixels24();
	VOID DumpRawPixels32();

private:

	static const INT MAX_TEXT = 1024;

	FILE* file;

	SIZE_T err;

	CHAR text[MAX_TEXT];

	VOID LoadHeader();

	VOID LoadImageDescription();

	VOID LoadColorTable();

	VOID LoadPixelData();

	VOID Load8BitUncompressed();
	VOID Load24BitUncompressed();
	VOID Load32BitUncompressed();

	VOID Load8BitCompressed();
	VOID Load24BitCompressed();
	VOID Load32BitCompressed();

	VOID LoadExtensions();
};
#endif


/*
www.gamers.org/dEngine/quake3/TGA.txt

TGA specs, from the 2D graphics format web collection.
This was annotated with a remark that there are a few
inaccuracies in this ASCII version.          - b.

-----------------------------------------------------------------------
This file has been created to satisfy numerous requests for information
on Targa image file formats.  The information has been taken from
Appendix C of the Truevision Technical Guide.  Requests for further
information could be directed to:

		   AT&T
		   Electronic Photography and Imaging Center
		   2002 Wellesley Ave.
		   Indianapolis, IN 42619

This document does not pretend to be complete, but it does pretend to
be accurate.  If you discover any finger checks or erroneous information
please let me know, ( David McDuffee, 75530,2626), and I will upload the
corrections.  Thanks.

The lack of completeness is due to the fact that the Targa recognizes
over half a dozen image file formats, some of which are more widely
used than others.  I have chosen to re-key the details on only those
formats which I actually use.  Again, if you want to know more about
formats not coveR here, you could contact your Truevision representative.

All Targa formats are identified by a Data Type field, which is a one
byte binary integer located in byte three of the file.  The various
file types specified by this field are as follows:

	   0  -  No image data included.
	   1  -  Uncompressed, color-mapped images.
	   2  -  Uncompressed, RGB images.
	   3  -  Uncompressed, black and white images.
	   9  -  Runlength encoded color-mapped images.
	  10  -  Runlength encoded RGB images.
	  11  -  Compressed, black and white images.
	  32  -  Compressed color-mapped data, using Huffman, Delta, and
					runlength encoding.
	  33  -  Compressed color-mapped data, using Huffman, Delta, and
					runlength encoding.  4-pass quadtree-type process.

This document will describe only four formats: 1, 2, 9, and 10.




--------------------------------------------------------------------------------
DATA TYPE 1:  Color-mapped images.                                             |
_______________________________________________________________________________|
| Offset | Length |                     Description                            |
|--------|--------|------------------------------------------------------------|
|--------|--------|------------------------------------------------------------|
|    0   |     1  |  Number of Characters in Identification Field.             |
|        |        |                                                            |
|        |        |  This field is a one-byte unsigned integer, specifying     |
|        |        |  the length of the Image Identification Field.  Its range  |
|        |        |  is 0 to 255.  A value of 0 means that no Image            |
|        |        |  Identification Field is included.                         |
|        |        |                                                            |
|--------|--------|------------------------------------------------------------|
|    1   |     1  |  Color Map Type.                                           |
|        |        |                                                            |
|        |        |  This field contains a binary 1 for Data Type 1 images.    |
|        |        |                                                            |
|--------|--------|------------------------------------------------------------|
|    2   |     1  |  Image Type Code.                                          |
|        |        |                                                            |
|        |        |  This field will always contain a binary 1.                |
|        |        |  ( That's what makes it Data Type 1 ).                     |
|        |        |                                                            |
|--------|--------|------------------------------------------------------------|
|    3   |     5  |  Color Map Specification.                                  |
|        |        |                                                            |
|    3   |     2  |  Color Map Origin.                                         |
|        |        |  Integer ( lo-hi ) index of first color map entry.         |
|        |        |                                                            |
|    5   |     2  |  Color Map Length.                                         |
|        |        |  Integer ( lo-hi ) count of color map entries.             |
|        |        |                                                            |
|    7   |     1  |  Color Map Entry Size.                                     |
|        |        |  Number of bits in each color map entry.  16 for           |
|        |        |  the Targa 16, 24 for the Targa 24, 32 for the Targa 32.   |
|        |        |                                                            |
|--------|--------|------------------------------------------------------------|
|    8   |    10  |  Image Specification.                                      |
|        |        |                                                            |
|    8   |     2  |  X Origin of Image.                                        |
|        |        |  Integer ( lo-hi ) X coordinate of the lower left corner   |
|        |        |  of the image.                                             |
|        |        |                                                            |
|   10   |     2  |  Y Origin of Image.                                        |
|        |        |  Integer ( lo-hi ) Y coordinate of the lower left corner   |
|        |        |  of the image.                                             |
|        |        |                                                            |
|   12   |     2  |  Width of Image.                                           |
|        |        |  Integer ( lo-hi ) width of the image in pixels.           |
|        |        |                                                            |
|   14   |     2  |  Height of Image.                                          |
|        |        |  Integer ( lo-hi ) height of the image in pixels.          |
|        |        |                                                            |
|   16   |     1  |  Image Pixel Size.                                         |
|        |        |  Number of bits in a stoR pixel index.                   |
|        |        |                                                            |
|   17   |     1  |  Image Descriptor Byte.                                    |
|        |        |  Bits 3-0 - number of attribute bits associated with each  |
|        |        |             pixel.                                         |
|        |        |  Bit 4    - reserved.  Must be set to 0.                   |
|        |        |  Bit 5    - screen origin bit.                             |
|        |        |             0 = Origin in lower left-hand corner.          |
|        |        |             1 = Origin in upper left-hand corner.          |
|        |        |             Must be 0 for Truevision images.               |
|        |        |  Bits 7-6 - Data storage interleaving flag.                |
|        |        |             00 = non-interleaved.                          |
|        |        |             01 = two-way (even/odd) interleaving.          |
|        |        |             10 = four way interleaving.                    |
|        |        |             11 = reserved.                                 |
|        |        |  This entire byte should be set to 0.  Don't ask me.       |
|        |        |                                                            |
|--------|--------|------------------------------------------------------------|
|   18   | varies |  Image Identification Field.                               |
|        |        |  Contains a free-form identification field of the length   |
|        |        |  specified in byte 1 of the image record.  It's usually    |
|        |        |  omitted ( length in byte 1 = 0 ), but can be up to 255    |
|        |        |  characters.  If more identification information is        |
|        |        |  requiR, it can be stoR after the image data.          |
|        |        |                                                            |
|--------|--------|------------------------------------------------------------|
| varies | varies |  Color map data.                                           |
|        |        |                                                            |
|        |        |  The offset is determined by the size of the Image         |
|        |        |  Identification Field.  The length is determined by        |
|        |        |  the Color Map Specification, which describes the          |
|        |        |  size of each entry and the number of entries.             |
|        |        |  Each color map entry is 2, 3, or 4 bytes.                 |
|        |        |  Unused bits are assumed to specify attribute bits.        |
|        |        |                                                            |
|        |        |  The 4 byte entry contains 1 byte for B, 1 byte         |
|        |        |  for G, 1 byte for R, and 1 byte of attribute        |
|        |        |  information, in that order.
|        |        |                                                            |
|        |        |  The 3 byte entry contains 1 byte each of B, G,     |
|        |        |  and R.                                                  |
|        |        |                                                            |
|        |        |  The 2 byte entry is broken down as follows:               |
|        |        |  ARRRRRGG GGGBBBBB, where each letter represents a bit.    |
|        |        |  But, because of the lo-hi storage order, the first byte   |
|        |        |  coming from the file will actually be GGGBBBBB, and the   |
|        |        |  second will be ARRRRRGG. "A" represents an attribute bit. |
|        |        |                                                            |
|--------|--------|------------------------------------------------------------|
| varies | varies |  Image Data Field.                                         |
|        |        |                                                            |
|        |        |  This field specifies (width) x (height) color map         |
|        |        |  indices.  Each index is stoR as an integral number      |
|        |        |  of bytes (typically 1 or 2).   All fields are unsigned.   |
|        |        |  The low-order byte of a two-byte field is stoR first.   |
|        |        |                                                            |
--------------------------------------------------------------------------------






--------------------------------------------------------------------------------
DATA TYPE 2:  Unmapped RGB images.                                             |
_______________________________________________________________________________|
| Offset | Length |                     Description                            |
|--------|--------|------------------------------------------------------------|
|--------|--------|------------------------------------------------------------|
|    0   |     1  |  Number of Characters in Identification Field.             |
|        |        |                                                            |
|        |        |  This field is a one-byte unsigned integer, specifying     |
|        |        |  the length of the Image Identification Field.  Its value  |
|        |        |  is 0 to 255.  A value of 0 means that no Image            |
|        |        |  Identification Field is included.                         |
|        |        |                                                            |
|--------|--------|------------------------------------------------------------|
|    1   |     1  |  Color Map Type.                                           |
|        |        |                                                            |
|        |        |  This field contains either 0 or 1.  0 means no color map  |
|        |        |  is included.  1 means a color map is included, but since  |
|        |        |  this is an unmapped image it is usually ignoR.  TIPS    |
|        |        |  ( a Targa paint system ) will set the border color        |
|        |        |  the first map color if it is present.                     |
|        |        |                                                            |
|--------|--------|------------------------------------------------------------|
|    2   |     1  |  Image Type Code.                                          |
|        |        |                                                            |
|        |        |  This field will always contain a binary 2.                |
|        |        |  ( That's what makes it Data Type 2 ).                     |
|        |        |                                                            |
|--------|--------|------------------------------------------------------------|
|    3   |     5  |  Color Map Specification.                                  |
|        |        |                                                            |
|        |        |  IgnoR if Color Map Type is 0; otherwise, interpreted    |
|        |        |  as follows:                                               |
|        |        |                                                            |
|    3   |     2  |  Color Map Origin.                                         |
|        |        |  Integer ( lo-hi ) index of first color map entry.         |
|        |        |                                                            |
|    5   |     2  |  Color Map Length.                                         |
|        |        |  Integer ( lo-hi ) count of color map entries.             |
|        |        |                                                            |
|    7   |     1  |  Color Map Entry Size.                                     |
|        |        |  Number of bits in color map entry.  16 for the Targa 16,  |
|        |        |  24 for the Targa 24, 32 for the Targa 32.                 |
|        |        |                                                            |
|--------|--------|------------------------------------------------------------|
|    8   |    10  |  Image Specification.                                      |
|        |        |                                                            |
|    8   |     2  |  X Origin of Image.                                        |
|        |        |  Integer ( lo-hi ) X coordinate of the lower left corner   |
|        |        |  of the image.                                             |
|        |        |                                                            |
|   10   |     2  |  Y Origin of Image.                                        |
|        |        |  Integer ( lo-hi ) Y coordinate of the lower left corner   |
|        |        |  of the image.                                             |
|        |        |                                                            |
|   12   |     2  |  Width of Image.                                           |
|        |        |  Integer ( lo-hi ) width of the image in pixels.           |
|        |        |                                                            |
|   14   |     2  |  Height of Image.                                          |
|        |        |  Integer ( lo-hi ) height of the image in pixels.          |
|        |        |                                                            |
|   16   |     1  |  Image Pixel Size.                                         |
|        |        |  Number of bits in a pixel.  This is 16 for Targa 16,      |
|        |        |  24 for Targa 24, and .... well, you get the idea.         |
|        |        |                                                            |
|   17   |     1  |  Image Descriptor Byte.                                    |
|        |        |  Bits 3-0 - number of attribute bits associated with each  |
|        |        |             pixel.  For the Targa 16, this would be 0 or   |
|        |        |             1.  For the Targa 24, it should be 0.  For     |
|        |        |             Targa 32, it should be 8.                      |
|        |        |  Bit 4    - reserved.  Must be set to 0.                   |
|        |        |  Bit 5    - screen origin bit.                             |
|        |        |             0 = Origin in lower left-hand corner.          |
|        |        |             1 = Origin in upper left-hand corner.          |
|        |        |             Must be 0 for Truevision images.               |
|        |        |  Bits 7-6 - Data storage interleaving flag.                |
|        |        |             00 = non-interleaved.                          |
|        |        |             01 = two-way (even/odd) interleaving.          |
|        |        |             10 = four way interleaving.                    |
|        |        |             11 = reserved.                                 |
|        |        |                                                            |
|--------|--------|------------------------------------------------------------|
|   18   | varies |  Image Identification Field.                               |
|        |        |  Contains a free-form identification field of the length   |
|        |        |  specified in byte 1 of the image record.  It's usually    |
|        |        |  omitted ( length in byte 1 = 0 ), but can be up to 255    |
|        |        |  characters.  If more identification information is        |
|        |        |  requiR, it can be stoR after the image data.          |
|        |        |                                                            |
|--------|--------|------------------------------------------------------------|
| varies | varies |  Color map data.                                           |
|        |        |                                                            |
|        |        |  If the Color Map Type is 0, this field doesn't exist.     |
|        |        |  Otherwise, just read past it to get to the image.         |
|        |        |  The Color Map Specification describes the size of each    |
|        |        |  entry, and the number of entries you'll have to skip.     |
|        |        |  Each color map entry is 2, 3, or 4 bytes.                 |
|        |        |                                                            |
|--------|--------|------------------------------------------------------------|
| varies | varies |  Image Data Field.                                         |
|        |        |                                                            |
|        |        |  This field specifies (width) x (height) pixels.  Each     |
|        |        |  pixel specifies an RGB color value, which is stoR as    |
|        |        |  an integral number of bytes.                              |
|        |        |                                                            |
|        |        |  The 2 byte entry is broken down as follows:               |
|        |        |  ARRRRRGG GGGBBBBB, where each letter represents a bit.    |
|        |        |  But, because of the lo-hi storage order, the first byte   |
|        |        |  coming from the file will actually be GGGBBBBB, and the   |
|        |        |  second will be ARRRRRGG. "A" represents an attribute bit. |
|        |        |                                                            |
|        |        |  The 3 byte entry contains 1 byte each of B, G,     |
|        |        |  and R.                                                  |
|        |        |                                                            |
|        |        |  The 4 byte entry contains 1 byte each of B, G,     |
|        |        |  R, and attribute.  For faster speed (because of the     |
|        |        |  hardware of the Targa board itself), Targa 24 images are  |
|        |        |  sometimes stoR as Targa 32 images.                      |
|        |        |                                                            |
--------------------------------------------------------------------------------





--------------------------------------------------------------------------------
DATA TYPE 9:  Run Length Encoded, color-mapped images.                         |
_______________________________________________________________________________|
| Offset | Length |                     Description                            |
|--------|--------|------------------------------------------------------------|
|--------|--------|------------------------------------------------------------|
|    0   |     1  |  Number of Characters in Identification Field.             |
|        |        |                                                            |
|        |        |  This field is a one-byte unsigned integer, specifying     |
|        |        |  the length of the Image Identification Field.  Its value  |
|        |        |  is 0 to 255.  A value of 0 means that no Image            |
|        |        |  Identification Field is included.                         |
|        |        |                                                            |
|--------|--------|------------------------------------------------------------|
|    1   |     1  |  Color Map Type.                                           |
|        |        |                                                            |
|        |        |  This field is always 1 for color-mapped images.           |
|        |        |                                                            |
|--------|--------|------------------------------------------------------------|
|    2   |     1  |  Image Type Code.                                          |
|        |        |                                                            |
|        |        |  A binary 9 for this data type.                            |
|        |        |                                                            |
|--------|--------|------------------------------------------------------------|
|    3   |     5  |  Color Map Specification.                                  |
|        |        |                                                            |
|    3   |     2  |  Color Map Origin.                                         |
|        |        |  Integer ( lo-hi ) index of first color map entry.         |
|        |        |                                                            |
|    5   |     2  |  Color Map Length.                                         |
|        |        |  Integer ( lo-hi ) count of color map entries.             |
|        |        |                                                            |
|    7   |     1  |  Color Map Entry Size.                                     |
|        |        |  Number of bits in each color map entry.  16 for the       |
|        |        |  Targa 16, 24 for the Targa 24, 32 for the Targa 32.       |
|        |        |                                                            |
|--------|--------|------------------------------------------------------------|
|    8   |    10  |  Image Specification.                                      |
|        |        |                                                            |
|    8   |     2  |  X Origin of Image.                                        |
|        |        |  Integer ( lo-hi ) X coordinate of the lower left corner   |
|        |        |  of the image.                                             |
|        |        |                                                            |
|   10   |     2  |  Y Origin of Image.                                        |
|        |        |  Integer ( lo-hi ) Y coordinate of the lower left corner   |
|        |        |  of the image.                                             |
|        |        |                                                            |
|   12   |     2  |  Width of Image.                                           |
|        |        |  Integer ( lo-hi ) width of the image in pixels.           |
|        |        |                                                            |
|   14   |     2  |  Height of Image.                                          |
|        |        |  Integer ( lo-hi ) height of the image in pixels.          |
|        |        |                                                            |
|   16   |     1  |  Image Pixel Size.                                         |
|        |        |  Number of bits in a pixel.  This is 16 for Targa 16,      |
|        |        |  24 for Targa 24, and .... well, you get the idea.         |
|        |        |                                                            |
|   17   |     1  |  Image Descriptor Byte.                                    |
|        |        |  Bits 3-0 - number of attribute bits associated with each  |
|        |        |             pixel.  For the Targa 16, this would be 0 or   |
|        |        |             1.  For the Targa 24, it should be 0.  For the |
|        |        |             Targa 32, it should be 8.                      |
|        |        |  Bit 4    - reserved.  Must be set to 0.                   |
|        |        |  Bit 5    - screen origin bit.                             |
|        |        |             0 = Origin in lower left-hand corner.          |
|        |        |             1 = Origin in upper left-hand corner.          |
|        |        |             Must be 0 for Truevision images.               |
|        |        |  Bits 7-6 - Data storage interleaving flag.                |
|        |        |             00 = non-interleaved.                          |
|        |        |             01 = two-way (even/odd) interleaving.          |
|        |        |             10 = four way interleaving.                    |
|        |        |             11 = reserved.                                 |
|        |        |                                                            |
|--------|--------|------------------------------------------------------------|
|   18   | varies |  Image Identification Field.                               |
|        |        |  Contains a free-form identification field of the length   |
|        |        |  specified in byte 1 of the image record.  It's usually    |
|        |        |  omitted ( length in byte 1 = 0 ), but can be up to 255    |
|        |        |  characters.  If more identification information is        |
|        |        |  requiR, it can be stoR after the image data.          |
|        |        |                                                            |
|--------|--------|------------------------------------------------------------|
| varies | varies |  Color map data.                                           |
|        |        |                                                            |
|        |        |  The offset is determined by the size of the Image         |
|        |        |  Identification Field.  The length is determined by        |
|        |        |  the Color Map Specification, which describes the          |
|        |        |  size of each entry and the number of entries.             |
|        |        |  Each color map entry is 2, 3, or 4 bytes.                 |
|        |        |  Unused bits are assumed to specify attribute bits.        |
|        |        |                                                            |
|        |        |  The 4 byte entry contains 1 byte for B, 1 byte         |
|        |        |  for G, 1 byte for R, and 1 byte of attribute        |
|        |        |  information, in that order.
|        |        |                                                            |
|        |        |  The 3 byte entry contains 1 byte each of B, G,     |
|        |        |  and R.                                                  |
|        |        |                                                            |
|        |        |  The 2 byte entry is broken down as follows:               |
|        |        |  ARRRRRGG GGGBBBBB, where each letter represents a bit.    |
|        |        |  But, because of the lo-hi storage order, the first byte   |
|        |        |  coming from the file will actually be GGGBBBBB, and the   |
|        |        |  second will be ARRRRRGG. "A" represents an attribute bit. |
|        |        |                                                            |
|--------|--------|------------------------------------------------------------|
| varies | varies |  Image Data Field.                                         |
|        |        |                                                            |
|        |        |  This field specifies (width) x (height) color map         |
|        |        |  indices.  The indices are stoR in packets.  There       |
|        |        |  two types of packets:  Run-length packets, and Raw        |
|        |        |  packets.  Both types of packets consist of a 1-byte       |
|        |        |  header, identifying the type of packet and specifying a   |
|        |        |  count, followed by a variable-length body.                |
|        |        |  The high-order bit of the header is "1" for the           |
|        |        |  run length packet, and "0" for the raw packet.            |
|        |        |                                                            |
|        |        |  For the run-length packet, the header consists of:        |
|        |        |      __________________________________________________    |
|        |        |      | 1 bit |   7 bit repetition count minus 1.      |    |
|        |        |      |   ID  |   Since the maximum value of this      |    |
|        |        |      |       |   field is 127, the largest possible   |    |
|        |        |      |       |   run size would be 128.               |    |
|        |        |      |-------|----------------------------------------|    |
|        |        |      |   1   |  C     C     C     C     C     C    C  |    |
|        |        |      --------------------------------------------------    |
|        |        |                                                            |
|        |        |  For the raw packet, the header consists of:               |
|        |        |      __________________________________________________    |
|        |        |      | 1 bit |   7 bit number of pixels minus 1.      |    |
|        |        |      |   ID  |   Since the maximum value of this      |    |
|        |        |      |       |   field is 127, there can never be     |    |
|        |        |      |       |   more than 128 pixels per packet.     |    |
|        |        |      |-------|----------------------------------------|    |
|        |        |      |   0   |  N     N     N     N     N     N    N  |    |
|        |        |      --------------------------------------------------    |
|        |        |                                                            |
|        |        |  For the run length packet, the header is followed by      |
|        |        |  a single color index, which is assumed to be repeated     |
|        |        |  the number of times specified in the header.  The RLE     |
|        |        |  packet may cross scan lines ( begin on one line and end   |
|        |        |  on the next ).                                            |
|        |        |                                                            |
|        |        |  For the raw packet, the header is followed by the number  |
|        |        |  of color indices specified in the header.  The raw        |
|        |        |  packet may cross scan lines ( begin on one line and end   |
|        |        |  on the next ).                                            |
|        |        |                                                            |
--------------------------------------------------------------------------------





--------------------------------------------------------------------------------
DATA TYPE 10:  Run Length Encoded, RGB images.                                 |
_______________________________________________________________________________|
| Offset | Length |                     Description                            |
|--------|--------|------------------------------------------------------------|
|--------|--------|------------------------------------------------------------|
|    0   |     1  |  Number of Characters in Identification Field.             |
|        |        |                                                            |
|        |        |  This field is a one-byte unsigned integer, specifying     |
|        |        |  the length of the Image Identification Field.  Its range  |
|        |        |  is 0 to 255.  A value of 0 means that no Image            |
|        |        |  Identification Field is included.                         |
|        |        |                                                            |
|--------|--------|------------------------------------------------------------|
|    1   |     1  |  Color Map Type.                                           |
|        |        |                                                            |
|        |        |  This field contains either 0 or 1.  0 means no color map  |
|        |        |  is included.  1 means a color map is included, but since  |
|        |        |  this is an unmapped image it is usually ignoR.  TIPS    |
|        |        |  ( a Targa paint system ) will set the border color        |
|        |        |  the first map color if it is present.  Wowie zowie.       |
|        |        |                                                            |
|--------|--------|------------------------------------------------------------|
|    2   |     1  |  Image Type Code.                                          |
|        |        |                                                            |
|        |        |  Binary 10 for this type of image.                         |
|        |        |                                                            |
|--------|--------|------------------------------------------------------------|
|    3   |     5  |  Color Map Specification.                                  |
|        |        |                                                            |
|        |        |  IgnoR if Color Map Type is 0; otherwise, interpreted    |
|        |        |  as follows:                                               |
|        |        |                                                            |
|    3   |     2  |  Color Map Origin.                                         |
|        |        |  Integer ( lo-hi ) index of first color map entry.         |
|        |        |                                                            |
|    5   |     2  |  Color Map Length.                                         |
|        |        |  Integer ( lo-hi ) count of color map entries.             |
|        |        |                                                            |
|    7   |     1  |  Color Map Entry Size.                                     |
|        |        |  Number of bits in color map entry.  This value is 16 for  |
|        |        |  the Targa 16, 24 for the Targa 24, 32 for the Targa 32.   |
|        |        |                                                            |
|--------|--------|------------------------------------------------------------|
|    8   |    10  |  Image Specification.                                      |
|        |        |                                                            |
|    8   |     2  |  X Origin of Image.                                        |
|        |        |  Integer ( lo-hi ) X coordinate of the lower left corner   |
|        |        |  of the image.                                             |
|        |        |                                                            |
|   10   |     2  |  Y Origin of Image.                                        |
|        |        |  Integer ( lo-hi ) Y coordinate of the lower left corner   |
|        |        |  of the image.                                             |
|        |        |                                                            |
|   12   |     2  |  Width of Image.                                           |
|        |        |  Integer ( lo-hi ) width of the image in pixels.           |
|        |        |                                                            |
|   14   |     2  |  Height of Image.                                          |
|        |        |  Integer ( lo-hi ) height of the image in pixels.          |
|        |        |                                                            |
|   16   |     1  |  Image Pixel Size.                                         |
|        |        |  Number of bits in a pixel.  This is 16 for Targa 16,      |
|        |        |  24 for Targa 24, and .... well, you get the idea.         |
|        |        |                                                            |
|   17   |     1  |  Image Descriptor Byte.                                    |
|        |        |  Bits 3-0 - number of attribute bits associated with each  |
|        |        |             pixel.  For the Targa 16, this would be 0 or   |
|        |        |             1.  For the Targa 24, it should be 0.  For the |
|        |        |             Targa 32, it should be 8.                      |
|        |        |  Bit 4    - reserved.  Must be set to 0.                   |
|        |        |  Bit 5    - screen origin bit.                             |
|        |        |             0 = Origin in lower left-hand corner.          |
|        |        |             1 = Origin in upper left-hand corner.          |
|        |        |             Must be 0 for Truevision images.               |
|        |        |  Bits 7-6 - Data storage interleaving flag.                |
|        |        |             00 = non-interleaved.                          |
|        |        |             01 = two-way (even/odd) interleaving.          |
|        |        |             10 = four way interleaving.                    |
|        |        |             11 = reserved.                                 |
|        |        |                                                            |
|--------|--------|------------------------------------------------------------|
|   18   | varies |  Image Identification Field.                               |
|        |        |  Contains a free-form identification field of the length   |
|        |        |  specified in byte 1 of the image record.  It's usually    |
|        |        |  omitted ( length in byte 1 = 0 ), but can be up to 255    |
|        |        |  characters.  If more identification information is        |
|        |        |  requiR, it can be stoR after the image data.          |
|        |        |                                                            |
|--------|--------|------------------------------------------------------------|
| varies | varies |  Color map data.                                           |
|        |        |                                                            |
|        |        |  If the Color Map Type is 0, this field doesn't exist.     |
|        |        |  Otherwise, just read past it to get to the image.         |
|        |        |  The Color Map Specification, describes the size of each   |
|        |        |  entry, and the number of entries you'll have to skip.     |
|        |        |  Each color map entry is 2, 3, or 4 bytes.                 |
|        |        |                                                            |
|--------|--------|------------------------------------------------------------|
| varies | varies |  Image Data Field.                                         |
|        |        |                                                            |
|        |        |  This field specifies (width) x (height) pixels.  The      |
|        |        |  RGB color information for the pixels is stoR in         |
|        |        |  packets.  There are two types of packets:  Run-length     |
|        |        |  encoded packets, and raw packets.  Both have a 1-byte     |
|        |        |  header, identifying the type of packet and specifying a   |
|        |        |  count, followed by a variable-length body.                |
|        |        |  The high-order bit of the header is "1" for the           |
|        |        |  run length packet, and "0" for the raw packet.            |
|        |        |                                                            |
|        |        |  For the run-length packet, the header consists of:        |
|        |        |      __________________________________________________    |
|        |        |      | 1 bit |   7 bit repetition count minus 1.      |    |
|        |        |      |   ID  |   Since the maximum value of this      |    |
|        |        |      |       |   field is 127, the largest possible   |    |
|        |        |      |       |   run size would be 128.               |    |
|        |        |      |-------|----------------------------------------|    |
|        |        |      |   1   |  C     C     C     C     C     C    C  |    |
|        |        |      --------------------------------------------------    |
|        |        |                                                            |
|        |        |  For the raw packet, the header consists of:               |
|        |        |      __________________________________________________    |
|        |        |      | 1 bit |   7 bit number of pixels minus 1.      |    |
|        |        |      |   ID  |   Since the maximum value of this      |    |
|        |        |      |       |   field is 127, there can never be     |    |
|        |        |      |       |   more than 128 pixels per packet.     |    |
|        |        |      |-------|----------------------------------------|    |
|        |        |      |   0   |  N     N     N     N     N     N    N  |    |
|        |        |      --------------------------------------------------    |
|        |        |                                                            |
|        |        |                                                            |
|        |        |  For the run length packet, the header is followed by      |
|        |        |  a single color value, which is assumed to be repeated     |
|        |        |  the number of times specified in the header.  The         |
|        |        |  packet may cross scan lines ( begin on one line and end   |
|        |        |  on the next ).                                            |
|        |        |                                                            |
|        |        |  For the raw packet, the header is followed by             |
|        |        |  the number of color values specified in the header.       |
|        |        |                                                            |
|        |        |  The color entries themselves are two bytes, three bytes,  |
|        |        |  or four bytes ( for Targa 16, 24, and 32 ), and are       |
|        |        |  broken down as follows:                                   |
|        |        |                                                            |
|        |        |  The 2 byte entry -                                        |
|        |        |  ARRRRRGG GGGBBBBB, where each letter represents a bit.    |
|        |        |  But, because of the lo-hi storage order, the first byte   |
|        |        |  coming from the file will actually be GGGBBBBB, and the   |
|        |        |  second will be ARRRRRGG. "A" represents an attribute bit. |
|        |        |                                                            |
|        |        |  The 3 byte entry contains 1 byte each of B, G,     |
|        |        |  and R.                                                  |
|        |        |                                                            |
|        |        |  The 4 byte entry contains 1 byte each of B, G,     |
|        |        |  R, and attribute.  For faster speed (because of the     |
|        |        |  hardware of the Targa board itself), Targa 24 image are   |
|        |        |  sometimes stoR as Targa 32 images.                      |
|        |        |                                                            |
--------------------------------------------------------------------------------

*/