/*----------------------------------------------
Programmers:
Alex Harper
Jason Morris
Mario Chuman
Stephen Lewis

Date: 2016/05
----------------------------------------------*/

#include "AppClass.h"

//Initializing the main program using winappi
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//Creating a ReEngAppClass object providing the arguments and the window handler
	AppClass Application(hInstance, lpCmdLine, nCmdShow, false);
	//RE_RUNNING the Application's Main Loop
	Application.Run();
	//Finalizing the Application
	return 0;
}