//////////////////////////////////////////////////////////////////////
/*********************************************************************			
			author: Nitin Swami
			time: 3.30pm, 5/4/2016
*********************************************************************/
//////////////////////////////////////////////////////////////////////
#include"header.h"
#include"tftp_struct.h"
//tftp server(udp)

int sfd,len;
TFTP t1;

void read_req(int,struct sockaddr_in);
void write_req(int,struct sockaddr_in);

main()
{
struct sockaddr_in v;
short int opcode=0;
/////////////////////////////////////////////////////
while(1)
{
printf("\nserver: waiting for connections...\n");
sfd=socket(AF_INET,SOCK_DGRAM,0);
if(sfd<0)
{
	perror("socket");
	return;
}
perror("socket");
/////////////////////////////////////////////////////
v.sin_family=AF_INET;
v.sin_port=htons(2000);
v.sin_addr.s_addr=inet_addr("0.0.0.0");
len=sizeof(v);
/////////////////////////////////////////////////////
if(bind(sfd,(struct sockaddr *)&v,len) < 0)
{
	perror("bind");
	return;
}
perror("bind");
/////////////////////////////////////////////////////
//while(1)
//{
if(fork() == 0)
{
	recvfrom(sfd,&t1,sizeof(t1),0,(struct sockaddr *)&v,&len);
	printf("client %s connected\n",inet_ntoa(v.sin_addr));
	if(t1.r.opcode==1)
		read_req(sfd,v);
	else if(t1.w.opcode==2)
		write_req(sfd,v);
	exit(0);
}
else
{
	close(sfd);
	wait(0);
}
}
}
