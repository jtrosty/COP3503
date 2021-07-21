#include "TextureManager.h"

// "Redeclare" the variable, so this faile knows it exists and can use it
unordered_map<string, sf::Texture> TextureManager::textures;

void TextureManager::LoadTextures(string fileName) {
	string path = "images/";
	path += fileName + ".png";

	textures[fileName].loadFromFile(path);
}

sf::Texture& TextureManager::GetTexture(string textureName) {
	// If the textrue DOESN'T exist
	if (textures.find(textureName) == textures.end()) // we didn't find it
		LoadTextures(textureName);

	return textures[textureName];
}

void TextureManager::Clear() {
	textures.clear();
}
