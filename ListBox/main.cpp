//ListBox
#include<Windows.h>
#include <stdio.h>
#include <wchar.h>
#include"resource.h"

CONST CHAR* g_COMBO_BOX_ITEM[] = { "1This", "is", "my", "first", "Combo","Box" };

BOOL CALLBACK DlgProg(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), 0, (DLGPROC)DlgProg, 0);
	return 0;
}

BOOL CALLBACK DlgProg(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:	//Отрабатывает только один раз, при создании окна		
	{
		HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
		SendMessage(hwnd, WM_SETICON, 0, (LPARAM)hIcon);

		HWND hCombo = GetDlgItem(hwnd, IDC_COMBO1);
		for (int i = 0; i < sizeof(g_COMBO_BOX_ITEM) / sizeof(g_COMBO_BOX_ITEM[0]); i++)
		{
			SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)g_COMBO_BOX_ITEM[i]);
		}
		SendMessage(hCombo, CB_SETCURSEL, 0, 0);
	}
	break;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
			
		case IDOK:
		{
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE] = {};
			HWND hCombo = GetDlgItem(hwnd, IDC_COMBO1);
			int i = SendMessage(hCombo, CB_GETCURSEL, 0, 0);
			SendMessage(hCombo, CB_GETLBTEXT, i, (LPARAM)sz_buffer);
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