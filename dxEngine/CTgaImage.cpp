#include "CTgaImage.h"

CTgaImage::CTgaImage()
{
	memset(this, 0x00, sizeof(CTgaImage));
}

CTgaImage::~CTgaImage()
{
	delete header;

	delete footer;

	delete extension;

	if (pixels8)
	{
		free(pixels8);
	}

	if (pixels24)
	{
		free(pixels24);
	}

	if (pixels32)
	{
		free(pixels32);
	}
}

CTgaImage::CTgaImage(const CHAR* f)
{
	memset(this, 0x00, sizeof(CTgaImage));

	SIZE_T err = fopen_s(&file, f, "rb");

	if (err != 0)
	{
		return;
	}

	header = new CTgaHeader();
	footer = new CTgaFooter();
	extension = new CTgaExtension();

	CTgaImage::Load();

	isInitialized = TRUE;

	if (file)
	{
		fclose(file);
	}
}

BOOL CTgaImage::Load()
{
	LoadHeader();

	LoadImageDescription();

	LoadColorTable();

	LoadPixelData();

	LoadExtensions();

	if (header->imageDescriptor & 8)
	{
		CTgaImage::Flip();
	}

	return TRUE;
}

VOID CTgaImage::Flip()
{
	SIZE_T pitch = (SIZE_T)header->width * 4;
	SIZE_T height = (SIZE_T)header->height;

	BYTE* flip = (BYTE*)malloc(height * pitch);
	BYTE* fliph = flip;

	BYTE* start = pixels32 + (height * pitch) - pitch;

	for (UINT i = 0; i < height; i++)
	{
		memcpy(fliph, start, pitch);

		start -= pitch;
		fliph += pitch;
	}

	memcpy(pixels32, flip, height * pitch);

	free(flip);
}

VOID CTgaImage::DumpHeader()
{
	FILE* out;

	SIZE_T err = fopen_s(&out, "header.txt", "w");

	memset(text, 0x00, MAX_TEXT);
	sprintf_s(text, MAX_TEXT, "%05d", header->width);

	fwrite(text, sizeof(CHAR), strlen(text), out);

	memset(text, 0x00, MAX_TEXT);
	sprintf_s(text, MAX_TEXT, "%05d", header->height);

	fwrite(text, sizeof(CHAR), strlen(text), out);

	if (out)
	{
		fclose(out);
	}
}

VOID CTgaImage::DumpFooter()
{
	FILE* out;

	SIZE_T err = fopen_s(&out, "footer.txt", "w");

	fwrite(footer->signature, sizeof(CHAR), strlen(footer->signature), out);

	if (out)
	{
		fclose(out);
	}
}

VOID CTgaImage::DumpColorMap()
{
	FILE* out;

	SIZE_T err = fopen_s(&out, "colorMap.txt", "wb");

	INT i = sizeof(BGR);

	fwrite(colorTable, i, header->cMapLength, out);

	if (out)
	{
		fclose(out);
	}
}

VOID CTgaImage::DumpRawPixels8()
{
	FILE* out;

	SIZE_T err = fopen_s(&out, "pixels8.txt", "wb");

	if (pixels8 > 0)
	{
		fwrite(pixels8, sizeof(BYTE), size8, out);
	}

	if (out)
	{
		fclose(out);
	}
}

VOID CTgaImage::DumpRawPixels24()
{
	FILE* out;

	SIZE_T err = fopen_s(&out, "pixels24.txt", "wb");

	if (pixels24 > 0)
	{
		fwrite(pixels24, sizeof(RGB), size24, out);
	}

	if (out)
	{
		fclose(out);
	}
}

VOID CTgaImage::DumpRawPixels32()
{
	FILE* out;

	SIZE_T err = fopen_s(&out, "pixels32.txt", "wb");

	if (pixels32 > 0)
	{
		fwrite(pixels32, sizeof(RGBA), size32, out);
	}

	if (out)
	{
		fclose(out);
	}
}

