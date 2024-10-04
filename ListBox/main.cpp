//ListBox
#include<Windows.h>
#include <stdio.h>
#include <wchar.h>
#include <cstdio>
#include <list>
#include"resource.h"
#include <string>

CONST CHAR g_sz_INVITATION[] = "Введите текст";

CONST CHAR* g_LIST_BOX_ITEM[] = { "1This", "is", "my", "first", "Combo","Box" };

BOOL CALLBACK DlgProg(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
//BOOL CALLBACK DlgProcAdd(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
//std::list<string> list = { "1This", "is", "my", "first", "Combo","Box" };
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), 0, (DLGPROC)DlgProg, 0);
	return 0;
}

BOOL CALLBACK DlgProg(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{	
	case WM_INITDIALOG:		
	{
		HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
		SendMessage(hwnd, WM_SETICON, 0, (LPARAM)hIcon);

		HWND hCombo = GetDlgItem(hwnd, IDC_LIST1);
		for (int i = 0; i < sizeof(g_LIST_BOX_ITEM) / sizeof(g_LIST_BOX_ITEM[0]); i++)
		{
			SendMessage(hCombo, LB_ADDSTRING, 0, (LPARAM)g_LIST_BOX_ITEM[i]);
		}
		SendMessage(hCombo, CB_SETCURSEL, 0, 0);
		HWND hEditLogin = GetDlgItem(hwnd, IDC_EDIT_ADD);
		SendMessage(hEditLogin, WM_SETTEXT, 0, (__int64)g_sz_INVITATION);
	}
	break;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_BUTTON_ADD:
		{
			//1) Создаем буфер чтения:
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE] = {};
			//2) Получаем обработчики текстовых полей:
			HWND hEditAdd = GetDlgItem(hwnd, IDC_EDIT_ADD);//Функция GetDlgItem() по ID-ресурса дочернего окна возвращает HWND соответствующего дочернего окна.
			HWND hList = GetDlgItem(hwnd, IDC_LIST1);
			//3) Читаем текст :
			SendMessage(hEditAdd, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);			
			//4) Загружаем содржимое текстового буфера в поле :
			SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)sz_buffer);			
		}
		break; 
		case IDC_EDIT_ADD:
		{
			CONST INT SIZE = 256; //Длина соообщения
			CHAR sz_buffer[SIZE]{}; //массив бефера
			HWND hEditAdd = GetDlgItem(hwnd, IDC_EDIT_ADD);// Получаем дискриптор окна логина
			SendMessage(hEditAdd, WM_GETTEXT, SIZE, (LPARAM)sz_buffer); //считываем в буфер данные из окна логина
			if (HIWORD(wParam) == EN_SETFOCUS && strcmp(sz_buffer, g_sz_INVITATION) == 0)
				// strcmp - сравниваем строку1 и строку2 
				// int strcmp (const char * str1, const char * str2)
				// EN_SETFOCUS когда окошко получает фокус клавиатуры    
				// HIWORD() - Извлекает слово старшего порядка из указанного 32-разрядного значения
				// Если окно получает фокус (HIWORD(wParam) поменялся на EN_SETFOCUS) && "значение" sz_buffer было "предопределенным", то устанавливаем пустую строку "" 
				SendMessage(hEditAdd, WM_SETTEXT, 0, (LPARAM)"");
			if (HIWORD(wParam) == EN_KILLFOCUS && strcmp(sz_buffer, "") == 0)
				// Если окно теряет фокус (HIWORD(wParam) поменялся на EN_KILLFOCUS) && "значение" sz_buffer было пустым "", то устанавливаем строку "предопределенное" 
				SendMessage(hEditAdd, WM_SETTEXT, 0, (LPARAM)g_sz_INVITATION);
		}		
		break;
		
		case IDC_BUTTON_DEL:
		{
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE] = {};
			HWND hList = GetDlgItem(hwnd, IDC_LIST1);
			int i = SendMessage(hList, LB_GETCURSEL, 0, 0);
			SendMessage(hList, LB_DELETESTRING, i, 0);	
		}
		break;
		case IDOK:
		{
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE] = {};
			HWND hCombo = GetDlgItem(hwnd, IDC_LIST1);
			int i = SendMessage(hCombo, LB_GETCURSEL, 0, 0);
			SendMessage(hCombo, LB_GETTEXT, i, (LPARAM)sz_buffer);
			CHAR sz_message[SIZE]{};
			sprintf_s(sz_message, "Вы выбрали элемент № %i, со значением \"%s\"", i, (LPARAM)sz_buffer);
			MessageBox(hwnd, sz_message, "Info", MB_OK | MB_ICONINFORMATION);
		}
		break;		

		case IDCANCEL: EndDialog(hwnd, 0); break;
		}
		break;
	case WM_CLOSE: EndDialog(hwnd, 0); break;
	}
	return FALSE;
}

//BOOL CALLBACK DlgProcAdd(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
//{
//	switch (uMsg)
//	{
//		/*case IDC_BUTTON_ADD:
//		{
//			DialogBoxParam(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG_ADD), hwnd, DlgProcAdd, 0);
//		}
//		break;*/
//	case WM_INITDIALOG:	//Отрабатывает только один раз, при создании окна		
//	{
//		HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
//		SendMessage(hwnd, WM_SETICON, 0, (LPARAM)hIcon);
//
//		HWND hCombo = GetDlgItem(hwnd, IDC_COMBO1);
//		for (int i = 0; i < sizeof(g_COMBO_BOX_ITEM) / sizeof(g_COMBO_BOX_ITEM[0]); i++)
//		{
//			SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)g_COMBO_BOX_ITEM[i]);
//		}
//		SendMessage(hCombo, CB_SETCURSEL, 0, 0);
//	}
//	break;
//
//	case WM_COMMAND:
//		switch (LOWORD(wParam))
//		{
//
//		case IDOK:
//		{
//			CONST INT SIZE = 256;
//			CHAR sz_buffer[SIZE] = {};
//			HWND hCombo = GetDlgItem(hwnd, IDC_COMBO1);
//			int i = SendMessage(hCombo, CB_GETCURSEL, 0, 0);
//			SendMessage(hCombo, CB_GETLBTEXT, i, (LPARAM)sz_buffer);
//			CHAR sz_message[SIZE]{};
//			sprintf_s(sz_message, "Вы выбрали элемент № %i, со значением \"%s\"", i, (LPARAM)sz_buffer);
//			MessageBox(hwnd, sz_message, "Info", MB_OK | MB_ICONINFORMATION);
//		}
//		break;
//		case IDCANCEL: EndDialog(hwnd, 0); break;
//		}
//		break;
//	case WM_CLOSE: EndDialog(hwnd, 0); break;
//	}
//	return FALSE;
//}