#include <Windows.h>
#include "../../dbg/Log.h"

/*
* Callback used to process the Windows' messages (user and OS)
* @param hwnd, window handle
* @param msg, the message code,
* @param wParam and lParam, contains additional data depending on message
* @return LRESULT, integer value returned to Windows, the program response.
*/
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wPAram, LPARAM lParam)
{
	//Default Message Handling
	switch (msg)
	{
		case WM_LBUTTONDOWN:
		{
			char fileName[MAX_PATH];
			HINSTANCE hInstance = GetModuleHandle(NULL);

			GetModuleFileName(hInstance, fileName, MAX_PATH);
			MessageBox(hwnd, fileName, "El programa es: ", MB_OK | MB_ICONINFORMATION);
		}
		break;
		case WM_CLOSE: 
			DestroyWindow(hwnd);
			break;
		case WM_DESTROY:
			PostQuitMessage(0); //returns false in getMessage so stops loop
			break;
		default:
			return DefWindowProc(hwnd, msg, wPAram, lParam);

	}
}

/* WinMain is the Main function in Windows
* 
* @param hInstance, handle to executable module (.exe)
* @param hPrevInstance, deprecated, always null
* @param lpCmdLine, arguments for command line
* @param nCmdShow, flag that says whether the main app will be min, max or shown normally
*/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PSTR lpCmdLine, int nCmdShow)
{

	//REGISTER MAIN CLASS
	const char g_szClassName[] = "myWindowClass";

	WNDCLASSEX  wc = {}; //Window structure. Gestiona mejor los estilos que WNDCLASS
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW; //Redeaw when horizontal and vertical movement.
	wc.lpfnWndProc = WndProc; //Puntero al procedure
	wc.cbClsExtra = 0; //Cantidad extra de asignacion de memoria para datos
	wc.cbWndExtra = 0; //Cantidad extra de memoria por ventana de este tipo.
	wc.hInstance = hInstance; //Handle a la instancia
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); //Handle al icono grande (32x32) Alt + Tab
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);//HAndle al icono pequeño (16x16) Barra de tareas y esquina superior izquierda
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); //Cursor en ventana
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); //Background color
	wc.lpszMenuName = NULL; //Reource name of the calss menu
	wc.lpszClassName = g_szClassName; //Nombre de la ventana

	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Goodbye, cruel world!", "Error!", MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}


	//CREATE WINDOW
	HWND hwnd;
	hwnd = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		g_szClassName,
		"The title of my window",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 240, 120,
		NULL, NULL, hInstance, NULL);

	if (!hwnd)
	{
		MessageBox(NULL, "Creación de ventana fallida", "Error!", MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg); //Related with keyboard. Translates keystrokes into characters.
		DispatchMessage(&msg); //Calls the window procedure
	}
	
}


