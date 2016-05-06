//tftp client(udp)
//////////////////////////////////////////////////////////////////////
/*********************************************************************			
			author: Nitin Swami
			time: 3.30pm, 5/4/2016
*********************************************************************/
//////////////////////////////////////////////////////////////////////
#include"header.h"
#include"tftp_struct.h"

main()
{
//TFTP t1;
int sfd,len;
short int opcode;
struct sockaddr_in v;
///////////////////////////////////////////////
sfd=socket(AF_INET,SOCK_DGRAM,0);
if(sfd<0)
{
	perror("socket");
	return;
}
perror("socket");
////////////////////////////////////////////////
v.sin_family=AF_INET;
v.sin_port=htons(2000);
v.sin_addr.s_addr=inet_addr("127.0.0.1");
len=sizeof(v);
////////////////////////////////////////////////
l1:printf("enter opcode\n");
scanf("%hd",&opcode);
////////////////////////////////////////////////
if(opcode==1)
	read_req(sfd,v);
else if(opcode==2)
	write_req(sfd,v);
else
{
	printf("wrong opcode........try again\n");
	goto l1;
}
//close(sfd);
}
