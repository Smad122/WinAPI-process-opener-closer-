
#include <iostream>
#include <Windows.h>
#include <string>
#include <tchar.h>
#include "Header.h"
HWND hbox1;
HWND buttonb;
Worker ab;



LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{



    switch (uMsg)
    {

    case WM_COMMAND:
    {
        if (LOWORD(wParam) == 1)

        {
          
            ab.Workeradd(buttonb, hbox1, hwnd);
            ab.startWork();
           
    
     

        }
        if (LOWORD(wParam) == 2)

        {

            ab.stopWork(buttonb);


        }
        if (LOWORD(wParam) == 4)
        {
            ab.createNew(buttonb);
        }
        
        break;
    
    }

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case LB_ADDSTRING:
      
        break;
    case WM_TIMER:

    {
        ab.Check();
    }

          


    case  LB_RESETCONTENT:
        break;
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    return 0;
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pCmdLine, int nCmdShow)
{


    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = _T("MyWndClass");
    RegisterClass(&wc);


    HWND hWnd = CreateWindow(_T("MyWndClass"), _T("My Application"), WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        0, 0, 600, 400, NULL, NULL, hInstance, NULL);


    HWND butto1 = CreateWindow(_T("BUTTON"), _T("Начать"), WS_VISIBLE | WS_CHILD, 400, 50, 120, 30,
        hWnd, (HMENU)1, hInstance, NULL);
    HWND button2 = CreateWindow(_T("BUTTON"), _T("Закрыть процесс"), WS_VISIBLE | WS_CHILD, 400, 100, 120, 30,
        hWnd, (HMENU)2, hInstance, NULL);
    HWND button3 = CreateWindow(_T("BUTTON"), _T("Создать процесс"), WS_VISIBLE | WS_CHILD, 400, 150, 120, 30,
        hWnd, (HMENU)4, hInstance, NULL);
    HWND tbox = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T(""), WS_VISIBLE | WS_CHILD, 400, 200, 120, 30,
       hWnd, (HMENU)3, hInstance, NULL);
   

    HWND hListbox1 = CreateWindow(_T("LISTBOX"), _T("Listbox 1"), WS_VISIBLE | WS_CHILD | LBS_STANDARD, 20, 20, 350, 300, hWnd, NULL, NULL, NULL);

    buttonb = tbox;
   
    hbox1 = hListbox1;
 


    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
        
    }

    return 0;


}