#include "zCThread.h"

zCThread::~zCThread()
{

}

void zCThread::BeginThread()
{

}

void zCThread::EndThread()
{

}

int zCThread::IsThreadRunning()
{
	return 0;
}

int zCThread::SuspendThread()
{
	return 0;
}

int zCThread::ResumeThread()
{
	return 0;
}

int zCThread::GetTerminationRequested()
{
	return 0;
}

void zCThread::SetTerminationRequested(int request)
{
	TerminationRequest = request;
}

DWORD zCThread::ThreadProc()
{
	return 0;
}
