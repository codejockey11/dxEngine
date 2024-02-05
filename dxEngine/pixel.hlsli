float fogStart;
float fogEnd;
float fogDensity;
float minFog;
float maxFog;
float3 fogColor;

#define MAXLIGHTS		8

int	lightCount;

float4 lightPosition[MAXLIGHTS];
float  lightRadius[MAXLIGHTS];
float4 lightColor[MAXLIGHTS];
float  lightLinear[MAXLIGHTS];
float  lightQuadratic[MAXLIGHTS];
float  lightIntensity[MAXLIGHTS];

struct PS_STRUCT
{
	float4 rgb : COLOR0;
};
