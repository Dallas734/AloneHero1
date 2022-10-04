#include "Player.h"


void Player::Move(float time, String F, double x, double y, double width, double height)
{
	/*image.loadFromFile("Images/" + F);
	texture.loadFromImage(image);
	spriteMove.setTexture(texture);
	spriteMove.setTextureRect(IntRect(x, y, width, height));*/
	SetSprite("Run.png", MOVE, x, y, width, height);

	// Анимация
	if (Keyboard::isKeyPressed(Keyboard::Right))
	{
		this->currentFrame += 0.01 * time;
		if (this->currentFrame > 8) this->currentFrame -= 8;
		this->spriteMove.setTextureRect(IntRect(x * int(this->currentFrame), y, width, height));
		this->spriteMove.move(0.1 * time, 0);
	}

	//// Перемещение
	//switch (direction)
	//{
	//// Вправо 
	//case 0: 	
	//	dx = speed;
	//	dy = 0;
	//	break;
	//// Влево
	//case 1:
	//	dx = -speed;
	//	dy = 0;
	//	break;
	//}

	//// Движение
	//this->x += dx * time;
	//this->y += dy * time;

	//speed = 0;
	//sprite.setPosition(this->x, this->y);
}

int Player::Hit(double strength)
{
	return 0;
}

void Player::Damage(double strength)
{
}
