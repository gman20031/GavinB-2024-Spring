#include "TextureFileIO.h"

#include <fstream>
#include <assert.h>
#include "../System/StringHash.h"

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


std::unique_ptr<Texture> TextureFileIO::NewCreate(const std::string& textureIdentifier, SDL_Renderer* pRenderer)
{
	static std::unordered_map< uint32_t, SDL_Texture*> sdlTextureCache;

	//check if cached
	auto textureID = StringHash(textureIdentifier.c_str());
	auto it = sdlTextureCache.find(textureID);
	if (it != sdlTextureCache.end())
		return std::make_unique<Texture>(it->second, pRenderer);


}

std::unique_ptr<Texture> TextureFileIO::Create(const std::string& textureIdentifier, SDL_Renderer* pRenderer)
{
	static std::unordered_map< uint32_t, std::unique_ptr<TextureSaveInfo> > textureCache;
	
	//check if cached
	auto textureID = StringHash(textureIdentifier.c_str());
	auto it = textureCache.find(textureID);
	if (it != textureCache.end())
		return std::make_unique<Texture>(it->second, pRenderer);

	//find and read file
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
	saveInfo->m_imageFilePath = nextLine;
	textureFile >> saveInfo->m_maxFrameCount;
	textureFile >> saveInfo->m_width;
	textureFile >> saveInfo->m_height;
	textureFile >> saveInfo->m_currentFrame;
	int mode;
	textureFile >> mode;
	saveInfo->m_scaleMode = (SDL_ScaleMode)mode;

	textureFile.close();

	textureCache.emplace(textureID , std::move(saveInfo) );

	return std::make_unique<Texture>( textureCache.at(textureID), pRenderer);
}



