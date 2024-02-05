#include "CTextureManager.h"

CTextureManager::CTextureManager()
{
	memset(this, 0x00, sizeof(CTextureManager));
}

CTextureManager::CTextureManager(CErrorLog* el, CVideoDevice* d)
{
	memset(this, 0x00, sizeof(CTextureManager));

	errorLog = el;
	videoDevice = d;

	textures = new CLinkList();
}

CTextureManager::~CTextureManager()
{
	CLinkListNode* lln = textures->list;

	while (lln)
	{
		CTexture* e = (CTexture*)lln->element;

		delete e;

		lln = lln->next;
	}

	textures = nullptr;
}

CTexture* CTextureManager::MakeTexture(const CHAR* fn, D3DCOLOR* c)
{
	CTexture* tc = CTextureManager::GetTexture(fn);

	if (tc != NULL)
	{
		return tc;
	}

	texture = new CTexture(errorLog, videoDevice, fn, c);

	if (texture->image == NULL)
	{
		errorLog->WriteError("CTextureManager::MakeTexture:Failed:%s\n", fn);

		delete texture;

		return NULL;
	}

	textures->Add(texture, texture->filename->GetText());

	return texture;
}

VOID CTextureManager::DeleteTexture(const CHAR* fn)
{
	CLinkListNode* lln = textures->Search(fn);

	if (lln)
	{
		textures->Delete(lln);
	}
}

CTexture* CTextureManager::GetTexture(const CHAR* tn)
{
	CLinkListNode* tll = textures->Search(tn);

	if (tll)
	{
		return (CTexture*)tll->element;
	}

	return NULL;
}