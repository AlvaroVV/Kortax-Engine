#pragma once

class IKortaxApplication;

class IEntry
{
	IKortaxApplication*	CreateApplication() = 0;
	//bool			DestroyApplication() = 0;

	void			GetDefaultResolution(int& aResX, int& aResY) = 0;

	//void SendInputEvent();
	//void SendSystemEvent();
}

