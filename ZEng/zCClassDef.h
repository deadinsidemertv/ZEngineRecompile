#pragma once
#include "zCObject.h"
class zCClassDef : public zCObject
{
public:
    static void EndStartup();
    static void ObjectCreated(zCObject* object, zCClassDef* classdef,const char* name, int inf);
};

