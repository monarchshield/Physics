#include "RigidBody.h"

#pragma region Overload Constructors()

//RigidBody Sphere:
RigidBody::RigidBody(vec3 position, vec3 acceleration, float mass, float radius)
{
	m_position = position;
	m_acceleration = acceleration;
	m_mass = mass;
	m_radius = radius;
	m_gravity = vec3(0, 0, 0);
	m_shapeID = ShapeType::SPHERE;
	m_state = RigidBodyState::AWAKE;
	m_timestep = 1.0f;
}

//RigidBody AABB:
RigidBody::RigidBody(vec3 position, vec3 acceleration, float mass, float width, float length, float height)
{
	m_position = position;
	m_acceleration = acceleration;
	m_width = width;
	m_height = height;
	m_length = length;
	m_gravity = vec3(0, 0, 0);
	m_shapeID = ShapeType::BOX;
	m_state = RigidBodyState::AWAKE;
	m_timestep = 1.0f;
}

//RigidBody Plane:
RigidBody::RigidBody(vec3 position, vec3 normal)
{
	
	m_position = position;
	m_acceleration = vec3(0,0,0);
	m_normal = normal;
	m_mass = 0;
	m_width = 0;
	m_length = 0;
	m_gravity = vec3(0, 0, 0);
	m_shapeID = ShapeType::PLANE;
	m_state = RigidBodyState::ASLEEP;
	m_timestep = 1.0f;
}

#pragma endregion

RigidBody::~RigidBody()
{

}


void RigidBody::Update(float deltatime)
{
	m_position -= m_gravity * deltatime * m_timestep;
	
	
	m_force = m_mass * m_acceleration;
	m_acceleration = m_force / m_mass;

	m_velocity += m_acceleration * deltatime * m_timestep;



	std::cout << "Current Velocity: " << m_velocity.x << "," << m_velocity.y << "," << m_velocity.z << "\n";
	m_position += m_velocity;



}

void RigidBody::debug()
{

}

void RigidBody::applyForce(vec3 force)
{

}

void RigidBody::applyForceToActor(RigidBody* actor2, glm::vec3 force)
{
	ShapeType _id = actor2->m_shapeID;

	switch (m_shapeID)
	{
		case PLANE:
		{
			switch (_id)
			{
				case PLANE:
				  break;

				case SPHERE:
				  break;

				case BOX:
				  break;
			}
		}
		break;

		case SPHERE:
		{
			switch (_id)
			{
				case PLANE:
					SPHEREvsPLANE(actor2);
				   break;

				case SPHERE:
					SPHEREvsSPHERE(actor2);
				   break;

				case BOX:

				   break;
			}
		}
		break;

		case BOX:
		{
			switch (_id)
			{
			case PLANE:
				AABBvsPLANE(actor2);
				break;

			case SPHERE:
				break;

			case BOX:
				AABBvsAABB(actor2);
				break;
			}
		}
		break;

		default:
			std::cout << "Dont recognise collison type";
			break;

			//switch (actor2->m_shapeID)
			//{
			//case PLANE:
			//{
			//	std::cout << "Colliding with: PLANE!";
			//}
			//	break;
			//
			//case SPHERE:
			//{
			//			   SPHEREvsSPHERE(actor2);
			//}
			//	break;
			//
			//case BOX:
			//	std::cout << "Colliding with: AABB!";
			//	break;
			//
			//case CAPSULE:
			//	std::cout << "Colliding with: CAPSULE! doubtful!";
			//	break;
			//
			//default:
			//	std::cout << "I dont understand?";
			//	break;
			//}
	}
}



void RigidBody::Draw()
{
	switch (m_shapeID)
	{
	case PLANE: Gizmos::addAABBFilled(m_position, vec3(m_width, 1, m_length), vec4(1, 0, 0, 1), nullptr);
		break;
	case SPHERE: Gizmos::addSphere(m_position, m_radius, 10, 10, vec4(1, 0, 0, 1), nullptr);
		break;
	case BOX: Gizmos::addAABBFilled(m_position, vec3(m_width, m_height, m_length), vec4(1, 0, 0, 1), nullptr);
		break;
	case CAPSULE:
		break;
	
	default:
		break;
	}
}

#pragma region Get Functions()

vec3 RigidBody::GetPosition()
{
	return m_position;
}

vec3 RigidBody::GetForce()
{
	return m_force;
}

float RigidBody::GetRadius()
{
	return m_radius;
}

vec3 RigidBody::GetNormal()
{
	return m_normal;
}

float RigidBody::GetWidth()
{
	return m_width;
}

float RigidBody::GetHeight()
{
	return m_height;
}

float RigidBody::GetLength()
{
	return m_length;
}

#pragma endregion

#pragma region Set Functions()

void RigidBody::SetGravity(vec3 gravity)
{
	m_gravity = gravity;
}
void RigidBody::SetTimeStep(float val)
{
	m_timestep = val;
}

#pragma endregion

#pragma region RIGID BODY COLLISIONS

bool RigidBody::AABBvsAABB(RigidBody* actor)
{
	float b1_x = m_width / 2;
	float b1_y = m_height / 2;
	float b1_z = m_length / 2;

	float b2_x = actor->GetWidth() / 2;
	float b2_y = actor->GetHeight() / 2;
	float b2_z = actor->GetLength() / 2;

	vec3 b2_pos = actor->GetPosition();

	if (m_position.x - b1_x < b2_pos.x + b2_x
		&& m_position.x + b1_x > b2_pos.x - b2_x
		&& m_position.y - b1_y < b2_pos.y + b2_y
		&& m_position.y + b1_y > b2_pos.y - b2_y
		&& m_position.z - b1_z < b2_pos.z + b2_z
		&& m_position.z + b1_z > b2_pos.z - b2_z)
	{
		//Collision has occured occured gg
		std::cout << "Collision has occured!";
	}

}

bool RigidBody::SPHEREvsSPHERE(RigidBody* actor)
{
	vec3 temp_length = m_position - actor->GetPosition();
	float length = temp_length.length();

	if (length < actor->GetRadius())
	{
		std::cout << "Colliding with: SPHERE!";
		return true;
	}
	
	return false;
}

bool RigidBody::SPHEREvsPLANE(RigidBody* actor)
{
	vec3 collisionNormal = actor->GetNormal();

	float sphereToPlane = glm::dot(m_position, collisionNormal);

	if (sphereToPlane < 0)
	{
		//If we are behind the plane then we flip the normal
		collisionNormal *= -1;
		sphereToPlane *= -1;
	}

	float intersection = m_radius - sphereToPlane;

	if (intersection > 0)
	{
		//set sphere velocity to zero here:
		std::cout << "Collision with plane has occured";
	}

}

bool RigidBody::AABBvsPLANE(RigidBody* actor)
{
	vec3 collisionNormal = actor->GetNormal();

	float AABBToPlane = glm::dot(m_position, collisionNormal);

	if (AABBToPlane < 0)
	{
		//If we are behind the plane then we flip the normal
		collisionNormal *= -1;
		AABBToPlane *= -1;
	}

	float halfheight = m_height / 2;
	float intersection = halfheight - AABBToPlane;

	if (intersection > 0)
	{
		//set cube velocity to zero here:
		std::cout << "Collision with plane has occured";
	}

}

#pragma endregion