VOID CTgaImage::LoadHeader()
{
	err = fread_s(&header->idLength, sizeof(BYTE), sizeof(BYTE), 1, file);
	err = fread_s(&header->colorMapType, sizeof(BYTE), sizeof(BYTE), 1, file);
	err = fread_s(&header->imageType, sizeof(BYTE), sizeof(BYTE), 1, file);
	err = fread_s(&header->cMapStart, sizeof(WORD), sizeof(WORD), 1, file);
	err = fread_s(&header->cMapLength, sizeof(WORD), sizeof(WORD), 1, file);
	err = fread_s(&header->cMapDepth, sizeof(BYTE), sizeof(BYTE), 1, file);
	err = fread_s(&header->xOffset, sizeof(WORD), sizeof(WORD), 1, file);
	err = fread_s(&header->yOffset, sizeof(WORD), sizeof(WORD), 1, file);
	err = fread_s(&header->width, sizeof(WORD), sizeof(WORD), 1, file);
	err = fread_s(&header->height, sizeof(WORD), sizeof(WORD), 1, file);
	err = fread_s(&header->pixelDepth, sizeof(BYTE), sizeof(BYTE), 1, file);
	err = fread_s(&header->imageDescriptor, sizeof(BYTE), sizeof(BYTE), 1, file);

	size8 = header->width * header->height;
	size24 = header->width * header->height * sizeof(RGB);
	size32 = header->width * header->height * sizeof(RGBA);
}

VOID CTgaImage::LoadImageDescription()
{
	// max length is 256
	if (header->idLength > 0)
	{
		err = fread_s(&imageDescription, sizeof(BYTE) * 256, sizeof(BYTE), header->idLength, file);
	}
}

VOID CTgaImage::LoadColorTable()
{
	if (header->cMapLength > 0)
	{
		err = fread_s(&colorTable, sizeof(BGR) * 256, sizeof(BGR), header->cMapLength, file);
	}
}

VOID CTgaImage::LoadPixelData()
{
	switch (header->imageType)
	{
		// Colormapped image data
		case 1:
		{
			if (header->pixelDepth == 8)
			{
				Load8BitUncompressed();
			}

			break;
		}

		// Truecolor image data
		case 2:
		{
			if (header->pixelDepth == 24)
			{
				Load24BitUncompressed();
			}

			if (header->pixelDepth == 32)
			{
				Load32BitUncompressed();
			}

			break;
		}

		// Colormap with RLE Compression
		case 9:
		{
			if (header->pixelDepth == 8)
			{
				Load8BitCompressed();
			}

			if (header->pixelDepth == 24)
			{
				Load24BitCompressed();
			}

			if (header->pixelDepth == 32)
			{
				Load32BitCompressed();
			}

			break;
		}

		// BGR with RLE Compression
		case 10:
		{
			if (header->pixelDepth == 8)
			{
				Load8BitCompressed();
			}

			if (header->pixelDepth == 24)
			{
				Load24BitCompressed();
			}

			if (header->pixelDepth == 32)
			{
				Load32BitCompressed();
			}

			break;
		}

		default:
		{
			break;
		}
	}
}

VOID CTgaImage::Load8BitUncompressed()
{
	pixels8 = (BYTE*)malloc(size8);

	pixels24 = (BYTE*)malloc(size24);

	pixels32 = (BYTE*)malloc(size32);

	BYTE* pIterator8 = pixels8;

	BYTE* pIterator24 = pixels24;

	BYTE* pIterator32 = pixels32;

	BYTE value;

	INT pcount = 0;

	while (size32 > pcount)
	{
		fread_s(&value, sizeof(BYTE), sizeof(BYTE), 1, file);

		BGR bgr = colorTable[value];

		*pIterator8 = value;
		pIterator8 += 1;


		*pIterator24 = bgr.R;
		pIterator24 += 1;

		*pIterator24 = bgr.G;
		pIterator24 += 1;

		*pIterator24 = bgr.B;
		pIterator24 += 1;


		*pIterator32 = bgr.R;
		pIterator32 += 1;

		*pIterator32 = bgr.G;
		pIterator32 += 1;

		*pIterator32 = bgr.B;
		pIterator32 += 1;

		*pIterator32 = 255;
		pIterator32 += 1;

		pcount += 4;
	}
}

