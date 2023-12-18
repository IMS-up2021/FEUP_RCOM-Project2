## Question 1

To configure the DNS service in a host we simply have to edit /etc/resolv.conf and add the IP address of the DNS server we want, in this case we added:

```note
nameserver 172.16.1.1
```

## Question 2

The Domain Name System (DNS) is a hierarchical decentralized naming system for computers, services, or other resources connected to the Internet or a private network. DNS primarily operates through a client-server architecture, and the main purpose is to translate human-readable domain names into IP addresses that computers use to identify each other on the network. The DNS protocol involves the exchange of several types of packets between DNS clients and servers.

There are two main types of queries:

* Iterative queries: In an iterative query, the DNS client sends the query packet to a DNS server. The DNS server checks its cache to see if it has the IP address for the domain name. If it does, it sends the IP address back to the client. If it doesn't have the IP address, it sends a referral to another DNS server that might have the information. The client then sends the query to the referral server, and the process repeats until the client finds the IP address for the domain name.

* Recursive queries: In a recursive query, the DNS client sends the query packet to a DNS server and asks the server to find the IP address for the domain name. The DNS server will then send the query to other DNS servers and follow the referral chains until it finds the IP address. Once it has the IP address, it sends it back to the client.

The information transported in DNS packets includes the domain names, IP addresses, time-to-live (TTL) values for caching, and other DNS-related data. DNS operates over UDP (User Datagram Protocol) for normal queries, but it can also use TCP (Transmission Control Protocol) for large responses or certain types of queries.

                            
