#include <colors.hlsli>
#include <vertex.hlsli>
#include <pixel.hlsli>
#include <textures.hlsli>
#include <pointLight.hlsli>

PS_STRUCT PSMain(VS_STRUCT vs)
{
	PS_STRUCT pixel;

	pixel.rgb = tex2D(sampler00, vs.uv);

	float4 pointLight = PointLight(0, vs.vPos, vs.normal);

	pixel.rgb *= vs.diffuse + pointLight;

#include <fog.hlsli>

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
