#include<Windows.h>
#include"resource.h"

CONST CHAR g_sz_LOGIN_INVITATION[] = "Введите имя пользователя";

BOOL CALLBACK DlgProg(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
//HIWORD - старшее слово
//LOWORD - младшее слово
//LOWORD(wParam) - например


INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	//hInstance - это *.exe-модуль нашей программы
	//hPrevInst - этот параметр использовался в комбинированном коде IA-16/IA-32 (Win98)
	//			  на сегодня не актуален.
	//lpCmdLine - LongPointer to Command prompt, эта командная строка передается в функцию WinMain при запуске программы.
	//			  lpCmdLine представляет собой массив строк, нулевым элементом которого всегда является полный путь к *.exe-файлу.
	//MessageBox(NULL, "Hello Windows!\nThis is MessageBox ", "Window title",  MB_ICONWARNING  |  MB_HELP);	//MB_ICONERROR |MB_DEFBUTTON2|MB_ICONQUESTION MB_ICONINFORMATION MB_OK MB_ABORTRETRYIGNORE // MB_TOPMOST ?
	//MessageBox(NULL, "HelloWorld!\nЭто окно сообщения", "Hello WinAPI", MB_ABORTRETRYIGNORE | MB_ICONSTOP | MB_DEFBUTTON3 | MB_HELP | MB_TOPMOST);
	//std::cout << typeid(char).name() << std::endl;
	//std::cout << typeid(wchar_t).name() << std::endl;
	//WndProc

	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), 0, (DLGPROC)DlgProg, 0);
	// DialogBoxParam() Создает модальное диалоговое окно из ресурса шаблона диалогового окна. Перед отображением диалогового окна функция передает определенное приложением значение процедуре диалогового окна в качестве lParam параметра сообщения WM_INITDIALOG. Приложение может использовать это значение для инициализации элементов управления диалогового окна.
	// DialogBoxParam(идентификатор исполняемого модуля программы, идентификатор ресурса, содержащего шаблон диалогового окна, дескриптор окна - владельца, указатель на процедуру диалогового окна, значение передаваемое диалоговому окну в параметре lParam сообщения WM_INITDIALOG.)

	// DLGPROC - указатель на функцию ???? т.е. мы явно преобразуем в INT_PTR
	// typedef INT_PTR(CALLBACK* DLGPROC)(HWND, UINT, WPARAM, LPARAM);
	return 0;
}

BOOL CALLBACK DlgProg(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	//hwnd - Handler to Window (дескриптор окна)
	// uMsg - код сообщения  ???
	switch (uMsg)
	{
		//WM_ - Windows Message
	case WM_INITDIALOG:	//Отрабатывает только один раз, при создании окна
		//H - Handler (обработчик, дескриптор)
	{
		HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
		//		SendMessage(окно, сообщение, параметры сообщения)
		SendMessage(hwnd, WM_SETICON, 0, (LRESULT)hIcon); // LONG_PTR //   //??? typedef __int64 
		//SetFocus(hEditLogin); //функция SetFocus устанавливает фокус клавиатуры в указанное окно
		//SetFocus(GetDlgItem(hwnd, IDC_EDIT_LOGIN));
		HWND hEditLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);
		SendMessage(hEditLogin, WM_SETTEXT, 0, (__int64)g_sz_LOGIN_INVITATION);// LPARAM // LONG_PTR //  LRESULT //??? typedef __int64 
	}	break;
	
		case WM_COMMAND://Здесь обрабатываются нажатия на кнопки, ввод текста, и любые изменения состояния окна.
		switch (LOWORD(wParam))
			// LOWORD(wParam) — это макрос, который возвращает часть параметра wParam. 
			// wParam - Иногда информация, содержащаяся в wParam, может состоять из двух частей, которые размещаются в двух 16 - разрядных словах.Для простого доступа к этим частям в Windows определены два макроса — LOWORD и HIWORD.	
		{
		case IDC_EDIT_LOGIN:
		{
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
		}		break;

		
		case IDC_BUTTON_COPY:
		{
			//1) Создаем буфер чтения:
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE] = {};
			//2) Получаем обработчики текстовых полей:
			HWND hEditLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);//Функция GetDlgItem() по ID-ресурса дочернего окна возвращает HWND соответствующего дочернего окна.

			HWND hEditPassword = GetDlgItem(hwnd, IDC_EDIT_PASSWORD);
			//3) Читаем текст из текстового поля 'Login':
			SendMessage(hEditLogin, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
			//4) Загружаем содржимое текстового буфера в поле 'Password':
			SendMessage(hEditPassword, WM_SETTEXT, 0, (LPARAM)sz_buffer);
		}		break;


		case IDOK: MessageBox(hwnd, "БЫЛА НАЖАТА КНОПКА ОК", "Info", MB_OK | MB_ICONINFORMATION); break;
		case IDCANCEL: EndDialog(hwnd, 0); break;
		}		break;

	case WM_CLOSE: EndDialog(hwnd, 0); break;//Отрабатывает при нажатии на кнопку X (Закрыть)
	}
	return FALSE;
}
