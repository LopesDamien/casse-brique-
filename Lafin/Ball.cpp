#include "Ball.h"
#include "Player.h"

bool Ball::isRandInitialized = false;

Ball::Ball(int x, int y, int radius, float speed)
{
	position.x = x;
	position.y = y;
	oldPosition = position;
	shape.setFillColor(sf::Color(sf::Color::White));
	this->radius = radius;
	shape.setRadius(radius);
	this->speed = speed;

	setAngle(randomizeAngle());
}

Ball::~Ball()
{
}

double Ball::randomizeAngle()
{
	if (!isRandInitialized) {
		srand(time(NULL));
		isRandInitialized = true;
	}

	return (((double)rand() / (double)RAND_MAX) * 60.0) - 30.0;
}

void Ball::setAngle(double angle)
{
	direction.x = sin(angle);
	direction.y = -cos(angle);
}

void Ball::move(float ellapsedTime)
{
	position += ellapsedTime * speed * direction;
}

void Ball::draw(sf::RenderWindow& window)
{
	shape.setPosition(position);
	window.draw(shape);
}

float Ball::getSpeed()
{
	return speed;
}

void Ball::setSpeed(float newSpeed)
{
	speed = newSpeed;
}

void Ball::setPosition(sf::Vector2f newPosition)
{
	position = newPosition;
	oldPosition = position;
}

sf::Vector2f Ball::getPosition()
{
	return position;
}

void Ball::setDirection(sf::Vector2f newDirection)
{
	direction = newDirection;
}

void Ball::update(float deltaTime, Player& player, sf::RenderWindow& window)
{
	position += direction * speed * deltaTime;
	shape.setPosition(position);

	manageCollisionWith(player, window);

	// réinitialise sa position di la balle reste collé au joueur 
	if (collisionCount > 5) {
		position.y = player.getPosition().y - 2 * radius;
		collisionCount = 0;
	}
}

void Ball::manageCollisionWith(Player& player, sf::RenderWindow& window)
{
	float MAX_ANGLE = 45;
	const int MARGE = 2;

	// Vérifie si la balle touche le joueur
	if (position.y + 2 * radius >= player.getPosition().y &&
		position.y + 2 * radius <= player.getPosition().y + player.getSize().y &&
		position.x + 2 * radius >= player.getPosition().x &&
		position.x <= player.getPosition().x + player.getSize().x)
	{
		// Calcule la position relative de la balle par rapport au joueur
		double relativeIntersectX = position.x + radius - player.getPosition().x - player.getSize().x / 2.0;

		// Normalise la position relative de la balle
		double normalizedRelativeIntersectionX = relativeIntersectX / (player.getSize().x / 2.0);

		// Calcule l'angle de rebond de la balle
		double angle = normalizedRelativeIntersectionX * MAX_ANGLE;

		// Change la direction de la balle en fonction de l'angle de rebond
		setAngle(angle);

		// Déplace la balle en dehors du joueur
		position.y = player.getPosition().y - 2 * radius - 0.1f;
		direction.y = -std::abs(direction.y);

		// Ajoute un peu de variation à la direction en x pour éviter que la balle ne rebondisse toujours dans la même direction
		double randomAngle = (((double)rand() / (double)RAND_MAX) * 30.0) - 15.0;
		double newAngle = angle + randomAngle;
		if (newAngle > MAX_ANGLE) {
			newAngle = MAX_ANGLE;
		}
		if (newAngle < -MAX_ANGLE) {
			newAngle = -MAX_ANGLE;
		}
		setAngle(newAngle);
	}

	//pour le haut
	if (position.y <= 0)
	{
		position.y = 0;
		direction.y = std::abs(direction.y);
	}

	//pour le sol 
	if (position.y + 2 * radius >= window.getSize().y)
	{
		position.y = window.getSize().y - 2 * radius;
		direction.y = -std::abs(direction.y);
	}

	//pour le mur gauche
	if (position.x <= 0)
	{
		position.x = 0;
		direction.x = std::abs(direction.x);
	}

	//pour le mur droite 
	if (position.x + 2 * radius >= window.getSize().x)
	{
		position.x = window.getSize().x - 2 * radius;
		direction.x = -std::abs(direction.x);
	}
}
