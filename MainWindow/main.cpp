#include<Windows.h>

#define IDC_STATIC	1000
#define IDC_EDIT	1002
#define IDC_BUTTON	1003

//MDI - Multi Document Interface

CONST CHAR g_sz_WINDOW_CLASS[] = "Main Window";	//Имя класса окна.

INT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

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
	//wClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	//wClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);	//Small Icon
	wClass.hIcon = (HICON)LoadImage(hInstance, "ICO\\pizza_icon_black.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);
	wClass.hIconSm = (HICON)LoadImage(hInstance, "ICO\\pizza_icon_big.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);	//Small Icon

	//wClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wClass.hCursor = (HICON)LoadImage
	(
		hInstance,
		"CURSOR\\Star Wars Obi-Wan Kenobi Lightsaber Animated--cursor--SweezyCursors.ani",
		IMAGE_ICON,
		LR_DEFAULTSIZE,
		LR_DEFAULTSIZE,
		LR_LOADFROMFILE
	);
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
		WS_OVERLAPPED | WS_THICKFRAME | WS_MINIMIZEBOX| WS_SYSMENU | WS_MAXIMIZEBOX | WS_CAPTION,//Window Style
		CW_USEDEFAULT, CW_USEDEFAULT,	//Coordinates
		CW_USEDEFAULT, CW_USEDEFAULT,	//Window size
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

INT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
		CreateWindowEx
		(
			NULL,
			"Static",
			"Это статик текст",
			WS_CHILD | WS_VISIBLE,
			100, 10,
			200, 20,
			hwnd,
			(HMENU)IDC_STATIC,//(HWND)
			GetModuleHandle(NULL),
			NULL
		);
		CreateWindowEx
		(
			NULL,
			"Edit",
			"",
			WS_CHILD | WS_VISIBLE,
			100, 30,
			200, 20,
			hwnd,//(HWND)
			(HMENU)IDC_EDIT,
			GetModuleHandle(NULL),
			NULL
		);
		CreateWindowEx
		(
			NULL,
			"Button",
			"Применить",
			WS_CHILD | WS_VISIBLE,
			200, 50,
			100, 32,
			hwnd,//(HWND)
			(HMENU)IDC_BUTTON,
			GetModuleHandle(NULL),
			NULL
		);
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_BUTTON:
		{
			CONST INT SIZE = 256; //Длина соообщения
			CHAR sz_buffer[SIZE]{}; //массив буфера
			HWND hEdit = GetDlgItem(hwnd, IDC_EDIT);// Получаем дискриптор окна 
			SendMessage(hEdit, WM_GETTEXT, SIZE, (LPARAM)sz_buffer); //считываем в буфер данные из окна 

			HWND hStatic = GetDlgItem(hwnd, IDC_EDIT);// Получаем дискриптор окна 
			SendMessage(hStatic, WM_SETTEXT, 0, (LPARAM)sz_buffer); //
			SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)sz_buffer); // 
		}
		break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
	case WM_CLOSE:DestroyWindow(hwnd);
		break;
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return FALSE;
}