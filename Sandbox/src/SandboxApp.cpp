#include <Kortax.h>

class Sandbox : public kortax::Application
{
public:
	Sandbox()
	{
		kortax::LogString("Sandbox creada! \n");
	}

	~Sandbox()
	{

	}

};

kortax::Application* kortax::CreateApplication()
{
	return new Sandbox();
}