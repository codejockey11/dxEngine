#include "CDXFontManager.h"

CDXFontManager::CDXFontManager()
{
	memset(this, 0x00, sizeof(CDXFontManager));
}

CDXFontManager::CDXFontManager(CErrorLog* el, CVideoDevice* d, CWindow* w)
{
	memset(this, 0x00, sizeof(CDXFontManager));

	errorLog = el;
	videoDevice = d;
	window = w;

	fonts = new CLinkList();
}

CDXFontManager::~CDXFontManager()
{
	CLinkListNode* lln = fonts->list;

	while (lln)
	{
		CDXFont* e = (CDXFont*)lln->element;

		delete e;

		lln = lln->next;
	}

	fonts = nullptr;
}

CDXFont* CDXFontManager::MakeDXFont(const CHAR* face, UINT pitch, UINT bold)
{
	CDXFont* fc = CDXFontManager::GetFont(face);

	if (fc)
	{
		return fc;
	}

	font = new CDXFont(errorLog, videoDevice, window, face, pitch, bold);

	if (font->font == NULL)
	{
		errorLog->WriteError("CDXFontManager::CDXFont:Failed:%s\n", face);

		delete font;

		return NULL;
	}

	fonts->Add(font, face);

	return font;
}

CDXFont* CDXFontManager::GetFont(const CHAR* face)
{
	CLinkListNode* lln = fonts->Search(face);

	if (lln == NULL)
	{
		return NULL;
	}

	return (CDXFont*)lln->element;
}

VOID CDXFontManager::DeleteDXFont(const CHAR* face)
{
	CLinkListNode* lln = fonts->Search(face);

	if (lln)
	{
		fonts->Delete(lln);
	}
}