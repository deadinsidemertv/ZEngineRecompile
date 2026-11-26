#pragma once
#include <Windows.h>

class zCThread
{
public:

    int TerminationRequest;

    virtual ~zCThread();

    virtual void BeginThread();
    virtual void EndThread();
    virtual int IsThreadRunning();
    virtual int SuspendThread();
    virtual int ResumeThread();

    virtual int GetTerminationRequested();
    virtual void SetTerminationRequested(int request);

    virtual DWORD ThreadProc();
};

