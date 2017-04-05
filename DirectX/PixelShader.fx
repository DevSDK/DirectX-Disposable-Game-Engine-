Texture2D shaderTexturer : register(t0);
SamplerState SampleType;

struct VertexOut
{
	float4 Position : SV_POSITION;
	float2 Texcoord : TEXCOORD;
};

float4 PS(VertexOut pin) : SV_TARGET
{
	float4 finalcolor = shaderTexturer.Sample(SampleType, pin.Texcoord);
	clip(finalcolor.a - 0.1);
	return finalcolor;
}