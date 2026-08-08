Now that i have shell😊 i wanted to explore the machine a bit

## Processes
looking at the processes, i did ps -ef to see what was running on the machine, there of all there seems to be some processes that look like they should be known:
![[Pasted image 20250922015908.png]]
from reading online i saw that they are part of RDKB (RDK BroadBand) which is an open source software that gives core functions used in broadband communication (looks like they are in charge of the wifi side of things)
I found an interesting bash script
![[Pasted image 20250922020121.png]]

this script seems to be a watchdog and proprietary  :
![[Pasted image 20250922020235.png]]
this tells me that all of the processes mentioned here were created by the router's company and not by an open source software or linux, which is exactly what i am looking for😊

there are the hostapd processes:
![[Pasted image 20250922020657.png]]
which according to the internet are used to turn a NIC into an WIFI access point.

There are more interesting processes in there but i decided to look on other things

### Interesting files
I tried to look and find some interesting files,
i started by looking at /data:
![[Pasted image 20250922021228.png]]
this directory seems to have interesting data, for examples: the reboots that happend to the router and the reasons they happend.
