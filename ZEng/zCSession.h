#pragma once
#include "zCInputCallback.h"
#include <string>
#include "zCWorld.h"
#include "zCView.h"

class zCVob;
class zCCamera;
class zCAICamera;
class zTWorldSaveMode;
class zCCSManager;

class zCSession : public zCInputCallback
{
public:
    zCCamera* camera;
    zCAICamera* AICamera;
    zCVob* CameraVob;
    zCView* Viewport;
    zCWorld* World;
    zCCSManager* CutSceneManager;

    virtual ~zCSession();

    virtual void Init();
    virtual void Done();
    virtual void Render();
    virtual void RenderBlit();
    virtual void CamInit(zCVob* obj,zCCamera* camera);
    virtual void CamInit();          // слот 6 — Ghidra показала то же имя, что и слот 5
    virtual void SetCamera(zCCamera* camera);
    virtual zCCamera* GetCamera();
    virtual zCAICamera* GetCameraAI();
    virtual zCVob* GetCameraVob();
    virtual zCView* GetViewport();
    virtual zCWorld* GetWorld();
    virtual void  SaveWorld(std::string name, zCWorld::zTWorldSaveMode mode, int param_3, int param_4);
    virtual void  Unknown14();        // слот 14 — LAB_005b77b0, имя неизвестно
    virtual zCCSManager* GetCutsceneManager();
    virtual void  SetTime(int day, int hour, int minute);
    virtual void  GetTime(int &day,int &hour,int &minute);
    virtual void  SetWorld(zCWorld* _world);
    virtual void  DesktopInit();
    virtual void  CutsceneSystemInit();
};

