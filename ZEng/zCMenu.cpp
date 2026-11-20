#include "zCMenu.h"
#include <algorithm>
#include <iostream>


int zCMenu::inGameMenu = 0;

zCMenu::zCMenu(std::string menuName)
    : backTexture(menuName),
    fontName(menuName),
    title(menuName),
    menuID(menuName),       
    unknownString(menuName) 
{
    isActive = 1;

    InitValues();
    std::transform(menuID.begin(), menuID.end(), menuID.begin(), ::toupper);
    SetByScript(menuName);
}

void zCMenu::InitValues()
{

}

void zCMenu::SetByScript(std::string menuName)
{

}
