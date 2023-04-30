#include <SFML/Graphics.hpp>
#include "Ball.h"
#include "Player.h"
#include "Brick.h"
#include <deque>
#include <iostream>

double mapValue(double x, double a, double b, double c, double d) {
	double y = (x - a) / (b - a) * (d - c) + c;
	return y;
}

// Interpolation linéaire entre deux couleurs
sf::Color lerp(sf::Color color1, sf::Color color2, float t)
{
	int r = static_cast<int>(color1.r + t * (color2.r - color1.r));
	int g = static_cast<int>(color1.g + t * (color2.g - color1.g));
	int b = static_cast<int>(color1.b + t * (color2.b - color1.b));
	return sf::Color(r, g, b);
}

int main(int argc, char** argv)
{
	Ball ball(200, 250, 10, 600);
	Player player(500, 100, 10);

	std::deque<Brick*> bricks;

	int brickWidth = 80;
	int brickHeight = 35;

	int numRows = 5;
	int numCols = 8;

	// Calcul de la position du coin supérieur gauche du premier bloc
	int startX = (800 - numCols * brickWidth) / 2;
	int startY = 100;

	for (int i = 0; i < numRows; i++) {
		for (int j = 0; j < numCols; j++) {
			int x = startX + j * brickWidth;
			int y = startY + i * brickHeight;
			bricks.push_back(new Brick(x, y, brickWidth, brickHeight, 3));
		}
	}

	sf::RenderWindow window(sf::VideoMode(800, 600), "ma magnifique fenetre");

	sf::RectangleShape rdr2;
	rdr2.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));

	sf::Clock clock;
	float ellapsedTime = 0;


	while (window.isOpen())
	{
		ellapsedTime = clock.restart().asSeconds();

		
		sf::Event event;
		while (window.pollEvent(event))
		{
			
			if (event.type == sf::Event::Closed)
				window.close();
		}

		ball.move(ellapsedTime);

		ball.manageCollisionWith(player, window);

		window.clear();

		for (int i = 0; i < window.getSize().y; i++)
		{
			double mappedValue = mapValue(i, 0, window.getSize().y, 0, 1);
			sf::Color color1(255, 0, 0);
			sf::Color color2(0, 255, 0);
			sf::Color color = lerp(color1, color2, mappedValue);
			rdr2.setFillColor(color);
			rdr2.setPosition(0, i);
			window.draw(rdr2);
		}

		ball.draw(window);
		player.draw(window);

		// Dessin des briques
		for (int i = 0; i < bricks.size(); i++)
		{
			bricks[i]->draw(window);
		}

		window.display();
	}

	return 0;
}
