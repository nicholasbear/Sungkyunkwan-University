#pragma once
#ifndef __CIRCLE_H__
#define __CIRCLE_H__
#include <time.h>

struct circle_t
{
	vec2	center=vec2(0);		// 2D position for translation
	float	radius=1.0f;		// radius
	vec4	color;				// RGBA color in [0,1]
	vec2	velocity;			//speed
	mat4	model_matrix;		// modeling transformation

	// public functions
	void	update(float t, float prev_t, std::vector<circle_t> circles);
};

int Wall_Check(float x, float y, float radius) {
	if (x + radius > 16 / float(9) || x - radius < -16 / float(9))
		return 1;
	if (y + radius > 1 || y - radius < -1)
		return 1;
	return 0;
}

circle_t Make_Circle(std::vector<circle_t> circles) {
	//srand((unsigned)time(NULL));
	float r = (float)rand() / ((float)RAND_MAX);
	float g = (float)rand() / ((float)RAND_MAX);
	float b = (float)rand() / ((float)RAND_MAX);
	float x = (2 * (float)rand() - (float)RAND_MAX) / (float)RAND_MAX * 16 / float(9);
	float y = (2 * (float)rand() - (float)RAND_MAX) / (float)RAND_MAX;
	float radius = ((float)rand()*4 / ((float)RAND_MAX) + 0.50f)/10;
	float x_speed = (2 * (float)rand() - (float)RAND_MAX) / (float)RAND_MAX;
	float y_speed = (2 * (float)rand() - (float)RAND_MAX) / (float)RAND_MAX;

	circle_t temp;
	for (unsigned int i = 0; i < circles.size(); i++) {
		temp = circles[i];
		float dist = (vec2(x, y) - temp.center).length();
		//printf("Distances %f %f", dist, radius + temp.radius);
		if (dist < radius + temp.radius || Wall_Check(x,y,radius))
			return Make_Circle(circles);
	}
	return { vec2(x,y),radius,vec4(r,g,b,1),vec2(x_speed,y_speed)};
}

inline std::vector<circle_t> create_circles(uint num)
{
	std::vector<circle_t> circles;
	circle_t c;

	for (uint i = 0; i < num; i++) {
		c = Make_Circle(circles);
		circles.emplace_back(c);
	}
	return circles;
}

inline void circle_t::update(float t, float prev_t, std::vector<circle_t> circles)
{
	// °ø Ãæµ¹
	for (uint i = 0; i < circles.size(); i++) {
		
		const float distance = sqrt((circles[i].center.x - center.x) * (circles[i].center.x -center.x) + (circles[i].center.y - center.y) * (circles[i].center.y - center.y));
		float approach = 1;
		if (circles[i].velocity.x * velocity.x >= 0)
		{
			if (circles[i].velocity.y * velocity.y >= 0)
			{
				approach = -1;
			}
		}

		if (distance <= circles[i].radius + radius)
		{
			if (approach == 1)
			{
				circles[i].center.x -= circles[i].velocity.x;
				circles[i].center.y -= circles[i].velocity.y;
				center.x -= velocity.x;
				center.y -= velocity.y;
			}
			else
			{
				if (circles[i].velocity.x * circles[i].velocity.x + circles[i].velocity.y * circles[i].velocity.y >= velocity.x * velocity.x + velocity.y * velocity.y)
				{
					circles[i].center.x -= circles[i].velocity.x;
					circles[i].center.y -= circles[i].velocity.y;
				}
				else
				{
					center.x -= velocity.x;
					center.y -= velocity.y;
				}
			}
		}
	}
	center.x += velocity.x * (t - prev_t);
	center.y += velocity.y * (t - prev_t);
	//printf("center is %f %f\n", center.x, center.y);
	// these transformations will be explained in later transformation lecture
	mat4 scale_matrix =
	{
		radius, 0, 0, 0,
		0, radius, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};

	mat4 translate_matrix =
	{
		1, 0, 0, center.x,
		0, 1, 0, center.y,
		0, 0, 1, 0,
		0, 0, 0, 1
	};
	
	model_matrix = translate_matrix*scale_matrix;
}

#endif
