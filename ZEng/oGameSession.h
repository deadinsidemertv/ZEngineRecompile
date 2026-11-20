#pragma once

class oGameSession {
public:
    virtual void Dummy1() {} // 0x00
    virtual void Dummy2() {} // 0x04
    virtual void Dummy3() {} // 0x08
    virtual void Dummy4() {} // 0x0C
    virtual void Dummy5() {} // 0x10
    virtual void Dummy6() {} // 0x14
    virtual void Dummy7() {} // 0x18
    virtual void Dummy8() {} // 0x1C
    virtual void Dummy9() {} // 0x20

    // Вот наш метод со смещением 0x24 (возвращает int)
    virtual int Update() { return 0; }
};