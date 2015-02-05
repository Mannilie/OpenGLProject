#include "SolarSystemApp.h"

int main()
{
	Application* theApp = new SolarSystemApp();
	if (theApp->Startup() == true)
	{
		while (theApp->Update() == true)
			theApp->Draw();
		theApp->Shutdown();
	}
	delete theApp;
	return 0;
}