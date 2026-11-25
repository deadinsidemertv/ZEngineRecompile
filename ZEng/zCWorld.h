#pragma once

class zCWorld
{
public:

    zCSession* GameSession;

    enum zTWorldSaveMode {
        ZWOLDMODE_UNKNOWN = 0,
        // значения потом
    };

    void SetOwnerSession(zCSession* Session);
};