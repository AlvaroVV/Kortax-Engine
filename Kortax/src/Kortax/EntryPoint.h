#pragma once

#ifdef KT_PLATFORM_WINDOWS

extern Kortax::Application* Kortax::CreateApplication();

int main(int argc, char** argv)
{
	auto sandbox = Kortax::CreateApplication();
	const char* testName = "Kortax";
	Kortax::LogFormatString("Game Engine < %s > entry point ! \n", testName);
	sandbox->Run();
	delete sandbox;
}

#endif 
