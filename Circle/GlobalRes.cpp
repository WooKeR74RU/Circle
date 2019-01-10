#include "GlobalRes.h"

bool GlobalRes::onScreen(const Sprite &sprite)
{
	if (sprite.getPosition().x + sprite.getLocalBounds().height >= 0 &&
		sprite.getPosition().x - sprite.getLocalBounds().height <= resolution.first &&
		sprite.getPosition().y + sprite.getLocalBounds().width >= 0 &&
		sprite.getPosition().y - sprite.getLocalBounds().width <= resolution.second)
	{
		return 1;
	}
	return 0;
}

void GlobalRes::loadMap(string linkMap, string linkTexture)
{
	levelMap.clear();
	ifstream fin;
	fin.open(linkMap);
	while (1)
	{
		string s;
		getline(fin, s);
		if (s.empty())
			break;
		levelMap.push_back(s);
	}
	fin.close();
	H = levelMap.size();
	W = levelMap[0].size();

	mapTexture.loadFromFile(linkTexture);
	blockSprite.setTexture(mapTexture);

	mapRand.clear();
	mapRand.resize(H, vector<pair<int, int>>(W));
	for (int i = 0; i < H; i++)
	{
		for (int j = 0; j < W; j++)
		{
			if (levelMap[i][j] == ' ')
				continue;
			mapRand[i][j].first = rand() % 12;
			mapRand[i][j].second = rand() % 7;
		}
	}

	return;
}

void GlobalRes::displayMap(RenderWindow &window)
{
	for (int i = 0; i < H; i++)
	{
		for (int j = 0; j < W; j++)
		{
			if (levelMap[i][j] == '0' &&
				j * blockSize - offsetX + blockSize >= 0 &&
				j * blockSize - offsetX - blockSize <= resolution.first &&
				i * blockSize - offsetY + blockSize >= 0 &&
				i * blockSize - offsetY - blockSize <= resolution.second)
			{
				blockSprite.setPosition(j * blockSize - offsetX, i * blockSize - offsetY);
				blockSprite.setTextureRect(IntRect(mapRand[i][j].first * blockSize, mapRand[i][j].second * blockSize, blockSize, blockSize));
				window.draw(blockSprite);
			}
		}
	}
	return;
}