#include "zCEngine.h"
#include "Globals.h"
#include "SystemFunc.h"
#include "zCObjectFactory.h";
#include "zCClassDef.h"


int zCEngine::Init(HWND* hwnd)
{
    zCClassDef::EndStartup();

    if (g_zfactory == nullptr)
    {
        g_zfactory = new zCObjectFactory();
    }
    zCClassDef::ObjectCreated(g_zfactory, &zCObjectFactory::classDef, "D:\\dev\\gothic\\current_work\\ZenGin\\...", 0x6C);

    sysEvent();
    zInitOptions();

}
