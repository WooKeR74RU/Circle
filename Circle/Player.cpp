#include "Player.h"
bool pressedL, pressedR, pressedUp, pressedShift;
double frict = 0.00005;

//Player types
void Type1(Player &p) //standard type
{
	if (pressedL)
	{
		p.dx -= 0.0005;
	}
	if (pressedR)
	{
		p.dx += 0.0005;
	}
	if (pressedShift)
	{
		if (p.dx < -0.2)
		{
			p.dx = -0.2;
		}
		if (p.dx > 0.2)
		{
			p.dx = 0.2;
		}
		if (pressedUp && p.onGround)
		{
			p.dy -= 0.45;
		}
	}
	else
	{
		if (p.dx < -0.1)
		{
			p.dx = -0.1;
		}
		if (p.dx > 0.1)
		{
			p.dx = 0.1;
		}
		if (pressedUp && p.onGround)
		{
			p.dy -= 0.3;
		}
	}
	return;
}

int accumX, accumY;
void Type2(Player &p) //accumulation type
{
	if (pressedShift)
	{
		if (accumX < 1000)
		{
			accumX += 1;
		}
		if (p.onGround && accumY < 1000)
		{
			accumY += 1;
		}
	}
	else
	{
		if (accumX >= 10)
		{
			if (pressedL)
			{
				p.dx -= 0.015;
			}
			if (pressedR)
			{
				p.dx += 0.015;
			}
			accumX -= 10;
		}
		else
		{
			if (pressedL)
			{
				if (p.dx > -0.1)
				{
					p.dx -= 0.0005;
				}
			}
			if (pressedR)
			{
				if (p.dx < 0.1)
				{
					p.dx += 0.0005;

				}
			}
		}
		if (accumY >= 100)
		{
			if (pressedUp)
			{
				p.dy -= 0.1;
			}
			accumY -= 100;
		}
		else
		{
			if (p.onGround && pressedUp)
			{
				p.dy -= 0.3;
			}
		}
	}
	return;
}

void Type3(Player &p) //fly mode
{
	if (pressedShift)
	{
		if (pressedL)
		{
			p.dx = -0.25;
		}
		if (pressedR)
		{
			p.dx = 0.25;
		}
		if (pressedUp)
		{
			p.dy = -0.25;
		}
	}
	else
	{
		if (pressedL)
		{
			p.dx = -0.1;
		}
		if (pressedR)
		{
			p.dx = 0.1;
		}
		if (pressedUp && p.onGround)
		{
			p.dy = -0.3;
		}
	}

	return;
}

Player::Player(const FloatRect &start_position, string link, int variable_pos, int frame_count)
{
	heroType.push_back(Type1);
	heroType.push_back(Type2);
	heroType.push_back(Type3);

	frameCount = frame_count;
	texture.resize(frame_count);
	for (int i = 0; i < frame_count; i++)
	{
		texture[i].loadFromFile(link);
		link[variable_pos]++;
	}
	sprite.setTexture(texture[0]);
	position = start_position;
	typeNum = onGround = curFrame = dx = dy = 0;
}

void Player::update(const GlobalRes &res)
{
	pressedL = Keyboard::isKeyPressed(Keyboard::A);
	pressedR = Keyboard::isKeyPressed(Keyboard::D);
	pressedUp = Keyboard::isKeyPressed(Keyboard::W);
	pressedShift = Keyboard::isKeyPressed(Keyboard::LShift);
	heroType[typeNum](*this);

	//Velocity
	if (typeNum == 1)
	{
		dx /= 1.001;
	}
	else
	{
		if (dx > 0)
		{
			if (dx - frict < 0)
				dx = 0;
			else
				dx -= frict;
		}
		if (dx < 0)
		{
			if (dx + frict > 0)
				dx = 0;
			else
				dx += frict;
		}
	}
	if (!pressedL && !pressedR && fabs(dx) < 0.015)
		dx = 0;
	position.left += dx * res.time;
	collision(0, res);

	if (!onGround)
		dy += 0.0005 * res.time;
	position.top += dy * res.time;
	onGround = 0;
	collision(1, res);

	//Animation
	curFrame += 0.003 * res.time;
	if (curFrame > frameCount || !pressedL && !pressedR)
		curFrame = 0;
	if (pressedR)
		sprite.setTextureRect(IntRect(0, 0, res.blockSize, res.blockSize));
	if (pressedL)
		sprite.setTextureRect(IntRect(res.blockSize, 0, -res.blockSize, res.blockSize));
	sprite.setTexture(texture[int(curFrame)]);

	sprite.setPosition(position.left - res.offsetX, position.top - res.offsetY);

	return;
}

void Player::collision(bool direction, const GlobalRes &res)
{
	for (int i = position.top / res.blockSize; i < (position.top + position.height) / res.blockSize; i++)
	{
		for (int j = position.left / res.blockSize; j < (position.left + position.width) / res.blockSize; j++)
		{
			if (res.levelMap[i][j] == '0')
			{
				if (direction)
				{
					if (dy > 0)
					{
						position.top = i * res.blockSize - position.height;
						onGround = 1;
					}
					if (dy < 0)
					{
						position.top = i * res.blockSize + position.height;
					}
					dy = 0;
				}
				else
				{
					if (dx > 0)
					{
						position.left = j * res.blockSize - position.width;
					}
					if (dx < 0)
					{
						position.left = j * res.blockSize + position.width;
					}
					//dx = 0;
				}
			}
		}
	}
	return;
}