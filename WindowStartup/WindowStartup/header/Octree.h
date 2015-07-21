#ifndef OCTREE_H
#define OCTREE_H

#include "Entity.h"
#include <list>
#include <vector>

class Rectangle
{
public:
	Rectangle();
	Rectangle(vec3 position, float width, float length, float height);

	~Rectangle();

	float GetWidth();
	float GetHeight();
	float GetLength();
	vec3 GetPos();

private:
	vec3 m_position;
	float m_width;
	float m_length;
	float m_height;


};

class Octree
{
public:
	Octree();
	Octree(int pLevel, Rectangle* pBounds);
	~Octree();

	void Split();
	int getIndex(Entity pRect);
	void insert(Entity* pRect);
	void clear();

	void Draw();

	//Return function
	std::list<Entity> Retrieve(std::list<Entity> returnObjects, Entity pRect);


	//Recursive Return
	std::list<Octree> Childrenof(Octree parent, std::list<Octree> result);



private:
	
	//Just a rectangle
	//Rectangle* m_bounds;

	//The number of nodes each parent is holding
	Octree* nodes[4];

	//The list of entities each node is holding
	std::vector<Entity* > m_objects;

	//Max amount of objects something can hold before it splits
	const int MAX_OBJECTS = 5;

	//Deepest level subnode 
	const int MAX_LEVELS = 3;

	int m_index;

	int m_level;
	float m_width;
	float m_length;
	float m_height;


};

#endif