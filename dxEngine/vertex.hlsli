float4x4 world : WORLD;
float4x4 view : VIEW;
float4x4 proj : PROJ;

float4x4 wvp : WORLDVIEWPROJ;

float4 material;

float  lightAmbient;

struct VS_STRUCT
{
	float4 pos : POSITION;
	float4 diffuse : COLOR0;
	float2 uv : TEXCOORD0;
	float  depth : DEPTH;
	float4 vPos : TEXCOORD1;
	float3 normal : TEXCOORD2;
};

VS_STRUCT VSMain(float4 pos : POSITION, float3 normal : NORMAL, float2 uv : TEXCOORD0)
{
	VS_STRUCT vertex;

	vertex.pos = mul(pos, wvp);

	vertex.diffuse = material * lightAmbient;
	
	vertex.diffuse.a = 1.0;

	vertex.uv = uv;

	vertex.depth = vertex.pos.z;

	vertex.vPos = pos;

	vertex.normal = normal;

	return vertex;
}
