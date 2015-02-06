#include "CameraAndProjections.h"

int main()
{
	CameraAndProjections theApp;

	theApp.SetDefault(1280, 720, "Manny's Project");

	if (theApp.Startup() == false) //Checks for error messages (< 0)
	{
		return -1;
	}
	while (theApp.Update() == true) //Updates apps while there are no errors
	{
		theApp.Draw();
	}
	theApp.Shutdown();
	return 0;
}