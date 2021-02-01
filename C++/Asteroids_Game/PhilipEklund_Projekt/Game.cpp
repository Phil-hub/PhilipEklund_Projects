/*
* By: Philip Eklund
* Course: DT047G
* Date 15 JAN 2021
* PROJECT: ASTEROIDS GAME
*/
#include "Game.h"
#include <iostream>
#include <algorithm>
//#include "Entity.h"





Game::Game() //Default Constructor
	: mWindow(sf::VideoMode(640, 480), "SFML Application"), //Init new window
	score_i(0),  //Init score
	bg(),//, //Init background object
	player(), //Init player
	blaster(loadSound("Sound/blaster.wav")), //Load sound
	explosion(loadSound("Sound/explosion.wav")), //Load sound
	sprites(),		//INIT THE LISTS
	asteroids(),	//INIT THE LISTS
	shots(),		//INIT THE LISTS
	score(),//Init score text obj
	timer(sf::Time::Zero), //Init timer
	nextFireTime(sf::Time::Zero), //Init time since last fire obj
	asteroidSpawnTimer(sf::seconds(1.f)), //Init asteroid spawn timer
	sound(), //Init sound object
	font(), //Init font obj
	alive(true)
{
	//LOAD SPRITE PRESETS FOR ASTEROIDS, SHOT & EXPLOSION
	sprites.push_back(loadTextureRect("Textures/asteroids.png", 0, 0, 38, 40));
	sprites.push_back(loadTextureRect("Textures/asteroids.png", 38, 0, 32, 40));
	sprites.push_back(loadTextureRect("Textures/asteroids.png", 70, 0, 30, 38));
	sprites.push_back(loadTextureRect("Textures/asteroids.png", 69, 47, 28, 30));
	sprites.push_back(loadTextureRect("Textures/asteroids.png", 0, 38, 45, 42));
	sprites.push_back(loadTexture("Textures/shot.png"));
	sprites.push_back(loadTexture("Textures/explosion.png"));
	sprites.back()->setOrigin(30, 30); //Set center of origin of explosion sprite

	font.loadFromFile("font.ttf");							//Load the font file
	score.setFont(font);									//Set font to score obj
	score.setCharacterSize(42);								//Set font size
	score.setFillColor(sf::Color::Red);						//Set font color
	score.setPosition(50.f, 20.f);						//Set text position
	score.setString("Score: " + std::to_string(score_i));	//Set the Score text

}

Game::~Game() { //call destructors of all custom class objects
	shots.~ObjectList();
	asteroids.~ObjectList();
	sprites.~ObjectList();
	explosions.~ObjectList();
	player.~player();
	bg.~Background();
}

void Game::run() //RUN THE GAME
{
	
	sf::Clock clock; //Load clock
	sf::Time timeAtNextUpdate = sf::Time::Zero; //Create a timestamp for next update (Frames per second limiter) (sf::seconds(1.f / 60.f) = 60FPS)

	
	while (mWindow.isOpen()) //Simple while loop, when window is being closed in Process, later exit the while loop
	{

		timer += clock.restart(); //Count up the time since last update and restart the clock

		while (timeAtNextUpdate < timer ) //If timestamp for next update is bigger than, we check for events and update the state
		{
			timeAtNextUpdate += sf::seconds(1.f / 60.f);	//SET next timestamp to be 1/60 seconds later

			processEvents();								//Check for events such as key pressed etc

			if(alive)
				update(sf::seconds(1.f / 60.f));				//Run update (sf::seconds(1.f / 60.f) = 60FPS it's been 1/60 of seconds)
		}
		render(); //Render new image
		
	}


}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed) //Handle player keyboard inputs.
{
	switch (key) //Check which key is being pressed and set the bool (true = pressed, false = released)
	{
	case sf::Keyboard::Key::Up :
		player.MoveUp(isPressed);
		break;
	case sf::Keyboard::Key::Down:
		player.MoveDown(isPressed);
		break;
	case sf::Keyboard::Key::Left:
		player.MoveLeft(isPressed);
		break;
	case sf::Keyboard::Key::Right:
		player.MoveRight(isPressed);
		break;
	case sf::Keyboard::Key::Space:
		fire(isPressed);
		if (!alive)
			Restart();
		break;
	}
}

