
The NIC is a computer hardware component that connects a computer to a computer network.
Early controllers were in the form of expansion cards that connected to the computer bus.
Nowadays most modern NICs are part of the motherboard itself (LAN on motherboard - LOM), although there sometimes it still comes as a separate card.

## Purpose
The NIC implements the electronic circuitry required to communicate using a specific physical layer and data link layer standard such as Ethernet or Wi-Fi.
The NIC acts a physical layer and data link layer device:
For the physical layer, it holds the circuitry required for this type of communication, for example an RF receiver and transmitter for WI-FI, an ethernet port for Ethernet and etc.
For the data link layer, it implements logic related to the data link layer communication, for example, in the case of an Ethernet NIC, it will split the data into ethernet frames, own the mac address, only accept packets that are coming to our mac address and etc.


## Functionality
The NIC receives packets from the computer (kernel, mostly) and sends them (Tx - Transmitting)
The NIC receives packet from the network and sends them to the computer (Rx - Receiving)

The NIC communicates with the CPU using one or more of the ordinary ways that are used in the CPU communication with the peripheries in the computer, which include the following:
For notification of availability of packets to transfer it will use either Polling or Interrupt driven I/O
in order to transfer packet data it will either use Programmed input/output or DMA

The CPU will communicate with the NIC with the help of the NIC's driver.

In the case of ethernet NICs, the following functionality will happen:
When a packet is received, it will check if it is received to its mac address, if it is not the packet will be dropped (unless in promiscuous mode)

## Advanced functionality
Did not read about that

## Notes
Theoretically, the NIC is only a must for the special circuitry that  it provides for the physical layer.
the data link layer it does can be done on the main CPU.
I suppose that it does some of the data link logic because of a few reasons, mostly historic ones, first of all, when computer networks started, people did not use them and did not code their computers to work with them, so the NIC had to give this functionality.
Another reason, is that with this logic happening on the NIC, you can create hardware optimizations that make this logic more efficient than on the normal central processor.

Also in the end it is important to remember that the OS and the kernel still know about the ethernet layer and use it, so the NIC does not exclusively handle this.