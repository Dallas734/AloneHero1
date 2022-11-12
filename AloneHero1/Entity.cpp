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

States Entity::Hit(float time, double xBeginSprite, double yBeginSprite, double width, double height, int frames, double bufOfHit, Directions direction, RenderWindow& window, Level* level)
{
	SetSprite("Hit.png", HIT, xBeginSprite, yBeginSprite, width, height);
	currentFrame += time * 0.01;
	if (this->currentFrame > frames)
	{
		this->currentFrame -= frames;
		state = RUN;
		return RUN;
	}
	
	if (direction == RIGHT)
	{
		sprites[HIT].setOrigin({ 0, 0 });
		sprites[HIT].setScale(1, 1);
		this->state = HIT;
	}
	else if (direction == LEFT)
	{
		sprites[HIT].setOrigin({ sprites[HIT].getLocalBounds().width / 2, 0 });
		sprites[HIT].setScale(-1, 1);
		this->state = HIT;
	}

	sprites[HIT].setTextureRect(IntRect(xBeginSprite + (width + bufOfHit) * int(currentFrame), yBeginSprite, width, height));
	sprites[HIT].setPosition(this->x, this->y);
	

	return HIT;
}

States Entity::Death(float time, double xBeginSprite, double yBeginSprite, double width, double height, int frames, Directions direction, RenderWindow& window, Level* Level)
{
	SetSprite("Death.png", DEATH, xBeginSprite, yBeginSprite, width, height);
	
	currentFrame += time * 0.01;
	if (this->currentFrame > frames)
	{
		this->currentFrame -= frames;
		this->state = DEATH;
	}

	if (direction == RIGHT)
	{
		sprites[DEATH].setOrigin({ 0, 0 });
		sprites[DEATH].setScale(1, 1);
	}
	else if (direction == LEFT)
	{
		sprites[DEATH].setOrigin({ sprites[DEATH].getLocalBounds().width, 0 });
		sprites[DEATH].setScale(-1, 1);
	}

	sprites[DEATH].setTextureRect(IntRect(xBeginSprite + (width + bufWidth) * int(currentFrame), yBeginSprite, width, height));
	sprites[DEATH].setPosition(this->x, this->y);
	
	return DEATH;
}

States Entity::Damage(float time, double xBeginSprite, double yBeginSprite, double width, double height, int frames, double damage, Directions direction)
{
	SetSprite("Damage.png", DAMAGE, xBeginSprite, yBeginSprite, width, height);
	currentFrame += time * 0.005;
	if (this->currentFrame > frames)
	{
		this->currentFrame -= frames;
		this->health -= damage;
	}

	if (direction == RIGHT)
	{
		sprites[DAMAGE].setOrigin({ 0, 0 });
		sprites[DAMAGE].setScale(1, 1);
		this->state = DAMAGE;
	}
	else if (direction == LEFT)
	{
		sprites[DAMAGE].setOrigin({ sprites[DAMAGE].getLocalBounds().width, 0 });
		sprites[DAMAGE].setScale(-1, 1);
		this->state = DAMAGE;
	}

	//this->health -= damage;

	sprites[DAMAGE].setTextureRect(IntRect(xBeginSprite + (width + bufWidth) * int(currentFrame), yBeginSprite, width, height));
	sprites[DAMAGE].setPosition(this->x, this->y);

	return DAMAGE;
}


States Entity::Move(float time, double xBeginSprite, double yBeginSprite, double width, double height, int frames, Directions direction, RenderWindow& window, Level* level)
{
	Message* message;

	SetSprite("Run.png", RUN, xBeginSprite, yBeginSprite, width, height);
	if (direction == RIGHT && onGround)
	{
		dx = speed;
		sprites[RUN].setOrigin({ 0, 0 });
		sprites[RUN].setScale(1, 1);
		this->state = RUN;
	}
	else if (direction == LEFT && onGround)
	{
		dx = -speed;
		sprites[RUN].setOrigin({ sprites[RUN].getLocalBounds().width, 0 });
		sprites[RUN].setScale(-1, 1);
		this->state = RUN;
	}
	
	sprites[RUN].setTextureRect(IntRect(xBeginSprite + (width + bufWidth) * int(currentFrame), yBeginSprite, width, height));
	
	this->x += dx * time;
	message = new Message(RUN_C, 0 , this, this->x, this->y, this->dx, 0);
	level->GetMessage(*message);
	//level->CheckCollision(dx, 0, this);

	currentFrame += time * 0.005;
	if (this->currentFrame > frames)
	{
		this->currentFrame -= frames;
	}

	if (onGround)
	{
		sprites[RUN].setPosition(this->x, this->y);
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
		sprites[IDLE].setOrigin({ 0, 0 });
		sprites[IDLE].setScale(1, 1);
		this->state = IDLE;
	}
	else if (direction == LEFT)
	{
		sprites[IDLE].setOrigin({ sprites[IDLE].getLocalBounds().width, 0 });
		sprites[IDLE].setScale(-1, 1);
		this->state = IDLE;
	}
	
	sprites[IDLE].setTextureRect(IntRect(xBeginSprite + (width + bufWidth) * int(currentFrame), yBeginSprite, width, height));
	sprites[IDLE].setPosition(x, y);

	return IDLE;
}

