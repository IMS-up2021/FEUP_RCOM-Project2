## Question 1

First we restarted the networking service with 

```note 
systemctl restart networking
```

Then we configured the tux, by first activating the interface eth0 with:

```note
ifconfig eth0 up
```

We listed the current network configurations with:

```note
ifconfig
```

Next we configured eth0 with IP Address 172.16.1.53/24 with a mask of 24 bits and did the same for the IP Address 172.16.1.54/24:

```note
ifconfig eth0 172.16.1.53/24
```

Finally we configured the Mikrotik router, we reset the configuration with GTKterm first with:

```note
/system reset-configuration
```

And then we added a static route to the IP Address 172.16.1.54/24 with the gateway:

```note
/ip route add dst-address=172.16.1.0/24 gateway=X
```

## Question 2

ARP packets are used to discover the MAC address associated with a given IP address on the same local network.

## Question 3

In ARP packets, we have the following components:

Sender's MAC Address (SMAC): This is the MAC address of the device that is sending the ARP packet. It helps identify the sender of the packet.

Sender's IP Address (SIP): This field contains the IP address of the sender device. It is used by the recipient to associate the sender's MAC address with its corresponding IP address.

Target MAC Address (TMAC): In an ARP Request packet, this field is typically set to all zeroes because the sender is requesting the MAC address associated with a specific IP address and does not yet know it. In an ARP Reply packet, it contains the MAC address associated with the target IP address.

Target IP Address (TIP): This is the IP address for which the sender is seeking the MAC address in an ARP Request or the IP address whose MAC address is being provided in an ARP Reply.

These components allow devices on a local network to dynamically discover and update the mapping between IP and MAC addresses, enabling efficient communication within the network.

## Question 4

The ping command generates ICMP (Internet Control Message Protocol) packets to test the reachability of a network host and to measure the round-trip time for messages sent from the originating host to a destination computer.

## Question 5

The ICMP packet is encapsulated within the IP packet.

Source IP Address (SIP): The IP address of the host sending the ping request.
Destination IP Address (DIP): The IP address of the destination host.

## Question 6

To determine the type of protocol encapsulated in an Ethernet frame, we need to examine the EtherType field in the Ethernet frame header. The EtherType field is a 16-bit field that indicates the type of the payload carried in the Ethernet frame. 


## Question 7

To determine the length of a receiving Ethernet frame, we can look at the Frame Length field in the Ethernet frame header. The Frame Length field indicates the total length of the Ethernet frame, including both the frame header and the frame payload.

## Question 8

The loopback interface, often identified by the IP address 127.0.0.1 and the associated subnet mask 255.0.0.0, is a special network interface on a computer. It is commonly referred to as "localhost".

The loopback interface is a fundamental component in networking for local testing, debugging, and ensuring consistent behavior in networked applications. It provides a controlled environment for communication within the same device and is an essential tool for developers, network administrators, and system operators.

