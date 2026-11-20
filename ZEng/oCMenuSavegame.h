#pragma once
#include "zCMenu.h"
#include <string>

class oCMenuSavegame : public zCMenu
{
public:
	oCMenuSavegame(std::string menuName, int mode);

	void* saveManager = nullptr;

	void Update();
};

