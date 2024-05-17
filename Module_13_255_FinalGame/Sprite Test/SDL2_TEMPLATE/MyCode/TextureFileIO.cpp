#include "TextureFileIO.h"

#include <fstream>
#include <assert.h>


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

Texture& TextureFileIO::Save(const Texture& texture, const std::string& textureIdentifier)
{
	std::filesystem::path texturePath = (kTextureFolder / (textureIdentifier + kFileExtension) );
	std::fstream textureFile(texturePath);
	assert(textureFile.is_open());


}


std::unique_ptr<Texture> TextureFileIO::Create(const std::string& textureIdentifier)
{
    return Texture_ptr();
}
