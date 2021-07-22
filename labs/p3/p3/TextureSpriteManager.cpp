#include "TextureSpriteManager.h"

/***********************************************************************
****************** Texture Manger Class Definition *********************
************************************************************************/

// "Redeclare" the variable, so this faile knows it exists and can use it
unordered_map<string, sf::Texture> TextureSpriteManager::textures;
unordered_map<string, sf::Sprite> TextureSpriteManager::sprites;


void TextureSpriteManager::LoadAllTextures() {
   string listFileNames[] = {  "mine",       "tile_hidden", "tile_revealed", 
                               "number_1",   "number_2",    "number_3", 
                               "number_4",   "number_5",    "number_6", 
                               "number_7",   "number_8",    "flag", 
                               "face_happy", "face_win",    "face_lose", 
                               "digits",     "debug",       "test_1", 
                               "test_2",     "test_3" };
   int size = 20;

   for (int i = 0; i < size; i++) {
	   TextureSpriteManager::GetSprite(listFileNames[i]);
   }
}

void TextureSpriteManager::LoadTextures(string fileName) {
	string path = "images/";
	path += fileName + ".png";

	textures[fileName].loadFromFile(path);
}

sf::Texture& TextureSpriteManager::GetTexture(string textureName) {
	// If the textrue DOESN'T exist
	if (textures.find(textureName) == textures.end()) // we didn't find it
		LoadTextures(textureName);

	return textures[textureName];
}

/***********************************************************************
****************** Sprite Section **************************************
************************************************************************/

sf::Sprite& TextureSpriteManager::GetSprite(string spriteName) {
	// If the textrue DOESN'T exist
	if (sprites.find(spriteName) == sprites.end()) // we didn't find it
		sprites[spriteName].setTexture(TextureSpriteManager::GetTexture(spriteName));

	return sprites[spriteName];
}

/// <summary>
/// Clear
/// </summary>

void TextureSpriteManager::Clear() {
	textures.clear();
	sprites.clear();
}
