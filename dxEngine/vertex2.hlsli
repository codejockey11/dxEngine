float4x4 world : WORLD;
float4x4 view : VIEW;
float4x4 proj : PROJ;

float4x4 wvp : WORLDVIEWPROJ;

float4 material;

float  lightAmbient;

struct VS_STRUCT
{
	float4 pos : POSITION;
	float2 uv : TEXCOORD0;
	float  depth : DEPTH;
	float4 vPos : TEXCOORD1;
};

VS_STRUCT VSMain(float4 pos : POSITION, float2 uv : TEXCOORD0)
{
	VS_STRUCT vertex;

	vertex.pos = mul(pos, wvp);

	vertex.uv = uv;

	vertex.depth = vertex.pos.z;

	vertex.vPos = pos;

	return vertex;
}
