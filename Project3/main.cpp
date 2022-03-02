#include "pch.h"
#include "Core.h"

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    PSTR lpCmdLine, INT nCmdShow)
{
    
    if (FAILED(Core::Get_Inst()->init(hInstance)))
        return -1;

    Core::Get_Inst()->process();

    return 0;
}