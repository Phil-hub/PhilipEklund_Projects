#ifndef ENTITY_H
#define ENTITY_H
/*
* By: Philip Eklund
* Course: DT047G
* Date 15 JAN 2021
* PROJECT: ASTEROIDS GAME
*/
#include <SFML/Graphics.hpp>
/*!
*
*  \brief     Entity class, This is the basic class for all objects on the screen.
*  \details   This class is used for all objects displayed on the screen that use some kind of movement or collision detection.
*  \author    Philip EKlund
*  \version   1.0
*  \date      2021
*  \pre       If you want a constant speed/rotation on the object (like an asteroid) set velocity and rotation at construction of object.
*  \warning   Improper use can crash your application!
*  \copyright GNU Public License. Free to do whatever you want.
*/
class Entity
{
public:

	/**
* Default constructor, everything is empty/zero
*
*/
	Entity(); //Default constructor
		/**
* Constructor
* @param sprite, sf::sprite object containing a texture for the object
* @param position, sf::Vector2f of desired position to spawn the object at
*/ 
	Entity(sf::Sprite sprite, sf::Vector2f position); //constructor with sprite and position only
	/**
	*Constructor
	* @param sprite, sf::sprite object containing a texture for the object
	* @param position, sf::Vector2f of desired position to spawn the object at
	* @param vel, sf::Vector2f of static velocity of the object (constant speed)
	* @param rot, float of constant rotation of the object, default set to 0
	*/
	Entity(sf::Sprite sprite, sf::Vector2f position, sf::Vector2f vel, float rot = 0); //Constructor with all parameters
		/**
* Default destructor
*/
	~Entity();

	/**
	* Move move object with default velocity
	* @param deltaTime sf::Time since last time it moved
	*/
	virtual void Move(sf::Time deltaTime); //Move by deltatime

	/**
	* Move move object with custom vector
	* @param movement sf::Vector2f of desired custom movement
	*/
	virtual void Move(sf::Vector2f movement); //Move by movement
	/**
	* Rotate rotate the object with constant rotation
	*/
	virtual void Rotate(); //Rotate
	/**
	* Rotate rotate the object with custom rotation
	* @param rot float of desired rotation
	*/
	virtual void Rotate(float rot); //Rotate
	/**
	* setPosition set the desired position of the entity
	* @param X position on the screen
	* @param Y position on the screen
	*/
	void setPosition(float x, float y); //Set position

	/**
	* setTexture set the desired position of the entity
	* @param texture sf::Texture pointer to a texture object to set the texture to
	*/
	void setTexture(sf::Texture* texture); //Set texture
	/**
	* setTextureRect set the desired area of the texture to display, normally for animation purposes
	* @param rect sf::IntRect containing pixel position and size of x, y for the area to display
	*/
	void setTextureRect(sf::IntRect rect); //Set portion of texture
	/**
	* Return boundary of object(x, y, x size, y size)
	* @return sf::FloatRect rectangle of the boundary position and rotation of the object, used for collision detection
	*/
	sf::FloatRect Boundary() const; //Return boundary of object(x, y, x size, y size)
	/**
	* Return the sprite object
	* @return sf::Sprite object, mainly used for rendering ( window.draw(sf::sprite) function).
	*/
	sf::Sprite EntityShape() const; //Return the sprite object
	/**
	* Return the x and y position of the object
	* @return sf::Vector2f of the position of object
	*/
	sf::Vector2f getPosition() const; //Return the position of sprite object (x,y)

private:
	sf::Sprite Shape;
	sf::Vector2f Velocity;
	float rotation;


};
/*!
*\example Example_Entity.cpp
*/
#endif