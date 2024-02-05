if (fogDensity > 0.0)
{
	float fog = (vs.depth - fogStart) / (fogEnd - fogStart);
	fog *= fogDensity;
	fog = clamp(fog, minFog, maxFog);
	pixel.rgb = lerp(pixel.rgb, float4(fogColor, 1.0), fog);
	pixel.rgb.a = 1.0;
}
