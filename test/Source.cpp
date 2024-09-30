#include<Windows.h>
#include"resource.h"

CONST CHAR g_sz_LOGIN_INVITATION[] = "������� ��� ������������";

BOOL CALLBACK DlgProg(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
//HIWORD - ������� �����
//LOWORD - ������� �����
//LOWORD(wParam) - ��������


INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	//hInstance - ��� *.exe-������ ����� ���������
	//hPrevInst - ���� �������� ������������� � ��������������� ���� IA-16/IA-32 (Win98)
	//			  �� ������� �� ��������.
	//lpCmdLine - LongPointer to Command prompt, ��� ��������� ������ ���������� � ������� WinMain ��� ������� ���������.
	//			  lpCmdLine ������������ ����� ������ �����, ������� ��������� �������� ������ �������� ������ ���� � *.exe-�����.

	/*MessageBox(NULL, "HelloWorld!\n��� ���� ���������", "Hello WinAPI", MB_ABORTRETRYIGNORE | MB_ICONSTOP | MB_DEFBUTTON3 | MB_HELP | MB_TOPMOST);
	std::cout << typeid(char).name() << std::endl;
	std::cout << typeid(wchar_t).name() << std::endl;
	WndProc*/

	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), 0, (DLGPROC)DlgProg, 0);
	// DialogBoxParam() ������� ��������� ���������� ���� �� ������� ������� ����������� ����. ����� ������������ ����������� ���� ������� �������� ������������ ����������� �������� ��������� ����������� ���� � �������� lParam ��������� ��������� WM_INITDIALOG. ���������� ����� ������������ ��� �������� ��� ������������� ��������� ���������� ����������� ����.
	// DialogBoxParam(������������� ������������ ������ ���������, ������������� �������, ����������� ������ ����������� ����, ���������� ���� - ���������, ��������� �� ��������� ����������� ����, �������� ������������ ����������� ���� � ��������� lParam ��������� WM_INITDIALOG.)
	
	// DLGPROC - ��������� �� ������� ???? �.�. �� ���� ����������� � INT_PTR
	// typedef INT_PTR(CALLBACK* DLGPROC)(HWND, UINT, WPARAM, LPARAM);
	return 0;
}

BOOL CALLBACK DlgProg(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	//hwnd - Handler to Window (���������� ����)
	// uMsg - ��� ���������  ???
	switch (uMsg)
	{
		//WM_ - Windows Message
	case WM_INITDIALOG:	//������������ ������ ���� ���, ��� �������� ����
		//H - Handler (����������, ����������)
	{
		HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
		//		SendMessage(����, ���������, ��������� ���������)
		SendMessage(hwnd, WM_SETICON, 0, (LRESULT)hIcon); // LONG_PTR //   //??? typedef __int64 
		//SetFocus(hEditLogin); //������� SetFocus ������������� ����� ���������� � ��������� ����
		//SetFocus(GetDlgItem(hwnd, IDC_EDIT_LOGIN));
		HWND hEditLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);
		SendMessage(hEditLogin, WM_SETTEXT, 0, (__int64)g_sz_LOGIN_INVITATION);// LPARAM // LONG_PTR //  LRESULT //??? typedef __int64 
	}	break;		

	case WM_COMMAND://����� �������������� ������� �� ������, ���� ������, � ����� ��������� ��������� ����.
		switch (LOWORD(wParam))
		// LOWORD(wParam) � ��� ������, ������� ���������� ����� ��������� wParam. 
		// wParam - ������ ����������, ������������ � wParam, ����� �������� �� ���� ������, ������� ����������� � ���� 16 - ��������� ������.��� �������� ������� � ���� ������ � Windows ���������� ��� ������� � LOWORD � HIWORD.	
		{
		case IDC_EDIT_LOGIN:
		{
			CONST INT SIZE = 256; //����� ����������
			CHAR sz_buffer[SIZE]{}; //������ ������
			HWND hEditLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);// �������� ���������� ���� ������
			SendMessage(hEditLogin, WM_GETTEXT, SIZE, (LPARAM)sz_buffer); //��������� � ����� ������ �� ���� ������
			if (HIWORD(wParam) == EN_SETFOCUS && strcmp(sz_buffer, g_sz_LOGIN_INVITATION) == 0)
            // strcmp - ���������� ������1 � ������2 
			// int strcmp (const char * str1, const char * str2)
			// EN_SETFOCUS ����� ������ �������� ����� ����������    
			// HIWORD() - ��������� ����� �������� ������� �� ���������� 32-���������� ��������
			// ���� ���� �������� ����� (HIWORD(wParam) ��������� �� EN_SETFOCUS) && "��������" sz_buffer ���� "����������������", �� ������������� ������ ������ "" 
				SendMessage(hEditLogin, WM_SETTEXT, 0, (LPARAM)"");
			if (HIWORD(wParam) == EN_KILLFOCUS && strcmp(sz_buffer, "") == 0)
			// ���� ���� ������ ����� (HIWORD(wParam) ��������� �� EN_KILLFOCUS) && "��������" sz_buffer ���� ������ "", �� ������������� ������ "����������������" 
				SendMessage(hEditLogin, WM_SETTEXT, 0, (LPARAM)g_sz_LOGIN_INVITATION);
		}		break; 
		
		case IDC_BUTTON_COPY:
		{
			//1) ������� ����� ������:
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE] = {};
			//2) �������� ����������� ��������� �����:
			HWND hEditLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);//������� GetDlgItem() �� ID-������� ��������� ���� ���������� HWND ���������������� ��������� ����.
			
			HWND hEditPassword = GetDlgItem(hwnd, IDC_EDIT_PASSWORD);
			//3) ������ ����� �� ���������� ���� 'Login':
			SendMessage(hEditLogin, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
			//4) ��������� ��������� ���������� ������ � ���� 'Password':
			SendMessage(hEditPassword, WM_SETTEXT, 0, (LPARAM)sz_buffer);
		}		break;

		case IDOK: MessageBox(hwnd, "���� ������ ������ ��", "Info", MB_OK | MB_ICONINFORMATION); break;
		case IDCANCEL: EndDialog(hwnd, 0); break;
		}		break;

	case WM_CLOSE: EndDialog(hwnd, 0); break;//������������ ��� ������� �� ������ X (�������)
	}
	return FALSE;
}