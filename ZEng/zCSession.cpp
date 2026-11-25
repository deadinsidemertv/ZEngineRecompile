#include "zCSession.h"

zCSession::~zCSession()
{

}

void zCSession::Init()
{

}

void zCSession::Done()
{

}

void zCSession::Render()
{

}

void zCSession::RenderBlit()
{

}

void zCSession::CamInit(zCVob* obj, zCCamera* camera)
{

}

void zCSession::CamInit()
{

}

void zCSession::SetCamera(zCCamera* camera)
{

}

zCCamera* zCSession::GetCamera()
{
	return camera;
}

zCAICamera* zCSession::GetCameraAI()
{
	return AICamera;
}

zCVob* zCSession::GetCameraVob()
{
	return CameraVob;
}

zCView* zCSession::GetViewport()
{
	return Viewport;
}

zCWorld* zCSession::GetWorld()
{
	return World;
}

void zCSession::SaveWorld(std::string name, zCWorld::zTWorldSaveMode mode, int param_3, int param_4)
{

}

void zCSession::Unknown14()
{

}

zCCSManager* zCSession::GetCutsceneManager()
{
	return CutSceneManager;
}

void zCSession::SetTime(int day, int hour, int minute)
{

}

void zCSession::GetTime(int& day, int& hour, int& minute)
{

}

void zCSession::SetWorld(zCWorld* _world)
{
	World = _world;
	World->SetOwnerSession(this);
}

void zCSession::DesktopInit()
{

}

void zCSession::CutsceneSystemInit()
{

}
