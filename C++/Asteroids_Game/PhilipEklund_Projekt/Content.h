#ifndef CONTENT_H
#define CONTENT_H

/*
* By: Philip Eklund
* Course: DT047G
* Date 15 JAN 2021
* PROJECT: ASTEROIDS GAME
*/

#include "Entity.h"
#include "Engine.h"
/*!
*  
*  \brief     Shot struct derrived from Entity class.
*  \details   Shot struct implement a static velocity upon creation to the Entity class.
*  \author    Philip EKlund
*  \version   1.0
*  \date      2021
*  \copyright GNU Public License. Free to do whatever you want.
*/
struct Shot : Entity
{
	/**
* Default constructor, everything is zero
*/
	Shot();
	/**
	*	Constructor Shots will create an Entity object with a default velocity of -80.f
	* @param sprite, sf::sprite object containing a texture for the object
	* @param position, sf::Vector2f of desired position to spawn the object at
	*
	*/
	Shot(sf::Sprite sprite, sf::Vector2f pos); //Regular constructor
		/**
	* Default destructor
	*/
	~Shot();

};
/*!
*  
*  \brief     Asteroid struct derrived from Entity class.
*  \details   Asteroid struct implement random generator for spawning position, velocity and rotation of entity object.
*  \author    Philip EKlund
*  \version   1.0
*  \date      2021
*  \copyright GNU Public License. Free to do whatever you want.
*/
struct Asteroid : Entity
{
	/**
	* Default constructor, everything is zero
	*/
	Asteroid();
	/**
	*	Constructor Asteroid will create an Entity object with a random velocity  in x and y, also a random rotation.
	* @param sprite, sf::sprite object containing a texture for the object
	*/
	Asteroid(sf::Sprite sprite); //Regular constructor
	/**
	* Default destructor
	*/
	~Asteroid();
	/**
	* \overload 
	* \n OVERRIDE Move function of entity class to include default velocity AND rotation
	* @param deltaTime sf::Time since last time it moved
	*/
	virtual void Move(sf::Time deltaTime) override; //Override Move function
};
/*!
*
*  \brief     Explosion class derrived from Entity.
*  \details   Explosion implement a sprite that animate a sprite and then returns a bool to be "killed".
*  \author    Philip EKlund
*  \version   1.0
*  \date      2021
*  \copyright GNU Public License. Free to do whatever you want.
*/
class Explosion : public Entity
{
public:
	/**
	* Default constructor, everything is zero
	*/
	Explosion();
	/**
	*	Constructor Explosion will create an Entity object at specified position and will die after Time
	* @param sprite, sf::sprite object containing a texture for the object
	* @param position, sf::Vector2f of desired position to spawn the object at
	* @param time, sf::Time time that the object will be alive
	*/
	Explosion(sf::Sprite sprite, sf::Vector2f pos, sf::Time time); //Regular constructor
	/**
	* Default destructor
	*/
	~Explosion();
	/**
	*	time: Check if we are still allowed to live, also change animation state if 0,2 seconds left to live
	* @param time, sf::Time check if current time is greater than the time to live specified at construction
	*/
	bool timeToDie(sf::Time time); //Check if time expired

private:
	sf::IntRect rect; //Texture frame
	bool anim; //Have we changed texture frame?
	sf::Time timer; //Timer to live
};
/*!
*  \brief     Background class using Engine for loading resources.
*  \details   Class is responsible for all the background graphics such as stars and planet and put these Entitys in a std::vector.
*/
class Background : public Engine {

public:

	/**
* Default constructor, load star.png and planet file. create 100 random star objects on random positions on the screen
*  \pre       loads "Textures/stars.png" and "Textures/planet.png" on construction.
*/
	Background();
	/**
* Default destructor, everything is zero
*/
	~Background();
	/**
* drawBackground
* @param window, sf::RenderWindow& the renderwindow. call draw function on all objects in background vector to the input window&.
*/
	void drawBackground(sf::RenderWindow& window); //Draw objects in the background
	/**
	* moveBackground move all the objects in the background using iterator and MoveTransform struct function.
	* @param deltaTime sf::Time since last time it moved
	*/
	void moveBackground(sf::Time deltaTime); //Move objects in the background
	/*!
	*  \brief    MoveTransfrom STRUCT function object used in std::transform to move all objects contained in background vector
	*/
	struct MoveTransfrom //Transform object function for std::tranform
	{
		/**
		* MoveTransfrom constructor set the dT variable at construction.
		* @param deltaTime, sf::Time since last time objects were moved.
		*/
		MoveTransfrom(sf::Time deltatime); //Constructor
		/**
		* operator function used in std::tranfsorm on all objects in vector
		* @param e, Entity& of object to be transformed.
		* @return transformed Entity object
		*/
		Entity operator()(Entity& e); //Function used by transfrom
		/**
		* Deltatime set at construction of struct, this will be used in the Entity::Move(sf::Time deltatime) function.
		*/
		sf::Time dT; //Delta time parameter
	};

private:
	std::vector<Entity> bgObjects; //Vector with the backgroun objects.
};

#endif