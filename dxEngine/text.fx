#include <colors.hlsli>
#include <vertex2.hlsli>
#include <pixel.hlsli>

Texture2D texture00 : register(t0);
sampler2D sampler00 : register(s0) = sampler_state
{
	Texture = (texture00);
	
	MipFilter = LINEAR;
	MinFilter = LINEAR;
	MagFilter = LINEAR;

	AddressU = CLAMP;
	AddressV = CLAMP;
};

PS_STRUCT PSMain(VS_STRUCT vs)
{
	PS_STRUCT pixel;

	pixel.rgb = tex2D(sampler00, vs.uv);

	float a = pixel.rgb.a;

	pixel.rgb *= material;// *lightAmbient;

	pixel.rgb.a = a;

	return pixel;
}

technique tech
{
	pass P0
	{
		VertexShader = compile vs_3_0 VSMain();
		PixelShader = compile ps_3_0 PSMain();
	}
}
