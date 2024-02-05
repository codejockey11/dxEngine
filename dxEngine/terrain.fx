#include <colors.hlsli>
#include <vertex.hlsli>
#include <pixel.hlsli>
#include <textures.hlsli>
#include <pointLight.hlsli>

PS_STRUCT PSMain(VS_STRUCT vs)
{
	PS_STRUCT pixel;

	pixel.rgb = tex2D(sampler01, vs.uv * 128);

	float4 maskMap1 = tex2D(sampler03, vs.uv);

	if (maskMap1.r > 0.0)
	{
		float b1 = 1.0 - maskMap1.r;
		float b2 = 1.0 - b1;

		float4 ts = tex2D(sampler02, vs.uv * 128);

		pixel.rgb = (pixel.rgb * b1) + (ts * b2);
	}

	float4 maskMap2 = tex2D(sampler04, vs.uv);

	if (maskMap2.r > 0.0)
	{
		float b1 = 1.0 - maskMap2.r;
		float b2 = 1.0 - b1;

		float4 ts = tex2D(sampler00, vs.uv * 128);

		pixel.rgb = (pixel.rgb * b1) + (ts * b2);
	}

	pixel.rgb *= tex2D(sampler05, vs.uv);

	float4 pointLight = PointLight(0, vs.vPos, vs.normal);

	pixel.rgb *= vs.diffuse + pointLight;

#include <fog.hlsli>

	pixel.rgb.a = 1.0;

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
