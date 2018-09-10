#include <stdio.h>
#include "IApplication.hpp"
#include "MDUILibAfx.hpp"

using namespace MDUILib;

int main(int argc,char** argv)
{
    int ret;
    if((ret = g_pApp->Initialize()) != 0)
    {
        printf("Failed!");
    }

	g_pApp->Run();

    g_pApp->Finalize();

    return 0;
}
