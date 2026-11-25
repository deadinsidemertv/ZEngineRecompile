#pragma once
#include "zCObject.h"

class zCSession;


class zCWorld : zCObject
{
public:

    zCSession* GameSession;

    enum zTWorldSaveMode {
        ZWOLDMODE_UNKNOWN = 0,
        // значения потом
    };

    void SetOwnerSession(zCSession* Session);
};