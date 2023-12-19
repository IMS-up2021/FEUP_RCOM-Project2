## Question 1

None, we didn't use an FTP connection, we tested with ubuntu download instead.

## Question 3

A TCP (Transmission Control Protocol) connection undergoes several phases during its establishment, data transfer, and termination. The key phases of a TCP connection are:

1. Connection Establishment (Three-Way Handshake):

* SYN (Synchronize): The client initiates a connection by sending a TCP segment with the SYN flag set to the server.
* SYN-ACK (Synchronize-Acknowledge): The server responds with a TCP segment containing SYN and ACK flags to acknowledge the client's request and signal its own readiness to establish a connection.
* ACK (Acknowledge): The client acknowledges the server's response by sending a TCP segment with the ACK flag set. At this point, the connection is established.

This process is often referred to as the "Three-Way Handshake" and ensures synchronization and agreement between the client and server regarding the initial sequence numbers for data exchange.

2. Data Transfer:

Once the connection is established, the two endpoints can begin exchanging data. TCP handles error detection and correction, ensuring reliable data transfer. It breaks the data into segments, adds a TCP header with various control information, and sends them through the underlying IP network. The receiving endpoint reassembles the segments into the original data.

TCP maintains a congestion window (CWND), which limits the amount of data it sends at a time to prevent congestion in the network. It also employs other techniques like selective acknowledgments (SACK) to improve efficiency and reduce retransmissions.

3. Connection Termination (Four-Way Handshake):

* FIN (Finish): Either the client or server, or both, may decide to terminate the connection. The party initiating the termination sends a TCP segment with the FIN flag set.
* ACK (Acknowledge): The other party acknowledges the FIN by sending a TCP segment with the ACK flag set.
* FIN (Finish): If the other party also wants to terminate the connection, it sends a TCP segment with the FIN flag set.
* ACK (Acknowledge): The initiating party acknowledges the final FIN, and the connection is fully terminated.

This process is often referred to as the "Four-Way Handshake" and ensures a graceful termination of the connection, allowing both sides to confirm the closure of the communication.

## Question 4


Automatic Repeat Request (ARQ) is an error-control mechanism used in TCP (Transmission Control Protocol) to ensure reliable data transfer over an unreliable network. It works by using acknowledgments (ACKs) and timeouts to detect and retransmit lost or corrupted data.

ARQ Mechanism

* Segment Transmission: TCP segments, containing data and control information, are sent from the sender to the receiver. Each segment has a unique sequence number that indicates its position in the data stream.

* ACK Reception: The receiver acknowledges the receipt of each successfully received segment by sending an ACK segment. The ACK segment includes the sequence number of the next expected byte, indicating the sender which segments it has received and which ones it still needs to send.

* Timeout Detection: If the sender does not receive an ACK for a segment within a specified timeout period, it assumes that the segment has been lost or corrupted.

* Segment Retransmission: Upon timeout detection, the sender retransmits the lost or corrupted segment. The retransmission process continues until the receiver acknowledges the correct receipt of the segment.

Relevant TCP Fields

The following TCP fields play a crucial role in the ARQ mechanism:

* Sequence Number: Each TCP segment has a sequence number that is incremented for each byte of data sent. This number is used for reordering the segments at the receiver and detecting lost or out-of-order segments.

* Acknowledgment Number (ACK): The ACK field in the TCP header indicates the next byte of data that the sender expects to receive. This helps the receiver keep track of the progress of data transfer and detects missing segments.

* Window Size (WND): The WND field in the TCP header specifies the maximum number of bytes that the receiver can accept at one time. This helps control the flow of data between the sender and receiver and prevents congestion in the network.

Relevant Information in Logs

Examining TCP logs can provide valuable insights into the ARQ mechanism in action:

* SYN-ACKs: The presence of SYN-ACK segments indicates the successful establishment of a TCP connection.

* ACK Number Progression: The steady increase of the ACK number in the logs signifies that data is being transferred reliably.

* Duplicate ACKs: Repeated ACKs with the same ACK number indicate that a segment is being retransmitted due to a timeout or retransmission request.

* Dropped Packets: A sudden drop in ACK numbers or gaps in the sequence number sequence may indicate packet loss due to network congestion or other issues.

By analyzing these log entries, network administrators can monitor the performance of TCP connections, identify potential problems, and take corrective actions to maintain reliable data transfer over the network.

## Question 5


TCP (Transmission Control Protocol) employs a congestion control mechanism to manage the flow of data over a network, ensuring efficient and reliable communication. It dynamically adjusts the sending rate to prevent congestion and maintain network stability. The mechanism relies on two key factors:

* Congestion Window (CWND): The CWND represents the maximum number of bytes that the sender can send without receiving an acknowledgment (ACK) from the receiver. It serves as a measure of available network bandwidth.

* Additive Increase Multiplicative Decrease (AIMD) Algorithm: AIMD is a congestion avoidance algorithm that governs the growth and reduction of the CWND. It increases the CWND by a constant amount for successful transmissions and halves it upon detecting congestion.

Evolution of Throughput:

The throughput of a TCP data connection typically follows an S-shaped curve, reflecting the interplay of the CWND and AIMD algorithm. The initial phase is characterized by a rapid increase in throughput as the CWND grows exponentially. This is known as the slow start phase.

As the CWND approaches the network's available bandwidth, the AIMD algorithm kicks in, causing the CWND to increase more gradually. This is called the congestion avoidance phase. During this phase, throughput fluctuates as the sender gains and loses information about the network's congestion level.

If the network becomes congested, causing packet loss, the sender reduces the CWND significantly, entering the congestion avoidance phase. This temporary slowdown allows the network to recover from congestion, and the throughput gradually increases again.

The overall throughput pattern reflects the TCP congestion control mechanism's ability to adapt to varying network conditions, ensuring reliable data transfer without overwhelming the network.
## Question 6


