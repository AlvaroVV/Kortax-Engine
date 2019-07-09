#include <Kortax.h>

class Sandbox : public Kortax::Application
{
public:
	Sandbox()
	{
		Kortax::LogString("Sandbox creada! \n");
	}

	~Sandbox()
	{

	}

};

Kortax::Application* Kortax::CreateApplication()
{
	return new Sandbox();
}