#include <Kortax\Kortax.h>
#include "Kortax\dbg\Log.h"
//#include <Kortax\entry\Application.h>


class Sandbox //: public kortax::IKortaxApplication
{
public:

	Sandbox()
	{
		kortax::LogString("Sandbox creada! \n");
	}



};

namespace kortax
{
	void testAPI()
	{

	}
}

void kortax::testAPI()
{
	//kortax::LogString("test API \n");
}
/*
kortax::IKortaxApplication* kortax::CreateApplication()
{
	return new Sandbox();
}