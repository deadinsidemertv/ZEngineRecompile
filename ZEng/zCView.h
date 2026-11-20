#pragma once
#include "zCInputCallback.h"
class zCView : public zCInputCallback
{
	public:
        zCView();
        zCView(int x, int y, int w, int h, int mode);

        // Тот самый метод +0x20 (закрытие)
        void Close(int param);

        // Вставка элемента (вызывается в InitScreen_Open)
        void InsertItem(zCView* item, int pos);

        // Отрисовка (вызывается в InitScreen_Open и в Run)
        void Render();
};

