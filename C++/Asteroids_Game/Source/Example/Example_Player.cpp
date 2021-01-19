#include "../Player.h"
void main()
{
	//Create default player
	Player player;

	//Tell player to move down
	player.MoveDown(true);

	//Tell player to also move left
	//This will AUTOMATICALLY CHANGE TEXTURE RECT to left(0,0,53,43) in PLAYER object
	player.MoveLeft(true);

	//Player will no longer move left, texture will reset to (53,0,53,43)
	player.MoveLeft(false);

	//Tell player to also move right
	//This will AUTOMATICALLY CHANGE TEXTURE RECT to right(105,0,53,43) in PLAYER object
	player.MoveRight(true);

	//Make the movement, time since last update was 0.05 seconds (Down + Right)
	player.MovePlayer(sf::seconds(0.05));
}