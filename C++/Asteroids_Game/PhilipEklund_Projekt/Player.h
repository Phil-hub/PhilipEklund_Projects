#ifndef PLAYER_H
#define PLAYER_H
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
*  \brief     Player class derived from Entity using Engine to load texture file.
*  \details   This is the player handling movement inputs and animation state.
*  \author    Philip EKlund
*  \version   1.0
*  \date      2021
*  \pre       Uses the file "Textures/ship.png", start position set at default to 300 ,320
*  \copyright GNU Public License. Free to do whatever you want.
*/
class Player : public Entity, Engine
{
public:
	/**
	*	Default constructor for player,
	*	Default position: sf::Vector2f(300.f,320.f))
	*	Default texture rectangle: rect(53, 0, 53, 43)
	*/
	Player(); //Init the player
	/**
	*	Default destructor
	*/
	~Player(); //Init the player
	/**
	* MoveUp
	* @param TF, True/false set if we are trying to move up.
	*/
	void MoveUp(bool TF);		//Key pressed?
		/**
	* MoveLeft
	* @param TF, True/false set if we are trying to move Left.
	*/
	void MoveLeft(bool TF);		//Key pressed?
		/**
	* MoveRight
	* @param TF, True/false set if we are trying to move Right.
	*/
	void MoveRight(bool TF);	//Key pressed?	
	/**
	*MoveDown
	* @param TF, True / false set if we are trying to move Down.
	*/
	void MoveDown(bool TF);		//Key pressed?

	/**
	* MovePlayer
	* @param deltaTime sf::Time since last time we moved the player.
	* Calculate movement depending on movement bools
	*/

	void MovePlayer(sf::Time deltaTime); //Get and Apply movement vector
private:

	sf::IntRect rect; //SPRITE texture rectangle

	bool leftAnim = false;		//ANIMATION
	bool rightAnim = false;		//ANIMATION

	bool mIsMovingUp = false;		//MOVEMENT
	bool mIsMovingDown = false;		//MOVEMENT
	bool mIsMovingLeft = false;		//MOVEMENT
	bool mIsMovingRight = false;	//MOVEMENT
};
/*!
*\example Example_Player.cpp
*/
#endif