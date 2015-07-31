#include "KinematicController.h"


KinematicController::KinematicController(float radius, float height ,glm::vec3 position, Physx1* a_phyiscs) :
m_radius(radius), m_height(height),m_position(position), m_physicsObject(a_phyiscs)
{
	//Blah blah blah Nothing happens here
	//initialising identity matrix to identity
	m_identity = glm::mat4(1, 0, 0, 0,
						   0, 1, 0, 0,
						   0, 0, 1, 0,
						   1, 1, 1, 1);



	CreatePhyiscsAgent();

	m_controller = PxCreateControllerManager(*m_physicsObject->m_PhysicsScene);

	PxCapsuleControllerDesc desc;
	desc.height = 1.6f;
	desc.radius = 0.4;
	desc.position.set(m_position.x, m_position.y, m_position.z);
	desc.material = m_physicsObject->m_PhysicsMaterial;
	desc.density = 10;

	//Create the layer controller
	m_player = m_controller->createController(desc);
	m_player->setPosition(PxExtendedVec3(0, 1, 0));

	

}

KinematicController::~KinematicController()
{

}

void KinematicController::CreatePhyiscsAgent()
{
	PxTransform transform(PxVec3(m_position.x, m_position.y, m_position.z));
	//transform = PxVec3(0, 0, 0);
	float density = 50;

	float halfHeight = m_height / 2;


	PxCapsuleGeometry capsule(m_radius, m_height);
	m_actor = PxCreateDynamic(*m_physicsObject->m_Physics, transform, capsule, *m_physicsObject->m_PhysicsMaterial, density);



	m_physicsObject->m_PhysicsScene->addActor(*m_actor);
	m_physicsObject->m_boxActors.push_back(m_actor);
	
}

void KinematicController::CreateCapsule()
{

	float halfheight = m_height / 2;
	PxVec3 p = m_actor->getGlobalPose().p;

	
	//PxTransform transform = m_actor->getGlobalPose().p;
	
	PxMat44 m(m_actor->getGlobalPose()); //Create a rotation matrix from the transform
	glm::mat4* M = (glm::mat4*)(&m);

	//Get the world position from the Physx transform
	glm::vec3 position = vec3(p.x, p.y, p.z);
	glm::vec4 axis(halfheight, 0, 0, 0);

	axis = *M * axis;
	glm::mat4 m2 = glm::rotate(*M, 11 / 7.0f, glm::vec3(0.0f, 0.0f, 1.0f));
	
	//Creating a capsule
	Gizmos::addSphere(position + axis.xyz(), m_radius, 15, 15, vec4(1, 0, 0, 1), &m2);
	Gizmos::addSphere(position - axis.xyz(), m_radius, 15, 15, vec4(1, 0, 0, 1), &m2);
	Gizmos::addCylinderFilled(position, m_radius, halfheight, 10, vec4(1, 0, 0, 1) ,&m2);

}

void KinematicController::Update()
{
	//Insert Control Keys here for stuffs! :)
}


void KinematicController::Draw()
{
	CreateCapsule();
}