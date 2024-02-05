#include "CEffectManager.h"

CEffectManager::CEffectManager()
{
	memset(this, 0x00, sizeof(CEffectManager));
}

CEffectManager::CEffectManager(CErrorLog* el, CVideoDevice* d)
{
	memset(this, 0x00, sizeof(CEffectManager));

	errorLog = el;
	videoDevice = d;

	effects = new CLinkList();
}

CEffectManager::~CEffectManager()
{
	CLinkListNode* lln = effects->list;

	while (lln)
	{
		CEffect* e = (CEffect*)lln->element;

		delete e;

		lln = lln->next;
	}

	effects = nullptr;
}

CEffect* CEffectManager::MakeEffect(const CHAR* fn)
{
	CEffect* ec = CEffectManager::GetEffect(fn);

	if (ec)
	{
		return ec;
	}

	effect = new CEffect(errorLog, videoDevice, fn);

	if (effect->effect == NULL)
	{
		errorLog->WriteError("CEffectManager::MakeEffect:Failed:%s\n", fn);

		delete effect;

		return NULL;
	}

	effects->Add(effect, effect->filename->GetText());

	return effect;
}

CEffect* CEffectManager::GetEffect(const CHAR* fn)
{
	CLinkListNode* lln = effects->Search(fn);

	if (lln)
	{
		return (CEffect*)lln->element;
	}

	return NULL;
}

VOID CEffectManager::DeleteEffect(const CHAR* fn)
{
	CLinkListNode* lln = effects->Search(fn);

	if (lln)
	{
		effects->Delete(lln);
	}
}