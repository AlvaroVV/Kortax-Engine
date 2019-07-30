#pragma once

#include "Kortax\Core.h"

namespace kortax
{

	class  IKortaxApplication
	{
	public:
		
		virtual bool Init() = 0;
		//virtual bool Run() = 0;
		//virtual bool End() = 0;

		//virtual const char* GetApplicationName() = 0;
		

	};

	 IKortaxApplication*  CreateApplication();
}

