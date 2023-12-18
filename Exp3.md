## Question 1

To configure the ip's we had to use for tux53, tux54 and tux52, respectively:

```note
ifconfig eth0 172.16.50.1/24	(tux53)
ifconfig eth0 172.16.50.254/24  (tux54)
ifconfig eth1 172.16.51.253/24  (tux54)
ifconfig eth0 172.16.50.1/24	(tux52)
```

We then created two bridges in the switch, bridge50 and bridge51: 

```note
/interface bridge add name=bridge50
/interface bridge add name=bridge51
```

And defined which port would use which bridge, first we need to remove the port from the default bridge using the following commands:

```note
/interface bridge port remove [find interface=ether1]
/interface bridge port remove [find interface=ether2]
/interface bridge port remove [find interface=ether3]
/interface bridge port remove [find interface=ether4]
```

Then we added the ports to the bridges:

```note
/interface bridge port add bridge=bridge50 interface=ether1
/interface bridge port add bridge=bridge51 interface=ether2
/interface bridge port add bridge=bridge50 interface=ether3
/interface bridge port add bridge=bridge51 interface=ether4
```

Then we connected the cables from our tux's to the respective ports so that tux53 would be connected to bridge50, tux52 would be connected to bridge51 and tux54 would be connected to both bridges.

## Question 2

The routes in the tuxes are the following:

```note
routes tux54:
dest			gateway		interface
172.16.50.0 		0.0.0.0		eth0
172.16.51.0     	0.0.0.0		eth1

tux53:
dest			gateway		interface
172.16.50.0		0.0.0.0 	eth0
172.16.51.0		172.16.50.254	eth0

tux52:
dest			gateway		interface
172.16.51.0		0.0.0.0		eth0
172.16.50.0		172.16.51.253	eth0
```
It means that tux54 is connected to both bridges and is being used for tux52 to communicate with tux53 via the gateway 172.16.51.253.

## Question 3

A forwarding table entry contains information about how to forward packets to a specific destination. In this case it includes the destination address, gateway and the interface.

## Question 4

In the first Wireshark log we made, we can see that tux54 sent an ARP message asking who was 172.16.50.1 and tux53 who was in the same bridge responded with its MAC address. Then the opposite happened, this time tux53 sending the message and tux54 responding with its MAC address.

In the second Wireshark log, we can see that tux53 sent and ARP message asking who was 172.16.50.254 and tux54 who was in bridge50 responded with its MAC address. Then tux54 sent a message asking who was 172.16.51.1 and tux52 who was in bridge51 responded with its MAC address. After that tux54 sent another message asking who was 172.16.50.1 and tux53 in bridge50 answered with its MAC address. Finally tux52 asked who was 172.16.51.253 and tux54 in bridge51 answered with its MAC address.

## Question 5

In the first Wireshark log we can see that there was connectivity between all the tux's, in tux53 we pinged tux54 in bridge50(172.16.50.254), tux54 in bridge51(172.16.51.253) and tux52 in bridge51(172.16.51.1) and got a reply in all of them.

In the second Wireshark log we can see that there was connectivity between all the tux's because there were reply's in all requests.But this time we can see the specific ping's in each network interface since the log was made in tux54 which was connected to both bridges in eth0 and eth1 making it the link between the other 2 tux's(tux52 and tux53).

## Question 6

ICMP (Internet Control Message Protocol) is a network layer protocol that is used for sending error messages and operational information about network conditions. 

The IP address associated with an ICMP packet determines the destination of the packet. It identifies the specific host or network that the packet is intended for. When a device sends an ICMP packet, it includes the IP address of the destination in the IP header. The network layer then uses this IP address to route the packet through the network towards the destination.

The MAC address associated with an ICMP packet is used for layer 2 encapsulation. It is the physical address of the network interface card (NIC) on the sender and receiver of the packet. The MAC address is included in the Ethernet header, which is the lower layer of the packet. When a device sends an ICMP packet, it copies its own MAC address into the source MAC field of the Ethernet header. The destination device then uses the source MAC address to determine the MAC address on its own Ethernet interface to which it should send the reply.

The use of both IP and MAC addresses in ICMP packets is crucial for efficient communication on IP networks.

* IP Address: The IP address provides the logical addressing at the network layer, allowing the packet to be routed to the correct destination network or host.

* MAC Address: The MAC address provides the physical addressing at the data link layer, enabling the packet to be delivered to the specific NIC on the destination device.

Without both IP and MAC addresses, ICMP packets would be unable to efficiently traverse the network and reach their intended recipients.
