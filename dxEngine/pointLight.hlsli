// pointlight attenuation
//
// a = intensity / (1.0 + (linear * dist) + (quadratic * dist^2));
float4 PointLight(int count, float4 vPos, float3 normal)
{
	float4 lightFinal = float4(0, 0, 0, 1);

	float4 pointVector = vPos - lightPosition[count];

	float dist = length(pointVector);

	float attenuation = lightIntensity[count] / (1.0 + (lightLinear[count] * dist) + (lightQuadratic[count] * (dist * dist)));

	float NdL = max(1.0, dot(normal, (float3)normalize(pointVector)));

	lightFinal.r = NdL * lightColor[count].rgb.r * attenuation;
	lightFinal.g = NdL * lightColor[count].rgb.g * attenuation;
	lightFinal.b = NdL * lightColor[count].rgb.b * attenuation;

	return lightFinal;
}
