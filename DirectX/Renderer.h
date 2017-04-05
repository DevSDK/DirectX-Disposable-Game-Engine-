#pragma once
#include <d3d11_2.h>
#include <wrl\client.h>
#include <D3DX11.h>
#include <DirectXMath.h>
#include <D3Dcompiler.h>
#include <vector>
#include <DirectXColors.h>
#include <d3dx9.h>
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "d3dx9.lib")
#define HR(x) { HRESULT nValue = (x); if(FAILED(nValue)) assert(!"NO HERE"); } 

class Renderer
{

public:
	void SetClearColor(float r, float g, float b,float a);
	void  SetClearColor(const DirectX::XMVECTORF32&);
	DirectX::XMVECTORF32 GetClearColor();
	void AllDraw();
	ID3D11Device* GetDevice();
	ID3D11DeviceContext* GetDeviceContext();
	DirectX::XMINT2 FrameSize();
	DirectX::XMMATRIX GetProjectionMatrix();
	Renderer(int width, int height, HWND hwnd);
	~Renderer();
private:
	DirectX::XMVECTORF32 Color = DirectX::XMVECTORF32{0};
	bool InitVertexShader();
	bool InitPixelShader();
	float LastDelta = 0;
	int Width, Height;
	ID3D11Device*       m_Device;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_DeviceContext;
	IDXGISwapChain*		m_DXGISwapChain;
	ID3D11Texture2D* 	m_DepthStencil;
	ID3D11DepthStencilView* m_DepthStencilView;
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_BackBuffer;
	ID3D11RenderTargetView* m_RenderTarget;
	ID3D11VertexShader*   m_vertexshader;
	ID3D11PixelShader*	m_pixelshader;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_InputLayer;
	ID3D11BlendState* m_BlendState;
	DirectX::XMMATRIX OrthoGraphicMatrix;
	D3D11_VIEWPORT m_ViewPort;

};