#include "Player.h"
#include "Level.h"


States Player::Jump(float time, double xBeginSprite, double yBeginSprite, double width, double height, int frames, Directions direction, RenderWindow& window, Level* level)
{
	this->state = JUMP;
	SetSprite("Jump.png", JUMP, xBeginSprite, yBeginSprite, width, height);
	currentFrame += time * 0.01;
	if (this->currentFrame > frames) this->currentFrame -= frames;

	if (onGround)
	{
		dy = -0.1; // Высота прыжка
		onGround = false;
	}

	/*if (direction == RIGHT)
	{
		dx = speed;
		x += dx * time;
		CheckCollisionWithMap(dx, 0, level, time);
		spriteJump.setOrigin({ 0, 0 });
		spriteJump.setScale(1, 1);
	}
	else if (direction == LEFT)
	{
		dx = -speed;
		x += dx * time;
		CheckCollisionWithMap(dx, 0, level, time);
		spriteJump.setOrigin({ spriteJump.getLocalBounds().width, 0 });
		spriteJump.setScale(-1, 1);
	}*/

	if (onGround)
	{
		dy = 0;
		CheckCollisionWithMap(0, dy, level, time);
		return IDLE;
	}
	else
	{
		y += dy * time;
		dy += 0.0001 * time;
		CheckCollisionWithMap(0, dy, level, time);
	}

	//CheckCollisionWithMap(0, dy, level);
	dx = 0;

	spriteJump.setTextureRect(IntRect(width * int(currentFrame), yBeginSprite, width, height));
	spriteJump.setPosition(x, y);
	/*window.clear();
	window.draw(GetSprite(JUMP));
	window.display();*/
	
	return JUMP;
}

States Player::Fall(float time, double xBeginSprite, double yBeginSprite, double width, double height, int frames, Directions direction, RenderWindow& window, Level* level)
{
	SetSprite("Fall.png", FALL, xBeginSprite, yBeginSprite, width, height);
	currentFrame += time * 0.005;
	if (this->currentFrame > frames) this->currentFrame -= frames;

	if (direction == RIGHT)
	{
		spriteFall.setOrigin({ 0, 0 });
		spriteFall.setScale(1, 1);
		this->state = FALL;
	}
	else if (direction == LEFT)
	{
		spriteFall.setOrigin({ spriteFall.getLocalBounds().width, 0 });
		spriteFall.setScale(-1, 1);
		this->state = FALL;
	}

	CheckCollisionWithMap(0, dy, level, time);
	if (onGround)
	{
		dy = 0;
		CheckCollisionWithMap(0, dy, level, time);
		return IDLE;
	}
	else
	{
		y += dy * time;
		dy += 0.0001 * time;
		CheckCollisionWithMap(0, dy, level, time);
	}

	spriteFall.setTextureRect(IntRect(width * int(currentFrame), yBeginSprite, width, height));
	spriteFall.setPosition(x, y);

	return FALL;
}

void Player::HelthUP(int regenerationUnits)
{
	this->health += regenerationUnits;
}

void Player::SpeedUp(double improveUnits)
{
	this->speed += improveUnits;
}

void Player::Update(float time, RenderWindow& window, Level* level)
{
	std::cout << dy;

	// Уровень земли и падение

	if (onGround && dy == 0 && state != IDLE)
	{
		state = FALL;
		onGround = false;
		dy += 0.0001 * time;
	}
	//dy += 0.0001 * time; // Раскоментировав, будет больше притяжение.
	y += dy * time; 
	CheckCollisionWithMap(0, dy, level, time);

	// Состояния
	if (Keyboard::isKeyPressed(Keyboard::D)/* && onGround*/)
	{	
		if (state == IDLE)
		{
			direction = RIGHT;
			state = RUN;
			Move(time, 56, 44, this->width, this->height, 8, direction, window, level);
			ViewOnPlayer(x, y);
		}
		if (state == JUMP)
		{
			dx = speed;
			x += dx * time;
			CheckCollisionWithMap(dx, 0, level, time);
			spriteJump.setOrigin({ 0, 0 });
			spriteJump.setScale(1, 1);
			dx = 0;
		}
		
	}
	else if (Keyboard::isKeyPressed(Keyboard::A)/* && onGround*/)
	{
		if (state == IDLE)
		{
			direction = LEFT;
			state = RUN;
			Move(time, 56, 44, this->width, this->height, 8, direction, window, level);
			ViewOnPlayer(x, y);
		}
		if (state == JUMP)
		{
			dx = -speed;
			x += dx * time;
			CheckCollisionWithMap(dx, 0, level, time);
			spriteJump.setOrigin({ spriteJump.getLocalBounds().width, 0 });
			spriteJump.setScale(-1, 1);
			dx = 0;
		}
		
	}
	else if (Keyboard::isKeyPressed(Keyboard::Right))
	{
		direction = RIGHT;
		state = HIT;
		Hit(time, 0, 0, this->width, this->height, 4, this->strength, direction, window);
		ViewOnPlayer(x, y);
	}
	else if (Keyboard::isKeyPressed(Keyboard::Left)  && onGround)
	{
		direction = LEFT;
		state = HIT;
		Hit(time, 0, 0, this->width, this->height, 4, this->strength, direction, window);
		ViewOnPlayer(x, y);
	}
	else if (state == IDLE)
	{
		state = IDLE;
		Idle(time, 56, 44, this->width, this->height, 8, direction, window, level);
		ViewOnPlayer(x, y);
	}

	if (state == FALL)
	{
		state = Fall(time, 0, 0, this->width, this->height, 2, direction, window, level);
		ViewOnPlayer(x, y);
	}
	

	if ((Keyboard::isKeyPressed(Keyboard::Space) && onGround) || (!onGround && state == JUMP))
	{
		state = JUMP;
		Jump(time, 0, 0, this->width, this->height, 2, direction, window, level);
		ViewOnPlayer(x, y);
	}

}

void Player::ViewOnPlayer(double x, double y)
{
	view.setCenter(x + 100, y);
}

View Player::GetPlayerView()
{
	return this->view;
}

void Player::CheckCollisionWithMap(double dx, double dy, Level* level, float time)
{
	std::vector<Object> obj = level->GetAllObjects();
	for (int i = 0; i < obj.size(); i++)
	{
		if (getRect().intersects(obj[i].rect))
		{
			if (obj[i].name == "Solid")
			{
				if (dy > 0) {
					y = obj[i].rect.top - height;
					this->dy = 0; // Для анимации
					state = IDLE;
					onGround = true;
				}
				if (dy < 0) { y = obj[i].rect.top + obj[i].rect.height; /*this->dy = 0;*/ std::cout << "I'm minus!"; }
				if (dx > 0) { x = obj[i].rect.left - width; }
				if (dx < 0) { x = obj[i].rect.left + obj[i].rect.width; }
			}
		}
	}
}

