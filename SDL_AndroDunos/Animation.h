#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include "SDL/include/SDL_rect.h"
#define MAX_FRAMES 300

class Animation
{
public:
	bool loop = true;
	float speed = 1.0f;
	SDL_Rect frames[MAX_FRAMES];
	int last_frame = 0;
	float current_frame = 0;
	//bool pingpong

private:
	int loops = 0;

	//enum pingpong
	//{
	//	forward,
	//	backward
	//} direction = forward;

public:

	void PushBack(const SDL_Rect& rect)
	{
		frames[last_frame++] = rect;
	}

	SDL_Rect& GetCurrentFrame()
	{
		current_frame += speed;
		if (current_frame >= last_frame)
		{
			current_frame = (loop) ? 0.0f : last_frame - 1;
			loops++;
		}

		return frames[(int)current_frame];

		//switch (direction)
		//{
		//case pingpong::forward:
		//{
		//	current_frame += speed;
		//	if (current_frame >= last_frame)
		//	{
		//		current_frame = (loop || pingpong) ? 0.0f : last_frame - 1;
		//		direction = pingpong ? pingpong::backward : pingpong::forward;
		//		loops++;
		//	}
		//}
		//break;
		//case pingpong::backward:
		//{
		//	current_frame -= speed;
		//	if (current_frame <= 0.0f)
		//	{
		//		current_frame = 0.0f;
		//		direction = pingpong::forward;
		//		loops++;
		//	}
		//}
		//break;
		//}

		//return frames[(int)current_frame];
	}

	bool Finished() const
	{
		return loops > 0;
	}

	void reset() {
		current_frame = 0;
	}
};

#endif