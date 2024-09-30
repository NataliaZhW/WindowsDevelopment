#include<Windows.h>
#include"resource.h"


BOOL CALLBACK DlgProg(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	//MessageBox(NULL, "Hello Windows!\nThis is MessageBox ", "Window title",  MB_ICONWARNING  |  MB_HELP);	//MB_ICONERROR |MB_DEFBUTTON2|MB_ICONQUESTION MB_ICONINFORMATION MB_OK MB_ABORTRETRYIGNORE // MB_TOPMOST ?
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), 0, (DLGPROC)DlgProg, 0);
	return 0;
}
BOOL CALLBACK DlgProg(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
			// LOWORD(wParam) — это макрос, который возвращает часть параметра wParam. 
			// wParam - Иногда информация, содержащаяся в wParam, может состоять из двух частей, которые размещаются в двух 16 - разрядных словах.Для простого доступа к этим частям в Windows определены два макроса — LOWORD и HIWORD.	
			{
		case IDC_EDIT_LOGIN:
		{
			CONST CHAR g_sz_LOGIN_INVITATION[] = "Введите имя пользователя";

			CONST INT SIZE = 256; //Длина соообщения
			CHAR sz_buffer[SIZE]{}; //массив бефера
			HWND hEditLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);// Получаем дискриптор окна логина
			SendMessage(hEditLogin, WM_GETTEXT, SIZE, (LPARAM)sz_buffer); //считываем в буфер данные из окна логина
			if (HIWORD(wParam) == EN_SETFOCUS && strcmp(sz_buffer, g_sz_LOGIN_INVITATION) == 0)
				// strcmp - сравниваем строку1 и строку2 
				// int strcmp (const char * str1, const char * str2)
				// EN_SETFOCUS когда окошко получает фокус клавиатуры    
				// HIWORD() - Извлекает слово старшего порядка из указанного 32-разрядного значения
				// Если окно получает фокус (HIWORD(wParam) поменялся на EN_SETFOCUS) && "значение" sz_buffer было "предопределенным", то устанавливаем пустую строку "" 
				SendMessage(hEditLogin, WM_SETTEXT, 0, (LPARAM)"");
			if (HIWORD(wParam) == EN_KILLFOCUS && strcmp(sz_buffer, "") == 0)
				// Если окно теряет фокус (HIWORD(wParam) поменялся на EN_KILLFOCUS) && "значение" sz_buffer было пустым "", то устанавливаем строку "предопределенное" 
				SendMessage(hEditLogin, WM_SETTEXT, 0, (LPARAM)g_sz_LOGIN_INVITATION);
		}
		break;

		case IDC_BUTTON_COPY:
		{
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE] = {};
			HWND hEditLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);
			HWND hEditPassword = GetDlgItem(hwnd, IDC_EDIT_PASSWORD);
			SendMessage(hEditLogin, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
			SendMessage(hEditPassword, WM_SETTEXT, 0, (LPARAM)sz_buffer);
		}
		break;
		case IDOK: MessageBox(hwnd, "БЫЛА НАЖАТА КНОПКА ОК", "Info", MB_OK | MB_ICONINFORMATION);
			break;
		case IDCANCEL:
			EndDialog(hwnd, 0);
			break;
			}
			break;
		case WM_CLOSE:
			EndDialog(hwnd, 0);
			break;
		}
		return FALSE;
	}