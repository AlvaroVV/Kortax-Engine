#pragma once

#include "Core.h"

namespace kortax
{ 
	class KORTAX_API Application
	{
	public:
		Application();
		//Virtual for game clients
		virtual ~Application();

		void Run();

	};

	//Defined by CLIENT 
	Application* CreateApplication();
}

