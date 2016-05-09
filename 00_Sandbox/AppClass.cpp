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

	m_pBOMngr = BOManager::getInstance();
	
	

	//rotate model to face away from the player
	shipMatrix *= glm::rotate(shipMatrix, 90.0f, vector3(1.0f, 0.0f, 0.0f));
	shipMatrix *= glm::scale(vector3(2.0f,2.0f,2.0f));
	generateAsteroids();
}

void AppClass::Update(void)
{

	//generate walls
	for (float i = 0; i < 15; i++)
	{
		matrix4 topMat = IDENTITY_M4;
		matrix4 rightMat = IDENTITY_M4;
		matrix4 leftMat = IDENTITY_M4;
		matrix4 bottomMat = IDENTITY_M4;
		
		matrix4 topRightMat = IDENTITY_M4;
		matrix4 bottomRightMat = IDENTITY_M4;
		matrix4 topLeftMat = IDENTITY_M4;
		matrix4 bottomLeftMat = IDENTITY_M4;
		
		topMat = glm::translate(vector3(0.0f, 5.0f, -i));
		leftMat = glm::translate(vector3(-5.0f, 0.0f, -i));
		bottomMat = glm::translate(vector3(0.0f, -5.0f, -i));
		rightMat = glm::translate(vector3(5.0f, 0.0f, -i));
		
		topRightMat = glm::translate(vector3(5.0f, 5.0f, -i));
		topLeftMat = glm::translate(vector3(-5.0f, 5.0f, -i));
		bottomRightMat = glm::translate(vector3(5.0f, -5.0f, -i));
		bottomLeftMat = glm::translate(vector3(-5.0f, -5.0f, -i));
		
		float color = .75 - i *.05;
		//m_pMeshMngr->AddCubeToQueue(topMat, vector3(i*.05, i*.05, i*.05));
		m_pMeshMngr->AddCubeToQueue(topMat, vector3(color));
		m_pMeshMngr->AddCubeToQueue(rightMat, vector3(color));
		m_pMeshMngr->AddCubeToQueue(leftMat, vector3(color));
		m_pMeshMngr->AddCubeToQueue(bottomMat, vector3(color));

		m_pMeshMngr->AddCubeToQueue(topRightMat, vector3(color));
		m_pMeshMngr->AddCubeToQueue(bottomRightMat, vector3(color));
		m_pMeshMngr->AddCubeToQueue(topLeftMat, vector3(color));
		m_pMeshMngr->AddCubeToQueue(bottomLeftMat, vector3(color));
	}

	
	
	
	//Update the system's time
	m_pSystem->UpdateTime();
	
	AddStars();

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

	double timeDiff = m_pSystem->LapClock();
	//move and draw projectiles
	if (projectiles.size() > 0)
	{
		for (int x = 0; x < projectiles.size(); x++)
		{
			projectiles[x].moveProjectile(timeDiff);
			if (projectiles[x].isTargetReached() == false)
			{
				m_pMeshMngr->AddSphereToQueue(projectiles[x].getMatrix(), REBLUE, WIRE);
			}
			else
			{
				projectiles.erase(projectiles.begin() + x);
			}
		}
	}

	if (asteroids.size() > 0)
	{
		for (int x = 0; x < asteroids.size(); x++)
		{
			asteroids[x].moveAsteroid(timeDiff); 
			if (asteroids[x].isTargetReached() == false)
			{
				m_pMeshMngr->AddSphereToQueue(asteroids[x].getMatrix(), REGREEN, SOLID);
			}
			else
			{
				asteroids.erase(asteroids.begin() + x);
			}
		}
	}
	if (asteroids.size() == 0)
	{
		generateAsteroids();
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
		String sName = "Asteroid" + std::to_string(i);
		m_pBOMngr->addObject(sName);
		vector3 pos(rand() % 8 - 4, rand() % 8 - 4, -20);
		vector3 targetPos(rand() % 8 - 4, rand() % 8 - 4, 10);
		asteroids.push_back(Asteroid(pos, targetPos, rand() % 10));
	}
}
void AppClass::AddStars(void)
{
	matrix4 star1 = IDENTITY_M4;
	matrix4 star2 = IDENTITY_M4;
	matrix4 star3 = IDENTITY_M4;
	matrix4 star4 = IDENTITY_M4;
	matrix4 star5 = IDENTITY_M4;
	matrix4 star6 = IDENTITY_M4;
	matrix4 star7 = IDENTITY_M4;
	matrix4 star8 = IDENTITY_M4;
	matrix4 star9 = IDENTITY_M4;
	matrix4 star10 = IDENTITY_M4;

	star1 = glm::translate(vector3(0.0f, 0.0f, -15.0f));
	star2 = glm::translate(vector3(0.0f, 0.0f, -15.0f));
	star3 = glm::translate(vector3(5.0f, 2.0f, -15.0f));
	star4 = glm::translate(vector3(5.0f, 2.0f, -15.0f));
	star5 = glm::translate(vector3(8.0f, -4.0f, -15.0f));
	star6 = glm::translate(vector3(8.0f, -4.0f, -15.0f));
	star7 = glm::translate(vector3(-3.0f, 7.0f, -15.0f));
	star8 = glm::translate(vector3(-3.0f, 7.0f, -15.0f));
	star9 = glm::translate(vector3(-3.0f, -5.0f, -15.0f));
	star10 = glm::translate(vector3(-3.0f, -5.0f, -15.0f));

	star1 = glm::rotate(star1, 45.0f, REAXISZ);
	star2 = glm::rotate(star1, 45.0f, REAXISZ);
	star3 = glm::rotate(star3, 45.0f, REAXISZ);
	star4 = glm::rotate(star3, 45.0f, REAXISZ);
	star5 = glm::rotate(star5, 45.0f, REAXISZ);
	star6 = glm::rotate(star5, 45.0f, REAXISZ);
	star7 = glm::rotate(star7, 45.0f, REAXISZ);
	star8 = glm::rotate(star7, 45.0f, REAXISZ);
	star9 = glm::rotate(star9, 45.0f, REAXISZ);
	star10 = glm::rotate(star9, 45.0f, REAXISZ);

	star1 *= glm::scale(vector3(0.5f));
	star2 *= glm::scale(vector3(0.5f));
	star3 *= glm::scale(vector3(0.5f));
	star4 *= glm::scale(vector3(0.5f));
	star5 *= glm::scale(vector3(0.5f));
	star6 *= glm::scale(vector3(0.5f));
	star7 *= glm::scale(vector3(0.5f));
	star8 *= glm::scale(vector3(0.5f));
	star9 *= glm::scale(vector3(0.5f));
	star10 *= glm::scale(vector3(0.5f));

	m_pMeshMngr->AddCubeToQueue(star1, REWHITE, SOLID);
	m_pMeshMngr->AddCubeToQueue(star2, REWHITE, SOLID);
	m_pMeshMngr->AddCubeToQueue(star3, RERED, SOLID);
	m_pMeshMngr->AddCubeToQueue(star4, RERED, SOLID);
	m_pMeshMngr->AddCubeToQueue(star5, REBLUE, SOLID);
	m_pMeshMngr->AddCubeToQueue(star6, REBLUE, SOLID);
	m_pMeshMngr->AddCubeToQueue(star7, REYELLOW, SOLID);
	m_pMeshMngr->AddCubeToQueue(star8, REYELLOW, SOLID);
	m_pMeshMngr->AddCubeToQueue(star9, REORANGE, SOLID);
	m_pMeshMngr->AddCubeToQueue(star10, REORANGE, SOLID);
}