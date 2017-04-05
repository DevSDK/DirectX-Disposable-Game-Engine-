#include "Sprite.h"
#include "Renderer.h"
#include "TextureManager.h"
struct Input
{
	DirectX::XMFLOAT3 Position;
	DirectX::XMFLOAT2 Texcoord;
};
using namespace DirectX;
Sprite * Sprite::Create(std::string sprite, int Width, int Height)
{
	Sprite* spr = new Sprite(sprite, Width, Height);
	return spr;
}

Sprite::Sprite(std::string f, int Width, int Height) : filePath(f), Width(Width), Height(Height),
DrawableNode(Width,Height)
{
	
}

Sprite::~Sprite()
{
}

void Sprite::Init(ID3D11Device *device,ID3D11DeviceContext* context)
{
	m_Texture = TextureManager::GetTexture(filePath, device);
	Input verticesCombo[]
	{
		XMFLOAT3(-Width / 2, -Height / 2, 0.0f), XMFLOAT2(1,1),
		XMFLOAT3(-Width / 2, Height / 2, 0.0f), XMFLOAT2(1,0),
		XMFLOAT3(Width / 2, -Height / 2, 0.0f), XMFLOAT2(0,1),
		XMFLOAT3(Width / 2, Height / 2, 0.0f), XMFLOAT2(0,0)
	};
	D3D11_BUFFER_DESC def;
	def.Usage = D3D11_USAGE_DEFAULT;

	def.ByteWidth = sizeof(Input) * 4;
	def.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	def.CPUAccessFlags = 0;
	def.MiscFlags = 0;
	def.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA dat;
	dat.pSysMem = verticesCombo;

	dat.SysMemPitch = 0;
	dat.SysMemSlicePitch = 0;

	UINT *indecs = new UINT[6]{ 0, 1, 2 ,2,1,3};

	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	m_stride = sizeof(Input);


	device->CreateBuffer(&def, &dat, &m_vb);

	D3D11_BUFFER_DESC ind;

	ind.Usage = D3D11_USAGE_DEFAULT;
	ind.ByteWidth = sizeof(UINT) * 6;
	ind.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ind.CPUAccessFlags = 0;
	ind.MiscFlags = 0;
	ind.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA idd;

	idd.pSysMem = indecs;
	idd.SysMemPitch = 0;
	idd.SysMemSlicePitch = 0;

	device->CreateBuffer(&ind, &idd, &m_ib);



	context->IASetIndexBuffer(m_ib, DXGI_FORMAT_R32_UINT, 0);
	context->IASetVertexBuffers(0, 1, &m_vb, &m_stride, &m_offset);
	D3D11_SAMPLER_DESC sampler_desc;
	sampler_desc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	sampler_desc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	sampler_desc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	sampler_desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampler_desc.MipLODBias = 0;
	sampler_desc.MinLOD = -3.402823466e+38F;
	sampler_desc.MaxLOD = 3.402823466e+38F;
	sampler_desc.MaxAnisotropy = 1;
	sampler_desc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampler_desc.BorderColor[0] = 0;
	sampler_desc.BorderColor[1] = 0;
	sampler_desc.BorderColor[2] = 0;
	sampler_desc.BorderColor[3] = 0;
	ID3D11SamplerState* state;
	device->CreateSamplerState(&sampler_desc, &state);
	context->PSSetSamplers(0, 1,&state);
	state->Release();


	isInitalized = true;
}

void Sprite::onDraw(Renderer* renderer)
{
	ID3D11Device* device = renderer->GetDevice();
	ID3D11DeviceContext* context = renderer->GetDeviceContext();
	if(isInitalized == false)
		Init(device, context);




	context->PSSetShaderResources(0, 1, &m_Texture);
	context->IASetIndexBuffer(m_ib, DXGI_FORMAT_R32_UINT, 0);
	context->IASetVertexBuffers(0, 1, &m_vb, &m_stride, &m_offset);



	context->DrawIndexed(6, 0, 0);
	


}
