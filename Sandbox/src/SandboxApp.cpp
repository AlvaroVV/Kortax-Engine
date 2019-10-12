#include "Kortax.h"


class Sandbox : public kortax::IKortaxApplication
{
public:

	Sandbox()
	{
		kortax::LogString("Sandbox creada! \n");
	}

	virtual bool Init()
	{
		kortax::LogString("Init del Sandbox!");
		return true;
	}

};


kortax::IKortaxApplication* kortax::CreateApplication()
{
	return new Sandbox();
}

