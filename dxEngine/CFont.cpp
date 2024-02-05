#include "CFont.h"

CFont::CFont()
{
	memset(this, 0x00, sizeof(CFont));
}

CFont::CFont(CErrorLog* el, CVideoDevice* d, CEffectManager* em, CTextureManager* tm, const CHAR* fn, CVertex2* sz)
{
	memset(this, 0x00, sizeof(CFont));

	errorLog = el;
	videoDevice = d;
	effectMgr = em;
	textureMgr = tm;

	effect = effectMgr->GetEffect("text.fx");

	CString* name = new CString(128);

	D3DCOLOR cc = D3DCOLOR_XRGB(0, 0, 0);

	for (UINT i = 0; i < CFont::MAXFONTCOUNT; i++)
	{
		UINT c = 33 + i;

		name->Format("./%s/%d.BMP", fn, c);

		textureMgr->MakeTexture(name->GetText(), &cc);

		bmp = new CBmpImage(name->GetText());

		height = bmp->bmapInfo.bmiHeader.biHeight;

		CVertex2 v1(bmp->bmapInfo.bmiHeader.biWidth / sz->X, bmp->bmapInfo.bmiHeader.biHeight / sz->Y);

		CVertex2 v2(0.0F, 0.0F);

		fonts[i] = new CHudImage(errorLog, videoDevice, textureMgr, NULL , name->GetText(), &v1, &v2, NULL);

		delete bmp;
	}

	delete name;
}

CFont::~CFont()
{
	for (UINT i = 0; i < CFont::MAXFONTCOUNT; i++)
	{
		delete fonts[i];
	}
}

VOID CFont::Draw(const CHAR* text, UINT x, UINT y, CColor* color)
{
	if (!effect)
	{
		return;
	}

	hr = effect->effect->SetFloatArray(effect->hmaterial, color->GetFloatArray(), 4);

	UINT s = (UINT)strlen(text);

	UINT sp = x;

	for (UINT i = 0; i < s; i++)
	{
		INT c = text[i] - 33;

		if ((c > -1) && (c < 95))
		{
			fonts[c]->position.X = (FLOAT)sp;
			fonts[c]->position.Y = (FLOAT)y;

			fonts[c]->UpdatePosition();

			if (effect)
			{
				hr = effect->effect->Begin(&effect->cPasses, 0);

				for (UINT e = 0; e < effect->cPasses; e++)
				{
					hr = effect->effect->BeginPass(e);

					hr = effect->effect->SetTexture(effect->htexture00, fonts[c]->texture->image);

					hr = effect->effect->CommitChanges();

					fonts[c]->vertexBuffer->DrawIndexed(fonts[c]->indexBuffer);

					hr = effect->effect->EndPass();
				}

				hr = effect->effect->End();
			}

			sp += (UINT)(fonts[c]->size.X) + 3;
		}
		else if (c == -1)
		{
			sp += 6;
		}
	}
}