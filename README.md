# RdtOverUDP

## Introduction

In this assignment, we aimed to implement our own socket layer and reliable transport layer. So we implemented a reliable transfer service on the top of UDP/IP protocol. In other words, you need to implement a service that guarantees the arrival of datagrams in the correct order on top of the UDP/IP protocol, along with congestion control.

## Reliability layer

### Specifications

Suppose you’ve a file and you want to send this file from one side to the other(server to client), you will need to split the file into chunks of data of fixed length and add the data of one chunk to a UDP datagram packet in the data field of the packet.

### Reliable data transfer (RDT) methods

We have implemented 3 different methods, and will explain them below

#### Stop-and-wait
The server sends a single datagram, and blocks until an acknowledgment from the client is received (or until a timeout expires).

#### Selective-repeat
At any given time, the server is allowed to have up to N datagrams that have not yet been acknowledged by the client. The server has to be able to buffer up to N datagrams, since it should be able to retransmit them until they get acknowledged by the client. Moreover, the server has to associate a timer with each datagram transmitted, so that it can retransmit a datagram if it is not acknowledged in time.

#### Go-Back-End (GBN)
The server sends up to N datagrams that have not yet acknowledged by the client. the server also has to be able to buffer up to N datagrams, since it should be able to retransmit them until they get acknowledged by the client. The server should accept cumulative acknowledgment, which mean that the client would send acknowledgment with last expected acknowledgment number, so if the expected packet lost, and the client received other packets, then the client would send acknowledgment for the last correctly received packet, from that the server knows that packet loss happened, and starts sending that packet again.

## Packet Specifications

There is 2 types of packets sent through the network. Data packets, and acknowledgment packets. Both packets have the same header, but the data packet got extra field for the data we want to transfer.

## Congestion Control

### Introduction

congestion is informally: "too many sources sending too much data too fast for network to handle", there are two main indicators for congestion: lost packets (buffer overflow at routers) long delays (queuing in router buffers). No handling network congestion may lead to unneeded retransmissions(link carries multiple copies of a packet, since when packet dropped, any upstream
transmission capacity used for that packet was wasted)!  

### Additive increase Multiplicative decrease

the sender increases transmission rate (window size), probing for usable
bandwidth, until loss occurs. So we implemented dynamic window, that its size increased by 2 in case of receiving correct acknowledgment, decreasing the window size to 1 in case of time-out of the packet, and decreasing it to its half size in case of 3-duplicate acknowledgments.

## Packet Loss Simulation

- Since we don’t have machines with OS that we can modify, our implementation will run in a simulated environment, this means that we will simulate the packet loss with packet loss probability (PLP) since packet loss is infrequent in a local-host or LAN environment.

- We used seed to generate random indices of the lost packets, to simulate the loss.

- We start the timer of the packet will be sent, then determine if it would be sent or not, if it will not be sent the timer of this packet will raise time-out to simulate time-out, then we will really send this packet again.

## Checksum Error Detection.

We provided error detection using checksum to detect transmission errors. We choose to make the checksum of 16 bits as in Internet checksum to make undetected errors very rare, but we can not guarantee completely error-free delivery because of the checksum limitations.


**Made with love :heart:**
