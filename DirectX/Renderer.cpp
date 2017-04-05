#include "Renderer.h"
#include "Scene.h"
#include "SceneManager.h"
#include <ctime>
void Renderer::SetClearColor(float r, float g, float b, float a)
{
	Color.f[0] = r;
	Color.f[1] = g;
	Color.f[2] = b;
	Color.f[3] = a;
}
void Renderer::SetClearColor(const DirectX::XMVECTORF32& color)
{
	Color = color;
}
DirectX::XMVECTORF32 Renderer::GetClearColor()
{
	return Color;
}
void Renderer::AllDraw()
{
	float start = std::clock();
	m_DeviceContext->ClearRenderTargetView(m_RenderTarget, Color);
	m_DeviceContext->ClearDepthStencilView(m_DepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	m_DeviceContext->IASetInputLayout(m_InputLayer.Get());
	m_DeviceContext->PSSetShader(m_pixelshader, 0, 0);
	RECT rt = { 100,100,400,300 };
	DrawText(NULL, "HasdasdasdaI", 2, &rt ,DT_CENTER);
	if (SceneManager::GetInstance()->GetCurrentScene() != NULL)
	{
		SceneManager::GetInstance()->GetCurrentScene()->Update(LastDelta);
		SceneManager::GetInstance()->GetCurrentScene()->
			DrawAllNodes(this);
	}
	m_DXGISwapChain->Present(1, 0);
	LastDelta = (std::clock() - start)/ CLOCKS_PER_SEC/1000;
}

ID3D11Device * Renderer::GetDevice()
{
	return m_Device;
}

ID3D11DeviceContext * Renderer::GetDeviceContext()
{
	return m_DeviceContext.Get();
}

DirectX::XMINT2 Renderer::FrameSize()
{
	return DirectX::XMINT2(Width,Height);
}

DirectX::XMMATRIX Renderer::GetProjectionMatrix()
{
	return OrthoGraphicMatrix;
}


Renderer::Renderer(int width, int height, HWND hwnd) : Width(width) , Height(height)
{
	D3D_FEATURE_LEVEL featurelevel;
	HRESULT hr = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr,
		D3D11_CREATE_DEVICE_DEBUG, 0, 0, D3D11_SDK_VERSION, &m_Device, &featurelevel, &m_DeviceContext);

	if (FAILED(hr))
	{
		MessageBox(nullptr, "Failed", nullptr, 0);
	
	}
	if (featurelevel != D3D_FEATURE_LEVEL_11_0)
	{
		MessageBox(nullptr, "Initalize Failed DirectX11", nullptr, 0);

	}
	DXGI_SWAP_CHAIN_DESC sd;

	sd.BufferDesc.Width = Width;
	sd.BufferDesc.Height = Height;
	sd.BufferDesc.RefreshRate.Numerator = 0;
	sd.BufferDesc.RefreshRate.Denominator = 0;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	
		sd.SampleDesc.Count = 1;
		sd.SampleDesc.Quality = 0;


	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferCount = 1;
	sd.OutputWindow = hwnd;
	sd.Windowed = true;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd.Flags = 0;

	IDXGIDevice* dxgiDevice = nullptr;
	HR(m_Device->QueryInterface(__uuidof(IDXGIDevice), (void**)&dxgiDevice));
	IDXGIAdapter* dxgiAdapter = nullptr;
	HR(dxgiDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&dxgiAdapter));
	IDXGIFactory* dxgiFactory = nullptr;
	HR(dxgiAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&dxgiFactory));


	HR(dxgiFactory->CreateSwapChain(m_Device, &sd, &m_DXGISwapChain));

	dxgiDevice->Release();
	dxgiAdapter->Release();
	dxgiFactory->Release();

	ID3D11Texture2D* BackBuffer;
	HR(m_DXGISwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&BackBuffer));
	m_Device->CreateRenderTargetView(BackBuffer, 0, &m_RenderTarget);

	D3D11_TEXTURE2D_DESC depthStencilDesc;
	depthStencilDesc.Width = Width;;
	depthStencilDesc.Height = Height;
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;


		depthStencilDesc.SampleDesc.Count = 1;
		depthStencilDesc.SampleDesc.Quality = 0;
		
	depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
	depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStencilDesc.CPUAccessFlags = 0;
	depthStencilDesc.MiscFlags = 0;

	HR(m_Device->CreateTexture2D(&depthStencilDesc, 0, &m_DepthStencil));
	HR(m_Device->CreateDepthStencilView(m_DepthStencil, 0, &m_DepthStencilView ));
	m_DeviceContext->OMSetRenderTargets(1, &m_RenderTarget, NULL);
	

	D3D11_VIEWPORT vp;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	vp.Width = (float)Width;
	vp.Height = (float)Height;
	vp.MinDepth = 0.0;
	vp.MaxDepth = 1.0f;
	m_DeviceContext->RSSetViewports(1, &vp);

	Microsoft::WRL::ComPtr<ID3DBlob>  m_shader_vertex;


	InitVertexShader();
	InitPixelShader();
	OrthoGraphicMatrix = DirectX::XMMatrixOrthographicLH(Width, Height, 0, 1);

	D3D11_BLEND_DESC BSDesc;
	ZeroMemory(&BSDesc, sizeof(D3D11_BLEND_DESC));

	BSDesc.RenderTarget[0].BlendEnable = TRUE;
	BSDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	BSDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	BSDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	BSDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	BSDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	BSDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	BSDesc.RenderTarget[0].RenderTargetWriteMask = 0x0F;

	HR(m_Device->CreateBlendState(&BSDesc, &m_BlendState));
	float mult[] { 0,0,0,0 };
	UINT sampleMask = 0xffffffff;
	m_DeviceContext->OMSetBlendState(m_BlendState, mult, sampleMask);

	
}

Renderer::~Renderer()
{
}

bool Renderer::InitVertexShader()
{

	ID3DBlob* blob;
	ID3DBlob* errb;

	DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
	dwShaderFlags |= D3DCOMPILE_DEBUG;
	HRESULT hr = D3DX11CompileFromFile("VertexShader.fx", NULL, NULL, "VS", 
		"vs_5_0", dwShaderFlags, 0,
		NULL, &blob, &errb,NULL);
	if (FAILED(hr))
	{
		if (errb != NULL)
			OutputDebugStringA((char*)errb->GetBufferPointer());
		errb->Release();
		return false;
	}	
	m_Device->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), NULL, &m_vertexshader);
	m_DeviceContext->VSSetShader(m_vertexshader, nullptr, 0);
	const D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA,0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	m_Device->CreateInputLayout(layout, 2, blob->GetBufferPointer(), blob->GetBufferSize(), &m_InputLayer);

	


	return true;
}

bool Renderer::InitPixelShader()
{
	
	ID3DBlob* blob;
	ID3DBlob* errb;
	DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
	dwShaderFlags |= D3DCOMPILE_DEBUG;
	HRESULT hr = D3DX11CompileFromFile("PixelShader.fx", NULL, NULL, "PS",
		"ps_5_0", dwShaderFlags, 0,
		NULL, &blob, &errb, NULL);
	if (FAILED(hr))
	{
		if (errb != NULL)
			OutputDebugStringA((char*)errb->GetBufferPointer());
		errb->Release();
		return false;
	}
	m_Device->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), NULL, &m_pixelshader);
	m_DeviceContext->PSSetShader(m_pixelshader, nullptr, 0);
	return true;
}

