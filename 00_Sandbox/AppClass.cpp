#include "AppClass.h"
void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("Space Debris"); // Window Name

	// Set the clear color based on Microsoft's CornflowerBlue (default in XNA)
	//if this line is in Init Application it will depend on the .cfg file, if it
	//is on the InitVariables it will always force it regardless of the .cfg
	m_v4ClearColor = vector4(0.0f, 0.0f, 0.0f, 0.0f);

	//hide cursor
	ShowCursor(FALSE);
}

void AppClass::InitVariables(void)
{
	//Reset the selection to -1, -1
	m_selection = std::pair<int, int>(-1, -1);
	//Set the camera position
	m_pCameraMngr->SetPositionTargetAndView(
		vector3(0.0f, 0.0f, 15.0f),//Camera position
		vector3(0.0f, 0.0f, 0.0f),//What Im looking at
		REAXISY);//What is up

	//Load a model onto the Mesh manager
	m_pMeshMngr->LoadModel("Zelda\\MasterSword.bto", "Ship");

	//rotate model to face away from the player
	shipMatrix *= glm::rotate(shipMatrix, 90.0f, vector3(1.0f, 0.0f, 0.0f));
	shipMatrix *= glm::scale(vector3(2.0f,2.0f,2.0f));
	generateAsteroids();
}

void AppClass::Update(void)
{
	//Update the system's time
	m_pSystem->UpdateTime();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update();

	//First person camera movement
	if (m_bFPC == true)
		CameraRotation();

	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();
	//print info into the console
	//printf("FPS: %d            \r", nFPS);//print the Frames per Second
	//Print info on the screen
	//m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), REYELLOW);
	m_pMeshMngr->PrintLine("Space Debris", REWHITE);

	/*m_pMeshMngr->Print("Selection: ");
	m_pMeshMngr->PrintLine(m_pMeshMngr->GetInstanceGroupName(m_selection.first, m_selection.second), REYELLOW);*/
	
	m_pMeshMngr->Print("FPS:");
	m_pMeshMngr->Print(std::to_string(nFPS), RERED);

	//draw a wire sphere at the mouse location
	POINT mousePos;
	GetCursorPos(&mousePos);
	float windowWidth = static_cast<float>(m_pSystem->GetWindowWidth());
	float windowHeight = static_cast<float>(m_pSystem->GetWindowHeight());

	float mouseX = MapValue(static_cast<float>(mousePos.x), 0.0f, 1920.0f, -20.0f, 20.0f);
	float mouseY = MapValue(static_cast<float>(mousePos.y), 0.0f, 1080.0f, 10.0f, -10.0f);
	matrix4 mouseMat = glm::translate(vector3(mouseX, mouseY, -10.0f));
	m_pMeshMngr->AddSphereToQueue(mouseMat, RERED, WIRE);

	//set the model matrix for the ship
	m_pMeshMngr->SetModelMatrix(shipMatrix, "Ship");

	//move and draw projectiles
	if (projectiles.size() > 0)
	{
		for (int x = 0; x < projectiles.size(); x++)
		{
			projectiles[x].moveProjectile(m_pSystem->LapClock());
			m_pMeshMngr->AddSphereToQueue(projectiles[x].getMatrix(), REBLUE, WIRE);
		}
	}

	if (asteroids.size() > 0)
	{
		for (int x = 0; x < asteroids.size(); x++)
		{
			asteroids[x].moveAsteroid(m_pSystem->LapClock());
			m_pMeshMngr->AddSphereToQueue(asteroids[x].getMatrix(), REGREEN, WIRE);
		}
	}
		
		//Adds all loaded instance to the render list
	m_pMeshMngr->AddInstanceToRenderList("ALL");
}

void AppClass::Display(void)
{
	//clear the screen
	ClearScreen();

	//Render the grid based on the camera's mode:
	switch (m_pCameraMngr->GetCameraMode())
	{
	default: //Perspective
		m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::XY); //renders the XY grid with a 100% scale
		break;
	case CAMERAMODE::CAMROTHOX:
		m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::YZ, RERED * 0.75f); //renders the YZ grid with a 100% scale
		break;
	case CAMERAMODE::CAMROTHOY:
		m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::XZ, REGREEN * 0.75f); //renders the XZ grid with a 100% scale
		break;
	case CAMERAMODE::CAMROTHOZ:
		m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::XY, REBLUE * 0.75f); //renders the XY grid with a 100% scale
		break;
	}
	
	m_pMeshMngr->Render(); //renders the render list

	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

void AppClass::Release(void)
{
	super::Release(); //release the memory of the inherited fields
}

void AppClass::generateAsteroids(void)
{
	for (int i = 0; i < 10; i++)
	{

		vector3 pos(rand() % 8-4, rand() % 8-4, -20);
		vector3 targetPos(rand() % 8-4, rand() % 8-4, 10);
		asteroids.push_back(Asteroid(pos, targetPos, rand() % 10));
	}
}