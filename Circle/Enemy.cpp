#include "Enemy.h"

Enemy::Enemy(const FloatRect &start_position, string link, int variable_pos, int frame_count)
{
	frameCount = frame_count;
	texture.resize(frame_count);
	for (int i = 0; i < frame_count; i++)
	{
		texture[i].loadFromFile(link);
		link[variable_pos]++;
	}
	sprite.setTexture(texture[0]);
	position = start_position;
	dx = onGround = curFrame = dy = 0;
	life = 1;
}

void Enemy::update(const GlobalRes &res)
{
	if (life)
	{
		//Velocity
		position.left += dx * res.time;
		collision(0, res);

		if (!onGround)
			dy += 0.0005 * res.time;
		position.top += dy * res.time;
		onGround = 0;
		collision(1, res);

		//Animation
		curFrame += res.time * 0.003;
		if (curFrame > frameCount || !dx)
			curFrame = 0;
		if (dx > 0)
			sprite.setTextureRect(IntRect(0, 0, res.blockSize, res.blockSize));
		if (dx < 0)
			sprite.setTextureRect(IntRect(res.blockSize, 0, -res.blockSize, res.blockSize));
		sprite.setTexture(texture[int(curFrame)]);

		sprite.setPosition(position.left - res.offsetX, position.top - res.offsetY);
	}
	else
	{
		sprite.setPosition(position.left - res.offsetX, position.top - res.offsetY);
		if (dx)
		{
			dx = 0;
			sprite.setColor(Color::Black);
		}
	}

	return;
}

void Enemy::collision(bool direction, const GlobalRes &res)
{
	for (int i = position.top / res.blockSize; i < (position.top + position.height) / res.blockSize; i++)
	{
		for (int j = position.left / res.blockSize; j < (position.left + position.width) / res.blockSize; j++)
		{
			if (i >= res.levelMap.size() || j >= res.levelMap[i].size())
				continue;
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
					dx = -dx;
				}
			}
		}
	}
	return;
}