
### Background
Before i start explaining about what the linux kernel does to packets, i want to mention the OSI model (more about the model can be explained here: [[OSI Model]]):
![[Pasted image 20251108161148.png]]
The operating system distributes the responsibilities of the packet handling according to the OSI model.

The physical layer and the data link layer will be handled by the [[NIC (Network Interface Controller)]] - when a packet is received by it, it will be handled and sent to the kernel if valid (more information of the NIC page).
When a packet needs to be sent from the computer, the kernel will communicate with the NIC and tell it to send the packet.
> [!Note]
> The NIC is the first to handle the data link layer of the packets.
> With that, the kernel is also aware of the data link layer and also takes a later part of handling it according to the OS needs.

The kernel handles the data link, network and transport layers.
After the kernel handles those layers, it will put the packets in the corresponding socket, which from there it will be sent to a user mode application.
The user mode application will handle the Application layer (which also includes the Session and Presentation layers)
## Kernel network stack handling

#### General concepts

#### net_device
The linux kernel has the net_device structure, each represent a different network device.
This struct contains much information that is used in the various linux INET functions.

The full struct with documentation can be found here:
https://elixir.bootlin.com/linux/v6.17.8/source/include/linux/netdevice.h#L1770

P.S
This struct is being called a "bad struct" in the linux kernel documentation because it contains so much information about many different things.
```
Actually, this whole structure is a big mistake.  It mixes I/O
 *	data with strictly "high-level" data, and it has to know about *	almost every data structure used in the INET module.
``` 


#### Packets
Packets in the kernel are saved in various structs, it is explained here: [[Packets]]
#### Features that can change packet traversal

here i will mention features in the linux kernel that can affect the usual network stack handling
##### Netfilter
Netfilter is a framework given by the linux kernel.
Netfilter offers various functions and operations for packet filtering, network address translation, and port translation, which provide the functionality required for directing packets through a network and prohibiting packets from reaching sensitive locations within a network.
Netfilter works by hooking various parts of the linux kernel and giving kernel modules the ability to register callback functions to them.

##### Ipsec subsystem

### Data Link Layer

> [!Info]
> This paragraph will refer to concepts explained in [[Packets#Socket Buffer (SKB)]]
> 

The packet flow starts when a packet is received on the wire.
When it is received on the wire the network device driver will call the method netdev_alloc_skb (or the dev_alloc_skb method, which is a legacy version of netdev_alloc_skb)


