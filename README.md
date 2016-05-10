# my_tftp
simple tftp implementation in C lang using UDP
-----------------------------------------------------------------------------------------------------------

how to install------
# make -f makefile_client           	  //to create client executable
# make -f makefile_server         		  //to create server executable
-----------------------------------------------------------------------------------------------------------

# RRQ
  The read request (RRQ) message is used by the client to establish a connection for reading data from the server. The RRQ message fields are as follows:
    ❑ OpCode. The first field is a 2-byte operation code. The value is 1 for the RRQ message.
    ❑ File name. The next field is a variable-size string (encoded in ASCII) that defines the name of the file. Since the file name varies in length, termination is signaled by a 1-byte field of 0s.
    ❑ Mode. The next field is another variable-size string defining the transfer mode. The mode field is terminated by another 1-byte field of 0s. The mode can be one of two strings: “netascii” (for an ASCII file) or “octet” (for a binary file). The file name
    and mode fields can be in upper- or lowercase, or a combination of both.
-----------------------------------------------------------------------------------------------------------

# WRQ
  The write request (WRQ) message is used by the client to establish a connection for writing data to the server.
-----------------------------------------------------------------------------------------------------------

# DATA
  The data (DATA) message is used by the client or the server to send blocks of data. The DATA message fields are as follows:
    ❑ OpCode. The first field is a 2-byte operation code. The value is 3 for the DATA message.
    ❑ Block number. This is a 2-byte field containing the block number. The sender of the data (client or server) uses this field for sequencing. All blocks are numbered sequentially starting with 1. The block number is necessary for acknowledgment as we will see shortly.
    ❑ Data. This block must be exactly 512 bytes in all DATA messages except the last block, which must be between 0 and 511 bytes. A non-512 byte block is used as a signal that the sender has sent all the data. In other words, it is used as an end-of-file indicator. If the data in the file happens to be an exact multiple of 512 bytes, the sender must send one extra block of zero bytes to show the end of transmission. Data can be transferred in either NVT ASCII (netascii) or binary octet (octet).
-----------------------------------------------------------------------------------------------------------

# ACK
  The acknowledge (ACK) message is used by the client or server to acknowledge the receipt of a data block. The message is only 4 bytes long. The ACK message fields are as follows:
    ❑ OpCode. The first field is a 2-byte operation code. The value is 4 for the ACK message.
    ❑ Block number. The next field is a 2-byte field containing the number of the block received.
  The ACK message can also be a response to a WRQ. It is sent by the server to indicate that it is ready to receive data from the client. In this case the value of the block number field is 0. An example of an ACK message is given in a later section.
-----------------------------------------------------------------------------------------------------------

# ERROR
  The ERROR message is used by the client or the server when a connection cannot be established or when there is a problem during data transmission. It can be sent as a negative response to RRQ or WRQ. It can also be used if the next block cannot be transferred during the actual data transfer phase. The error message is not used to declare a damaged or duplicated message. The ERROR message fields are as follows:
   ❑ OpCode. The first field is a 2-byte operation code. The value is 5 for the ERROR message.
   ❑ Error number. This 2-byte field defines the type of error. 
   ❑ Error data. This variable-byte field contains the textual error data and is terminated by a 1-byte field of 0s.
-----------------------------------------------------------------------------------------------------------
