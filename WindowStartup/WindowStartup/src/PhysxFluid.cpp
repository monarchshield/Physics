#include "PhysxFluid.h"

PhysxFluid::PhysxFluid(Physx1* physics) : g_Physics(physics)
{
	SetUpScene();
	
	//PxParticleSystem* pf;
	PxParticleFluid* pf;
	

	//Create particle system in Physx SDK
	//set immutable properties
	
	PxU32 maxParticles = 4000;
	bool perParticleRestOffset = false;


	pf = g_Physics->m_Physics->createParticleFluid(maxParticles, perParticleRestOffset);
	
	

	pf->setRestParticleDistance(.3f);
	pf->setDynamicFriction(0.1);
	pf->setStaticFriction(0.1);
	pf->setDamping(0.1);
	pf->setParticleMass(.1);
	pf->setRestitution(0);
	
	pf->setParticleBaseFlag(PxParticleBaseFlag::eCOLLISION_TWOWAY, true);
	pf->setStiffness(100);

	if(pf)
	{
		g_Physics->m_PhysicsScene->addActor(*pf);
		m_particleEmitter = new ParticleFluidEmitter(maxParticles, PxVec3(0, 7, 0), pf, .1);
		m_particleEmitter->setStartVelocityRange(-2.0f, 0, -2.0f, 2.0f, 0.0f, 2.0f);
	}
	
}

PhysxFluid::~PhysxFluid()
{
	delete g_Physics;
}


void PhysxFluid::SetUpScene()
{

	//Add a plane
	PxTransform pose = PxTransform(PxVec3(0.0f, 0, 0.0f), PxQuat(PxHalfPi, PxVec3(0.0f, 0.0f, 1.0f)));
	PxRigidStatic* plane = PxCreateStatic(*g_Physics->m_Physics, pose, PxPlaneGeometry(), *g_Physics->m_PhysicsMaterial);
	
	


	//g_PhysicsMaterial we created with the first tutorial so review on that.
	const PxU32 numShapes = plane->getNbShapes();
	//g_Physics->m_PhysicsScene->addActor(*plane);
	



	PxBoxGeometry side1(4.5, 1, .5);
	PxBoxGeometry side2(.5, 1, 4.5);
	pose = PxTransform(PxVec3(0.0f, 0, 4.0));

	PxRigidStatic*box = PxCreateStatic(*g_Physics->m_Physics, pose, side1, *g_Physics->m_PhysicsMaterial);
	g_Physics->m_PhysicsScene->addActor(*box);
	g_PhysXActors.push_back(box);
	
	
	pose = PxTransform(PxVec3(0.0f, 0, -4.0f));
	box = PxCreateStatic(*g_Physics->m_Physics, pose, side1, *g_Physics->m_PhysicsMaterial);
	
	g_Physics->m_PhysicsScene->addActor(*box);
	g_PhysXActors.push_back(box);
	
	pose = PxTransform(PxVec3(4.0f, 0, 0));
	box = PxCreateStatic(*g_Physics->m_Physics, pose, side2, *g_Physics->m_PhysicsMaterial);
	g_Physics->m_PhysicsScene->addActor(*box);
	g_PhysXActors.push_back(box);
	
	pose = PxTransform(PxVec3(-4.0f, 0, 0));
	box = PxCreateStatic(*g_Physics->m_Physics, pose, side2, *g_Physics->m_PhysicsMaterial);
	g_Physics->m_PhysicsScene->addActor(*box);
	g_PhysXActors.push_back(box);
}
	
	
void PhysxFluid::Update(float deltatime)
{
	if(m_particleEmitter)
	{
		m_particleEmitter->update(deltatime);
		m_particleEmitter->renderParticles();
	}
	
}
	
