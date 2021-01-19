#include "../Entity.h"
void main()
{
	//Create entity with sprite and position.
	Entity ent(sf::Sprite(),sf::Vector2f(150.f,75.f));

	//Load and set texture to entity
	sf::Texture* texture;
	texture->loadFromFile("image.png");
	ent.setTexture(texture);

	//Set specific area of texture to be displayed, x,y,size_x,size_y
	ent.setTextureRect(sf::IntRect(0, 0, 15, 15));

	//Move entety by 10 in X axis.
	ent.Move(sf::Vector2f(10, 0));

	//Rotate the entity by 2.
	ent.Rotate(2.f);

	//Get the position of entity
	sf::Vector2f position = ent.getPosition();

	//To draw the entity, use sf::RenderWindow.draw(sf::sprite) function
	sf::RenderWindow RWindow;
	RWindow.draw(ent.EntityShape());
}