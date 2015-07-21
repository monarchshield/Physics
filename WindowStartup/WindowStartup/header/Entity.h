#ifndef ENTITY_H
#define ENTITY_H

#include "Gizmos.h"
#include <random>
#include <glm/glm.hpp>
#include <glm/ext.hpp>


using glm::vec3;
using glm::vec4;
class Entity
{
public:
	Entity();
	Entity(vec3 pos, float radius);

	~Entity();

	vec3 GetPosition();
	vec3 MakeRandom();
	float GetRadius();

	void Update(float deltatime);
	void Draw();
	void Seek(vec3 TargetPos);
	

private:

	float m_deltatime;
	float m_radius;
	
	vec4 m_colour;
	vec3 m_heading; //The position its heading towards
	vec3 m_direction; //The direction its going
	vec3 m_position; //The current Position

};

#endif