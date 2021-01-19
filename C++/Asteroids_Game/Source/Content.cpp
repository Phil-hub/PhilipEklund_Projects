/*
* By: Philip Eklund
* Course: DT047G
* Date 15 JAN 2021
* PROJECT: ASTEROIDS GAME
*/
#include "Content.h"


Shot::Shot() : Entity() {} //Default constructor
Shot::Shot(sf::Sprite sprite, sf::Vector2f pos) : Entity(sprite, pos, sf::Vector2f(0.f, -80.f)) {} //regular constructor (set sprite and position, velocity.y = -80)
Shot::~Shot() {}


Asteroid::Asteroid() { } //Default constructor
Asteroid::Asteroid(sf::Sprite sprite) : //Regular constructor
	Entity(sprite, sf::Vector2f(std::rand() % 640, 0.f),				//Create entity with random X position,
		sf::Vector2f(std::rand() % 20 - 10.f, std::rand() % 60 + 20.f),	//random X and Y velocities 
		(std::rand() % 10 - 5.f) / 2)									//Lastly entity have a random rotation
{}
Asteroid::~Asteroid() {}
void Asteroid::Move(sf::Time deltaTime) //Override move function to unclude rotation
{
	Entity::Move(deltaTime); //Do regular move
	Entity::Rotate(); //Also rotate

}


Explosion::Explosion() {} //Default constructor
Explosion::Explosion(sf::Sprite sprite, sf::Vector2f pos, sf::Time time) : //Regular constructor
	Entity(sprite, pos), //Create entity on asteroid's position
	timer(time + sf::seconds(0.4f)), //Set time to live
	rect(60, 0, 60, 60),  //Set the first part of texture animation
	anim(false) //Animation bool
{ 
	setTextureRect(rect);  //Set the part of texture
}
Explosion::~Explosion() {}

bool Explosion::timeToDie(sf::Time time) //Check if we should terminate object after time
{
	if (!anim && time > timer - sf::seconds(0.2f)) //If 0.2 seconds left, change animation
	{
		anim = true; //Animation completed
		rect.left = 0; //New part of texture rectangle
		setTextureRect(rect); //Set the new texture part
	}
	return time > timer; //Time expired, return a termination bool
}



Background::Background()
{
	//Create temporary vector to use as random star selector.
	std::vector<sf::Sprite*> tmp;

	//Load stars and planet textures
	tmp.push_back(loadTextureRect("Textures/stars.png", 0, 0, 9, 9));
	tmp.push_back(loadTextureRect("Textures/stars.png", 8, 1, 7, 7));
	tmp.push_back(loadTextureRect("Textures/stars.png", 15, 0, 9, 9));
	tmp.push_back(loadTextureRect("Textures/stars.png", 26, 3, 3, 3));

	//Create 100 stars and push back into background objects vector
	for (int i = 0; i < 100; i++)
	{
		//Create entity from random star in our vector, random position inside screen width and height, random speed (illusion of depth)
		Entity* ent = new Entity(*tmp[std::rand() % 4], sf::Vector2f(std::rand() % 640, std::rand() % 480), sf::Vector2f(0, std::rand() % 3));
		bgObjects.push_back(*ent);
	}

	//Create the planet in the background
	Entity* ent = new Entity(*loadTexture("Textures/planet.png"), sf::Vector2f(std::rand() % 320 + 160, std::rand() % 240 + 120), sf::Vector2f(0, 1));
	bgObjects.push_back(*ent); //add the planet to our vector
	tmp.~vector();//Destroy the TEMP vector, should be done automatically but better safe than sorry
};
Background::~Background() { bgObjects.~vector(); }
void Background::drawBackground(sf::RenderWindow& window) //Draw all background objects.
{
	for (auto e : bgObjects) //Iterate through and draw all the objects
	{
		window.draw(e.EntityShape());
	}
};
void Background::moveBackground(sf::Time deltaTime)
{
	MoveTransfrom Move(deltaTime); //Create the move function object and initiate deltaTime
	std::transform(bgObjects.begin(), bgObjects.end(), bgObjects.begin(), Move); //Iterate through and move all objects in vector with Move function object
};

Entity Background::MoveTransfrom::operator()(Entity& e)  //Operator() for using in transform function
{
	e.Move(dT); //Use the regular move function in Entity class
	if (e.getPosition().y > 480) //If we end up outside the screen in Y axis
		e.setPosition(e.getPosition().x, -60); //Set position to be slightly above the screen to not make the repetition TO obvious
	return e; //Return the object
}
Background::MoveTransfrom::MoveTransfrom(sf::Time deltaTime) : dT(deltaTime) {} //constructor setting deltatime
