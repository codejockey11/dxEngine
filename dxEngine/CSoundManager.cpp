#include "CSoundManager.h"

CSoundManager::CSoundManager()
{
	memset(this, 0x00, sizeof(CSoundManager));
}

CSoundManager::CSoundManager(CErrorLog* el, CSoundDevice* d)
{
	memset(this, 0x00, sizeof(CSoundManager));

	errorLog = el;
	soundDevice = d;

	sounds = new CLinkList();
}

CSoundManager::~CSoundManager()
{
	CLinkListNode* lln = sounds->list;

	while (lln)
	{
		CSound* e = (CSound*)lln->element;

		delete e;

		lln = lln->next;
	}

	sounds = nullptr;
}

CSound* CSoundManager::MakeSound(const CHAR* fn, BYTE loop)
{
	CSound* sc = CSoundManager::GetSound(fn);

	if (sc != NULL)
	{
		return sc;
	}

	sound = new CSound(errorLog, soundDevice, fn, loop);

	if (!sound->initialized)
	{
		errorLog->WriteError("CSoundManager::MakeSound:Failed:%s\n", fn);

		delete sound;

		return NULL;
	}

	sounds->Add(sound, sound->filename->GetText());

	return sound;
}

CSound* CSoundManager::GetSound(const CHAR* sn)
{
	CLinkListNode* sll = sounds->Search(sn);

	if (sll)
	{
		return (CSound*)sll->element;
	}

	return NULL;
}