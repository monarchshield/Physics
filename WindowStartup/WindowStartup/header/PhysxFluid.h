#ifndef PHYSX_FLUID_H
#define PHYSX_FLUID_H

#include "Physx1.h"
#include "ParticleEmitter.h"
#include "ParticleFluidEmitter.h"

class PhysxFluid
{
public:

	PhysxFluid(Physx1* physics);
	~PhysxFluid();
	
	void SetUpScene();
	void Update(float deltatime);
	
	std::vector<PxRigidStatic*> g_PhysXActors;
 	

private:
	Physx1* g_Physics;
	ParticleFluidEmitter* m_particleEmitter;
};

#endif