#ifndef KINEMATIC_CONTROLLER_H
#define KINEMATIC_CONTROLLER_H

#include "Gizmos.h"
#include "Physx1.h"

class KinematicController
{
public:

	
	KinematicController(float radius, float height,glm::vec3 position, Physx1* a_phyiscs);
	~KinematicController();

	void CreateCapsule();
	void Update();
	void Draw();
	void CreatePhyiscsAgent();

private:
	float m_radius;
	float m_height;
	Physx1* m_physicsObject;

	PxController* m_player;
	PxControllerManager* m_controller;
	PxRigidDynamic* m_actor;
	glm::vec3 m_position;
	glm::mat4 m_identity;
};
#endif