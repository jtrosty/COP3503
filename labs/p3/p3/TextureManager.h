#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
using std::unordered_map;
using std::string;

class TextureManager {
	// Static == one and only one of these in memory ever
	static unordered_map<string, sf::Texture> textures;
	static void LoadTextures(string textureName);
public:
	static sf::Texture& GetTexture(string textrueName);
	static void Clear(); // Call this once, at the end of main()
};
