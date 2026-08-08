       Packets in the kernel are  stored in various structures that are built upon each other.

## Socket Buffer (SKB)
### sk_buff
sk_buff (socket buffer) is the most basic structure, it is a structure that holds metadata about the packet and all packets that get to the machine are represented by it.

#### members
You can find the full declaration of sk_buff here: https://elixir.bootlin.com/linux/v6.17.9/source/include/linux/skbuff.h#L337

Here i will explain about some of the members:
#### next + prev
![[Pasted image 20251129174151.png]]
Pointers to the next and previous buffers in the list, they match the members in the sk_buff_head struct.
These members are used to put the packet in a queue (for example socket), with the help of these members it is very efficient to move the buffer in the queue or to another queue.
A queue is defined by the struct [[#sk_buff_head]]

#### End Headers Group
a group of elements that must be at the end of the struct
![[Pasted image 20251130015801.png]]
##### head, data, tail and end pointers
The head, data, tail and end pointers all point to different parts of the struct as shown here:
![[Pasted image 20251130022204.png]]
***head*** points to the head of the struct.
***data*** points to the data portion of struct, which includes the packet headers and sometimes its payload (because the sk_buff size is limited sometimes some of the payload will not be stored inside the struct and because of that will not be accessible via the data offset, we will talk about this case in another part.)







### sk_buff_head
the sk_buff_head (socket buffer head) is the structure that represents a socket buffer queue.

#### members
you can find the full declaration in here: https://elixir.bootlin.com/linux/v6.17.9/source/include/linux/skbuff.h#L337


### Related Functions
Related functions can be found on these kernel sources:
definitions: include/linux/skbuff.h
implementations: net/core/skbuff.c 

#### dev_alloc_skb
``` c
static inline struct sk_buff *dev_alloc_skb(unsigned int length)
```

##### Explaination
This function is a legacy helper around the function [[#netdev_alloc_skb]]
![[Pasted image 20251129183222.png]]
All it does is call the function with NULL in it's net device parameter and with the inputted length.
Which means the buffer will be allocated according to the [[#netdev_alloc_skb]] function and its net device will be NULL.

#### netdev_alloc_skb
``` c
struct sk_buff *netdev_alloc_skb(struct net_device *dev, unsigned int length)
```
The function allocates an skbuff for rx (designated for received packets) on a specific device

> [!Warning]
> This function explanation is incomplete! i will research about it in the future and document! 

##### Source code research



 
#### skb_reset_mac_header
``` c
static inline void skb_reset_mac_header(struct sk_buff *skb)
```
##### Explanation

#### 

## Ethernet

> [!Info]
Here i will explain about structs and function in the kernel that help with the ethernet layer.
> Many of the functions and structs here will rely and use the SKB functionalities and structs

### Related functions

#### eth_type_trans
``` c
__be16 eth_type_trans(struct sk_buff *skb, struct net_device *dev)
```
This function is implemented [here](https://elixir.bootlin.com/linux/v6.17.9/source/net/ethernet/eth.c#L146)

#### Explaination


#### Source code research

I started by reading the documentation of the function:
![[Pasted image 20251130014359.png]]
it said that this function purpose is to determine the packet's protocol ID.
I wanted to understand what this protocol id means and how it determines it (i know protocol id in correlation with the ip header but not with the ethernet header)