VOID CTgaImage::Load24BitUncompressed()
{
	pixels24 = (BYTE*)malloc(size24);

	pixels32 = (BYTE*)malloc(size32);

	BYTE* pIterator24 = pixels24;

	BYTE* pIterator32 = pixels32;

	BGR bgr;

	INT pcount = 0;

	while (size32 > pcount)
	{
		fread_s(&bgr, sizeof(BGR), sizeof(BGR), 1, file);

		*pIterator24 = bgr.R;
		pIterator24 += 1;

		*pIterator24 = bgr.G;
		pIterator24 += 1;

		*pIterator24 = bgr.B;
		pIterator24 += 1;


		*pIterator32 = bgr.R;
		pIterator32 += 1;

		*pIterator32 = bgr.G;
		pIterator32 += 1;

		*pIterator32 = bgr.B;
		pIterator32 += 1;

		*pIterator32 = 255;
		pIterator32 += 1;

		pcount += 4;
	}
}

VOID CTgaImage::Load32BitUncompressed()
{
	pixels24 = (BYTE*)malloc(size24);

	pixels32 = (BYTE*)malloc(size32);

	BYTE* pIterator24 = pixels24;

	BYTE* pIterator32 = pixels32;

	BGRA bgra;

	INT pcount = 0;

	while (size32 > pcount)
	{
		fread_s(&bgra, sizeof(BGRA), sizeof(BGRA), 1, file);

		*pIterator24 = bgra.R;
		pIterator24 += 1;

		*pIterator24 = bgra.G;
		pIterator24 += 1;

		*pIterator24 = bgra.B;
		pIterator24 += 1;


		*pIterator32 = bgra.R;
		pIterator32 += 1;

		*pIterator32 = bgra.G;
		pIterator32 += 1;

		*pIterator32 = bgra.B;
		pIterator32 += 1;

		*pIterator32 = bgra.A;
		pIterator32 += 1;

		pcount += 4;
	}
}

VOID CTgaImage::Load8BitCompressed()
{
	pixels8 = (BYTE*)malloc(size8);

	pixels24 = (BYTE*)malloc(size24);

	pixels32 = (BYTE*)malloc(size32);

	BYTE* pIterator8 = pixels8;

	BYTE* pIterator24 = pixels24;

	BYTE* pIterator32 = pixels32;

	INT pcount = 0;

	RLEPacket8* p8 = new RLEPacket8();

	while (size32 > pcount)
	{
		p8->ReadCount(file);

		INT count = p8->GetCount();

		// encoded or raw
		if (p8->IsEncoded())
		{
			p8->ReadValue(file);

			BGR bgr = colorTable[p8->value];

			for (INT c = 0; c < count; c++)
			{
				*pIterator8 = p8->value;
				pIterator8 += 1;


				*pIterator24 = bgr.R;
				pIterator24 += 1;

				*pIterator24 = bgr.G;
				pIterator24 += 1;

				*pIterator24 = bgr.B;
				pIterator24 += 1;


				*pIterator32 = bgr.R;
				pIterator32 += 1;

				*pIterator32 = bgr.G;
				pIterator32 += 1;

				*pIterator32 = bgr.B;
				pIterator32 += 1;

				*pIterator32 = 255;
				pIterator32 += 1;

				pcount += 4;
			}
		}
		else
		{
			for (INT c = 0; c < count; c++)
			{
				fread_s(&p8->value, sizeof(BYTE), sizeof(BYTE), 1, file);

				BGR bgr = colorTable[p8->value];

				*pIterator8 = p8->value;
				pIterator8 += 1;


				*pIterator24 = bgr.R;
				pIterator24 += 1;

				*pIterator24 = bgr.G;
				pIterator24 += 1;

				*pIterator24 = bgr.B;
				pIterator24 += 1;


				*pIterator32 = bgr.R;
				pIterator32 += 1;

				*pIterator32 = bgr.G;
				pIterator32 += 1;

				*pIterator32 = bgr.B;
				pIterator32 += 1;

				*pIterator32 = 255;
				pIterator32 += 1;

				pcount += 4;
			}
		}
	}

	delete p8;
}

