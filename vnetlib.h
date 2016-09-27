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
 *
 *
 *
 *  the standard function naming is like this:
 *      __stdcall func(int a) -> "_func@4"
 *  but vnetlib.dll force the name to "func",
 *  so I have to load it myself, cause I don't known actual parameters......
 *
 *  Set Parameters save to registers, not conf file! and registers have higher priority.
 *      HKEY_LOCAL_MACHINE\SOFTWARE\Wow6432Node\VMware, Inc.\VMnetLib\VMnetConfig
 *      HKEY_LOCAL_MACHINE\SOFTWARE\VMware, Inc.\VMnetLib\VMnetConfig
 *
 *  this function change conf file from registers:
 *      VNL_UpdateAdapterFromConfig
 *      VNL_UpdateDHCPFromConfig
 *      VNL_UpdateNATFromConfig
 */

#ifndef VNETLIB_H_54043051_7D5D_11E6_A353_005056C00008_INCLUDED_
#define VNETLIB_H_54043051_7D5D_11E6_A353_005056C00008_INCLUDED_

////////////////////////////////////////////////////////////////////////////////
#define VERSION_MAGIC   0x10000

typedef int (*VNL_Version_pf)(void);
VNL_Version_pf VNL_Version;

typedef int (*VNL_GetIsHost64Bit_pf)(void);
VNL_GetIsHost64Bit_pf VNL_GetIsHost64Bit;

typedef int (*VNL_GetIsHostVista_pf)(void);
VNL_GetIsHostVista_pf VNL_GetIsHostVista;

typedef int (*VNL_GetIsHostWXP_pf)(void);
VNL_GetIsHostWXP_pf VNL_GetIsHostWXP;

typedef int (*VNL_GetNumberOfVnets_pf)(void);
VNL_GetNumberOfVnets_pf VNL_GetNumberOfVnets;

//@return BOOL
typedef __stdcall int (*VNL_GetProductInstallPath_pf)(wchar_t* buffer, int* nr_wchars);
VNL_GetProductInstallPath_pf VNL_GetProductInstallPath;

////////////////////////////////////////////////////////////////////////////////
//each message log is 2048 maximal,
//if longer than 2048, truncated!
//all this VNL_DEBUG_x is bit-wish flags.
//can be combined.
enum VNL_DEBUG {
    VNL_DEBUG_1     = 0x01, //default enabled
    VNL_DEBUG_2     = 0x02, //default enabled
    VNL_DEBUG_4     = 0x04,
    VNL_DEBUG_8     = 0x08,
    VNL_DEBUG_16    = 0x10,
    VNL_DEBUG_32    = 0x20,
    VNL_DEBUG_128   = 0x80,
    VNL_DEBUG_ALL   = 0xBF, //Verbose
};

typedef __stdcall int (*VNL_GetCurrentLogLevel_pf)(void);
VNL_GetCurrentLogLevel_pf VNL_GetCurrentLogLevel;

typedef __stdcall int (*VNL_GetDefaultLogLevel_pf)(void);
VNL_GetDefaultLogLevel_pf VNL_GetDefaultLogLevel;

typedef __stdcall int (*VNL_SetCurrentLogLevel_pf)(int loglevel);
VNL_SetCurrentLogLevel_pf VNL_SetCurrentLogLevel;

typedef __stdcall int (*VNL_SetDefaultLogLevel_pf)(int loglevel);
VNL_SetDefaultLogLevel_pf VNL_SetDefaultLogLevel;


////////////////////////////////////////////////////////////////////////////////
//@brief    Start/Stop control
//@return   BOOL
typedef int (*VNL_StartBridge_pf)(void);
typedef int (*VNL_StartDHCP_pf)(void);
typedef int (*VNL_StartNAT_pf)(void);
typedef int (*VNL_StartHcmon_pf)(void);
typedef int (*VNL_StartUserIf_pf)(void);
typedef int (*VNL_StartVMCI_pf)(void);
typedef int (*VNL_StartVMX86_pf)(void);
typedef int (*VNL_StartVmkbd_pf)(void);
typedef int (*VNL_StartVmparport_pf)(void);
typedef int (*VNL_StopBridge_pf)(void);
typedef int (*VNL_StopDHCP_pf)(void);
typedef int (*VNL_StopNAT_pf)(void);
typedef int (*VNL_StopHcmon_pf)(void);
typedef int (*VNL_StopUserIf_pf)(void);
typedef int (*VNL_StopVMCI_pf)(void);
typedef int (*VNL_StopVMX86_pf)(void);
typedef int (*VNL_StopVmkbd_pf)(void);
typedef int (*VNL_StopVmparport_pf)(void);
VNL_StartBridge_pf      VNL_StartBridge;
VNL_StartDHCP_pf        VNL_StartDHCP;
VNL_StartNAT_pf         VNL_StartNAT;
VNL_StartHcmon_pf       VNL_StartHcmon;
VNL_StartUserIf_pf      VNL_StartUserIf;
VNL_StartVMCI_pf        VNL_StartVMCI;
VNL_StartVMX86_pf       VNL_StartVMX86;
VNL_StartVmkbd_pf       VNL_StartVmkbd;
VNL_StartVmparport_pf   VNL_StartVmparport;
VNL_StopBridge_pf       VNL_StopBridge;
VNL_StopDHCP_pf         VNL_StopDHCP;
VNL_StopNAT_pf          VNL_StopNAT;
VNL_StopHcmon_pf        VNL_StopHcmon;
VNL_StopUserIf_pf       VNL_StopUserIf;
VNL_StopVMCI_pf         VNL_StopVMCI;
VNL_StopVMX86_pf        VNL_StopVMX86;
VNL_StopVmkbd_pf        VNL_StopVmkbd;
VNL_StopVmparport_pf    VNL_StopVmparport;

