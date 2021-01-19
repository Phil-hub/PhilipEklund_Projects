/*
* By: Philip Eklund
* Course: DT047G
* Date 15 JAN 2021
* PROJECT: ASTEROIDS GAME
*/
#include "Entity.h"


Entity::Entity() : Shape(), Velocity(0.f, 0.f), rotation(0.f) {}; //Default constructor set everything to 0
Entity::Entity(sf::Sprite sprite, sf::Vector2f position) : Shape(sprite), Velocity(0.f, 0.f), rotation(0.f) { Shape.setPosition(position); } //Position constructor, set everything else to 0
Entity::Entity(sf::Sprite sprite, sf::Vector2f position, sf::Vector2f vel, float rot) : Shape(sprite), Velocity(vel), rotation(rot) { Shape.setPosition(position); } //Full constructor, set all parameters (rotation = 0 by default)
Entity::~Entity() {}

//MOVEMENT
void Entity::Move(sf::Time deltaTime) { Move(Velocity*5.f * deltaTime.asSeconds()); } //Move function: create a 2vector based on standard velocity and time, call other move function
void Entity::Move(sf::Vector2f movement) { Shape.move(movement); }; //Move the object
void Entity::Rotate() { Shape.rotate(rotation); }//Rotate object
void Entity::Rotate(float rot) { Shape.rotate(rot); }//Rotate object
void Entity::setPosition(float x, float y) {	Shape.setPosition(x,y);	}//Set Position

//TEXTURE
void Entity::setTexture(sf::Texture* texture){ 	Shape.setTexture(*texture);} //Set texture
void Entity::setTextureRect(sf::IntRect rect) { Shape.setTextureRect(rect); } //Set portion of texture

//PROPERTIES (GET)
sf::FloatRect Entity::Boundary() const { return Shape.getGlobalBounds(); } //Return boundary of object (x, y, size x, size y)
sf::Sprite Entity::EntityShape() const { return Shape; } //Return the sprite object
sf::Vector2f Entity::getPosition() const{	return Shape.getPosition();	};//Return the position of object