#pragma once

#include <filesystem>
#include <memory>

#include "Texture.h"

class TextureFileIO
{
	using Texture_ptr = std::unique_ptr<Texture>;
	inline static const std::filesystem::path kTextureFolder = "Textures";


public:
	static const Texture& Save(const Texture& texture, const std::string& textureIdentifier);
	//Texture& Load(const Texture& texture, const std::string& textureIdentifier);
	static Texture_ptr Create( const std::string& textureIdentifier, SDL_Renderer* pRenderer);

};

