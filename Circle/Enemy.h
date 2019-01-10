#pragma once
#include "GlobalRes.h"
class Enemy
{
private:
	double curFrame;
	int frameCount;
	vector<Texture> texture;
public:
	double dx, dy;
	bool onGround, life;
	FloatRect position;
	Sprite sprite;
	Enemy(const FloatRect &start_positionm, string link, int variable_pos, int frame_count);
	void update(const GlobalRes &res);
	void collision(bool direction, const GlobalRes &res);
};