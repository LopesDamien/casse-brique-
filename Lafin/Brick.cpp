#include "Brick.h"

Brick::Brick(int x, int y, int width, int height, int health) :
	position(sf::Vector2f(x, y)), size(sf::Vector2f(width, height)), health(health)
{
	// Création de la forme rectangulaire représentant la brique
	shape = sf::RectangleShape(size);
	shape.setOutlineThickness(2);
	shape.setOutlineColor(sf::Color::Black);
	shape.setPosition(position);
	shape.setFillColor(getColorFromLife());
}

Brick::~Brick()
{
	
}

void Brick::draw(sf::RenderWindow& window)
{
	// Dessine la brique si celle-ci est "en vie"
	if (isAlive()) {
		window.draw(shape);
	}
}

sf::Color Brick::getColorFromLife()
{
	// Renvoie la couleur de la brique en fonction de sa vie mais marche pas 
	switch (health) {
	case 1:
		return sf::Color::Red;
	case 2:
		return sf::Color::Yellow;
	case 3:
		return sf::Color::Green;
	default:
		return sf::Color::White;
	}
}

bool Brick::isAlive()
{
	
	return health > 0;
}

void Brick::hit()
{
	// Méthode à appeler lorsque la brique est touchée
	//Enleve 1 de vie
	//marchhe pas !! 
	health--;
	shape.setFillColor(getColorFromLife());
}

sf::Vector2f Brick::getPosition()
{
	
	return position;
}

sf::Vector2f Brick::getSize()
{

	return size;
}