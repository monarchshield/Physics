#include "Application.h"

#include "stb-master\stb_image.h"


void OnMouseButton(GLFWwindow*, int b, int a, int m)
{
	TwEventMouseButtonGLFW(b, a);
}
void OnMousePosition(GLFWwindow*, double x, double y)
{
	TwEventMousePosGLFW((int)x, (int)y);
}
void OnMouseScroll(GLFWwindow*, double x, double y)
{
	TwEventMouseWheelGLFW((int)y);
}
void OnKey(GLFWwindow*, int k, int s, int a, int m)
{
	TwEventKeyGLFW(k, a);
}
void OnChar(GLFWwindow*, unsigned int c)
{
	TwEventCharGLFW(c, GLFW_PRESS);
}
void OnWindowResize(GLFWwindow*, int w, int h)
{
	TwWindowSize(w, h);
	glViewport(0, 0, w, h);
}



Application::Application()
{
	if(glfwInit() == false)
		return;

	window = glfwCreateWindow(1680,1050,"Computer Graphics" , nullptr,nullptr);
	camera = new FlyCamera();
	m_previousTime = 0;
	m_currentTime = 0;
	m_DeltaTime = 0;
	m_cooldown = 2;

	if(window == nullptr)
	{
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(window);

	if(ogl_LoadFunctions() == ogl_LOAD_FAILED)
	{
		glfwMakeContextCurrent(window);
		glfwDestroyWindow(window);
		glfwTerminate();
		return;
	}



	


	m_physics = new Physx1();
	m_particleEmitter = new PhysxFluid(m_physics);
	m_RagDoll = new RagDoll(m_physics);
	m_player = new KinematicController(1, 1, vec3(0, 10, 0), m_physics);

	m_skybox = new Skybox();



	//Create the layer controller
	
	
	m_rigidbodies.push_back(new RigidBody(vec3(0, 14, 0), vec3(50.0f, 0, 0), 2, 10));
	m_rigidbodies[0]->SetID(0);

	m_rigidbodies.push_back(new RigidBody(vec3(100, 14, 0), vec3(0, 0, 0), 2, 10));
	m_rigidbodies[1]->SetID(1);


	for (unsigned int i = 0; i < m_rigidbodies.size(); i++)
	{
		m_rigidbodies[i]->SetTimeStep(.5f);
	
	
	
		if (i = 1)
			m_rigidbodies[i]->SetColour(vec4(0, 1, 0, 1));
	}



	//m_RigidSphere->SetTimeStep(.5f);
	//m_RigidSphere1->SetTimeStep(.5f);

	Gizmos::create();
	


	
	for (unsigned int i = 0; i < 10; i++)
	{
		m_entities.push_back(new Entity(vec3(0, 15, 0), 10));
	}

	//boy do I like to eat some fresh penguin

	glfwSetMouseButtonCallback(window, OnMouseButton);
	glfwSetCursorPosCallback(window, OnMousePosition);
	glfwSetScrollCallback(window, OnMouseScroll);
	glfwSetKeyCallback(window, OnKey);
	glfwSetCharCallback(window, OnChar);
	glfwSetWindowSizeCallback(window, OnWindowResize);
	
	TwInit(TW_OPENGL_CORE, nullptr);
	TwWindowSize(1280, 720);

	m_bar = TwNewBar("Debug Console");
	TwAddSeparator(m_bar, "Camera position:", "");
	
	TwAddVarRW(m_bar, "X position: ", TW_TYPE_FLOAT, &camera->xPosition, "");
	TwAddVarRW(m_bar, "y position: ", TW_TYPE_FLOAT, &camera->yPosition, "");
	TwAddVarRW(m_bar, "z position: ", TW_TYPE_FLOAT, &camera->zPosition, "");
	TwAddVarRW(m_bar, "Camera Speed: ", TW_TYPE_FLOAT, &camera->Speed, "");



}

Application::~Application()
{
	glfwDestroyWindow(window);
	Gizmos::destroy();
	glfwTerminate();
	TwTerminate();


}

void Application::RunGame()
{

	while (glfwWindowShouldClose(window) == false && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS) 
	{
		
		
		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glDepthFunc(GL_LESS);
		glClearColor(0.25f,0.25f,0.25f,1);

		Update();
		Draw();

		////Update Loop Put all Crap here
		//currentTime = (float)glfwGetTime();
		//DeltaTime = currentTime - previousTime;
		//previousTime = currentTime;
	
		TwDraw();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}	
}

void Application::Update()
{

	Gizmos::clear();
	//Gizmos::clear();

	m_currentTime = (float)glfwGetTime();
	m_DeltaTime = m_currentTime - m_previousTime;
	m_previousTime = m_currentTime;
	m_cooldown -= m_DeltaTime;


	//for (unsigned int i = 0; i < m_entities.size(); i++)
	//{
	//	m_entities[i]->Update(m_DeltaTime);
	//}
	//if (m_cooldown < 0)
	//{
	//	m_cooldown = .90f;
	//	m_physics->MakeBlocks();
	//	
	//}

#pragma region UpdateMyPhysics
	for (unsigned int i = 0; i < m_rigidbodies.size(); i++)
	{
		m_rigidbodies[i]->Update(m_DeltaTime);
	
		for (unsigned int j = 0; j < m_rigidbodies.size(); j++)
		{
			if (i == j)
				break;
		
			else
				m_rigidbodies[i]->CheckCollision(m_rigidbodies[j]);
		}
	
	}
#pragma endregion
	
#pragma region PhysxUpdate

	//Physx stuff!
	//m_particleEmitter->Update(m_DeltaTime);
	//m_physics->Update(m_DeltaTime);
#pragma endregion

	camera->update(m_DeltaTime);
	camera->getWorldTransform();
}

void Application::Draw()
{

#pragma region MyPhysics
	Gizmos::addAABBFilled(vec3(0,2,0), vec3(250, 1, 250), vec4(0, 0, 1, 1), nullptr);
	Gizmos::addAABB(vec3(0, 35, 0), vec3(15, 15, 15), vec4(0, 1, 0, 1), nullptr);
	
	for (unsigned int i = 0; i < m_rigidbodies.size(); i++)
	{
		m_rigidbodies[i]->Draw();
	}
#pragma endregion

#pragma region PhysX stuff
	//m_physics->Draw();
	//m_player->Draw();
#pragma endregion

	//Gizmos::addSphere(vec3(0,0,0), 5, 5, 10, vec4(1, 0, 0, 1));
	

	//m_skybox->Draw(camera);
	//for (unsigned int i = 0; i < m_entities.size(); i++)
	//{
	//	m_entities[i]->Draw();
	//}

	Gizmos::draw(camera->getProjectionTransform());
}

