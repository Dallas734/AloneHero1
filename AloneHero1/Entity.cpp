#include "Entity.h"
#include "Level.h"

Entity::Entity(double x, double y, double speed, int health, double strength)
{
	this->x = x;
	this->y = y;
	this->speed = speed;
	this->health = health;
	this->strength = strength;
	this->direction = RIGHT;
	this->currentFrame = 0;
	this->dx = 0;
	this->dy = 0;
	this->onGround = false;
}

States Entity::Hit(float time, double xBeginSprite, double yBeginSprite, double width, double height, double buf, int frames, double strength, Directions direction, RenderWindow& window)
{
	SetSprite("Hit1.png", HIT, xBeginSprite, yBeginSprite, width, height);
	currentFrame += time * 0.01;
	if (this->currentFrame > frames) this->currentFrame -= frames;

	if (direction == RIGHT)
	{
		spriteHit.setOrigin({ 0, 0 });
		spriteHit.setScale(1, 1);
		this->state = HIT;
	}
	else if (direction == LEFT)
	{
		spriteHit.setOrigin({ spriteHit.getLocalBounds().width / 2, 0 });
		spriteHit.setScale(-1, 1);
		this->state = HIT;
	}
	
	spriteHit.setTextureRect(IntRect(xBeginSprite + (width + buf) * int(currentFrame), yBeginSprite, width, height));
	spriteHit.setPosition(x, y);
	/*window.clear();
	window.draw(GetSprite(HIT));
	window.display();*/

	return HIT;
}

void Entity::Damage(float time, double width, double height, int frames, double strength, Directions direction)
{
}

States Entity::Move(float time, double xBeginSprite, double yBeginSprite, double width, double height, int frames, Directions direction, RenderWindow& window, Level* level)
{

	SetSprite("Run.png", RUN, xBeginSprite, yBeginSprite, width, height);
	if (direction == RIGHT && /*(state == IDLE || state == RUN)*/onGround)
	{
		dx = speed;
		spriteMove.setOrigin({ 0, 0 });
		spriteMove.setScale(1, 1);
		this->state = RUN;
	}
	else if (direction == LEFT && /*(state == IDLE || state == RUN)*/onGround)
	{
		dx = -speed;
		spriteMove.setOrigin({ spriteMove.getLocalBounds().width, 0 });
		spriteMove.setScale(-1, 1);
		this->state = RUN;
	}
	
	//spriteMove.setTextureRect(IntRect(xBeginSprite * int(currentFrame), yBeginSprite, width, height));
	spriteMove.setTextureRect(IntRect(xBeginSprite + (width + bufWidth) * int(currentFrame), yBeginSprite, width, height));
	
	x += dx * time;
	CheckCollisionWithMap(dx, 0, level, time);
	//y += dy * time;
	currentFrame += time * 0.005;
	if (this->currentFrame > frames)
	{
		this->currentFrame -= frames;
	}
	//dx = 0;
	//dy = 0;
	CheckCollisionWithMap(0, dy, level, time);
	if (onGround)
	{
		//dy = 0;
		spriteMove.setPosition(x, y);
		/*window.clear();
		window.draw(GetSprite(RUN));
		window.display();*/
	}

	dx = 0;

	return RUN;
}

States Entity::Idle(float time, double xBeginSprite, double yBeginSprite, double width, double height, int frames, Directions direction, RenderWindow& window, Level* level)
{
	SetSprite("Idle.png", IDLE, xBeginSprite, yBeginSprite, width, height);
	currentFrame += time * 0.005;
	if (this->currentFrame > frames)
	{
		this->currentFrame -= frames;
	}

	if (direction == RIGHT)
	{
		spriteIdle.setOrigin({ 0, 0 });
		spriteIdle.setScale(1, 1);
		this->state = IDLE;
	}
	else if (direction == LEFT)
	{
		spriteIdle.setOrigin({ spriteIdle.getLocalBounds().width, 0 });
		spriteIdle.setScale(-1, 1);
		this->state = IDLE;
	}
	//dx = 0;
	//dy = 0;

	
	//spriteIdle.setTextureRect(IntRect(xBeginSprite * int(currentFrame), yBeginSprite, width, height));
	spriteIdle.setTextureRect(IntRect(xBeginSprite + (width + bufWidth) * int(currentFrame), yBeginSprite, width, height));
	
	/*spriteIdle.setTextureRect(IntRect(width * int(currentFrame), yBeginSprite, width, height));*/
	spriteIdle.setPosition(x, y);
	/*window.clear();
	window.draw(GetSprite(IDLE));
	window.display();*/

	return IDLE;
}

void Entity::SetSpeed(double speed)
{
	this->speed = speed;
}

double Entity::GetSpeed()
{
	return this->speed;
}


Sprite Entity::GetSprite(States spriteName)
{
	switch (spriteName)
	{
	case JUMP:
		return spriteJump;
		break;
	case RUN:
		return spriteMove;
		break;
	case DAMAGE:
		break;
	case HIT:
		return spriteHit;
		break;
	case IDLE:
		return spriteIdle;
		break;
	case FALL:
		return spriteFall;
		break;
	}
}

void Entity::SetSprite(String fileName, States spriteName, double xBeginSprite, double yBeginSprite, double width, double height)
{
	image.loadFromFile("Images/" + this->directory + fileName);
	//image.loadFromFile("Images/Player/" + fileName);
	texture.loadFromImage(image);

	switch (spriteName)
	{
	case JUMP:
		spriteJump.setTexture(texture);
		spriteJump.setTextureRect(IntRect(xBeginSprite, yBeginSprite, width, height));
		break;
	case RUN:
		spriteMove.setTexture(texture);
		spriteMove.setTextureRect(IntRect(xBeginSprite, yBeginSprite, width, height));
		break;
	case DAMAGE:
		break;
	case HIT:
		spriteHit.setTexture(texture);
		spriteHit.setTextureRect(IntRect(xBeginSprite, yBeginSprite, width, height));
		break;
	case IDLE:
		spriteIdle.setTexture(texture);
		spriteIdle.setTextureRect(IntRect(xBeginSprite, yBeginSprite, width, height));
		break;
	case FALL:
		spriteFall.setTexture(texture);
		spriteIdle.setTextureRect(IntRect(xBeginSprite, yBeginSprite, width, height));
	}
}

States Entity::GetState()
{
	return this->state;
}

FloatRect Entity::getRect()
{
	return FloatRect(x, y, width, height);
}
