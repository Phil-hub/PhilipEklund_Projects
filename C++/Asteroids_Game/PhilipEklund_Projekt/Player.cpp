/*
* By: Philip Eklund
* Course: DT047G
* Date 15 JAN 2021
* PROJECT: ASTEROIDS GAME
*/
#include "Player.h"
Player::Player() : Entity(*loadTexture("Textures/ship.png"),sf::Vector2f(300.f,320.f)), rect(53, 0, 53, 43) //Init the player
{
	setTextureRect(rect); //Set the "animation-state" of player
};
Player::~Player() {}
//Set the movement bools depending on which keys are pressed down.
void Player::MoveUp(bool TF) { mIsMovingUp = TF; }; 
void Player::MoveLeft(bool TF) { mIsMovingLeft = TF; };
void Player::MoveRight(bool TF) { mIsMovingRight = TF; };
void Player::MoveDown(bool TF) { mIsMovingDown = TF; };


void Player::MovePlayer(sf::Time deltaTime) //Get and Apply movement vector
{

	//PLAYER MOVEMENT!

	sf::Vector2f _movement(0.f, 0.f); //Create a vector for movement

	//Depending on which buttons are pressed, the bools are true.
	//Also make sure that we do not go outside the screenspace by limiting the position
	if (mIsMovingUp && getPosition().y > 0)
		_movement.y -= 10.f;
	if (mIsMovingDown && getPosition().y < 400)
		_movement.y += 10.f;
	if (mIsMovingLeft && getPosition().x > 20)
		_movement.x -= 10.f;
	if (mIsMovingRight && getPosition().x < 620)
		_movement.x += 10.f;

	//Move the object depending on above calculated vector * deltaTime
	Move(_movement*30.f * deltaTime.asSeconds());

	//---------------------------------------------------------------------------------------------------------//
	//PLAYER ANIMATION!
	//
	if (_movement.x < 0 && !leftAnim) //If we are moving LEFT and we have not triggered leftanim Bool, change Texture rectangle
	{
		rect.left = 0; //Left sprite pos
		setTextureRect(rect);
		rightAnim = false;
		leftAnim = true;
	}

	else if (_movement.x > 0 && !rightAnim) //If we are moving RIGHT and we have not triggered rightanim Bool, change Texture rectangle
	{
		rect.left = 105; //Right sprite pos
		setTextureRect(rect);
		rightAnim = true;
		leftAnim = false;
	}
	else if (_movement.x == 0 && (rightAnim || leftAnim)) //If we are NEITHER moving left or right and one of their bools are triggered, change Texture rectangle
	{
		rect.left = 53; //Middle sprite pos
		setTextureRect(rect);
		rightAnim = false;
		leftAnim = false;
	}
};

