#include "Bullet.hpp"

Bullet::Bullet(Vector2 bulletPos, int speed)
{
	this->bulletPos = bulletPos;
	this->speed = speed;
	active = true;
}