#pragma once
#include <string>
#include "zCView.h"
class zCMenu : public zCView
{

public:
    static int inGameMenu;

    std::string backTexture;
    std::string fontName;
    std::string title;

    std::string menuItems[150];

    std::string menuID;
    std::string unknownString;

    int unknownInt1, unknownInt2, unknownInt3;

    int isActive;

    zCMenu(std::string menuName);

    void InitValues();
    void SetByScript(std::string menuName);
};

