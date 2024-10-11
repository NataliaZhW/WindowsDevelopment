#include<Windows.h>
#include"resource.h"
#include<string>


CONST CHAR g_sz_WINDOW_CLASS[] = "Calc";	//Имя класса окна.

CONST INT g_BUTTON_SIZE = 50;	//
CONST INT g_INTERVAL = 5;	//
CONST INT g_START_X = 10;	//
CONST INT g_START_Y = 10;	//

CONST INT g_DISPLAY_WIDTH = 200;	//
CONST INT g_DISPLAY_HEIGHT = 25;	//

CONST INT g_BUTTON_START_X = g_START_X;	//
CONST INT g_BUTTON_START_Y = g_START_Y + g_DISPLAY_HEIGHT+ g_INTERVAL;	//

BOOL CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	//1) Регистрация класса окна:
	//		1.1. Создать и проинициализировать структуру WNDCLASSEX:
	WNDCLASSEX wClass;
	ZeroMemory(&wClass, sizeof(wClass));

	wClass.style = NULL;
	wClass.cbSize = sizeof(wClass);	//cb - Count Bytes
	wClass.cbClsExtra = 0;	//Class Extra Bytes
	wClass.cbWndExtra = 0;	//Window Extra Bytes

	//Appearance:
	wClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);	//Small Icon
	//wClass.hIcon = (HICON)LoadImage(hInstance, "ICO\\pizza_icon_black.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);
	//wClass.hIconSm = (HICON)LoadImage(hInstance, "ICO\\pizza_icon_big.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);	//Small Icon

	wClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	/*wClass.hCursor = (HICON)LoadImage
	(
		hInstance,
		"CURSOR\\Star Wars Obi-Wan Kenobi Lightsaber Animated--cursor--SweezyCursors.ani",
		IMAGE_ICON,
		LR_DEFAULTSIZE,
		LR_DEFAULTSIZE,
		LR_LOADFROMFILE
	);*/
	wClass.hbrBackground = (HBRUSH)COLOR_WINDOW;

	//
	wClass.hInstance = hInstance;
	wClass.lpfnWndProc = (WNDPROC)WndProc;
	wClass.lpszClassName = g_sz_WINDOW_CLASS;
	wClass.lpszMenuName = NULL;

	//		1.2. Вызвать функцию RegisterClassEx(...):
	if (RegisterClassEx(&wClass) == NULL)
	{
		MessageBox(NULL, "Class registration failed", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}

	//2) Создание окна:
	HWND hwnd = CreateWindowEx
	(
		NULL,	//Window ExStyle
		g_sz_WINDOW_CLASS,	//Window Class Name
		g_sz_WINDOW_CLASS,	//Window Title
		WS_OVERLAPPEDWINDOW | WS_THICKFRAME | WS_MAXIMIZEBOX,//Window Style
		CW_USEDEFAULT, CW_USEDEFAULT,	//Coordinates Position
		300, 300, 	//Window size (80 + 5) * 5 + 70 * 3, 50 + (80 + 5) * 5 + 5 * 2,
		NULL,	//Parent
		NULL,	//hMenu: Для главного окна это ResourceID главного меню,
		//для дочернего окна (кнопки и другие элементы) - 
		//это ResourceID соответствующего элемента (кнопки, текстового поля, и т.д.)
		//По этому RousourceID дочерниго элемента окна мы находим при помощи функции GetDlgItem()
		hInstance,
		NULL
	);
	if (hwnd == NULL)
	{
		MessageBox(NULL, "Window creation failed", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}
	ShowWindow(hwnd, nCmdShow);	//Задает режим отображения окна (развернуто на весь экран, свернуто в окно, свернуто в панель задач)
	UpdateWindow(hwnd);	//Прорисовывает окно

	//3) Запуск цикла сообщений:
	MSG msg;
	while (GetMessage(&msg, 0, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.message;
}


BOOL CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
	{
		HWND hEditDisplay = CreateWindowEx
		(
			NULL,
			"Edit",
			"0",
			WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER|ES_RIGHT,//
			g_START_X, g_START_Y,
			g_DISPLAY_WIDTH, g_DISPLAY_HEIGHT,		
			hwnd,
			(HMENU)IDC_EDIT_DISPLAY,
			GetModuleHandle(NULL),
			NULL
		);
		int number_temp = 0;
		char number[2] = "";
		for (int i = 6; i >= 0; i -= 3)
		{
			for (int j = 0; j < 3; j++)
			{
				number_temp++;
				number[0] = number_temp + 48 ;//
				//CHAR number[256];
				//sprintf_s(number, "%i", IDC_BUTTON_0 + j + i - 999);
				CreateWindowEx
				(
					NULL,
					"Button", 
					number,//
					WS_CHILD | WS_VISIBLE,
					g_BUTTON_START_X + (g_BUTTON_SIZE + g_INTERVAL) * j, g_BUTTON_START_Y + (g_BUTTON_SIZE + g_INTERVAL) * (i / 3),
					g_BUTTON_SIZE, g_BUTTON_SIZE,
					hwnd,
					(HMENU)(IDC_BUTTON_0+ i+j),
					GetModuleHandle(NULL),
					NULL
				);
			}
		}

		//CreateWindowEx
		//(
		//	NULL,
		//	"Static",
		//	"Применить",
		//	WS_CHILD | WS_VISIBLE,
		//	200, 50,
		//	100, 32,
		//	hwnd,//(HWND)
		//	(HMENU)IDC_STATIC,
		//	GetModuleHandle(NULL),
		//	NULL
		//);
	}
	break;
	case WM_COMMAND:
		//switch (LOWORD(wParam))
		//{
		//case IDC_BUTTON:
		//{
		//	CONST INT SIZE = 256; //Длина соообщения
		//	CHAR sz_buffer[SIZE]{}; //массив буфера
		//	HWND hEdit = GetDlgItem(hwnd, IDC_EDIT);// Получаем дискриптор окна 
		//	SendMessage(hEdit, WM_GETTEXT, SIZE, (LPARAM)sz_buffer); //считываем в буфер данные из окна 

		//	HWND hStatic = GetDlgItem(hwnd, IDC_EDIT);// Получаем дискриптор окна 
		//	SendMessage(hStatic, WM_SETTEXT, 0, (LPARAM)sz_buffer); //
		//	SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)sz_buffer); // 
		//}
		//break;
		//}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
	case WM_CLOSE:DestroyWindow(hwnd);
		break;
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return 0;
}









//
//#define IDC_STATIC	1000
//#define IDC_EDIT	1002
//#define IDC_BUTTON	1003
//
////MDI - Multi Document Interface
//
//
//
//
//
//
//	//1) Регистрация класса окна:
//	//		1.1. Создать и проинициализировать структуру WNDCLASSEX:
//	WNDCLASSEX wClass;
//	ZeroMemory(&wClass, sizeof(wClass));
//
//	wClass.style = NULL;
//	wClass.cbSize = sizeof(wClass);	//cb - Count Bytes
//	wClass.cbClsExtra = 0;	//Class Extra Bytes
//	wClass.cbWndExtra = 0;	//Window Extra Bytes
//
//	//Appearance:
//	//wClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
//	//wClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);	//Small Icon
//	wClass.hIcon = (HICON)LoadImage(hInstance, "ICO\\pizza_icon_black.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);
//	wClass.hIconSm = (HICON)LoadImage(hInstance, "ICO\\pizza_icon_big.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);	//Small Icon
//
//	//wClass.hCursor = LoadCursor(NULL, IDC_ARROW);
//	wClass.hCursor = (HICON)LoadImage
//	(
//		hInstance,
//		"CURSOR\\Star Wars Obi-Wan Kenobi Lightsaber Animated--cursor--SweezyCursors.ani",
//		IMAGE_ICON,
//		LR_DEFAULTSIZE,
//		LR_DEFAULTSIZE,
//		LR_LOADFROMFILE
//	);
//	wClass.hbrBackground = (HBRUSH)COLOR_WINDOW;
//
//	//
//	wClass.hInstance = hInstance;
//	wClass.lpfnWndProc = (WNDPROC)WndProc;
//	wClass.lpszClassName = g_sz_WINDOW_CLASS;
//	wClass.lpszMenuName = NULL;
//
//	//		1.2. Вызвать функцию RegisterClassEx(...):
//	if (RegisterClassEx(&wClass) == NULL)
//	{
//		MessageBox(NULL, "Class registration failed", "Error", MB_OK | MB_ICONERROR);
//		return 0;
//	}
//
//	//2) Создание окна:
//	HWND hwnd = CreateWindowEx
//	(
//		NULL,	//Window ExStyle
//		g_sz_WINDOW_CLASS,	//Window Class Name
//		g_sz_WINDOW_CLASS,	//Window Title
//		WS_OVERLAPPED | WS_THICKFRAME | WS_MINIMIZEBOX | WS_SYSMENU | WS_MAXIMIZEBOX | WS_CAPTION,//Window Style
//		CW_USEDEFAULT, CW_USEDEFAULT,	//Coordinates
//		CW_USEDEFAULT, CW_USEDEFAULT,	//Window size
//		NULL,	//Parent
//		NULL,	//hMenu: Для главного окна это ResourceID главного меню,
//		//для дочернего окна (кнопки и другие элементы) - 
//		//это ResourceID соответствующего элемента (кнопки, текстового поля, и т.д.)
//		//По этому RousourceID дочерниго элемента окна мы находим при помощи функции GetDlgItem()
//		hInstance,
//		NULL
//	);
//	if (hwnd == NULL)
//	{
//		MessageBox(NULL, "Window creation failed", "Error", MB_OK | MB_ICONERROR);
//		return 0;
//	}
//	ShowWindow(hwnd, nCmdShow);	//Задает режим отображения окна (развернуто на весь экран, свернуто в окно, свернуто в панель задач)
//	UpdateWindow(hwnd);	//Прорисовывает окно
//
//	//3) Запуск цикла сообщений:
//	MSG msg;
//	while (GetMessage(&msg, 0, 0, 0) > 0)
//	{
//		TranslateMessage(&msg);
//		DispatchMessage(&msg);
//	}
//	return msg.message;
//}
//
//INT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
//{
//	switch (uMsg)
//	{
//	case WM_CREATE:
//		CreateWindowEx
//		(
//			NULL,
//			"Static",
//			"Это статик текст",
//			WS_CHILD | WS_VISIBLE,
//			100, 10,
//			200, 20,
//			hwnd,
//			(HMENU)IDC_STATIC,//(HWND)
//			GetModuleHandle(NULL),
//			NULL
//		);
//		CreateWindowEx
//		(
//			NULL,
//			"Edit",
//			"",
//			WS_CHILD | WS_VISIBLE,
//			100, 30,
//			200, 20,
//			hwnd,//(HWND)
//			(HMENU)IDC_EDIT,
//			GetModuleHandle(NULL),
//			NULL
//		);
//		CreateWindowEx
//		(
//			NULL,
//			"Button",
//			"Применить",
//			WS_CHILD | WS_VISIBLE,
//			200, 50,
//			100, 32,
//			hwnd,//(HWND)
//			(HMENU)IDC_BUTTON,
//			GetModuleHandle(NULL),
//			NULL
//		);
//		break;
//	case WM_COMMAND:
//		switch (LOWORD(wParam))
//		{
//		case IDC_BUTTON:
//		{
//			CONST INT SIZE = 256; //Длина соообщения
//			CHAR sz_buffer[SIZE]{}; //массив буфера
//			HWND hEdit = GetDlgItem(hwnd, IDC_EDIT);// Получаем дискриптор окна 
//			SendMessage(hEdit, WM_GETTEXT, SIZE, (LPARAM)sz_buffer); //считываем в буфер данные из окна 
//
//			HWND hStatic = GetDlgItem(hwnd, IDC_EDIT);// Получаем дискриптор окна 
//			SendMessage(hStatic, WM_SETTEXT, 0, (LPARAM)sz_buffer); //
//			SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)sz_buffer); // 
//		}
//		break;
//		}
//		break;
//	case WM_DESTROY:
//		PostQuitMessage(0);
//	case WM_CLOSE:DestroyWindow(hwnd);
//		break;
//	default:
//		return DefWindowProc(hwnd, uMsg, wParam, lParam);
//	}
//	return FALSE;
//}