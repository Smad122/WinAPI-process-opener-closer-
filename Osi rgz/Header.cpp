#include "Header.h"
#include "tchar.h"
#include <Windows.h>
#include <psapi.h>
#include <iostream>
#include <string>
Worker::Worker()
{
    nums = 0;
  
    pinfo = new PROCESS_INFORMATION[0];
    sinfo = new STARTUPINFO[0];
    processH = new HANDLE[0];
    hbox = NULL;
    IDT_TIMER = NULL;
    hwnd = NULL;
}
void Worker::Workeradd( HWND Text, HWND hbox1, HWND hwndH)
{



    hbox= hbox1;
    hwnd = hwndH;

    SetTimer(hwnd, IDT_TIMER, 100, 0);
    const int maxtextlength = 3;
    TCHAR textvalue[maxtextlength] = TEXT("");
    GetWindowText(Text, textvalue, maxtextlength);
    nums = _wtoi(textvalue);
    pinfo = new PROCESS_INFORMATION[nums];
    sinfo = new STARTUPINFO[nums];
    processH = new HANDLE[nums];

   
}

Worker::~Worker()
{
    for (int i = 0; i < nums; i++)
    {
        DWORD temp;
        GetExitCodeProcess(processH[i], &temp);
        if (temp == STILL_ACTIVE) {
         
            TerminateProcess(processH[i], 1);
         
        }
        CloseHandle(processH[i]);
   }

   
    
    KillTimer(hwnd, IDT_TIMER);

}
void Worker::Check()
{
    SendMessage(hbox, LB_RESETCONTENT, 0, 0);
    for (int i = 0; i < nums; i++)
    {
        DWORD temp;
        GetExitCodeProcess(processH[i], &temp);
        if (temp == STILL_ACTIVE)
        {
            std::wstring str;
            str =std::to_wstring(i);
            str += ' ';
            str += std::to_wstring(1);
            SendMessage(hbox, LB_ADDSTRING, 0, (LPARAM)str.c_str());
        }
        else
        {
            std::wstring str;
            str = std::to_wstring(i);
            str += ' ';
            str += std::to_wstring(0);
            SendMessage(hbox, LB_ADDSTRING, 0, (LPARAM)str.c_str());
        }


   }
}
void    Worker::startWork()
{
    for (int i = 0; i < nums; i++)
    {



    memset(&pinfo[i], 0, sizeof(pinfo[i]));
    memset(&sinfo[i], 0, sizeof(sinfo[i]));
    sinfo[i].cb = sizeof(sinfo[i]);
    char text[] = "d:\\WindowsProject1.exe";
    wchar_t wtext[30];
    std::mbstowcs(wtext, text, strlen(text) + 1);
    LPWSTR ptr = wtext;

      CreateProcess(NULL, ptr, NULL, NULL, false, PROCESS_QUERY_INFORMATION,
        NULL, NULL, &sinfo[i], &pinfo[i]);
      processH[i] = pinfo[i].hProcess;
    }
   
}
void    Worker::createNew(HWND Text)
{
    const int maxtextlength = 3;
    TCHAR textvalue[maxtextlength] = TEXT("");
    GetWindowText(Text, textvalue, maxtextlength);
    int n = _wtoi(textvalue);
    if ((n < nums) && (n >= 0))
    {
        DWORD temp;
        GetExitCodeProcess(processH[n], &temp);
        if ((temp != STILL_ACTIVE))
        {
            CloseHandle(processH[n]);
            memset(&pinfo[n], 0, sizeof(pinfo[n]));
            memset(&sinfo[n], 0, sizeof(sinfo[n]));
            sinfo[n].cb = sizeof(sinfo[n]);
            char text[] = "d:\\WindowsProject1.exe";
            wchar_t wtext[30];
            std::mbstowcs(wtext, text, strlen(text) + 1);
            LPWSTR ptr = wtext;

            CreateProcess(NULL, ptr, NULL, NULL, false, PROCESS_QUERY_INFORMATION,
                NULL, NULL, &sinfo[n], &pinfo[n]);
            processH[n] = pinfo[n].hProcess;
        }
    }
}
void    Worker::stopWork(HWND Text)
{
    const int maxtextlength = 3;
    TCHAR textvalue[maxtextlength] = TEXT("");
    GetWindowText(Text, textvalue, maxtextlength);
   int n = _wtoi(textvalue);
   if ((n < nums) && (n >= 0))
   {
       DWORD temp;
       GetExitCodeProcess(processH[n], &temp);
       if (temp == STILL_ACTIVE) {

           TerminateProcess(processH[n], 1);


       }
   }
}
