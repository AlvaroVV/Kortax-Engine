
#include <Windows.h>
#include <gl\GL.h>
#include <gl\GLU.h>

//---------- Examples-------------
//#include "Examples\ShapeAndColors.h"
#include "Examples\SimpleTexture.h"



//--------- OPENGL ---------
HDC		hDC = NULL;		//Private GDI Device Context
HGLRC	hRC = NULL;		//Permanent Rendering Context
HWND	hWnd = NULL;	//Holds the Window Handle
HINSTANCE hInstance = NULL; //Holds the App Instance


bool keys[256];			//Array used for keyboard routine
bool active = TRUE;		//Variable to control minimize
bool fullscreen = TRUE; //Control fullscreen mode

GLProgram* glProgram = nullptr;

/*
* Callback used to process the Windows' messages (user and OS)
* @param hwnd, window handle
* @param msg, the message code,
*@param wParam and lParam, contains additional data depending on message
* @return LRESULT, integer value returned to Windows, the program response.
*/
LRESULT CALLBACK WndProc(HWND , UINT , WPARAM , LPARAM );



/*
* @param GLsizei, non-negative binary integer, for sizes
* @return GLvoid, used for cross-platform
*/
GLvoid ReSizeGLScene(GLsizei width, GLsizei height)
{
	if (height == 0)
	{
		height = 1;
	}
	
	glViewport(0, 0, width, height);

	//--perspective view---
	//For now just know that it HAS to be if we want perspective view
	glMatrixMode(GL_PROJECTION);	//Select the projection matrix
	glLoadIdentity();				//Reset the projection matrix

	//calculate aspect ratio of the window
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);

	glMatrixMode(GL_MODELVIEW); //Select the model view Matrix, encargado de los datos del modelo
	glLoadIdentity();			//Reset the model view matrix
}

/*
* All setup for OpenGL goes here, ponemos el color de la ventana, activamos el depth buffer, activamos el shading smooth
* Se llama cuando la ventana de OpenGL ha sido creada.
*/
int InitGL(GLvoid)
{

	glProgram->Init();

	return TRUE;	//Everything OK
}

/*
*	Section to draw
*/
int DrawGLScene(GLvoid)
{
	glProgram->Draw();
	return TRUE;
}

/*
* Primero debemos liberar el Rendering Context, después el Device Context y finalmente el Window Handle
*/
GLvoid KillGLWindow(GLvoid)
{
	if (fullscreen)
	{
		//Pasando NULL y 0 obligamos a Windows a usar los valores almacenados en el registro (la resolución por defecto, bit depth, frecuencia)
		ChangeDisplaySettings(NULL, 0);
		ShowCursor(TRUE);
	}

	if (hRC)
	{
		//Si tenemos Rendering Context lo desatacheamos del Device Context si es posible.
		if (!wglMakeCurrent(NULL, NULL))
		{
			//Ventana padre, Mensaje, Título, Botón de OK e icono informativo.
			MessageBox(NULL, "Release of DC and RC Failed", "Shotdown ERROR", MB_OK | MB_ICONINFORMATION);
		}

		//Ahora intentamos borrar el Rendering Context
		if (!wglDeleteContext(hRC))
		{
			MessageBox(NULL, "Release of Rendering Context Failed", "Shotdown ERROR", MB_OK | MB_ICONINFORMATION);
		}
		hRC = NULL;
	}

	//Comprobamos si tenemos Device Context, si lo tenemos, lo liberamos.
	if (hDC && !ReleaseDC(hWnd, hDC))
	{
		MessageBox(NULL, "Release of Device Context Failed", "Shotdown ERROR", MB_OK | MB_ICONINFORMATION);

		hDC = NULL;
	}

	//Comprobamos si tenemos Window Handle. Destruimos con DestroyWindow
	if (hWnd && !DestroyWindow(hWnd))
	{
		MessageBox(NULL, "Could not release HWnd", "Shotdown ERROR", MB_OK | MB_ICONINFORMATION);
		hWnd = NULL;
	}

	//Por último desregistramos nuestra Window Class. Evitamos error de "Window Class already registered"
	if (!UnregisterClass("OpenGL", hInstance))
	{
		MessageBox(NULL, "Could not unregister class", "Shotdown ERROR", MB_OK | MB_ICONINFORMATION);
		hInstance = NULL;
	}

	//Borramos el programa
	if (glProgram != nullptr)
		delete glProgram;
}

