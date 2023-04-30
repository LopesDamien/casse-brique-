#pragma once
#include <SFML/Graphics.hpp>
#include <deque>


class Brick
{
private:
	sf::RectangleShape shape;
	sf::Vector2f position;
	sf::Vector2f size;
	int health;

	sf::Vector2f generateRandomPosition(sf::Vector2f screenDimensions)
	{
		int x = rand() % static_cast<int>(screenDimensions.x - size.x);
		int y = rand() % static_cast<int>(screenDimensions.y / 2);
		return sf::Vector2f(x, y);
	}

public:
	Brick(int x, int y, int width, int height, int health);
	~Brick();
	void draw(sf::RenderWindow& window);
	sf::Color getColorFromLife();
	bool isAlive();
	void hit();
	sf::Vector2f getPosition();
	sf::Vector2f getSize();
};
