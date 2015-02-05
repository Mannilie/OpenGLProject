#include "SolarSystemApp.h"

int main()
{
	Application* theApp = new SolarSystemApp();
	if (theApp->Startup() >= 0) //Checks for error messages (< 0)
	{
		while (theApp->Update() >= 0) //Exits upon (< 0)
			theApp->Draw();
		theApp->Shutdown();
	}
	delete theApp;
	return 0;
}