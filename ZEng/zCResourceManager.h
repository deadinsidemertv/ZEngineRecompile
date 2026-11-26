#pragma once
#include "zCThread.h"

class zCResourceManager : public zCThread
{
public:
	void SetThreadingEnabled(int isEnable);

	int ThreadingEnable = 0;
};

