
void main()
{
	Engine t;
	sf::sprite sprite = *t.loadTexture("image.png");

	int x =10; //Start position of X
	int y =0; //Start position of y
	int size_x = 15; //Size in Pixels along X
	int size_y = 15; //Size in Pixels along y
	sf::sprite PortionSpriteState = *t.loadTextureRect("image.png", x,y, size_x, size_y);


	sf::SoundBuffer = t.loadSound("Sound/blaster.wav");
}
