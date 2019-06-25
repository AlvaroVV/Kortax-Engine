#include <Kortax.h>

class Sandbox : public Kortax::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}

};

Kortax::Application* Kortax::CreateApplication()
{
	return new Sandbox();
}