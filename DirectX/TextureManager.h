#pragma once
#include <unordered_map>
#include <assert.h>
#include <D3D11_2.h>
#include <D3DX11.h>
class TextureManager 
{
	static std::unordered_map<std::string, ID3D11ShaderResourceView* > TextureTable;

public:

	static ID3D11ShaderResourceView* GetTexture(std::string filepath, ID3D11Device* device)
	{
		if (TextureTable[(filepath)] != NULL)
			return TextureTable[(filepath)];

		ID3D11ShaderResourceView* texture;
		HRESULT result = D3DX11CreateShaderResourceViewFromFile(device, filepath.c_str(),
			NULL, NULL, &texture, NULL);
		if (FAILED(result)) { assert(!"NO FILE!"); }
		TextureTable[filepath]=  texture;
		return texture;
	}

};
//TODO: must be Deletes
std::unordered_map<std::string, ID3D11ShaderResourceView* > TextureManager::TextureTable;
