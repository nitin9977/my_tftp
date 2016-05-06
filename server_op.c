//////////////////////////////////////////////////////////////////////
/*********************************************************************			
			author: Nitin Swami
			time: 3.30pm, 5/4/2016
*********************************************************************/
//////////////////////////////////////////////////////////////////////
#include"header.h"
#include"tftp_struct.h"

extern TFTP t1;
void my_error(int sfd,int err_no,struct sockaddr_in v);
void ack(int sfd,struct sockaddr_in v);
void write_req(int sfd,struct sockaddr_in v);
//////////////////////////////////////////////////////////////////////
//RRQ
//////////////////////////////////////////////////////////////////////
void read_req(int sfd,struct sockaddr_in v)
{
int len,i,fd;
len=sizeof(v);
if((fd=open(t1.r.fname,O_RDONLY)) < 0)
{
//send error msg
	perror("open");
	my_error(sfd,errno,v);
	return;
}
printf("file opened successfully\n");
//send data msg
t1.d.opcode=3;
t1.d.block_no=0;
while(1)
{
t1.d.block_no++;
bzero(t1.d.data,512);
	if(read(fd,t1.d.data,512) == 0)
		break;
sendto(sfd,&t1,sizeof(t1),0,(struct sockaddr *)&v,len);
}
printf("file transfered\n");
close(fd);
}
////////////////////////////////////////////////////////////////////////
//ERROR
////////////////////////////////////////////////////////////////////////
void my_error(int sfd,int err_no,struct sockaddr_in v)
{
int len;
len=sizeof(v);

t1.e.opcode=5;
t1.e.block_no=0;
t1.e.error_no=err_no;
t1.e.zero='\0';
sendto(sfd,&t1,sizeof(t1),0,(struct sockaddr *)&v,len);
}
////////////////////////////////////////////////////////////////////////
//WRQ
////////////////////////////////////////////////////////////////////////
void write_req(int sfd,struct sockaddr_in v)
{
int i,len,fd;
TFTP t2;	//for data
len=sizeof(v);
//create the file
if((fd=open(t1.w.fname,O_WRONLY|O_CREAT|O_TRUNC,0664)) < 0)
{
//send ERROR msg
        my_error(sfd,errno,v);
        return;
}
//send ACK packet
printf("sending ack\n");
ack(sfd,v);
printf("ack sent\n");
//making socket file descriptor non blocking
fcntl(sfd,F_SETFL,O_NONBLOCK);
perror("fcntl");
//
bzero(t2.d.data,sizeof(t2.d.data));
//perror("bzero");
//receiving data
printf("receiving data\n");
recvfrom(sfd,&t2,sizeof(t2),0,(struct sockaddr *)&v,&len);
perror("recv");
while(1)
{
	if(t1.r.mode==1)
		write(fd,t2.d.data,strlen(t2.d.data));
	else if(t1.r.mode==2)
		write(fd,t2.d.data,512);
	
	if(recvfrom(sfd,&t2,sizeof(t2),0,(struct sockaddr *)&v,&len) <= 0)
		break;
}
printf("data received\n");
close(fd);
}
////////////////////////////////////////////////////////////////////////
//ACK
////////////////////////////////////////////////////////////////////////
void ack(int sfd,struct sockaddr_in v)
{
int len;
len=sizeof(v);
t1.a.opcode=4;
t1.a.block_no=0;
sendto(sfd,&t1,sizeof(t1),0,(struct sockaddr *)&v,len);
}

