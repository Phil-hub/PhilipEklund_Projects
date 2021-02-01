#include "Engine.h"

sf::Sprite* Engine::loadTexture(std::string path) {
	sf::Texture* texture = new sf::Texture; //Create texture object pointer
	if (!texture->loadFromFile(path)) //Load texture from path
	{
		// Handle loading error
	}
	sf::Sprite* sprite = new sf::Sprite(); //create sprite object pointer
	sprite->setTexture(*texture); //Set the texture of the sprite object
	return sprite; //return sprite pointer
}

//Load JUST a portion of the texture (used for animation or if several objects are found in the same file)

sf::Sprite* Engine::loadTextureRect(std::string path, int x = 0, int y = 0, int size_x = 0, int size_y = 0) {

	sf::Sprite* sprite = loadTexture(path); //Use simple loadTexture function declared above
	if (size_x && size_y) //Double check, if these are 0 just load the whole texture
	{
		sf::IntRect rect(x, y, size_x, size_y); //create a rectangle which contains the desired texture
		sprite->setOrigin(size_x / 2, size_y / 2); //Calculate and set the center of the sprite
		sprite->setTextureRect(rect); //Set the desired part of our texture we want to display
	}
	return sprite; //return sprite pointer
}


sf::SoundBuffer Engine::loadSound(std::string path)
{
	sf::SoundBuffer buffer; //Create a soundbuffer obj pointer
	if (!buffer.loadFromFile(path)) //Load sound from path
	{
	}
	return buffer; //return sound obj pointer
}
