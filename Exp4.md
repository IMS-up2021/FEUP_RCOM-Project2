## Question 1

To configure a static route in a router we use the following command:

```note
/ip route add dst-address=172.16.10.0/24 gateway=172.16.11.253 
```

In this case we configured the following routes:

```note
/ip route add dst-address=172.16.41.0/24 gateway=172.16.41.254 
/ip route add dst-address=172.16.1.49/24 gateway=172.16.1.254
```

## Question 2

The paths followed by the packets were the following:

If the packet was going from tux53 to tux52 then it would go through tux54 first using the ip(172.16.40.254), then tux54(172.16.41.253 would ping tux52(172.16.41.1) and the opposite route for the reply, tux52(172.16.41.1) to tux54(172.16.41.253) and from tux54(172.16.40.254) to tux5(172.16.40.1). 

When we deleted the route 172.16.41.253 in tux52, with NAT enabled, then the packet went through the Router(172.16.41.254) first, then to tux54(172.16.41.253) and then from tux54(172.16.40.254) to tux53(172.16.40.1). With NAT disabled then the packet would go through 172.16.41.253 directly without going to the router because the protocol realized there was an "easier" and "faster" route to tux53 and created the route we deleted before by itself and sent the packet through that route.

## Question 3

To disable default NAT, we used the following command:

```note
/ip firewall nat disable 0
```

If we wanted to add NAT rules we could use the following command:

```note
/ip firewall nat add chain=srcnat action=masquerade out-interface=ether1
```

## Question 4

Network Address Translation (NAT) is a method used to connect multiple devices on a private network to the internet using a single public IP address. This is necessary because there are not enough public IP addresses to assign one to every device on the internet.

NAT works by mapping private IP addresses to public IP addresses. This mapping is done dynamically, meaning that the NAT device keeps track of which private IP addresses are currently being used and translates them to the appropriate public IP address when outgoing traffic is sent.