////////////////////////////////////////////////////////////////////////////////
enum VNL_DHCPSTATUS{
    VNETLIB_SERVICE_STATUS_STOPPED              = 33796,
    VNETLIB_SERVICE_STATUS_STOP_PENDING         = 33797,
    VNETLIB_SERVICE_STATUS_RUNNING              = 33800,
    VNETLIB_SERVICE_STATUS_START_PENDING        = 33801,
    VNETLIB_SERVICE_STATUS_CONTINUE_PENDING     = 33802,
    VNETLIB_SERVICE_STATUS_PAUSED               = 33808,
    VNETLIB_SERVICE_STATUS_PAUSE_PENDING        = 33809,
    VNETLIB_SERVICE_STATUS_INVALID_OR_UNKNOWN   = 33824,
};

typedef __stdcall int (*VNL_GetDHCPStatus_pf)(void);
VNL_GetDHCPStatus_pf VNL_GetDHCPStatus;

typedef __stdcall int (*VNL_GetNATStatus_pf)(void);
VNL_GetNATStatus_pf VNL_GetNATStatus;

typedef __stdcall int (*VNL_GetDHCPConfigFilePath_pf)(wchar_t* buffer, int* nr_wchars);
VNL_GetDHCPConfigFilePath_pf VNL_GetDHCPConfigFilePath;

typedef __stdcall int (*VNL_GetNATConfigFilePath_pf)(wchar_t* buffer, int* nr_wchars);
VNL_GetNATConfigFilePath_pf VNL_GetNATConfigFilePath;


#define VNL_METHOD_READBACK 1
#define VNL_METHOD_READOLY  0

typedef enum VNL_DHCPPARAMS {
    VNETLIB_DHCPLeaseBeginIP            = 13350,
    VNETLIB_DHCPLeaseEndIP              = 13351,
    VNETLIB_DHCPDefaultLeaseDuration    = 13354,
    VNETLIB_DHCPMaxLeaseDuration        = 13355,
}vnl_dhcp_params_t;

typedef enum VNL_NATPARAMS {
    VNETLIB_NATGatewayIPAddress                 = 9027,
    VNETLIB_NATConfigPort                       = 9030,
    VNETLIB_NATActiveFTP                        = 9031,
    VNETLIB_NATAllowAnyOUI                      = 9032,
    VNETLIB_NATUDPTimeOut                       = 9033,
    VNETLIB_NATDNSPolicy                        = 9034,
    VNETLIB_NATDNSTimeout                       = 9035,
    VNETLIB_NATDNSRetries                       = 9036,
    VNETLIB_NATDNSAutodetect                    = 9037,
    VNETLIB_NATDNSNameServer1                   = 9038,
    VNETLIB_NATDNSNameServer2                   = 9039,
    VNETLIB_NATDNSNameServer3                   = 9040,
    VNETLIB_NATNBNSTimeout                      = 9041,
    VNETLIB_NATNBNSRetries                      = 9042,
    VNETLIB_NATNBDSTimeout                      = 9043,
    VNETLIB_NATAutoPrivTCP                      = 9044,
    VNETLIB_NATAutoPrivUDP                      = 9045,
    VNETLIB_NATExternalIP                       = 9046,
    VNETLIB_NATResetConnectionOnLinkDown        = 9047,
    VNETLIB_NATTimeWaitTimeout                  = 9048,
    VNETLIB_NATResetConnectionOnDestLocalHost   = 9049,
    VNETLIB_NATIp6Enable                        = 9050,
    VNETLIB_NATIp6Prefix                        = 9051,
}vnl_nat_params_t;

//@params   name    "vmnet%d"
//@params   len     [in] max buffer size
//                  [out] wrote bytes (include '\0')
typedef __stdcall int (*VNL_GetDHCPParam_pf)(const char* name, vnl_dhcp_params_t type, int method, char* buffer, int* len);
VNL_GetDHCPParam_pf VNL_GetDHCPParam;

//@params   buffer  string end with '\0'
//@params   len     string length
typedef __stdcall int (*VNL_SetDHCPParam_pf)(const char* name, vnl_dhcp_params_t type, const char* buffer, int* len);
VNL_SetDHCPParam_pf VNL_SetDHCPParam;

