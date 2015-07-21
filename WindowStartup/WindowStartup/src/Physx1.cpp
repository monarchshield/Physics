#include "Physx1.h"

void* myAllocator::allocate(size_t size, const char* typeName, const char* filename, int line)
{
	void* pointer = _aligned_malloc(size, 16);
	return pointer;
}

void myAllocator::deallocate(void* ptr)
{
	_aligned_free(ptr);
}

Physx1::Physx1()
{
	
	m_boxCount = 0;
	setUpPhysX();
	setUpTutorial();
	setUpVisualDebugger();
}

Physx1::~Physx1()
{
	m_PhysicsScene->release();
	m_Physics->release();
	m_PhysicsFoundation->release();
}


void Physx1::Update(float deltaTime)
{
	if (deltaTime <= 0)
		return;

	m_PhysicsScene->simulate(deltaTime);

	while (m_PhysicsScene->fetchResults() == false)
	{
		
		//Dont need to do anything here yet but we have to fetch results
	}

}

void Physx1::MakeBlocks()
{
	PxTransform m_transform(PxVec3(0, 20, 0));
	PxBoxGeometry box(2, 2, 2);
	float density = 50;
	

	m_dynamicActor = PxCreateDynamic(*m_Physics, m_transform, box, *m_PhysicsMaterial, density);
	m_boxActors.push_back(m_dynamicActor);

	int size = m_boxActors.size();

	m_PhysicsScene->addActor(*m_boxActors[size - 1]);

	m_boxCount++;

	std::cout << "Boxes in Scene: " << m_boxCount << "\n";
	
}

void Physx1::setUpVisualDebugger()
{
	//Check if  pvdconnection manager is available on this platform
	if (m_Physics->getPvdConnectionManager() == NULL)
		return;

	//Setup connection parameters
	const char* pvd_host_ip = "127.0.0.1";

	//ip of the pc which is running pvd 
	int port = 5425;

	//TCP port to connect to, where pvd is listening
	unsigned int timeout = 100;

	//Timeout in milliseconds to wait for pvd to respond
	//consoels and remote pcs need  a higher timeout
	PxVisualDebuggerConnectionFlags connectionFlags = PxVisualDebuggerExt::getAllConnectionFlags();

	//and now try to connect pxvisauldebuggerext
	auto theConnection = PxVisualDebuggerExt::createConnection(m_Physics->getPvdConnectionManager(), pvd_host_ip, port, timeout, connectionFlags);


}

void Physx1::setUpPhysX()
{
	m_myCallback = new myAllocator();
	m_PhysicsFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, *m_myCallback, m_defaultErrorCallback);
	m_Physics = PxCreatePhysics(PX_PHYSICS_VERSION, *m_PhysicsFoundation, PxTolerancesScale());
	PxInitExtensions(*m_Physics);
	
	//Create physics material
	m_PhysicsMaterial = m_Physics->createMaterial(0.5f, 0.5f, .5f);
	PxSceneDesc sceneDesc(m_Physics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0, -10.0f, 0);
	sceneDesc.filterShader = &physx::PxDefaultSimulationFilterShader;
	sceneDesc.cpuDispatcher = PxDefaultCpuDispatcherCreate(1);
	m_PhysicsScene = m_Physics->createScene(sceneDesc);




	
}

void Physx1::Draw()
{
	
	for (int i = 0; i < m_boxActors.size(); i++)
	{
		mat4* identity;

		PxTransform position = m_boxActors[i]->getGlobalPose();
		vec3 pos = vec3(position.p.x, position.p.y, position.p.z);
		

		vec3 rot1 = vec3(position.q.getBasisVector0().x, position.q.getBasisVector0().y, position.q.getBasisVector0().z);
		vec3 rot2 = vec3(position.q.getBasisVector1().x, position.q.getBasisVector1().y, position.q.getBasisVector1().z);
		vec3 rot3 = vec3(position.q.getBasisVector2().x, position.q.getBasisVector2().y, position.q.getBasisVector2().z);

		identity = new mat4(rot1.x, rot1.y, rot1.z, 1,
							rot2.x, rot2.y, rot2.z, 1,
							rot3.x, rot3.y, rot3.z, 1,
							pos.x, pos.y, pos.z, 1);




		//std::cout << "Cube Position: " << pos.x << "," << pos.y << "," << pos.z << "\n";

	
		//Just render out stuff with gizmos here
		Gizmos::addAABBFilled(pos, vec3(2, 2, 2), vec4(1, 0, 0, 1), identity);
		//Position  //Width (X), Height(Y), Length(Z)  //Colour(vec4) //mat4 Identity Matrix
	}

	
}


void Physx1::setUpTutorial()
{
	//add a plane
	PxTransform pose = PxTransform(PxVec3(0, 5, 0), PxQuat(PxHalfPi * 1.0f, PxVec3(0, 0, 1)));
	PxRigidStatic* plane = PxCreateStatic(*m_Physics, pose, PxPlaneGeometry(), *m_PhysicsMaterial);

	//add it to the physx scene
	m_PhysicsScene->addActor(*plane);

}



