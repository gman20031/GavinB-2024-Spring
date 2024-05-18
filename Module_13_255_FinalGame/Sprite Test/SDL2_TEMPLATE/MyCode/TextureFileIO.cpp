#include "TextureFileIO.h"

#include <fstream>
#include <assert.h>
#include <unordered_map>


/**
* Texture scheme
* 
* Identifier:
*\t ImageFile
*\t max frames
*\t spriteWidth, spriteHieght
*\t starting frame
*\t scale modifier
* end
*/

const Texture& TextureFileIO::Save(const Texture& texture, const std::string& textureIdentifier)
{
	assert(!textureIdentifier.empty());

	std::filesystem::path TexturePath = kTextureFolder / (textureIdentifier + ".txt");
	std::fstream textureFile;
	textureFile.open(TexturePath, std::ios_base::out );
	assert(textureFile.is_open() && textureFile.good() );

	TextureSaveInfo info = texture.GetSaveInfo();
	textureFile << textureIdentifier << '\n';
	textureFile << info.m_imageFilePath << '\n';
	textureFile << info.m_maxFrameCount << '\n';
	textureFile << info.m_width << '\n';
	textureFile << info.m_height << '\n';
	textureFile << info.m_currentFrame << '\n';
	textureFile << info.m_scaleMod << '\n';
	textureFile << "end\n";
	
	textureFile.close();

	return texture;
}


constexpr uint32_t StringHash(const char* cString)
{
	// kPrime = 16777619;
	// kOffset = 2166136261U
	unsigned int character, result = 2166136261U; // They implement an FNV-like string hash.
	while ((character = *(cString++)) != '\0')
		result = (result * 16777619) ^ character;
	return (uint32_t)result;
}

std::unique_ptr<Texture> TextureFileIO::Create(const std::string& textureIdentifier, SDL_Renderer* pRenderer)
{
	static std::unordered_map< uint32_t, std::unique_ptr<TextureSaveInfo> > textureCache;

	auto textureID = StringHash(textureIdentifier.c_str());
	auto it = textureCache.find(textureID);
	if (it != textureCache.end())
		return make_unique<Texture>(it->second, pRenderer);

	std::filesystem::path texturePath = kTextureFolder / (textureIdentifier + ".txt");
	std::fstream textureFile;
	textureFile.open(texturePath, std::ios_base::in);
	if (textureFile.is_open() == false || !textureFile.good())
		return nullptr;

	std::string nextLine;
	std::unique_ptr<TextureSaveInfo> saveInfo = std::make_unique<TextureSaveInfo>();
	std::getline(textureFile, nextLine);
	if (nextLine != textureIdentifier)
		return nullptr;

	std::getline(textureFile, nextLine);
	saveInfo->m_imageFilePath = nextLine.c_str();
	textureFile >> saveInfo->m_maxFrameCount;
	textureFile >> saveInfo->m_width;
	textureFile >> saveInfo->m_height;
	textureFile >> saveInfo->m_currentFrame;
	textureFile >> saveInfo->m_scaleMod;

	textureFile.close();
	return std::make_unique<Texture>(saveInfo, pRenderer);
}



