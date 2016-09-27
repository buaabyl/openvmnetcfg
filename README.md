# openvmnetcfg
An open source implement of vmnetcfg.

VMware VMNetcfg is a useful tool, you can change IP, DNS, NAT quickly. But begin from VMware Player 3.x, it have been removed from then standard installer. You must extract from Workstation version, painful...

In the older days, you can extract from VMware Player installer, and it removed from the installer from VMware Player 5.x... But we still have vmnetui.dll,VMNetUI_ShowStandalone. But now is removed too... We have to extract from Workstation, but it really huge(500MB+).

So I decided to create an open source UI, like vmnetcfg.

## Progress
I have created a wrap library for vnetlib.dll, which work fine.
And wrote a small demo which show current IP,DNS information, and can change IP and DNS setting by api.
All this code compiled under MinGW32-W64 GCC 5.4.0

- [X] create a library for vnetlib.dll
- [X] create a simple demo which can change ip and dns
- [ ] create a Qt5 based vmnetcfg UI.



## references

[communities.vmware.com: Vnetlib - Documenting the command line](https://communities.vmware.com/docs/DOC-9571)

[kb.vmware.com: Cleaning up after an incomplete uninstallation on a Windows host (kb1308)](https://kb.vmware.com/selfservice/microsites/search.do?language=en_US&cmd=displayKC&externalId=1308)

[kb.vmware.com: VMware USB Arbitration service fails to start in VMware Workstation (kb2043656)](https://kb.vmware.com/selfservice/microsites/search.do?language=en_US&cmd=displayKC&externalId=2043656)

[stackoverflow.com: Assign IP to VMware Player](http://stackoverflow.com/questions/13153399/assign-ip-to-vmware-player)

[sanbarrow.com: Command Guide to Workstation](http://sanbarrow.com/network/cmdguide2workstation.html)

