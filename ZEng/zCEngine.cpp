#include "zCEngine.h"
#include "Globals.h"
#include "SystemFunc.h"
#include <string>
#include "zCObjectFactory.h"
#include "zMemory_Generic.h"
#include "zCResourceManager.h"
#include "zERROR.h"
#include "zCClassDef.h"
#include "Zdisk_vdfs.h"
#include "zCOption.h"

#include "Zzbert.h"
#include "ZzUlfi.h"
#include "ZzDieter.h"
#include "ZzCarsten.h"

#include "zCTexture.h"
#include "zTools.h"


int zCEngine::Init(HWND* hwnd)
{
    zCClassDef::EndStartup();

    if (g_zfactory == nullptr)
    {
        g_zfactory = new zCObjectFactory();
    }
    //zCClassDef::ObjectCreated(g_zfactory, &zCObjectFactory::classDef, "D:\\dev\\gothic\\current_work\\ZenGin\\...", 0x6C);

    sysEvent();
    zInitOptions();

    std::string optionName = "ZMEMPROFILER";
    int result = g_zoption->Parm(optionName);

    g_zmalloc->Init(result);
    zFILE_VDFS::InitFileSystem();
    sysEvent();

    g_zresMan = new zCResourceManager();

    optionName = "ZNORESTHREAD";
    result = g_zoption->Parm(optionName);

    g_zresMan->SetThreadingEnabled(result == 0);
    g_zerr->Separator();

    zBert_StartUp();
    zUlfi_StartUp();
    sysEvent();
    zDieter_StartUp(hwnd);
    zCarsten_StartUp(hwnd);

    sysEvent();

    optionName = "ZTEXCONVERT";
    result = g_zoption->Parm(optionName);

    if (result != 0)
    {
        zCTexture::ScanConvertTextures();
    }

    g_zfpuControler->RestoreDefaultControlWord();
    g_zfpuControler->SaveCurrentControlWord();

    return 1;
}