VOID CTgaImage::Load24BitCompressed()
{
	pixels24 = (BYTE*)malloc(size24);

	pixels32 = (BYTE*)malloc(size32);

	BYTE* pIterator24 = pixels24;

	BYTE* pIterator32 = pixels32;

	INT pcount = 0;

	RLEPacket24* p24 = new RLEPacket24();

	while (size32 > pcount)
	{
		p24->ReadCount(file);

		INT count = p24->GetCount();

		// encoded or raw
		if (p24->IsEncoded())
		{
			p24->ReadValue(file);

			for (INT c = 0; c < count; c++)
			{
				*pIterator24 = p24->value.R;
				pIterator24 += 1;

				*pIterator24 = p24->value.G;
				pIterator24 += 1;

				*pIterator24 = p24->value.B;
				pIterator24 += 1;


				*pIterator32 = p24->value.R;
				pIterator32 += 1;

				*pIterator32 = p24->value.G;
				pIterator32 += 1;

				*pIterator32 = p24->value.B;
				pIterator32 += 1;

				*pIterator32 = 255;
				pIterator32 += 1;

				pcount += 4;
			}
		}
		else
		{
			for (INT c = 0; c < count; c++)
			{
				p24->ReadValue(file);

				*pIterator24 = p24->value.R;
				pIterator24 += 1;

				*pIterator24 = p24->value.G;
				pIterator24 += 1;

				*pIterator24 = p24->value.B;
				pIterator24 += 1;


				*pIterator32 = p24->value.R;
				pIterator32 += 1;

				*pIterator32 = p24->value.G;
				pIterator32 += 1;

				*pIterator32 = p24->value.B;
				pIterator32 += 1;

				*pIterator32 = 255;
				pIterator32 += 1;

				pcount += 4;
			}
		}
	}
}

VOID CTgaImage::Load32BitCompressed()
{
	pixels24 = (BYTE*)malloc(size24);

	pixels32 = (BYTE*)malloc(size32);

	BYTE* pIterator24 = pixels24;

	BYTE* pIterator32 = pixels32;

	INT pcount = 0;

	RLEPacket32* p32 = new RLEPacket32();

	while (size32 > pcount)
	{
		p32->ReadCount(file);

		INT count = p32->GetCount();

		// encoded or raw
		if (p32->IsEncoded())
		{
			p32->ReadValue(file);

			for (INT c = 0; c < count; c++)
			{
				*pIterator24 = p32->value.R;
				pIterator24 += 1;

				*pIterator24 = p32->value.G;
				pIterator24 += 1;

				*pIterator24 = p32->value.B;
				pIterator24 += 1;


				*pIterator32 = p32->value.R;
				pIterator32 += 1;

				*pIterator32 = p32->value.G;
				pIterator32 += 1;

				*pIterator32 = p32->value.B;
				pIterator32 += 1;

				*pIterator32 = p32->value.A;
				pIterator32 += 1;

				pcount += 4;
			}
		}
		else
		{
			for (INT c = 0; c < count; c++)
			{
				p32->ReadValue(file);

				*pIterator24 = p32->value.R;
				pIterator24 += 1;

				*pIterator24 = p32->value.G;
				pIterator24 += 1;

				*pIterator24 = p32->value.B;
				pIterator24 += 1;


				*pIterator32 = p32->value.R;
				pIterator32 += 1;

				*pIterator32 = p32->value.G;
				pIterator32 += 1;

				*pIterator32 = p32->value.B;
				pIterator32 += 1;

				*pIterator32 = p32->value.A;
				pIterator32 += 1;

				pcount += 4;
			}
		}
	}
}

VOID CTgaImage::LoadExtensions()
{
	if (!feof(file))
	{
		footer->ReadValues(file);
	}

	if (footer->extensionOffset > 0)
	{

	}

	if (footer->developerOffset > 0)
	{

	}
}