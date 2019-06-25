#pragma once

#ifdef KT_PLATFORM_WINDOWS

extern Kortax::Application* Kortax::CreateApplication();

int main(int argc, char** argv)
{
	auto sandbox = Kortax::CreateApplication();
	printf("Game Engine entry point ! \n");
	sandbox->Run();
	delete sandbox;
}

#endif 
