#ifndef RIGID_BODY_H
#define RIGID_BODY_H

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <Gizmos.h>
#include <iostream>
using namespace glm;

enum ShapeType
{
	PLANE = 0,
	SPHERE = 1,
	BOX = 2,
	CAPSULE = 3,

};

enum RigidBodyState
{
	ASLEEP,
	AWAKE
};

class RigidBody 
{
public:

	//Overload Constructor
	RigidBody(vec3 position, vec3 velocity, float mass);
								 
	//RigidBody Sphere:		
	RigidBody(vec3 position, vec3 velocity, float mass, float radius);
								
	//RigidBody AABB:			
	RigidBody(vec3 position, vec3 velocity, float mass, float width, float length, float height);
								 
	//RigidBody Plane:			  
	RigidBody(vec3 position, vec3 normal);

	//Deconstructor
	~RigidBody ();
	
	//Update Loop
	void Update(float deltatime);
	
	void CheckCollision(RigidBody* actor);

	void debug();
	void Draw();

	//Collision Detection Functions
	bool AABBvsAABB(RigidBody* actor);				 //In progress!
	bool AABBvsSPHERE(RigidBody* actor);			 //Not completed yet!
	bool AABBvsPLANE(RigidBody* actor);				 //Finished!
	bool SPHEREvsSPHERE(RigidBody* actor);			 //Completed!
	bool SPHEREvsPLANE(RigidBody* actor);			 //Done!
	//--------------------------------------

	//Just for debug stuff
	void SetID(int id);

	//Sets the gravity
	void SetGravity(vec3 gravity);

	//Applys a force to the target
	void applyForce(vec3 force);
	
	//Apply force when colliding with a object
	void applyForceToActor(RigidBody* actor2, glm::vec3 force);

	//Setter for timestep value
	void SetTimeStep(float val);

	//For Renderer Reasons
	void SetColour(vec4 colour);


	//Returns type functions
	//----------------------------------------
	vec3 GetPosition();
	vec3 GetForce();
	vec3 GetNormal();
	vec3 GetVelocity();

	float GetWidth();
	float GetHeight();
	float GetLength();
	float GetRadius();
	float GetMass();
	//------------------------------------------
	
	vec3 m_position;

private:
	
	ShapeType m_shapeID;
	RigidBodyState m_state;
	
	//object size properties
	//----------------------------
	float m_radius;
	float m_width;
	float m_height;
	float m_length;
	float m_timestep;
	//----------------------------

	//Debug stuff
	//-------------------------------
	int m_id;
	//-------------------------------


	//Physics stuff
	//-------------------------
	vec3 m_velocity;
	vec3 m_gravity;
	//vec3 m_acceleration;
	vec3 m_normal;

	vec3 m_force;
	float m_mass;
	float m_deltatime;
	//-------------------------


	//Graphics& Colour stuff
	vec4 m_colour;



};


#endif 
