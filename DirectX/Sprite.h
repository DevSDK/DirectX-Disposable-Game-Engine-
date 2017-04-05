#pragma once
#include "DrawableNode.h"
#include <D3DX11.h>
#include <string>
#include <DirectXMath.h>
#include <D3D11_2.h>


class Sprite : public DrawableNode
{
public:
	static Sprite* Create(std::string, int Width, int Height);
private:
	int Width;
	int Height;
	Sprite(std::string, int Width, int Height);
	~Sprite();
	void Init(ID3D11Device*, ID3D11DeviceContext*);
	virtual void onDraw(Renderer*	);
	bool isInitalized = false;
	std::string filePath;
	DirectX::XMVECTOR pos ;
	ID3D11ShaderResourceView* m_Texture;
	ID3D11Buffer* m_vb;
	ID3D11Buffer* m_ib;
	UINT m_stride;
	UINT m_offset = 0 ;
};
