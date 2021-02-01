#ifndef GAME_H
#define GAME_H
/*
* By: Philip Eklund
* Course: DT047G
* Date 15 JAN 2021
* PROJECT: ASTEROIDS GAME
*/
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <SFML/Audio.hpp>

#include "ObjectList.hpp"

#include "Player.h"
#include "Content.h"


/*!
*  
*  \brief     Game class, using Engine for loading resuorces. This is the actual game controller class.
*  \details   Class that controls the game with frame updates and user inputs.
*  \author    Philip EKlund
*  \version   1.0
*  \date      2021
*  \pre       Default constructor uses: \n Textures/asteroids.png \n Textures/explosion.png \n Textures/shot.png \n font.ttf 
*  \n Sound/blaster.wav \n Sound/explosion.wav
*  \warning   Improper use can crash your application!
*  \copyright GNU Public License. Free to do whatever you want.
*/
class Game : public Engine
{
public:	
	/**
* Default constructor
* Default window size is 640 x 400 pixels
*/
	Game(); //Default constructor
	/**
* Default destructor
*/
	~Game();
	/**
* Run the game
*/
	void run(); //Run Game
		/**
* Game over
*/
	void GameOver();
	/**
* Reset to start
*/
	void Restart();


	/**
* Spawn an asteroid game object
*/
	void spawnAsteroid(); //Spawn asteroid
	/**
* handlePlayerInput Set bool of the key to true/false (Pressed, Released)
* @param key is a sf::keyboard::key input
* @param bool if it is pressed or not
*/
	void handlePlayerInput(sf::Keyboard::Key key, bool isPressed); //Keyboard inputs

	/**
* processEvents process keyboard events from sf::Events
* @param key is a sf::keyboard::key input
* @param bool if it is pressed or not
*/
	void processEvents(); //Process the events 
	/**
	*Update runs every frame, update the gamestate depending on if deltaTime is greater than desired FPS output
	* @param deltaTime is a sf::Time of the time elapsed since last update
	*/
	void update(sf::Time delstaTime); //Update game state (deltatime = time since last update)
	/**
	* Render clear last frame window and draw all objects contained in the game to a new frame.
	* 
	*/
	void render(); //Render game
	/**
	* CollisionDetection run an collision detection algorithm between all asteroids player and shots.
	*
	*/
	void collisionDetection(); //Do collision detection
		/**
	* fire 
	* @param bool if we are trying to fire the blasters
	*/
	void fire(bool); //Fire control

private:
	Player player; //Player object
	Background bg; //Background class
	sf::RenderWindow mWindow; //Render window
	ObjectList<Asteroid> asteroids; //List of all Asteroids
	ObjectList<Shot> shots; //List of all shots
	ObjectList<Explosion> explosions; //List of all explosions
	ObjectList<sf::Sprite*> sprites; //List of standard sprite assets
	sf::Text score; //Score text

	bool alive;

	sf::Font font;
	int score_i; //Score value

	sf::Time timer; //Time game have been running
	sf::Time nextFireTime; //Time since last fire
	sf::Time asteroidSpawnTimer; //Time when next asteroid spawns

	sf::SoundBuffer blaster; //Blaster sound
	sf::SoundBuffer explosion; //Explosion sound
	sf::Sound sound; //Sound object
};
#endif