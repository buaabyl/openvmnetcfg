/*  
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; see the file COPYING.  If not, write to
 *  the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <wchar.h>
#include <ctype.h>
#include <sys/types.h>

#include "vnetlib.h"

//
//logfile:  %TEMP%/vminst.log
//

void memdump(void* buf, int nr_bytes, int prefix_white)
{
    uint8_t* p;
    int i;
    int j;

    p = (uint8_t*)buf;

    if ((buf == NULL) || (nr_bytes <= 0)) {
        return;
    }

    for (j = 0;j < prefix_white;j++) {
        printf(" ");
    }
    printf("%08p: ", p);
    for (i = 0;i < nr_bytes;i++) {
        printf("%02x ", p[i] & 0xFFu);
        if ((i % 8) == 7) {
            printf("  ");

            for (j = i - 7;j <= i;j++) {
                if (!iscntrl(p[j]) && isprint(p[j])) {
                    putchar(p[j]);
                } else if (p[j] == '\t') {
                    printf("t");
                } else if (p[j] == '\r') {
                    printf("r");
                } else if (p[j] == '\n') {
                    printf("n");
                } else {
                    putchar('.');
                }
            }

            printf("\n");
            if (i != nr_bytes - 1) {
                for (j = 0;j < prefix_white;j++) {
                    printf(" ");
                }
                printf("%08p: ", p + i + 1);
            }
        }
    }
    if ((i % 8) != 0) {
        printf("    ");

        for (j = i/8*8;j < i;j++) {
            if (isalnum(p[j])) {
                putchar(p[j]);
            } else if (p[j] == '\t') {
                printf("\\t");
            } else if (p[j] == '\r') {
                printf("\\r");
            } else if (p[j] == '\n') {
                printf("\\n");
            } else {
                putchar('.');
            }
        }


        printf("\n");
    }
}

void print_service_status(int status)
{
    switch (status) {
        case VNETLIB_SERVICE_STATUS_STOPPED:
            printf("stoped");
            break;
        case VNETLIB_SERVICE_STATUS_STOP_PENDING:
            printf("stop_pending");
            break;
        case VNETLIB_SERVICE_STATUS_RUNNING:
            printf("running");
            break;
        case VNETLIB_SERVICE_STATUS_START_PENDING:
            printf("start_pending");
            break;
        case VNETLIB_SERVICE_STATUS_CONTINUE_PENDING:
            printf("continue_pending");
            break;
        case VNETLIB_SERVICE_STATUS_PAUSED:
            printf("paused");
            break;
        case VNETLIB_SERVICE_STATUS_PAUSE_PENDING:
            printf("pause_pending");
            break;
        case VNETLIB_SERVICE_STATUS_INVALID_OR_UNKNOWN:
            printf("unknown");
            break;
        default:
            printf("error");
            break;
    }
}

void print_vnet()
{
    char vname[128];
    char buffer[256];
    char* param_names[] = {
        "DHCPLeaseBeginIP",
        "DHCPLeaseEndIP",
        "DHCPDefaultLeaseDuration",
        "DHCPMaxLeaseDuration",
    };
    int params[] = {
        VNETLIB_DHCPLeaseBeginIP,
        VNETLIB_DHCPLeaseEndIP,
        VNETLIB_DHCPDefaultLeaseDuration,
        VNETLIB_DHCPMaxLeaseDuration,
    };
    int ret;
    int len;
    int n;
    int i;
    int j;

    n = VNL_GetNumberOfVnets();

    for (i = 0;i < n;i++) {
        sprintf(vname, "vmnet%d", i);

        len = sizeof(buffer);
        memset(buffer, 0, sizeof(buffer));
        ret = VNL_GetVnetAdapterAddr(vname, buffer, &len);
        if (!ret) {
            continue;
        }

        printf("VNL_GetDHCPParam(%s):\n", vname);
        printf("  %-25s : %d\n", "DHCP", VNL_GetVnetUseDHCP(vname));
        printf("  %-25s : %d\n", "NAT", VNL_GetVnetUseNAT(vname));
        printf("  %-25s : (%d) \"%s\"\n", "Adapter Address", len, buffer);

        len = sizeof(buffer);
        memset(buffer, 0, sizeof(buffer));
        ret = VNL_GetVnetSubnetAddr(vname, buffer, &len);
        printf("  %-25s : (%d) \"%s\"\n", "Adapter Sub Address", len, buffer);

        len = sizeof(buffer);
        memset(buffer, 0, sizeof(buffer));
        ret = VNL_GetVnetSubnetMask(vname, buffer, &len);
        printf("  %-25s : (%d) \"%s\"\n", "Adapter Sub Mask", len, buffer);

        for (j = 0;j < sizeof(params)/sizeof(params[0]);j++) {
            len = 100;
            memset(buffer, 0, sizeof(buffer));

            ret = VNL_GetDHCPParam(vname, params[j], VNL_METHOD_READBACK, buffer, &len);
            if (ret) {
                printf("  %-25s : (%d) \"%s\"\n", param_names[j], len, buffer);
            }
        }
        printf("\n");
    }
}

void change_ip()
{
    int ret;
    int len;
    const char sub_mask[]           = "255.255.255.0";
    const char sub_addr[]           = "192.168.65.0";
    const char host_adapter_ip[]    = "192.168.65.1";
    const char dhcp_begin[]         = "192.168.65.128";
    const char dhcp_end[]           = "192.168.65.254";

    printf("VNL_StopNAT                 %d\n", VNL_StopNAT());
    printf("VNL_StopDHCP                %d\n", VNL_StopDHCP());

    ret = VNL_SetVnetSubnetAddr("vmnet8", sub_addr);
    printf("VNL_SetVnetSubnetAddr       %d\n", ret);

    ret = VNL_SetVnetSubnetMask("vmnet8", sub_mask);
    printf("VNL_SetVnetSubnetMask       %d\n", ret);

    ret = VNL_SetVnetAdapterAddr("vmnet8", host_adapter_ip);
    printf("VNL_SetVnetAdapterAddr      %d\n", ret);

    len = strlen(dhcp_begin);
    ret = VNL_SetDHCPParam("vmnet8", VNETLIB_DHCPLeaseBeginIP, dhcp_begin, &len);
    printf("VNL_SetDHCPParam            %d\n", ret);

    len = strlen(dhcp_end);
    ret = VNL_SetDHCPParam("vmnet8", VNETLIB_DHCPLeaseEndIP,   dhcp_end, &len);
    printf("VNL_SetDHCPParam            %d\n", ret);

    printf("VNL_SetVnetUseNAT           %d\n", VNL_SetVnetUseNAT("vmnet8", 1));
    printf("VNL_SetVnetUseDHCP          %d\n", VNL_SetVnetUseDHCP("vmnet8", 1));
    printf("VNL_UpdateDHCPFromConfig    %d\n", VNL_UpdateDHCPFromConfig("vmnet8"));
    printf("VNL_UpdateNATFromConfig     %d\n", VNL_UpdateNATFromConfig("vmnet8"));
    printf("VNL_UpdateAdapterFromConfig %d\n", VNL_UpdateAdapterFromConfig("vmnet8"));

    printf("VNL_StartNAT                %d\n", VNL_StartNAT());
    printf("VNL_StartDHCP               %d\n", VNL_StartDHCP());

    printf("VNL_DisableNetworkAdapter   %d\n", VNL_DisableNetworkAdapter("vmnet8"));
    printf("VNL_EnableNetworkAdapter    %d\n", VNL_EnableNetworkAdapter("vmnet8"));
}

int main(int argc, char* argv[])
{
    void* h;
    wchar_t wbuffer[256];
    int ret;
    int len;
    int i;

    h = vnetlib_open();
    if (h == NULL) {
        printf("Error\n");
        return -1;
    }

    printf("VNL_Version                 0x%08x (expect 0x%08x)\n", VNL_Version(), VERSION_MAGIC);
    printf("VNL_GetIsHost64Bit          %d\n", VNL_GetIsHost64Bit());
    printf("VNL_GetIsHostVista          %d\n", VNL_GetIsHostVista());
    printf("VNL_GetIsHostWXP            %d\n", VNL_GetIsHostWXP());
    printf("VNL_GetNumberOfVnets        %d\n", VNL_GetNumberOfVnets());
    printf("VNL_GetDefaultLogLevel      %d\n", VNL_GetDefaultLogLevel());
    printf("VNL_GetCurrentLogLevel      %d\n", VNL_GetCurrentLogLevel());
    printf("VNL_SetCurrentLogLevel      %d\n", VNL_SetCurrentLogLevel(VNL_DEBUG_ALL));
    printf("VNL_GetCurrentLogLevel      %d\n", VNL_GetCurrentLogLevel());

    ret = VNL_GetDHCPStatus();
    printf("VNL_GetDHCPStatus           %d (", ret);
    print_service_status(ret);
    printf(")\n");

    ret = VNL_GetNATStatus();
    printf("VNL_GetNATStatus            %d (", ret);
    print_service_status(ret);
    printf(")\n");

    len = sizeof(wbuffer)/sizeof(wbuffer[0]);
    memset(wbuffer, 0, sizeof(wbuffer));
    ret = VNL_GetProductInstallPath(wbuffer, &len);
    printf("VNL_GetProductInstallPath   %d\n", ret);
    wprintf(L"  \"%ls\"\n", wbuffer);
    printf("\n");

    len = sizeof(wbuffer)/sizeof(wbuffer[0]);
    memset(wbuffer, 0, sizeof(wbuffer));
    ret = VNL_GetNATConfigFilePath(wbuffer, &len);
    printf("VNL_GetNATConfigFilePath    %d\n", ret);
    wprintf(L"  \"%ls\"\n", wbuffer);
    printf("\n");

    len = sizeof(wbuffer)/sizeof(wbuffer[0]);
    memset(wbuffer, 0, sizeof(wbuffer));
    ret = VNL_GetDHCPConfigFilePath(wbuffer, &len);
    printf("VNL_GetDHCPConfigFilePath   %d\n", ret);
    wprintf(L"  \"%ls\"\n", wbuffer);
    printf("\n");

    print_vnet();

    //change_ip();

    vnetlib_close(h);


    return 0;
}