double Entity::GetStrength()
{
	return this->strength;
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
		return sprites[JUMP];
		break;
	case RUN:
		return sprites[RUN];
		break;
	case DAMAGE:
		return sprites[DAMAGE];
		break;
	case HIT:
		return sprites[HIT];
		break;
	case IDLE:
		return sprites[IDLE];
		break;
	case FALL:
		return sprites[FALL];
		break;
	case DEATH:
		return sprites[DEATH];
		break;
	}
}

void Entity::SetSprite(String fileName, States spriteName, double xBeginSprite, double yBeginSprite, double width, double height)
{
	image.loadFromFile("Images/" + this->directory + fileName);
	texture.loadFromImage(image);

	switch (spriteName)
	{
	case JUMP:
		sprites[JUMP].setTexture(texture);
		sprites[JUMP].setTextureRect(IntRect(xBeginSprite, yBeginSprite, width, height));
		break;
	case RUN:
		sprites[RUN].setTexture(texture);
		sprites[RUN].setTextureRect(IntRect(xBeginSprite, yBeginSprite, width, height));
		break;
	case DAMAGE:
		sprites[DAMAGE].setTexture(texture);
		sprites[DAMAGE].setTextureRect(IntRect(xBeginSprite, yBeginSprite, width, height));
		break;
	case HIT:
		sprites[HIT].setTexture(texture);
		sprites[HIT].setTextureRect(IntRect(xBeginSprite, yBeginSprite, width, height));
		break;
	case IDLE:
		sprites[IDLE].setTexture(texture);
		sprites[IDLE].setTextureRect(IntRect(xBeginSprite, yBeginSprite, width, height));
		break;
	case FALL:
		sprites[FALL].setTexture(texture);
		sprites[FALL].setTextureRect(IntRect(xBeginSprite, yBeginSprite, width, height));
		break;
	case DEATH:
		sprites[DEATH].setTexture(texture);
		sprites[DEATH].setTextureRect(IntRect(xBeginSprite, yBeginSprite, width, height));
		break;
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

double Entity::GetDX()
{
	return this->dx;
}

double Entity::GetDY()
{
	return this->dy;
}

double Entity::GetX()
{
	return this->x;
}

FloatRect Entity::getHitRect()
{
	if (direction == RIGHT)
	{
		return FloatRect(x, y, sprites[HIT].getLocalBounds().width - 20, height);
	}
	else if (direction == LEFT)
	{
		return FloatRect(x - 25, y, sprites[HIT].getLocalBounds().width, height);
	}
}

double Entity::GetY()
{
	return this->y;
}

void Entity::SetX(double x)
{
	this->x = x;
}

void Entity::SetY(double y)
{
	this->y = y;
}

void Entity::SetDX(double dx)
{
	this->dx = dx;
}

void Entity::SetDY(double dy)
{
	this->dy = dy;
}

void Entity::SetState(States state)
{
	this->state = state;
}

bool Entity::GetOnGround()
{
	return this->onGround;
}

void Entity::SetOnground(bool onGround)
{
	this->onGround = onGround;
}

Directions Entity::GetDirection()
{
	return this->direction;
}

void Entity::SetDirection(Directions direction)
{
	this->direction = direction;
}

double Entity::GetWidth()
{
	return this->width;
}

double Entity::GetHeight()
{
	return this->height;
}

void Entity::SetDamage(double damage)
{
	this->damage = damage;
}
