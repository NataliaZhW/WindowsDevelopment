#include<Windows.h>
#include"resource.h"
#include<string>
#include<string.h>


CONST CHAR g_sz_WINDOW_CLASS[] = "Calc";	//Имя класса окна.

CONST INT g_BUTTON_SIZE = 50;	//
CONST INT g_INTERVAL = 5;	//
CONST INT g_START_X = 10;	//
CONST INT g_START_Y = 10;	//
CONST INT g_BUTTON_DOUBLE_SIZE = g_BUTTON_SIZE * 2 + g_START_Y - g_INTERVAL;	//

CONST INT g_DISPLAY_WIDTH = g_BUTTON_SIZE * 5 + g_INTERVAL * 4;	//
CONST INT g_DISPLAY_HEIGHT = 25;	//

CONST INT g_BUTTON_START_X = g_START_X;	//
CONST INT g_BUTTON_START_Y = g_START_Y + g_DISPLAY_HEIGHT + g_INTERVAL;	//
CONST INT g_OPERETION_START_X = g_START_X + (g_BUTTON_SIZE + g_INTERVAL) * 3;	//
CONST INT g_OPERETION_START_Y = g_BUTTON_START_Y;	//

CONST INT g_CONTROL_BUTTONS_START_X = g_START_X + (g_BUTTON_SIZE + g_INTERVAL) * 4;	//
CONST INT g_CONTROL_BUTTONS_START_Y = g_BUTTON_START_Y;	//