//@params   name    "vmnet%d"
//@params   len     [in] max buffer size
//                  [out] wrote bytes (include '\0')
typedef __stdcall int (*VNL_GetNATParam_pf)(const char* name, vnl_nat_params_t type, int method, char* buffer, int* len);
VNL_GetNATParam_pf VNL_GetNATParam;

//@params   buffer  string end with '\0'
//@params   len     string length
typedef __stdcall int (*VNL_SetNATParam_pf)(const char* name, vnl_nat_params_t type, const char* buffer, int* len);
VNL_SetNATParam_pf VNL_SetNATParam;

//@brief    this function reload NAT service from "C:\ProgramData\VMware\vmnetdhcp.conf" 
//@params   name    "vmnet%d"
typedef __stdcall int (*VNL_UpdateDHCPFromConfig_pf)(const char* name);
VNL_UpdateDHCPFromConfig_pf VNL_UpdateDHCPFromConfig;

//@brief    this function reload NAT service from "C:\ProgramData\VMware\vmnetnat.conf" 
//@params   name    "vmnet%d"
typedef __stdcall int (*VNL_UpdateNATFromConfig_pf)(const char* name);
VNL_UpdateNATFromConfig_pf VNL_UpdateNATFromConfig;


////////////////////////////////////////////////////////////////////////////////
//@params   name    "vmnet%d"
//@params   ip_addr buffer
//@params   len     [in] max buffer size
//                  [out] wrote bytes (include '\0')
typedef __stdcall int (*VNL_GetVnetAdapterAddr_pf)(const char* name, char* ip_addr, int* len);
VNL_GetVnetAdapterAddr_pf VNL_GetVnetAdapterAddr;

//@params   name    "vmnet%d"
//@params   ip_addr buffer
//@params   len     [in] max buffer size
//                  [out] wrote bytes (include '\0')
typedef __stdcall int (*VNL_GetVnetSubnetAddr_pf)(const char* name, char* ip_addr, int* len);
VNL_GetVnetSubnetAddr_pf VNL_GetVnetSubnetAddr;

//@params   name    "vmnet%d"
//@params   ip_addr buffer
//@params   len     [in] max buffer size
//                  [out] wrote bytes (include '\0')
typedef __stdcall int (*VNL_GetVnetSubnetMask_pf)(const char* name, char* ip_mask, int* len);
VNL_GetVnetSubnetMask_pf VNL_GetVnetSubnetMask;


//@params   name    "vmnet%d"
//@params   ip_addr 192.168.100.2
typedef __stdcall int (*VNL_SetVnetAdapterAddr_pf)(const char* name, const char* ip_addr);
VNL_SetVnetAdapterAddr_pf VNL_SetVnetAdapterAddr;

//@params   name    "vmnet%d"
//@params   ip_addr 192.168.100.2
typedef __stdcall int (*VNL_SetVnetSubnetAddr_pf)(const char* name, const char* ip_addr);
VNL_SetVnetSubnetAddr_pf VNL_SetVnetSubnetAddr;

//@params   name    "vmnet%d"
//@params   ip_mask 255.255.255.0
typedef __stdcall int (*VNL_SetVnetSubnetMask_pf)(const char* name, const char* ip_mask);
VNL_SetVnetSubnetMask_pf VNL_SetVnetSubnetMask;

//@params   name    "vmnet%d"
typedef __stdcall int (*VNL_EnableNetworkAdapter_pf)(const char* name);
VNL_EnableNetworkAdapter_pf VNL_EnableNetworkAdapter;

//@params   name    "vmnet%d"
typedef __stdcall int (*VNL_DisableNetworkAdapter_pf)(const char* name);
VNL_DisableNetworkAdapter_pf VNL_DisableNetworkAdapter;

//@params   name    "vmnet%d"
typedef __stdcall int (*VNL_GetVnetUseDHCP_pf)(const char* name);
VNL_GetVnetUseDHCP_pf VNL_GetVnetUseDHCP;

//@params   name    "vmnet%d"
typedef __stdcall int (*VNL_SetVnetUseDHCP_pf)(const char* name, int enable);
VNL_SetVnetUseDHCP_pf VNL_SetVnetUseDHCP;

//@params   name    "vmnet%d"
typedef __stdcall int (*VNL_GetVnetUseNAT_pf)(const char* name);
VNL_GetVnetUseNAT_pf VNL_GetVnetUseNAT;

//@params   name    "vmnet%d"
typedef __stdcall int (*VNL_SetVnetUseNAT_pf)(const char* name, int enable);
VNL_SetVnetUseNAT_pf VNL_SetVnetUseNAT;

//@params   name    "vmnet%d"
typedef __stdcall int (*VNL_UpdateAdapterFromConfig_pf)(const char* name);
VNL_UpdateAdapterFromConfig_pf VNL_UpdateAdapterFromConfig;

////////////////////////////////////////////////////////////////////////////////
void* vnetlib_open(void);
void vnetlib_close(void* h);

#endif

