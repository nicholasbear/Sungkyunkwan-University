#ifndef __SPHERE_H__
#define __SPHERE_H__
#include "cgmath.h"

struct sphere_t
{
	float	radius = 1.0f;		// radius
	float	theta = 0.0f;		// 행성이자기중심으로 도는거
	float	revolr = 0.0f;		// 태양중심거리
	float	revolt = 0.0f;		// 태양도는속도
	vec4	color;				// RGBA color in [0,1]
	mat4	model_matrix;		// modeling transformation

	// public functions
	void	update( float t );	
};

inline std::vector<sphere_t> create_spheres()
{
	std::vector<sphere_t> spheres;
	sphere_t s;
	
	//Sun
	s = { 0.5f, 0.01f, 0.0f, 0.0f, vec4(0.5f,0.5f,0.5f,1.0f) };
	spheres.emplace_back(s);

	//Mercury
	s = { 0.05f, 2.0f, 0.6f, 3.0f, vec4(0.5f,0.5f,0.5f,1.0f) };
	spheres.emplace_back(s);

	//Venus
	s = { 0.15f, 1.8f, 0.85f, 2.0f, vec4(0.5f,0.5f,0.5f,1.0f) };
	spheres.emplace_back(s);

	//Earth
	s = { 0.18f, 1.5f, 0.9f, 1.5f, vec4(0.5f,0.5f,0.5f,1.0f) };
	spheres.emplace_back(s);

	//Mars
	s = { 0.09f, 1.9f, 1.20f, 2.5f, vec4(0.5f,0.5f,0.5f,1.0f) };
	spheres.emplace_back(s);

	//Jupiter
	s = { 0.3f, 0.5f, 1.75f, 0.5f, vec4(0.5f,0.5f,0.5f,1.0f) };
	spheres.emplace_back(s);

	//Saturn
	s = { 0.22f, 0.8f, 2.15f, 0.6f, vec4(0.5f,0.5f,0.5f,1.0f) };
	spheres.emplace_back(s);

	//Uranus
	s = { 0.17f, 1.0f, 2.55f, 0.3f, vec4(0.5f,0.5f,0.5f,1.0f) };
	spheres.emplace_back(s);

	//Neptune
	s = { 0.14f, 1.7f, 2.95f, 0.2f, vec4(0.5f,0.5f,0.5f,1.0f) };
	spheres.emplace_back(s);

	return spheres;
}

inline void sphere_t::update( float t )
{
	float c	= -cos(theta), s=sin(theta);

	// these transformations will be explained in later transformation lecture
	mat4 scale_matrix =
	{
		radius, 0, 0, 0,
		0, radius, 0, 0,
		0, 0, radius, 0,
		0, 0, 0, 1
	};

	float pi = theta * t;
	mat4 rotation_matrix =
	{
		c, 0, s, 0,
		0, 1, 0, 0,
		-s, 0, c, 0,
		0, 0, 0, 1
	};

	//이상하게나와서 x축 -90도 z축 90도 돌려야함
	pi = -PI / 2.0f;

	mat4 rotate_x =
	{
		1, 0, 0, 0,
		0, cos(pi), -sin(pi), 0,
		0, sin(pi), cos(pi), 0,
		0, 0, 0, 1
	};

	mat4 rotate_y =
	{
		cos(pi), 0, sin(pi), 0,
		0, 1, 0, 0,
		-sin(pi),0, cos(pi), 0,
		0, 0, 0, 1
	};

	mat4 rotate_z =
	{
		cos(pi), -sin(pi), 0, 0,
		sin(pi), cos(pi), 0, 0,
		0,0, 1, 0,
		0, 0, 0, 1
	};

	float w = revolt * t;
	float x = revolr * cos(w);
	float z = revolr * sin(w);
	mat4 translate_matrix =
	{
		1, 0, 0, x,
		0, 1, 0, 0,
		0, 0, 1, z,
		0, 0, 0, 1
	};
	
	//model_matrix = translate_matrix * rotation_matrix * scale_matrix;
	model_matrix = translate_matrix * rotation_matrix * rotate_x * rotate_z * scale_matrix;
}

#endif
