#pragma once
////////////////////////////////////////
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <cmath>
#include <vector>
#include <array>
#include <list>
#include <stack>
#include <map>
#include <set>
#include <queue>
#include <sstream>
#include <iomanip>
#include <functional>
#include <SFML/Graphics.hpp>
#include <windows.h>
using namespace std;
using namespace sf;
////////////////////////////////////////
class GlobalRes
{
public:
	pair<int, int> resolution;
	int blockSize, H, W;
	double time, offsetX, offsetY;

	//Map
	vector<string> levelMap;
	vector<vector<pair<int, int>>> mapRand;
	Texture mapTexture;
	Sprite blockSprite;

	void loadMap(string linkMap, string linkTexture);
	void displayMap(RenderWindow &window);
	bool onScreen(const Sprite &sprite);
};