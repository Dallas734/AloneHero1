#include "Player.h"

void Player::Update(float time)
{
	Move(time);
}

void Player::Move(float time)
{
	double minSpeed = 0.1;
	double currentFrameX = 0;
	double currentFrameY = 0;
	double animationSpeed = 0.05;

	// Анимация
	if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D))
	{
		SetDirection(LEFT);
		SetSpeed(minSpeed);
		currentFrameX += animationSpeed * time;
		// Переход на новую строку
		if (currentFrameX > 3)
		{
			currentFrameX = 0;
			currentFrameY++;
		}
		if (currentFrameY > 3)
		{
			currentFrameX = 0;
			currentFrameY = 0;
		}
		// Вырезаем спрайт
		this->sprite.setTextureRect(IntRect(45 * int(currentFrameX), 17 * int(currentFrameY), 128, 64));
	}

	// Перемещение
	switch (direction)
	{
	// Вправо 
	case 0: 	
		dx = speed;
		dy = 0;
		break;
	// Влево
	case 1:
		dx = -speed;
		dy = 0;
		break;
	}

	// Движение
	x += dx * time;
	y += dy * time;

	speed = 0;
	sprite.setPosition(x, y);
}

int Player::Hit(double strength)
{
	return 0;
}

void Player::Damage(double strength)
{
}

void Player::Walk()
{
}
