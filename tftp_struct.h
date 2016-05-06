//////////////////////////////////////////////////////////////////////
/*********************************************************************			
			author: Nitin Swami
			time: 3.30pm, 5/4/2016
*********************************************************************/
//////////////////////////////////////////////////////////////////////
typedef struct rrq
{
short int opcode;
char fname[255];
char zero;
//char mode[9];
int mode;
char zero1;
}RRQ;

typedef struct wrq
{
short int opcode;
char fname[255];
char zero;
//char mode[9];
int mode;
char zero1;
}WRQ;

typedef struct data
{
short int opcode;
short int block_no;
char data[512];
}DATA;

typedef struct ack
{
short int opcode;
short int block_no;
}ACK;

typedef struct error
{
short int opcode;
short int block_no;
char error_no;
char zero;
}ERROR;

typedef union tftp
{
RRQ r;
WRQ w;
DATA d;
ACK a;
ERROR e;
}TFTP;
