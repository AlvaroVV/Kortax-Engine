#include <Windows.h>
#include <Kortax\Kortax.h>


void SetWindowSize(HWND hwnd, int width, int height);

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
		case WM_SIZE:
		{
			int width = LOWORD (lParam);
			int height = HIWORD(lParam);
			kortax::LogFormatString("Cambiado el tamaño: [%i,%i]", width,height);

		}
		break;
		case WM_PAINT :
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd, &ps);

			// All painting occurs here, between BeginPaint and EndPaint.

			FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_ACTIVEBORDER + 1));

			EndPaint(hwnd, &ps);
		}
		return 0;
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
	wc.style = CS_HREDRAW | CS_VREDRAW; //Redraw when horizontal and vertical movement.
	wc.lpfnWndProc = WndProc; //Puntero al procedure
	wc.cbClsExtra = 0; //Cantidad extra de asignacion de memoria para datos
	wc.cbWndExtra = 0; //Cantidad extra de memoria por ventana de este tipo.
	wc.hInstance = hInstance; //Handle a la instancia
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); //Handle al icono grande (32x32) Alt + Tab
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);//HAndle al icono pequeño (16x16) Barra de tareas y esquina superior izquierda
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); //Cursor en ventana
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOWFRAME + 1); //Background color
	wc.lpszMenuName = NULL; //Reource name of the calss menu
	wc.lpszClassName = g_szClassName; //Nombre de la ventana

	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Goodbye, cruel world!", "Error!", MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}


	//CREATE WINDOW
	//Calculate window size based on client size
	int width = 480;
	int height = 240;
	RECT rect = {0,0,width,height};
	DWORD dwStyle = WS_OVERLAPPEDWINDOW;
	DWORD dxStyle = WS_EX_WINDOWEDGE;

	AdjustWindowRectEx(&rect, dwStyle,  false, dxStyle);

	HWND hwnd;
	hwnd = CreateWindowEx(
		dxStyle, //estilo extendido
		g_szClassName, //nombre de la clase registrada
		"The title of my window", //título de la ventana
		dwStyle, //Estilo de la ventana
		CW_USEDEFAULT, CW_USEDEFAULT, rect.right - rect.left, rect.bottom - rect.top, //Window size, not client
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


void SetWindowSize(HWND hwnd, int width, int height)
{
	RECT lCurrentRect;
	::GetWindowRect(hwnd, &lCurrentRect);
	RECT lClientRect = {0,0,width, height};

	WINDOWINFO lInfo;
	::GetWindowInfo(hwnd, &lInfo);
	::AdjustWindowRect(&lClientRect, lInfo.dwStyle, false);

	::MoveWindow(hwnd, lCurrentRect.left, lCurrentRect.top, lClientRect.right - lClientRect.left, lClientRect.bottom - lClientRect.top, true);
}
