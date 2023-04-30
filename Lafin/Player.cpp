#include "Player.h"
#include <cmath>

Player::Player(int y, int width, int height) : y(y) {
	position = sf::Vector2f(0, y);
	size = sf::Vector2f(width, height);

	// création de la forme de la plateforme
	shape.setPointCount(4);
	shape.setPoint(0, sf::Vector2f(0, 0));
	shape.setPoint(1, sf::Vector2f(size.x, 0));
	shape.setPoint(2, sf::Vector2f(size.x * 0.75, size.y));
	shape.setPoint(3, sf::Vector2f(size.x * 0.25, size.y));
	shape.setFillColor(sf::Color(255, 205, 0)); // couleur orignal
	shape.setPosition(position);
}

Player::~Player() {}

void Player::draw(sf::RenderWindow& window) {
	// déplacement de la plateforme en fonction de la position de la souris
	position.x = sf::Mouse::getPosition(window).x - size.x / 2;
	shape.setPosition(position);

	window.draw(shape);
}

sf::Vector2f Player::getPosition() {
	return position;
}

sf::Vector2f Player::getSize() {
	return size;
}
