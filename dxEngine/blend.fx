#include <colors.hlsli>

float4x4 world : WORLD;
float4x4 view : VIEW;
float4x4 proj : PROJ;

float4x4 wvp : WORLDVIEWPROJ;

struct VS_STRUCT2
{
	float4 pos : POSITION;
};

VS_STRUCT2 VSMain(float4 pos : POSITION)
{
	VS_STRUCT2 vertex;

	vertex.pos = mul(pos, wvp);

	return vertex;
}

struct PS_STRUCT
{
	float4 rgb : COLOR0;
};

PS_STRUCT PSMain(VS_STRUCT2 vs)
{
	PS_STRUCT p;

	p.rgb = WatermelonPink;

	p.rgb.a = 0.25;

	return p;
}

technique tech
{
	pass P0
	{
		VertexShader = compile vs_3_0 VSMain();
		PixelShader = compile ps_3_0 PSMain();
	}
}
