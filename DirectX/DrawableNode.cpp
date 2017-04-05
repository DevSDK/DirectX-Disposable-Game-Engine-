#include "DrawableNode.h"
#include "Renderer.h"
using namespace DirectX;
DrawableNode::DrawableNode(int width, int height)
{
}

void DrawableNode::DrawNode(Renderer *renderer)
{
	XMINT2 windowsize = renderer->FrameSize();

	if (isInitialized == false)
	{
		D3D11_BUFFER_DESC matrixBufferDesc;
		matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		matrixBufferDesc.ByteWidth = sizeof(MatrixType);
		matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		matrixBufferDesc.MiscFlags = 0;
		matrixBufferDesc.StructureByteStride = 0;
		renderer->GetDevice()->CreateBuffer(&matrixBufferDesc, NULL, &m_vertex_buffer);
		isInitialized = true;
	}

	D3D11_MAPPED_SUBRESOURCE mappedResource;
	MatrixType* dataPtr;
	unsigned int bufferNumber;

	DirectX::XMMATRIX Projection = XMMatrixTranspose(renderer->GetProjectionMatrix());
	DirectX::XMMATRIX translate = XMMatrixTranslation(Position.x- windowsize.x/2, Position.y- windowsize.y/2, 0);
	DirectX::XMMATRIX Rotate	=XMMatrixRotationAxis({ 0, 0, 1 }, XMConvertToRadians( Angle));
	DirectX::XMMATRIX ScaleMatrix = XMMatrixScaling(Scale.x, Scale.y, 1);

	DirectX::XMMATRIX ModelView = Rotate* translate*ScaleMatrix;

	renderer->GetDeviceContext()->
		IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	renderer->GetDeviceContext()->
		Map(m_vertex_buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);


	dataPtr = (MatrixType*)mappedResource.pData;
	dataPtr->Projection = Projection;
	dataPtr->ModelView = ModelView;
	
	renderer->GetDeviceContext()->Unmap(m_vertex_buffer, 0);

	bufferNumber = 0;
	renderer->GetDeviceContext()->VSSetConstantBuffers(bufferNumber, 1, &m_vertex_buffer);

	onDraw(renderer);
}

void DrawableNode::SetPosition(DirectX::XMFLOAT2 Pos)
{
	Position = Pos;
}

void DrawableNode::SetPosition(float x, float y)
{
	Position.x = x;
	Position.y = y;
}

DirectX::XMFLOAT2 DrawableNode::GetPosition()
{
	return Position;
}

void DrawableNode::SetScale(DirectX::XMFLOAT2 scale)
{
	Scale = scale;
}

void DrawableNode::SetScale(float x, float y)
{
	Scale.x = x;
	Scale.y = y;
}

DirectX::XMFLOAT2 DrawableNode::GetScale()
{
	return Scale;
}

DirectX::XMINT2 DrawableNode::GetSize()
{
	return DirectX::XMINT2(Width,Height);
}

void DrawableNode::SetRotateDigree(float dt)
{
	Angle = dt;
}

float DrawableNode::GetRotate()
{
	return Angle;
}
