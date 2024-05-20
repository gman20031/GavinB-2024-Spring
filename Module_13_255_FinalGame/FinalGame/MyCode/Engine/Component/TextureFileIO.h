#pragma once

#include <filesystem>
#include <memory>
#include <unordered_map>

#include "Texture.h"

class TextureFileIO
{
	inline static const std::filesystem::path kTextureFolder = "Textures";

public:
	static const Texture& Save(const Texture& texture, const std::string& textureIdentifier);
	static std::unique_ptr<Texture> Create( const std::string& textureIdentifier, SDL_Renderer* pRenderer);
};