void Game::processEvents() { //Process keypresses and releases

	sf::Event event;

	while (mWindow.pollEvent(event))
	{
		switch (event.type) //We have an event queued, check type
		{
		case sf::Event::KeyPressed: //Key pressed, send to input function
			handlePlayerInput(event.key.code, true);
			break;
		case sf::Event::KeyReleased: //Key is released, send to input function
			handlePlayerInput(event.key.code, false);
			break;
		case sf::Event::Closed: //Close event called, close window (X / Alt+F4)
			mWindow.close();

		}
	}
}
void Game::update(sf::Time deltaTime) { //UPDATE GAME STATE
	player.MovePlayer(deltaTime); //MOVE THE PLAYER
	bg.moveBackground(deltaTime); //MOVE THE BACKGROUND

	for(int i=0;i<asteroids.size(); i++) //MOVE ALL ASTEROIDS
	{
		asteroids[i].Move(deltaTime);
	}
	for (int i = 0; i < shots.size(); i++) // MOVE ALL SHOTS
	{
		shots[i].Move(deltaTime);
	}
	collisionDetection(); //CHECK FOR COLLISIONS

	if (asteroidSpawnTimer < timer) //TIME TO SPAWN ASTEROID?
	{
		asteroidSpawnTimer = timer + sf::seconds(std::rand() %10 / 5.f); //Set new random timestamp for spawning the next asteroid
		spawnAsteroid(); //Spawn asteroid
	}


	
}
void Game::spawnAsteroid() //Spawn asteroid
{
	Asteroid as(*sprites[rand() %5]); //Create asteroid obj
	asteroids.push_back(as); //Push object into asteroid list
}
void Game::render()
{


	mWindow.clear();//Clear last frame/image
	bg.drawBackground(mWindow); //DRAW Background objects
	
	mWindow.draw(player.EntityShape()); //Draw the player
	

	for (int i = 0; i < asteroids.size(); i++)
		mWindow.draw(asteroids[i].EntityShape()); //Draw all asteroids
	for (int i = 0; i < shots.size(); i++)
		mWindow.draw(shots.at(i).EntityShape()); //Draw all shots

	int size = explosions.size();

	for (int i = 0; i < size; i++)//Draw all explosions
	{		
		if (!explosions[i].timeToDie(timer)) //Check if it should still exists
			mWindow.draw(explosions[i].EntityShape()); 
		else // object is supposed to expire, remove it!
		{
			explosions.remove(i);
			i--;	//Decrease i and size
			size--;
		}
	}

	mWindow.draw(score);//Draw Score object

	mWindow.display(); //Display the new image
}

void Game::collisionDetection() //COLLISION DETECTION
{
	if (!asteroids.isEmpty())
	{	

		for(int i=0;i<asteroids.size();i++)
		{
			//IF outside of bounds, remove the asteroid
			if (asteroids[i].getPosition().x < -20.f || asteroids[i].getPosition().y < 0.f || asteroids[i].getPosition().x > 680.f) 
			{
				asteroids.remove(i);
				return; 
			}
			//IF asteroid collide with player, Game over!
			if (asteroids[i].Boundary().intersects(player.Boundary()))
			{
				GameOver();
				return;
			}
			
			for(int j = 0;j<shots.size();j++)
			{
				//IF Shot is outside screen bounds, remove
				if (shots[j].getPosition().x < -20.f || shots[j].getPosition().y < 0.f || shots[j].getPosition().x > 680.f)
				{
					shots.remove(j);
					return;
				}
				
				//IF shot and asteroid collide, create explosion and remove shot & asteroid
				if (asteroids[i].Boundary().intersects(shots[j].Boundary()))
				{
					//Give Score, remove shot and asteroid
					Explosion e(*sprites[6], asteroids[i].getPosition(), timer); //Create explosion at asteroid position
					asteroids.remove(i); // aremove asteroid
					shots.remove(j); //remove shot
					score_i += 8; //Add score
					score.setString("Score: " + std::to_string(score_i)); //Set new score string
					
					explosions.push_back(e); //Push explosion into list

					sound.setBuffer(explosion); //Play explosion sound
					sound.play();
					return;
				}
			}
		}
	}
}

void Game::fire(bool firing)//Firing module
{
	if (firing && nextFireTime < timer) //IF "SPACEBAR" is pressed (firing = true) AND timer for next fire is less than timer, fire the blaster!
	{
		nextFireTime =timer + sf::seconds(.2f); //Set timestamp for next possible fire

		sf::Vector2f position(player.getPosition().x+15, player.getPosition().y-5); //Get the position of player and offset to middle position

		Shot s(*sprites[5],position); //Create a blaster entity from the sprite assets list at position
		shots.push_back(s); //Push this shot into the list of shots
		sound.setBuffer(blaster); //Play sound
		sound.play();
	}
}

void Game::GameOver() {// GAME OVER SCREEN
	alive = false;  //We are not alive
	score.setCharacterSize(72); //INCREASE SIZE OF TEXT
	score.setString("GAME OVER\n YOUR SCORE WAS: " + std::to_string(score_i)+"\n\n press SPACE to restart"); //GAME OVER TEXT
}
void Game::Restart() //RESTART GAME FUNCTION
{
	alive = true; //set alive to true and reset score
	score_i = 0;
	score.setCharacterSize(36); //Reset text size and string
	score.setString("Score: " + std::to_string(score_i));

	while (!asteroids.isEmpty()) //Empty all asteroids and shots
		asteroids.pop_front();
	while (!shots.isEmpty())
		shots.pop_front();

	player.setPosition(300.f, 320.f); //Reset player position
}