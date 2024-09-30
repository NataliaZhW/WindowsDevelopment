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
	case WM_INITDIALOG:	//������������ ������ ���� ���, ��� �������� ����		
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

	case WM_CLOSE: EndDialog(hwnd, 0); break;//������������ ��� ������� �� ������ X (�������)
	}
	return FALSE;
}


















////HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
//		//		SendMessage(����, ���������, ��������� ���������)
//		//SendMessage(hwnd, WM_SETICON, 0, (LRESULT)hIcon); // LONG_PTR //   //??? typedef __int64 
//		//SetFocus(hEditLogin); //������� SetFocus ������������� ����� ���������� � ��������� ����
//		//SetFocus(GetDlgItem(hwnd, IDC_EDIT_LOGIN));
//HWND hEditLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);
//SendMessage(hEditLogin, WM_SETTEXT, 0, (__int64)g_sz_LOGIN_INVITATION);// LPARAM // LONG_PTR //  LRESULT //??? typedef __int64 


////����� �������������� ������� �� ������, ���� ������, � ����� ��������� ��������� ����.
//switch (LOWORD(wParam))
//// LOWORD(wParam) � ��� ������, ������� ���������� ����� ��������� wParam. 
//// wParam - ������ ����������, ������������ � wParam, ����� �������� �� ���� ������, ������� ����������� � ���� 16 - ��������� ������.��� �������� ������� � ���� ������ � Windows ���������� ��� ������� � LOWORD � HIWORD.	
//{
//case IDC_EDIT_LOGIN:
//{
//	CONST INT SIZE = 256; //����� ����������
//	CHAR sz_buffer[SIZE]{}; //������ ������
//	HWND hEditLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);// �������� ���������� ���� ������
//	SendMessage(hEditLogin, WM_GETTEXT, SIZE, (LPARAM)sz_buffer); //��������� � ����� ������ �� ���� ������
//	if (HIWORD(wParam) == EN_SETFOCUS && strcmp(sz_buffer, g_sz_LOGIN_INVITATION) == 0)
//		// strcmp - ���������� ������1 � ������2 
//		// int strcmp (const char * str1, const char * str2)
//		// EN_SETFOCUS ����� ������ �������� ����� ����������    
//		// HIWORD() - ��������� ����� �������� ������� �� ���������� 32-���������� ��������
//		// ���� ���� �������� ����� (HIWORD(wParam) ��������� �� EN_SETFOCUS) && "��������" sz_buffer ���� "����������������", �� ������������� ������ ������ "" 
//		SendMessage(hEditLogin, WM_SETTEXT, 0, (LPARAM)"");
//	if (HIWORD(wParam) == EN_KILLFOCUS && strcmp(sz_buffer, "") == 0)
//		// ���� ���� ������ ����� (HIWORD(wParam) ��������� �� EN_KILLFOCUS) && "��������" sz_buffer ���� ������ "", �� ������������� ������ "����������������" 
//		SendMessage(hEditLogin, WM_SETTEXT, 0, (LPARAM)g_sz_LOGIN_INVITATION);
//}		break;
//
//case IDC_BUTTON_COPY:
//{
//	//1) ������� ����� ������:
//	CONST INT SIZE = 256;
//	CHAR sz_buffer[SIZE] = {};
//	//2) �������� ����������� ��������� �����:
//	HWND hEditLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);//������� GetDlgItem() �� ID-������� ��������� ���� ���������� HWND ���������������� ��������� ����.
//
//	HWND hEditPassword = GetDlgItem(hwnd, IDC_EDIT_PASSWORD);
//	//3) ������ ����� �� ���������� ���� 'Login':
//	SendMessage(hEditLogin, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
//	//4) ��������� ��������� ���������� ������ � ���� 'Password':
//	SendMessage(hEditPassword, WM_SETTEXT, 0, (LPARAM)sz_buffer);
//}		break;
//
//case IDOK: MessageBox(hwnd, "���� ������ ������ ��", "Info", MB_OK | MB_ICONINFORMATION); break;
//case IDCANCEL: EndDialog(hwnd, 0); break;
