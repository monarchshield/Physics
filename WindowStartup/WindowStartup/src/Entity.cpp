#include "Entity.h"

Entity::Entity()
{

}

Entity::Entity(vec3 pos, float radius)
{
	m_position = pos;
	m_colour = vec4(1, 0, 0, 1);
	m_radius = radius;
}

Entity::~Entity()
{

}

void Entity::Update(float deltatime)
{
	vec3 distance = m_position - m_heading;
	float range = glm::length(distance);	
	m_deltatime = deltatime;

	if (range < 3)
	{
		MakeRandom();
	}

	else
		Seek(m_heading);

}
void Entity::Draw()
{
	Gizmos::addSphere(m_position, m_radius, 10, 10, m_colour, nullptr);
}

void Entity::Seek(vec3 TargetPos)
{
	m_direction = TargetPos - m_position;
	glm::normalize(m_direction);

	m_position += m_direction * m_deltatime;
}

vec3 Entity::MakeRandom()
{
	m_heading = vec3(rand() % 300 - 200, rand() % 200, rand() % 300 - 200);
	return m_heading;
}

vec3 Entity::GetPosition()
{
	return m_position;
}

float Entity::GetRadius()
{
	return m_radius;
}