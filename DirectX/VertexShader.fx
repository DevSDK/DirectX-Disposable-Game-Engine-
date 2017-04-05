cbuffer MatrixBuffer
{
	matrix translate;
	matrix modelview;
};
struct VertexIn
{
	float3 Pos : POSITION;
	float2 Tex : TEXCOORD;
};

struct VertexOut
{
	float4 Position : SV_POSITION;
	float2 Tex		: TEXCOORD;
};

VertexOut VS(VertexIn vin)
{
	VertexOut vout;
	float4 op = float4(vin.Pos.x, vin.Pos.y, vin.Pos.z, 1);

	vout.Position = mul(translate,mul(modelview, op));
	vout.Tex = vin.Tex;
	return vout;
}