//ComboBox
#include<Windows.h>
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

		HWND hCombo = GetDlgItem(hwnd, IDC_COMBO2);
		for (int i = 0; i < sizeof(g_COMBO_BOX_ITEM)/ sizeof(g_COMBO_BOX_ITEM[0]); i++)
		{
			SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)g_COMBO_BOX_ITEM[i]);
		}
		SendMessage(hCombo, CB_SETCURSEL, 0, 0);
	}
		break;

	case WM_COMMAND:	break;

	case WM_CLOSE: EndDialog(hwnd, 0); break;//Отрабатывает при нажатии на кнопку X (Закрыть)
	}
	return FALSE;
}


















////HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
//		//		SendMessage(окно, сообщение, параметры сообщения)
//		//SendMessage(hwnd, WM_SETICON, 0, (LRESULT)hIcon); // LONG_PTR //   //??? typedef __int64 
//		//SetFocus(hEditLogin); //функция SetFocus устанавливает фокус клавиатуры в указанное окно
//		//SetFocus(GetDlgItem(hwnd, IDC_EDIT_LOGIN));
//HWND hEditLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);
//SendMessage(hEditLogin, WM_SETTEXT, 0, (__int64)g_sz_LOGIN_INVITATION);// LPARAM // LONG_PTR //  LRESULT //??? typedef __int64 


////Здесь обрабатываются нажатия на кнопки, ввод текста, и любые изменения состояния окна.
//switch (LOWORD(wParam))
//// LOWORD(wParam) — это макрос, который возвращает часть параметра wParam. 
//// wParam - Иногда информация, содержащаяся в wParam, может состоять из двух частей, которые размещаются в двух 16 - разрядных словах.Для простого доступа к этим частям в Windows определены два макроса — LOWORD и HIWORD.	
//{
//case IDC_EDIT_LOGIN:
//{
//	CONST INT SIZE = 256; //Длина соообщения
//	CHAR sz_buffer[SIZE]{}; //массив бефера
//	HWND hEditLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);// Получаем дискриптор окна логина
//	SendMessage(hEditLogin, WM_GETTEXT, SIZE, (LPARAM)sz_buffer); //считываем в буфер данные из окна логина
//	if (HIWORD(wParam) == EN_SETFOCUS && strcmp(sz_buffer, g_sz_LOGIN_INVITATION) == 0)
//		// strcmp - сравниваем строку1 и строку2 
//		// int strcmp (const char * str1, const char * str2)
//		// EN_SETFOCUS когда окошко получает фокус клавиатуры    
//		// HIWORD() - Извлекает слово старшего порядка из указанного 32-разрядного значения
//		// Если окно получает фокус (HIWORD(wParam) поменялся на EN_SETFOCUS) && "значение" sz_buffer было "предопределенным", то устанавливаем пустую строку "" 
//		SendMessage(hEditLogin, WM_SETTEXT, 0, (LPARAM)"");
//	if (HIWORD(wParam) == EN_KILLFOCUS && strcmp(sz_buffer, "") == 0)
//		// Если окно теряет фокус (HIWORD(wParam) поменялся на EN_KILLFOCUS) && "значение" sz_buffer было пустым "", то устанавливаем строку "предопределенное" 
//		SendMessage(hEditLogin, WM_SETTEXT, 0, (LPARAM)g_sz_LOGIN_INVITATION);
//}		break;
//
//case IDC_BUTTON_COPY:
//{
//	//1) Создаем буфер чтения:
//	CONST INT SIZE = 256;
//	CHAR sz_buffer[SIZE] = {};
//	//2) Получаем обработчики текстовых полей:
//	HWND hEditLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);//Функция GetDlgItem() по ID-ресурса дочернего окна возвращает HWND соответствующего дочернего окна.
//
//	HWND hEditPassword = GetDlgItem(hwnd, IDC_EDIT_PASSWORD);
//	//3) Читаем текст из текстового поля 'Login':
//	SendMessage(hEditLogin, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
//	//4) Загружаем содржимое текстового буфера в поле 'Password':
//	SendMessage(hEditPassword, WM_SETTEXT, 0, (LPARAM)sz_buffer);
//}		break;
//
//case IDOK: MessageBox(hwnd, "БЫЛА НАЖАТА КНОПКА ОК", "Info", MB_OK | MB_ICONINFORMATION); break;
//case IDCANCEL: EndDialog(hwnd, 0); break;