CONST CHAR g_OPERATIONS[] = "*/-+";	//

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
	wClass.hIcon = (HICON)LoadImage(hInstance, "ICO\\calculator.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);
	wClass.hIconSm = (HICON)LoadImage(hInstance, "ICO\\calculator.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);	//Small Icon

	//wClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	///*wClass.hCursor = (HICON)LoadImage
	//(
	//	hInstance,
	//	"CURSOR\\Star Wars Obi-Wan Kenobi Lightsaber Animated--cursor--SweezyCursors.ani",
	//	IMAGE_ICON,
	//	LR_DEFAULTSIZE,
	//	LR_DEFAULTSIZE,
	//	LR_LOADFROMFILE
	//);*/
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
		WS_OVERLAPPEDWINDOW - WS_THICKFRAME - WS_MAXIMIZEBOX,//Window Style  ^ -
		CW_USEDEFAULT, CW_USEDEFAULT,	//Coordinates Position
		g_DISPLAY_WIDTH + g_BUTTON_START_X * 2 + 16,
		g_DISPLAY_HEIGHT * 2 + g_INTERVAL + (g_BUTTON_SIZE + g_INTERVAL) * 4 + g_START_X * 2 + 16 + 23, //Window size 		 	
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
	static double a, b;
	static char operation;
	static bool input;
	static bool operation_input = FALSE;

	switch (uMsg)
	{
	case WM_CREATE:
	{
		HWND hEditDisplay = CreateWindowEx
		(
			NULL,
			"Edit",
			"Memory",
			WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER | ES_RIGHT,//
			g_START_X, g_START_Y,
			g_DISPLAY_WIDTH, g_DISPLAY_HEIGHT,
			hwnd,
			(HMENU)IDC_EDIT_DISPLAY_MEMORY,
			GetModuleHandle(NULL),
			NULL
		);
		CreateWindowEx
		(
			NULL,
			"Edit",
			"0",
			WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER | ES_RIGHT,//
			g_START_X, g_START_Y + g_DISPLAY_HEIGHT + g_INTERVAL,
			g_DISPLAY_WIDTH, g_DISPLAY_HEIGHT,
			hwnd,
			(HMENU)IDC_EDIT_DISPLAY,
			GetModuleHandle(NULL),
			NULL
		);

		char number[2] = "";
		//int number_temp = 0;
		//char number[2] = "";
		for (int i = 6; i >= 0; i -= 3)
		{
			for (int j = 0; j < 3; j++)
			{

				number[0] = i + j + '1';//49
				//number_temp++;
				//number[0] = number_temp + 48 ;//
				// 
				//CHAR number[2];
				//sprintf_s(number, "%i", IDC_BUTTON_0 + j + i - 999);
				CreateWindowEx
				(
					NULL,
					"Button",
					number,//
					WS_CHILD | WS_VISIBLE,
					g_BUTTON_START_X + (g_BUTTON_SIZE + g_INTERVAL) * j, g_BUTTON_START_Y + (g_BUTTON_SIZE + g_INTERVAL) * (2 - i / 3) + g_DISPLAY_HEIGHT + g_INTERVAL,
					g_BUTTON_SIZE, g_BUTTON_SIZE,
					hwnd,
					(HMENU)(IDC_BUTTON_1 + i + j),
					GetModuleHandle(NULL),
					NULL
				);
			}
		}
		CreateWindowEx
		(
			NULL,
			"Button",
			"0",
			WS_CHILD | WS_VISIBLE,
			g_BUTTON_START_X, g_BUTTON_START_Y + (g_BUTTON_SIZE + g_INTERVAL) * 3 + g_DISPLAY_HEIGHT + g_INTERVAL,
			g_BUTTON_DOUBLE_SIZE, g_BUTTON_SIZE,
			hwnd,//(HWND)
			(HMENU)IDC_BUTTON_0,
			GetModuleHandle(NULL),
			NULL
		);
		CreateWindowEx
		(
			NULL,
			"Button",
			".",
			WS_CHILD | WS_VISIBLE,
			g_BUTTON_START_X + g_BUTTON_DOUBLE_SIZE + g_INTERVAL,
			g_BUTTON_START_Y + (g_BUTTON_SIZE + g_INTERVAL) * 3 + g_DISPLAY_HEIGHT + g_INTERVAL,
			g_BUTTON_SIZE, g_BUTTON_SIZE,
			hwnd,//(HWND)
			(HMENU)IDC_BUTTON_POINT,
			GetModuleHandle(NULL),
			NULL
		);
		char sz_operation[2] = "";
		for (int i = 0; i < 4; i++)
		{
			sz_operation[0] = g_OPERATIONS[i];//
			CreateWindowEx
			(
				NULL,
				"Button",
				sz_operation,//
				WS_CHILD | WS_VISIBLE,
				g_OPERETION_START_X, g_OPERETION_START_Y + (g_BUTTON_SIZE + g_INTERVAL) * i + g_DISPLAY_HEIGHT + g_INTERVAL,
				g_BUTTON_SIZE, g_BUTTON_SIZE,
				hwnd,
				(HMENU)(IDC_BUTTON_ASTER + i),
				GetModuleHandle(NULL),
				NULL
			);
		}
		CreateWindowEx
		(
			NULL,
			"Button",
			"<=",
			WS_CHILD | WS_VISIBLE,
			//g_BUTTON_START_X + g_BUTTON_DOUBLE_SIZE + g_INTERVAL,
			//g_BUTTON_START_Y + (g_BUTTON_SIZE + g_INTERVAL) * 3, 
			g_CONTROL_BUTTONS_START_X,
			g_CONTROL_BUTTONS_START_Y + g_DISPLAY_HEIGHT + g_INTERVAL,
			g_BUTTON_SIZE, g_BUTTON_SIZE,
			hwnd,//(HWND)
			(HMENU)IDC_BUTTON_BSP,
			GetModuleHandle(NULL),
			NULL
		);
		CreateWindowEx
		(
			NULL,
			"Button",
			"C",
			WS_CHILD | WS_VISIBLE,
			g_CONTROL_BUTTONS_START_X,
			g_CONTROL_BUTTONS_START_Y + g_BUTTON_SIZE + g_INTERVAL + g_DISPLAY_HEIGHT + g_INTERVAL,
			g_BUTTON_SIZE, g_BUTTON_SIZE,
			hwnd,//(HWND)
			(HMENU)IDC_BUTTON_CLEAR,
			GetModuleHandle(NULL),
			NULL
		);
		CreateWindowEx
		(
			NULL,
			"Button",
			"=",
			WS_CHILD | WS_VISIBLE,
			g_CONTROL_BUTTONS_START_X,
			g_CONTROL_BUTTONS_START_Y + (g_BUTTON_SIZE + g_INTERVAL) * 2 + g_DISPLAY_HEIGHT + g_INTERVAL,
			g_BUTTON_SIZE, g_BUTTON_DOUBLE_SIZE,
			hwnd,//(HWND)
			(HMENU)IDC_BUTTON_EQUAL,
			GetModuleHandle(NULL),
			NULL
		);
	}
	break;
	case WM_COMMAND:
	{
		CONST INT SIZE = 256; //Длина соообщения
		CHAR sz_display[SIZE]{}; //массив буфера
		CHAR sz_digit[2]{}; //массив буфера
		HWND hEditDisplay = GetDlgItem(hwnd, IDC_EDIT_DISPLAY);// Получаем дискриптор окна 
		HWND hEditDisplayMemory = GetDlgItem(hwnd, IDC_EDIT_DISPLAY_MEMORY);// Получаем дискриптор окна 
		if (LOWORD(wParam) >= IDC_BUTTON_0 && LOWORD(wParam) <= IDC_BUTTON_9)
		{
			if (operation_input == FALSE)
			{
				SendMessage(hEditDisplay, WM_SETTEXT, 0, (LPARAM)"0"); operation_input = TRUE;
			}
			sz_digit[0] = LOWORD(wParam) - IDC_BUTTON_0 + 48;
			SendMessage(hEditDisplay, WM_GETTEXT, SIZE, (LPARAM)sz_display);//считываем в буфер
			if (sz_display[0] == '0' && sz_display[1] != '.' && sz_display[1] != '+' && sz_display[1] != '-' && sz_display[1] != '/' && sz_display[1] != '*')sz_display[0] = 0;
			strcat(sz_display, sz_digit);
			SendMessage(hEditDisplay, WM_SETTEXT, 0, (LPARAM)sz_display);
			input = TRUE;
		}


		if (LOWORD(wParam) == IDC_BUTTON_POINT)
		{
			SendMessage(hEditDisplay, WM_GETTEXT, SIZE, (LPARAM)sz_display);//считываем в буфер данные из окна 

			if (operation_input == FALSE) //+предыдущий знак
			{
				SendMessage(hEditDisplay, WM_SETTEXT, 0, (LPARAM)"0.");
				operation_input = TRUE; break;//
			}
			if (sz_display[strlen(sz_display) - 1] == '+'
				|| sz_display[strlen(sz_display) - 1] == '-'
				|| sz_display[strlen(sz_display) - 1] == '*'
				|| sz_display[strlen(sz_display) - 1] == '/') //предыдущий знак
			{
				strcat(sz_display, "0.");
				SendMessage(hEditDisplay, WM_SETTEXT, 0, (LPARAM)sz_display);
				operation_input = TRUE; break;//
			}

			const int SIZE = 256;
			char buffer[SIZE]{};

			SendMessage(hEditDisplay, WM_GETTEXT, SIZE, (LPARAM)buffer);
			char number_temp[SIZE];
			const char delimiters[] = "*/-+";
			for (char* pch = strtok(buffer, delimiters); pch; pch = strtok(NULL, delimiters))
				//Функция strtok() разделяет строку на токены:
				sprintf_s(number_temp, pch);

			if (strchr(number_temp, '.')) break;// ==NULL
			if (sz_display[strlen(sz_display) - 1] == '.'
				|| sz_display[strlen(sz_display) - 1] == '+'
				|| sz_display[strlen(sz_display) - 1] == '-'
				|| sz_display[strlen(sz_display) - 1] == '*'
				|| sz_display[strlen(sz_display) - 1] == '/') sz_display[strlen(sz_display) - 1] = 0;
			strcat(sz_display, ".");
			SendMessage(hEditDisplay, WM_SETTEXT, 0, (LPARAM)sz_display);
		}
		if (LOWORD(wParam) == IDC_BUTTON_BSP)
		{
			if (operation_input == FALSE)
			{
				SendMessage(hEditDisplay, WM_SETTEXT, 0, (LPARAM)"0");
				operation_input = TRUE; break;//
			}
			SendMessage(hEditDisplay, WM_GETTEXT, SIZE, (LPARAM)sz_display);//считываем в буфер 

			if (strlen(sz_display) == 1)sz_display[0] = '0';// ==NULL  break

			else sz_display[strlen(sz_display) - 1] = 0;
			SendMessage(hEditDisplay, WM_SETTEXT, 0, (LPARAM)sz_display);
		}
		if (LOWORD(wParam) == IDC_BUTTON_CLEAR)
		{
			//if (operation_input == FALSE)
			{
				//SendMessage(hEditDisplay, WM_SETTEXT, 0, (LPARAM)"0");
				operation_input = TRUE;
			}
			//sz_display[0] = '0';// 			
			//SendMessage(hEditDisplay, WM_SETTEXT, 0, (LPARAM)sz_display);
			SendMessage(hEditDisplay, WM_SETTEXT, 0, (LPARAM)"0");
		}

		if (LOWORD(wParam) == IDC_BUTTON_PLUS || LOWORD(wParam) == IDC_BUTTON_MINUS || LOWORD(wParam) == IDC_BUTTON_ASTER || LOWORD(wParam) == IDC_BUTTON_SLASH)
		{
			if (operation_input == FALSE)
			{
				SendMessage(hEditDisplay, WM_SETTEXT, 0, (LPARAM)"0");
				operation_input = TRUE;
				if (LOWORD(wParam) != IDC_BUTTON_MINUS)
					break;//
			}



			const int SIZE = 256;  //предыдущий .0 убрать
			char sz_display[SIZE]{};
			char temp_sz_display[SIZE]{};

			SendMessage(hEditDisplay, WM_GETTEXT, SIZE, (LPARAM)sz_display);
			SendMessage(hEditDisplay, WM_GETTEXT, SIZE, (LPARAM)temp_sz_display);
			char number_temp[SIZE]{};
			const char delimiters[] = "*/-+";
			for (char* pch = strtok(temp_sz_display, delimiters); pch; pch = strtok(NULL, delimiters))
				//Функция strtok() разделяет строку на токены: на числа
				sprintf_s(number_temp, pch);
			//SendMessage(hEditDisplay, WM_SETTEXT, 0, (LPARAM)number_temp);

			if (strchr(number_temp, '.'))//number_temp
			{
				while (true)
				{
					if (number_temp[strlen(number_temp) - 1] == '0')
					{
						number_temp[strlen(number_temp) - 1] = 0;
						sz_display[strlen(sz_display) - 1] = 0;
					}
					else
						break;
				}

				/*char number_temp_decimal[SIZE]{};
				const char delimiters_decimal[] = ".";
				for (char* pch = strtok(number_temp, delimiters_decimal); pch; pch = strtok(NULL, delimiters))
					sprintf_s(number_temp_decimal, pch);*/

					//if (atoi(number_temp_decimal) == 0)
					//{
					//	SendMessage(hEditDisplay, WM_GETTEXT, SIZE, (LPARAM)sz_display);
					//	//for (int i = 0; i < sizeof(sz_display)/sizeof(char); i++)
					//	while (true)
					//	{
					//		if (strlen(sz_display) == 1) { sz_display[0] = '0'; break; }// ==NULL  

					//		else if (sz_display[strlen(sz_display) - 1] = '.'||(sz_display[strlen(sz_display) - 1] >= 49&& sz_display[strlen(sz_display) - 1] <=57))
					//		{
					//			sz_display[strlen(sz_display) - 1] = 0; break;
					//		}
					//		else sz_display[strlen(sz_display) - 1] = 0;
					//		//SendMessage(hEditDisplay, WM_SETTEXT, 0, (LPARAM)sz_display);
					//	}

					//};

			}
			if (sz_display[strlen(sz_display) - 1] == '.' ||
				sz_display[strlen(sz_display) - 1] == '+' ||
				sz_display[strlen(sz_display) - 1] == '-' ||
				sz_display[strlen(sz_display) - 1] == '*' ||
				sz_display[strlen(sz_display) - 1] == '/') sz_display[strlen(sz_display) - 1] = 0;

			//SendMessage(hEditDisplay, WM_SETTEXT, 0, (LPARAM)sz_display);


			//if (strlen(sz_display) == 1)sz_display[0] = '0';// ==NULL  break



			if (LOWORD(wParam) == IDC_BUTTON_PLUS)
			{
				//SendMessage(hEditDisplay, WM_GETTEXT, SIZE, (LPARAM)sz_display);
				strcat(sz_display, "+");
				//SendMessage(hEditDisplay, WM_SETTEXT, 0, (LPARAM)sz_display);

			}

			if (LOWORD(wParam) == IDC_BUTTON_MINUS)
			{
				//SendMessage(hEditDisplay, WM_GETTEXT, SIZE, (LPARAM)sz_display);

				if (sz_display[0] == '0' && sz_display[1] == 0)sz_display[0] = '-';//strlen(sz_display) == 2

				else strcat(sz_display, "-");
				//SendMessage(hEditDisplay, WM_SETTEXT, 0, (LPARAM)sz_display);
			}

			if (LOWORD(wParam) == IDC_BUTTON_ASTER)
			{
				//SendMessage(hEditDisplay, WM_GETTEXT, SIZE, (LPARAM)sz_display);
				//if (sz_display[strlen(sz_display) - 1] == '.'
				//	|| sz_display[strlen(sz_display) - 1] == '+'
				//	|| sz_display[strlen(sz_display) - 1] == '-'
				//	|| sz_display[strlen(sz_display) - 1] == '*'
				//	|| sz_display[strlen(sz_display) - 1] == '/') sz_display[strlen(sz_display) - 1] = 0;
				strcat(sz_display, "*");
				//SendMessage(hEditDisplay, WM_SETTEXT, 0, (LPARAM)sz_display);
			}

			if (LOWORD(wParam) == IDC_BUTTON_SLASH)
			{
				//SendMessage(hEditDisplay, WM_GETTEXT, SIZE, (LPARAM)sz_display);
				//if (sz_display[strlen(sz_display) - 1] == '.'
				//	|| sz_display[strlen(sz_display) - 1] == '+'
				//	|| sz_display[strlen(sz_display) - 1] == '-'
				//	|| sz_display[strlen(sz_display) - 1] == '*'
				//	|| sz_display[strlen(sz_display) - 1] == '/') sz_display[strlen(sz_display) - 1] = 0;
				strcat(sz_display, "/");
				//SendMessage(hEditDisplay, WM_SETTEXT, 0, (LPARAM)sz_display);
			}


			SendMessage(hEditDisplay, WM_SETTEXT, 0, (LPARAM)sz_display);

		}


		if (LOWORD(wParam) == IDC_BUTTON_EQUAL)
		{
			//SendMessage(hEditDisplay, WM_SETTEXT, 0, (LPARAM)sz_display);
			//if (operation_input)b = strtod(sz_display, NULL);
			//switch (operation)
			//{
			//case  IDC_BUTTON_ASTER: a *= b; break;
			//case  IDC_BUTTON_SLASH: a /= b; break;
			//case  IDC_BUTTON_MINUS: a -= b; break;
			//case  IDC_BUTTON_PLUS: a += b; break;
			//}
			//			

			//operation_input = FALSE;
			//sprintf_s(sz_display, "%g", a);
			//SendMessage(hEditDisplay, WM_SETTEXT, 0, (LPARAM)sz_display);

			const int SIZE = 256;
			char buffer[SIZE]{};

			SendMessage(hEditDisplay, WM_GETTEXT, SIZE, (LPARAM)buffer);
			//HWND hEditDisplayMemory = GetDlgItem(hwnd, IDC_EDIT_DISPLAY_MEMORY);
			SendMessage(hEditDisplayMemory, WM_SETTEXT, 0, (LPARAM)buffer);
			if (buffer[0] == '-')
			{
				char buffer_temp[SIZE] = "0";
				strcat(buffer_temp, buffer); //конкатенация
				strcpy(buffer, buffer_temp); // копирование
			}
			float number[10];
			int n = 0;
			const char delimiters[] = "*/-+";
			for (char* pch = strtok(buffer, delimiters); pch; pch = strtok(NULL, delimiters))
				//Функция strtok() разделяет строку на токены:
				number[n++] = atof(pch);
			//pch - Pointer to Character (Указатель на символ)

			/*for (int i = 0; i < n; i++)
			{
				char temp_sz_display[SIZE]{};

				sprintf_s(temp_sz_display, "%g",  number[i]);
				strcat(sz_display, temp_sz_display);
				SendMessage(hEditDisplay, WM_SETTEXT, 0, (LPARAM)sz_display);
			}*/

			SendMessage(hEditDisplay, WM_GETTEXT, SIZE, (LPARAM)buffer);
			//SendMessage(hEditDisplay, WM_SETTEXT, 0, (LPARAM)buffer);
			char znak[10];
			int n1 = 0;
			const char delimiters1[] = "0123456789.";
			//for (char* pch = strtok(buffer, delimiters1); pch; pch = strtok(NULL, delimiters))

			char temp_znak_sz_display[SIZE]{};
			char temp_znak_display[SIZE]{};
			for (int i = 0; i < SIZE; i++)//sizeof(buffer)/ sizeof(char)
			{
				if (buffer[i] == '*' || buffer[i] == '/' || buffer[i] == '-' || buffer[i] == '+')// 
				{
					znak[n1++] = buffer[i];
					sprintf_s(temp_znak_sz_display, "%c", buffer[i]);
					strcat(temp_znak_display, temp_znak_sz_display);
				}
			}
			//SendMessage(hEditDisplay, WM_SETTEXT, 0, (LPARAM)temp_znak_display);



			for (int i = 0; i < n1; i++)
				switch (znak[i])
				{
				case '*': {
					number[i + 1] = number[i] * (number[i + 1]);
					number[i] = 0;
					if (i == 0) znak[i] = '+';
					else znak[i] = znak[i - 1];
				}
						break;

				case '/': {
					number[i + 1] = number[i] / (number[i + 1]);
					number[i] = 0;
					if (i == 0) znak[i] = '+';
					else znak[i] = znak[i - 1];
				}
						break;
				}

			/*for (int i = 0; i < n1; i++)
			{
				char temp_sz_display[SIZE]{};

				sprintf_s(temp_sz_display, "%c", znak[i]);
				strcat(sz_display, temp_sz_display);
				SendMessage(hEditDisplay, WM_SETTEXT, 0, (LPARAM)sz_display);
			}*/

			/*for (int i = 0; i < n; i++)
			{
				char temp_sz_display[SIZE]{};

				sprintf_s(temp_sz_display, "%g", number[i]);
				strcat(sz_display, temp_sz_display);
				SendMessage(hEditDisplay, WM_SETTEXT, 0, (LPARAM)sz_display);
			}*/


			float result = number[0];
			CHAR message[SIZE]{};
			for (int i = 0; i < n1; i++)
				switch (znak[i])
				{
				case '+': result += number[i + 1]; break;
				case '-': result -= number[i + 1]; break;
				}

			sprintf_s(message, "%g", result);

			SendMessage(hEditDisplay, WM_SETTEXT, 0, (LPARAM)message);
			operation_input = FALSE;
		}
	}
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