BOOL CreateGLWindow(const char* title, int width, int height, int bits, bool fullScreenFlag)
{
	GLuint pixelFormat;		//Holds the results after searching for a match
	WNDCLASS wc;			//Window Class Structure
	//How the window look and behaves
	DWORD dwExStyle;		//Window Extended Style
	DWORD dwStyle;			//Window Style
	//Position and size. The borders take some of our resolution
	RECT windowRect;
	windowRect.left = (long)0;
	windowRect.right = (long)width;
	windowRect.top = (long)0;
	windowRect.bottom = (long)height;
	fullscreen = fullScreenFlag;

	hInstance = GetModuleHandle(NULL); //Grab an Instance for our Window
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC; //Redraw on move and own DC.
	wc.lpfnWndProc = (WNDPROC)WndProc;
	wc.cbClsExtra = 0;	//Extra data
	wc.cbWndExtra = 0;	//Extra data
	wc.hInstance = hInstance;	//The instance
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);	//Default Icon
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); //Arrow Pointer
	wc.hbrBackground = NULL;	//No Background required for GL
	wc.lpszMenuName = NULL;		// No menu
	wc.lpszClassName = "OpenGL";	//Set the Class name

	if (!RegisterClass(&wc))
	{
		MessageBox(NULL, "Failed to register the Window Class", "Shotdown ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;
	}

	if (fullscreen)
	{
		DEVMODE dmScreenSettings;	//Estructura con info del Device Mode
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings); //Set this number to sizeof(DEVMODE) to indicate the version of the DEVMODE structure being used.
		dmScreenSettings.dmPelsWidth = width; //Selected Screen width
		dmScreenSettings.dmPelsHeight = height; //Selected Screen height
		dmScreenSettings.dmBitsPerPel = bits; //Color resolution
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT; //Specifies whether certain members of the DEVMODE have been initialized

		//Si no podemos poner el fullscreen preguntamos que hacer
		if (LONG value = ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
		{
			DWORD error = GetLastError();
			if (MessageBox(NULL, "The resquest fullscreen mode is not supported by the video card. Use Windowed Instead?", "Kortax GL", MB_YESNO | MB_ICONEXCLAMATION) == IDYES)
			{
				fullscreen = FALSE;
			}
			else
			{
				MessageBox(NULL, "Program will now close", "ERROR", MB_OK | MB_ICONEXCLAMATION);
				return FALSE;
			}
		}
	}

	if (fullscreen)
	{
		dwExStyle = WS_EX_APPWINDOW;	//Forces top-level window onto the taskbar
		dwStyle = WS_POPUP;	//Style which has no border around it
		ShowCursor(FALSE); //Disable mouse if program is not interactive
	}
	else
	{
		dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE; //Windowedge gives the window a more 3D look
		dwStyle = WS_OVERLAPPEDWINDOW; //Window with title bar, sizing border, window menu and min/max buttons
	}

	//Adjust window to TRUE resquested size, including borders.
	AdjustWindowRectEx(&windowRect, dwStyle, FALSE, dwExStyle);

	if (!(hWnd = CreateWindowEx(dwExStyle,	//Extended Style
		"OpenGL",							//Class Name
		title,								//Title window name
		dwStyle |							//Selected window style
		WS_CLIPSIBLINGS |					//Required Window style
		WS_CLIPCHILDREN ,					//Required Window style
		0, 0,								//Window position
		windowRect.right - windowRect.left, //Calculate adjusted window width
		windowRect.bottom - windowRect.top,	//Calculate adjusted window height
		NULL,								//No parent window
		NULL,								//No Menu
		hInstance,							//Instance
		NULL)))								//Don't pass anything to WM_CREATE
	{
		DWORD error = GetLastError();
		KillGLWindow();
		MessageBox(NULL, "Unable to create the Window", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;
	}

	static PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),	//Size of pixel format descriptor
		1,								//Version Number
		PFD_DRAW_TO_WINDOW |			//Format must support Window
		PFD_SUPPORT_OPENGL |			//Format must support Opengl
		PFD_DOUBLEBUFFER,				//Format must support double buffering
		PFD_TYPE_RGBA,					//Request an RGBA Format
		bits,							//Select our color depth
		0,0,0,0,0,0,					//Color bits ignored
		0,								//No alpha buffer
		0,								//Shift bit ignored
		0,								//No accumulation buffer
		0,0,0,0,						//Accumulation bits ignored
		16,								//16bits z-buffer (Depth buffer)
		0,								//No Stencil Buffer
		0,								//No Auxiliary buffer
		PFD_MAIN_PLANE,					//Main Drawing Layer
		0,								//Reserved
		0,0,0							//Layer Masks ignored
	};

	//Attempt to get the DEVICE CONTEXT
	if (!(hDC = GetDC(hWnd)))
	{
		KillGLWindow();
		MessageBox(NULL, "Unable to create a GL Device Context", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	//Find matching Pixel format
	if (!(pixelFormat = ChoosePixelFormat(hDC, &pfd)))
	{
		KillGLWindow();
		MessageBox(NULL, "Unable to find a suitable pixel format", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	//Set Pixel format
	if (!SetPixelFormat(hDC, pixelFormat,&pfd))
	{
		KillGLWindow();
		MessageBox(NULL, "Can't Set the PixelFormat", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;
	}
	//Create Rendering Context
	if (!(hRC = wglCreateContext(hDC)))
	{
		//DWORD error = GetLastError();
		KillGLWindow();
		MessageBox(NULL, "Can't create a GL Rendering Context", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	//Make Rendering Context Active
	if (!wglMakeCurrent(hDC, hRC))
	{
		KillGLWindow();
		MessageBox(NULL, "Can't activate the Rendering Context", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	ShowWindow(hWnd, SW_SHOW);	//Show the Window
	SetForegroundWindow(hWnd);	//Higher Priority
	SetFocus(hWnd);				//Keyboard focus to the window
	ReSizeGLScene(width, height);	//Set up our perspective screen

	if(!InitGL())
	{
		KillGLWindow();
		MessageBox(NULL, "Initialization failed", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	return TRUE;

}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		//Si la ventana es minimizada, ya no está activa
		case WM_ACTIVATE:			//Window Activate Message
		{
			if (!HIWORD(wParam))
			{					//Check minimization state
				active = TRUE;
			}
			else
			{
				active = FALSE;
			}
			return 0;
		}
		case WM_SYSCOMMAND:			//System Commands
		{
			switch (wParam)
			{
				case SC_SCREENSAVE:	//Screensaver trying to start
				case SC_MONITORPOWER://Monitor entering power save
					return 0;		//Prevent
			}
			break;
		}
		case WM_CLOSE:				//Close message
		{
			PostQuitMessage(0);		//Send Quit message. The main loop will intercept it and stop.
			return 0;
		}
		case WM_KEYDOWN:			//Key pressed message
		{
			keys[wParam] = TRUE;	//Mark key as true
			return 0;
		}
		case WM_KEYUP:				//Key released
		{
			keys[wParam] = FALSE;	//Mark key as false
			return 0;
		}
		case WM_SIZE:
		{
			ReSizeGLScene(LOWORD(lParam), HIWORD(lParam)); //Loword = Width, Hiword = height
			return 0;
		}
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam); //Windows handle default
}


int WINAPI WinMain( HINSTANCE hInstance,
	 HINSTANCE hPrevInstance,
	LPSTR    lpCmdLine,
	int       nCmdShow)
{
	MSG msg;	//Windows Message Structure
	BOOL done = FALSE; //Bool variable to exit

	glProgram = new SimpleTexture();

	if (MessageBox(NULL, "Would you like to run it in fullscreen?", "Start Fullscreen?", MB_YESNO | MB_ICONQUESTION) == IDNO)
	{
		fullscreen = FALSE;
	}

	//Create our window
	if (!CreateGLWindow("Kortax first window", 640, 480, 32, fullscreen))
	{
		DWORD error = GetLastError();
		return 0;
	}
	while (!done)
	{
		//Look for message waiting
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				done = TRUE;
			else
			{
				TranslateMessage(&msg); //Translate the message
				DispatchMessage(&msg); //Dispatch the message for WndProc
			}
		}
		else
		{
			if (active)
			{
				if (keys[VK_ESCAPE])
					done = TRUE;
				else
				{
					DrawGLScene();
					SwapBuffers(hDC);
				}
			}

			if (keys[VK_F1])						// Is F1 Being Pressed?
			{
				keys[VK_F1] = FALSE;					// If So Make Key FALSE
				KillGLWindow();						// Kill Our Current Window
				fullscreen = !fullscreen;				// Toggle Fullscreen/Windowed Mode
														// Recreate Our OpenGL Window
				if (!CreateGLWindow("Kortax first window", 640, 480, 32, fullscreen))
				{
					return 0;						// Quit If Window Was No Created
				}
			}
		}
	}

	KillGLWindow();
	return (msg.wParam);
}

