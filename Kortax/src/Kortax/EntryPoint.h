#pragma once

#ifdef KT_PLATFORM_WINDOWS

extern kortax::Application* kortax::CreateApplication();

/*
int main(int argc, char** argv)
{
	MyLog log;
	log.test();
	auto sandbox = Kortax::CreateApplication();
	const char* testName = "Kortax";
	Kortax::LogFormatString("Game Engine < %s > entry point ! \n", testName);
	sandbox->Run();
	delete sandbox;
}
*/
#endif 
