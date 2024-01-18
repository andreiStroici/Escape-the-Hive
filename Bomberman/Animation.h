#pragma once

class Animation
{
public:
	int index;
	int frames;
	int speed;

	//whem i create an animation I will set the values from above
	Animation() {};
	Animation(int i, int f, int s)
	{
		index = i;
		frames = f;
		speed = s;
	}
};