#include "Octree.h"


Rectangle::Rectangle()
{

}

Rectangle::Rectangle(vec3 position, float width, float length, float height)
{
	m_position = position;
	m_width = width;
	m_length = length;
	m_height = height;
}

Rectangle::~Rectangle()
{

}

float Rectangle::GetWidth()
{
	return m_width;
}

float Rectangle::GetHeight()
{
	return m_height;
}

float Rectangle::GetLength()
{
	return m_length;
}

vec3 Rectangle::GetPos()
{
	return m_position;
}

Octree::Octree()
{

}


Octree::Octree(int pLevel, Rectangle* pBounds)
{
	m_level = pLevel;
	m_bounds = pBounds;
}

Octree::~Octree()
{

}

void Octree::Split()
{
	int subWidth = (int)(m_bounds->GetWidth() / 2);
	int subHeight = (int)(m_bounds->GetHeight() / 2);
	int subLength = (int)(m_bounds->GetLength() / 2);
	
	vec3 pos = m_bounds->GetPos();
	int x = pos.x;
	int y = pos.y;
	int z = pos.z;

	nodes[0] = new Octree(m_level + 1, new Rectangle(vec3(x + subWidth, y, subLength + z), subWidth, subLength, subHeight));
	nodes[1] = new Octree(m_level + 1, new Rectangle(vec3(x, y, z), subWidth, subLength, subHeight));
	nodes[2] = new Octree(m_level + 1, new Rectangle(vec3(x, y + subHeight, subLength), subWidth, subLength, subHeight));
	nodes[3] = new Octree(m_level + 1, new Rectangle(vec3(x + subWidth, y + subHeight, subLength + z), subWidth, subLength, subHeight));
}

int Octree::getIndex(Entity pRect)
{

	m_index = -1;
	
	
	
	double verticalMidpoint = m_bounds->GetPos().x + (m_bounds->GetWidth() / 2);
	double horizontalMidpoint = m_bounds->GetPos().y + (m_bounds->GetHeight() / 2);


	//Object can completly fit within the top quandrants

	bool topQuandrant = (pRect.GetPosition().y <= horizontalMidpoint && pRect.GetPosition().y + pRect.GetRadius() <= horizontalMidpoint);

	//Object can completly fit within the bottom quandrants
	bool bottomQuadrant = (pRect.GetPosition().y >= horizontalMidpoint);

	
	//Object can completly fit within the left quandrants
	if (pRect.GetPosition().x <= verticalMidpoint && pRect.GetPosition().x + pRect.GetRadius() <= verticalMidpoint)
	{
		if (topQuandrant)
			m_index = 1;

		else if (bottomQuadrant)
			m_index = 2;
	}

	//Object can completly fit within the right quandrants

	else if (pRect.GetPosition().x >= verticalMidpoint)
	{
		if (topQuandrant)
			m_index = 0;

		else if (bottomQuadrant)
			m_index = 3;
	}

	return m_index;


	//return -1;
}

void Octree::insert(Entity* pRect)
{
	if (nodes == nullptr)
	{
		m_index = getIndex(*pRect);

		if (m_index != -1)
		{
			nodes[m_index]->m_objects.push_back(pRect);
	
			return;
		}
	}
	
	m_objects.push_back(pRect);

	if (m_objects.size() > MAX_OBJECTS && m_level < MAX_LEVELS)
	{
		if (nodes[0] == nullptr)
		{
			Split();
		}
	}

	for (unsigned int i = 0; i < m_objects.size();)
	{
		
		m_index = getIndex(*m_objects[i]);

		if (m_index != -1 && nodes[0] != nullptr)
		{

			nodes[m_index]->insert(m_objects[i]);
			//m_objects.remove(m_objects[i]);
			m_objects.push_back(m_objects[i]);
			m_objects.pop_back();

		}

		else
			i++;
	}

}

void Octree::clear()
{
	m_objects.clear();

	if (nodes != nullptr)
	{
		
		for (int i = 0; i < 3; i++)
		{
			if (nodes[i] != nullptr)
			{
				nodes[i]->m_objects.clear();
				nodes[i] = nullptr;
			}
		}

	}
}

void Octree::Draw()
{
	Gizmos::addAABB(m_bounds->GetPos(), vec3(m_bounds->GetWidth(), m_bounds->GetHeight(), m_bounds->GetLength()), vec4(0, 1, 0, 1), nullptr);
}