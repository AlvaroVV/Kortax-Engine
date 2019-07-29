#pragma once

#include "Core.h"
#include "dbg\Log.h"
#include "Kortax\entry\Application.h"


namespace kortax
{
	//Must be implemented in client side
	extern IKortaxApplication* CreateApplication();
	//extern bool DestroyApplication();

	//extern void GetDefaultResolution(int& aResX, int& aResY);

	//SEND EVENTS
}

int main(int argc, char** argv)
{
	kortax::LogString("Start kortax Engine!");
	kortax::IKortaxApplication* app = kortax::CreateApplication();
	app->Init();
	delete app;
}
