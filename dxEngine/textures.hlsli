Texture2D texture00 : register(t0);
sampler2D sampler00 : register(s0) = sampler_state
{
	Texture = (texture00);
	
	MipFilter = ANISOTROPIC;
	MinFilter = ANISOTROPIC;
	MagFilter = ANISOTROPIC;

	MAXANISOTROPY = 4;

	AddressU = WRAP;
	AddressV = WRAP;
};

Texture2D texture01 : register(t1);
sampler2D sampler01 : register(s1) = sampler_state
{
	Texture = (texture01);
	
	MipFilter = ANISOTROPIC;
	MinFilter = ANISOTROPIC;
	MagFilter = ANISOTROPIC;

	MAXANISOTROPY = 4;

	AddressU = WRAP;
	AddressV = WRAP;
};

Texture2D texture02 : register(t2);
sampler2D sampler02 : register(s2) = sampler_state
{
	Texture = (texture02);
	
	MipFilter = ANISOTROPIC;
	MinFilter = ANISOTROPIC;
	MagFilter = ANISOTROPIC;

	MAXANISOTROPY = 4;

	AddressU = WRAP;
	AddressV = WRAP;
};

Texture2D texture03 : register(t3);
sampler2D sampler03 : register(s3) = sampler_state
{
	Texture = (texture03);
	
	MipFilter = ANISOTROPIC;
	MinFilter = ANISOTROPIC;
	MagFilter = ANISOTROPIC;

	MAXANISOTROPY = 4;

	AddressU = CLAMP;
	AddressV = CLAMP;
};

Texture2D texture04 : register(t4);
sampler2D sampler04 : register(s4) = sampler_state
{
	Texture = (texture04);
	
	MipFilter = ANISOTROPIC;
	MinFilter = ANISOTROPIC;
	MagFilter = ANISOTROPIC;

	MAXANISOTROPY = 4;

	AddressU = CLAMP;
	AddressV = CLAMP;
};

Texture2D texture05 : register(t5);
sampler2D sampler05 : register(s5) = sampler_state
{
	Texture = (texture05);
	
	MipFilter = ANISOTROPIC;
	MinFilter = ANISOTROPIC;
	MagFilter = ANISOTROPIC;

	MAXANISOTROPY = 4;

	AddressU = CLAMP;
	AddressV = CLAMP;
};
