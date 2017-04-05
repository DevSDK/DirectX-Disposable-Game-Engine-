#pragma once
#include <D3D11_2.h>
#include <DirectXMath.h>
class Renderer;
class DrawableNode
{
public:
	DrawableNode(int width, int height);
	void DrawNode(Renderer* renderer);
	void SetPosition(DirectX::XMFLOAT2 Pos);
	void SetPosition(float x, float y);
	DirectX::XMFLOAT2 GetPosition();

	void SetScale(DirectX::XMFLOAT2 scale);
	void SetScale(float x, float y);
	DirectX::XMFLOAT2 GetScale();

	DirectX::XMINT2 GetSize();

	void SetRotateDigree(float dt);
	float GetRotate();

protected:
	virtual void onDraw(Renderer*) = 0;
	int Width = 0;
	int Height = 0;
	DirectX::XMFLOAT2 Position = DirectX::XMFLOAT2(0,0);
	DirectX::XMFLOAT2 Scale = DirectX::XMFLOAT2(1, 1);
	float Angle =0 ;
private:
	bool isInitialized = false;

	ID3D11Buffer* m_vertex_buffer;
	struct MatrixType
	{
		DirectX::XMMATRIX Projection;
		DirectX::XMMATRIX ModelView;
	};


};