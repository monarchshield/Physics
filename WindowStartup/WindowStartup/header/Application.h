#ifndef APPLICATION_H
#define APPLICATION_H


#include <gl_core_4_4.h>
#include <GLFW\glfw3.h>
#include "Skybox.h"
#include "AntTweakBar.h"
#include <Gizmos.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "Camera.h"
#include "FlyCamera.h"
#include "Physx1.h"
#include <RigidBody.h>
#include "Entity.h"
#include "PhysxFluid.h"


class Texture;
class ProceduralGen;
class Skybox;
class ObjLoader;
class FbxLoader;
class Physx1;
class RigidBody;

class Application
{
public:
	Application();
	~Application();
	
	void RunGame();
	void Update();
	void Draw();
	
	

private:
	

	TwBar* m_bar;
	Skybox* m_skybox;
	GLFWwindow * window;
	FlyCamera * camera;
	Physx1* m_physics;
	float m_previousTime;
	float m_currentTime;
	float m_DeltaTime;
	float m_cooldown;


	RigidBody* m_RigidSphere;
	RigidBody* m_RigidSphere1;

	PhysxFluid* m_particleEmitter;

	std::vector<RigidBody*> m_rigidbodies;
	std::vector<Entity*> m_entities;
	
	int m_vertexCount;



};







#endif