#pragma once
#include "GlobalRes.h"
class Player
{
private:
	double curFrame;
	int frameCount;
	vector<function<void(Player &p)>> heroType;
	vector<Texture> texture;
public:
	double dx, dy;
	bool onGround;
	int typeNum;
	FloatRect position;
	Sprite sprite;
	Player(const FloatRect &start_position, string link, int variable_pos, int frame_count);
	void update(const GlobalRes &res);
	void collision(bool direction, const GlobalRes &res);
};