
#ifndef workerH
#define workerH
#include <windows.h>

class Worker
{
    HWND hbox;
    STARTUPINFO* sinfo;
    PROCESS_INFORMATION* pinfo;
   HANDLE* processH;
   
    int nums;
    HWND hwnd;
    UINT_PTR IDT_TIMER;
public:

    Worker();
    void Workeradd( HWND Text, HWND hbox1, HWND hwnd);
    ~Worker();
    void startWork();
    void stopWork(HWND Text);
    void Check();
    void createNew(HWND Text);

};


//---------------------------------------------------------------------------
#endif