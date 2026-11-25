#pragma once

class zColor;

class zCViewBase
{
public:
    virtual int anx(int x);
    virtual int any(int y);
    virtual int nax(int x);
    virtual int nay(int y);
    virtual int ClipLine(int& x1, int& y1, int& x2, int& y2);
    virtual void Line(int x1, int y1, int x2, int y2, zColor* color);
    virtual void GetViewport(int& x1, int& y1, int& x2, int& y2);
    virtual int  GetCode(int x,int y);
};

