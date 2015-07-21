#ifndef PHYSICS_H
#define PHYSICS_H

#include <PxPhysicsAPI.h>
#include <PxScene.h>
#include <pvd\PxVisualDebugger.h>
#include <Gizmos.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <iostream>
#include <vector>

using namespace physx;
using namespace glm;

class myAllocator : public PxAllocatorCallback
{
public:

	virtual ~myAllocator() {}

	virtual void* allocate(size_t size, const char* typeName, const char* filename, int line);
	virtual void deallocate(void* ptr);

	
private:

};

class Physx1
{
public:
	Physx1();
	~Physx1();

	void setUpPhysX();
	void Update(float deltaTime);
	void setUpVisualDebugger();
	void setUpTutorial();
	void MakeBlocks();
	void Draw(); //Lol use gizmos for this


private:

	


	//Creating a box;
	//-------------------------

	std::vector<PxRigidDynamic*>m_boxActors;
	PxBoxGeometry* m_box;
	PxRigidDynamic* m_dynamicActor;
	PxTransform* m_transform;

	float density;
	int m_boxCount;
	//-------------------------


	PxFoundation* m_PhysicsFoundation;
	PxPhysics* m_Physics;
	PxScene* m_PhysicsScene;
	PxDefaultErrorCallback m_defaultErrorCallback;
	PxDefaultAllocator m_DefaultAllocatorCallback;
	PxSimulationFilterShader m_defaultFilterShader = PxDefaultSimulationFilterShader;
	PxMaterial* m_PhysicsMaterial;
	PxMaterial* m_boxMaterial;
	PxCooking* m_PhysicsCooker;

	PxAllocatorCallback* m_myCallback;

};






#endif


