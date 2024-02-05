#include "CEffect.h"

CEffect::CEffect()
{
	memset(this, 0x00, sizeof(CEffect));
}

CEffect::CEffect(CErrorLog* el, CVideoDevice* d, const CHAR* fn)
{
	memset(this, 0x00, sizeof(CEffect));

	errorLog = el;
	videoDevice = d;

	filename = new CString(fn);

	dwShaderFlags |= D3DXSHADER_NO_PRESHADER;

	hr = D3DXCreateEffectFromFile(videoDevice->device, filename->GetText(), NULL, NULL, dwShaderFlags, NULL, &effect, &compileErrors);

	if (hr < 0)
	{
		errorLog->WriteError("CEffect::LoadShader::D3DXCreateEffectFromFile:%s:%s\n", filename->GetText(), errorLog->GetComErrorMessage(hr));

		if (compileErrors)
		{
			errorLog->WriteError("Compile Errors\n%s", (CHAR*)compileErrors->GetBufferPointer());
		}

		effect = NULL;

		return;
	}

	htechnique = effect->GetTechniqueByName("tech");

	hworld = effect->GetParameterByName(NULL, "world");
	hview = effect->GetParameterByName(NULL, "view");
	hproj = effect->GetParameterByName(NULL, "proj");
	hwvp = effect->GetParameterByName(NULL, "wvp");

	hlightAmbient = effect->GetParameterByName(NULL, "lightAmbient");

	hfogStart = effect->GetParameterByName(NULL, "fogStart");
	hfogEnd = effect->GetParameterByName(NULL, "fogEnd");
	hfogDensity = effect->GetParameterByName(NULL, "fogDensity");
	hminFog = effect->GetParameterByName(NULL, "minFog");
	hmaxFog = effect->GetParameterByName(NULL, "maxFog");
	hfogColor = effect->GetParameterByName(NULL, "fogColor");

	hlightCount = effect->GetParameterByName(NULL, "lightCount");

	hlightPosition = effect->GetParameterByName(NULL, "lightPosition");
	hlightRadius = effect->GetParameterByName(NULL, "lightRadius");
	hlightColor = effect->GetParameterByName(NULL, "lightColor");
	hlightLinear = effect->GetParameterByName(NULL, "lightLinear");
	hlightQuadratic = effect->GetParameterByName(NULL, "lightQuadratic");
	hlightIntensity = effect->GetParameterByName(NULL, "lightIntensity");

	hmaterial = effect->GetParameterByName(NULL, "material");

	htexture00 = effect->GetParameterByName(NULL, "texture00");
	htexture01 = effect->GetParameterByName(NULL, "texture01");
	htexture02 = effect->GetParameterByName(NULL, "texture02");
	htexture03 = effect->GetParameterByName(NULL, "texture03");
	htexture04 = effect->GetParameterByName(NULL, "texture04");
	htexture05 = effect->GetParameterByName(NULL, "texture05");

	CEffect::SetWVP();
}

CEffect::~CEffect()
{
	delete filename;

	if (effect)
	{
		effect->Release();
	}
}

VOID CEffect::SetWVP()
{
	hr = effect->SetMatrix(hworld, &videoDevice->worldMatrix);
	hr = effect->SetMatrix(hproj, &videoDevice->projMatrix);
}