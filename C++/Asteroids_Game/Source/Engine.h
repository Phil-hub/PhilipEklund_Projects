#ifndef ENGINE_H
#define ENGINE_H

/*! \mainpage Asteroid Game Implementation
* By: Philip Eklund
* Course: DT047G
* Date 15 JAN 2021
* PROJECT: ASTEROIDS GAME
* \section intro_sec Introduction
*
* This is the documentation for my project Asteroids game.
*
* \section install_sec Installation
*
* \subsection step1 Step 1: Download the project.
* It is easiest to use the visual studio project file included
* \subsection step2 Step 2: Make sure the project is set up in Release mode NOT debug.
* This is due to dll file settings
* \subsection step3 Step 3: Make sure dll files are setup in preferences (follow SFML tutorial if you need help with this)
* If you create a new project in desired code compiler
* \subsection step4 Step 4: Enjoy!
* feel free to tweak the parameters like asteroid/player speed and asteroid spawntime to increase/decrease difficulty
*
*/
/*!
*  \namespace sf
*  \brief     This is the namespace widely used in all classes.
*  \details   It is derived from the SFML library used for rendering, textures, sounds and geometrical information.
*/


#include "Entity.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

/*!
*
*  \brief     Engine class, Used for loading resources such as textures and sounds.
*  \details   Load texture files to sf::sprite pointers or sounds to sf::SoundBuffers.
*  \warning   MUST USE PROJECT IN RELEASE MODE FOR TEXTURES TO LOAD.
*/
struct Engine {

	/*!
	* Load JUST a portion of the texture
	* @param path is the path to a texture file
	* @param x is the X coordinate pixel from left to start the image
	* @param y is the Y coordinate pixel from top to start the image
	* @param size_x is the amount of pixels in X axis desired
	* @param size_y is the amount of pixels in Y axis desired
	* @return return a sf::sprite pointer
	*/
	sf::Sprite* loadTextureRect(std::string path, int x, int y, int size_x, int size_y); //Load a portion of the texture
	/*!
	* Load texture from file
	* @param path is the path to a texture file
	* @return return a sf::sprite pointer
	*/
	sf::Sprite* loadTexture(std::string path); //Load entire texture
	/**
	* Load sound function
	* @param path is the path to a wav file
	* @return return a sf::soundBuffer
	*/
	sf::SoundBuffer loadSound(std::string path); //Load sound

};
/*!
*\example Example_engine.cpp
*/
#endif