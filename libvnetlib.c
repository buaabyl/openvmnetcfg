#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <wchar.h>
#include <ctype.h>
#include <sys/types.h>

#include <dlwin.h>
#include "vnetlib.h"

#define LOAD(h, sym)  { \
    sym = (sym##_pf)dlsym(h, #sym); \
    if (sym == NULL) { \
        printf("Error %s not found!\n", #sym); \
        goto L_ERROR; \
    } \
}

void* vnetlib_open(void)
{
    void* h;

    h = dlopen("vnetlib.dll", RTLD_LAZY);
    if (h == NULL) {
        printf("Error\n");
        return NULL;
    }

    LOAD(h, VNL_Version);
    LOAD(h, VNL_GetIsHost64Bit);
    LOAD(h, VNL_GetIsHostVista);
    LOAD(h, VNL_GetIsHostWXP);
    LOAD(h, VNL_GetNumberOfVnets);
    LOAD(h, VNL_GetProductInstallPath);

    LOAD(h, VNL_GetDefaultLogLevel);
    LOAD(h, VNL_GetCurrentLogLevel);
    LOAD(h, VNL_SetDefaultLogLevel);
    LOAD(h, VNL_SetCurrentLogLevel);

    LOAD(h, VNL_StartBridge);
    LOAD(h, VNL_StartDHCP);
    LOAD(h, VNL_StartNAT);
    LOAD(h, VNL_StartHcmon);
    LOAD(h, VNL_StartUserIf);
    LOAD(h, VNL_StartVMCI);
    LOAD(h, VNL_StartVMX86);
    LOAD(h, VNL_StartVmkbd);
    LOAD(h, VNL_StartVmparport);

    LOAD(h, VNL_StopBridge);
    LOAD(h, VNL_StopDHCP);
    LOAD(h, VNL_StopNAT);
    LOAD(h, VNL_StopHcmon);
    LOAD(h, VNL_StopUserIf);
    LOAD(h, VNL_StopVMCI);
    LOAD(h, VNL_StopVMX86);
    LOAD(h, VNL_StopVmkbd);
    LOAD(h, VNL_StopVmparport);

    LOAD(h, VNL_GetDHCPStatus);
    LOAD(h, VNL_GetNATStatus);

    LOAD(h, VNL_GetNATConfigFilePath);
    LOAD(h, VNL_GetDHCPConfigFilePath);

    LOAD(h, VNL_GetDHCPParam);
    LOAD(h, VNL_SetDHCPParam);
    LOAD(h, VNL_GetNATParam);
    LOAD(h, VNL_SetNATParam);

    LOAD(h, VNL_UpdateDHCPFromConfig);
    LOAD(h, VNL_UpdateNATFromConfig);

    LOAD(h, VNL_GetVnetAdapterAddr);
    LOAD(h, VNL_GetVnetSubnetAddr);
    LOAD(h, VNL_GetVnetSubnetMask);

    LOAD(h, VNL_SetVnetAdapterAddr);
    LOAD(h, VNL_SetVnetSubnetAddr);
    LOAD(h, VNL_SetVnetSubnetMask);
    LOAD(h, VNL_EnableNetworkAdapter);
    LOAD(h, VNL_DisableNetworkAdapter);

    LOAD(h, VNL_GetVnetUseDHCP);
    LOAD(h, VNL_SetVnetUseDHCP);
    LOAD(h, VNL_GetVnetUseNAT);
    LOAD(h, VNL_SetVnetUseNAT);
    LOAD(h, VNL_UpdateAdapterFromConfig);

    return h;

L_ERROR:
    dlclose(h);
    return NULL;
}

void vnetlib_close(void* h)
{
    if (h) {
        dlclose(h);
    }
}


