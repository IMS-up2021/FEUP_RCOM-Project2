## Question 1

To configure bridge50 we first had to create the bridge using:

```note
/interface bridge add name=bridge50
```

After that we removed a port of our choice from the default bridge(in this case we used ether1):

```note
/interface bridge port remove [find interface=ether1]
```

And we added the port ether1 to our bridge50 using the following command:

```note
/interface bridge port add bridge=bridge50 interface=ether1
```

## Question 2

There are 2 broadcast domains, 172.16.50.255 and 172.16.51.255. From the logs we can see that when we pinged broadcast `172.16.50.255` using:

```note
ping -b 172.16.50.255
```

We got a request on both computers that were connected to bridge50 (tux53 and tux54), therefore proving that it is a valid broadcast domain.

On the other hand, when we pinged `172.16.51.255` using:

```note
ping -b 172.16.51.255
```

We only got a request on the computer that was connected to bridge51 (tux52), also proving that it is a valid broadcast domain.

So from the logs we can conclude that there are 2 valid broadcast domains, one for each bridge setup.
