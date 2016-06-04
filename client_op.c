
//////////////////////////////////////////////////////////////////////
/*********************************************************************			
			author: Nitin Swami
			time: 3.30pm, 5/4/2016
*********************************************************************/
//////////////////////////////////////////////////////////////////////
#include"header.h"
#include"tftp_struct.h"
TFTP t1,t2;
//////////////////////////////////////////////////////////////////////
//RRQ-adding ack after every packet
/////////////////////////////////////////////////////////////////////
void read_req(int sfd,struct sockaddr_in v)
{
int i,len,fd;
len=sizeof(v);
//sending RRQ packet
t1.r.opcode=1;
printf("enter filename\n");
scanf("%s",t1.r.fname);
printf("type of file\n1)netascii\n2)octel\n");
scanf("%d",&t1.r.mode);
sendto(sfd,&t1,sizeof(t1),0,(struct sockaddr *)&v,len);
//receiving 1st packet from server
recvfrom(sfd,&t2,sizeof(t2),0,(struct sockaddr *)&v,&len);
//checking whether its a data or error
if(t2.d.opcode==3)
{
//opening the file to copy the data
if((fd=open(t1.r.fname,O_WRONLY|O_TRUNC|O_CREAT,0664)) < 0)
{
	perror("open");
	return;
}
printf("receiving data...\n");
//making socket file descriptor non blocking
fcntl(sfd,F_SETFL,O_NONBLOCK);
while(1)
{
	//ascii
	if(t1.r.mode==1)
       		write(fd,t2.d.data,strlen(t2.d.data));
//this logic works but add extra 0's in file
	//octel
	else if(t1.r.mode==2)
		write(fd,t2.d.data,512);

	if(recvfrom(sfd,&t2,sizeof(t2),0,(struct sockaddr *)&v,&len) <= 0)
		break;
}
}
else if(t2.e.opcode==5)
	printf("%s\n",strerror(t2.e.error_no));

printf("data received\n");
close(fd);
}

//////////////////////////////////////////////////////////////////////
//WRQ
//////////////////////////////////////////////////////////////////////
void write_req(int sfd,struct sockaddr_in v)
{
int len,i,fd;
len=sizeof(v);
//sending WRQ packet
t1.w.opcode=2;
printf("enter filename\n");
scanf("%s",t1.w.fname);
printf("type of file\n1)netascii\n2)octel\n");
scanf("%d",&t1.r.mode);
if((fd=open(t1.w.fname,O_RDONLY)) < 0)
{
	perror("open");
	return;
}
printf("sending WRQ\n");
sendto(sfd,&t1,sizeof(t1),0,(struct sockaddr *)&v,len);
//waiting for ACK or ERROR packet
printf("waiting for ACK/ERROR\n");
recvfrom(sfd,&t1,sizeof(t1),0,(struct sockaddr *)&v,&len);
//ACK or ERROR received
if(t1.a.opcode==4)
{
	printf("sending data\n");
	//send data msg
	t1.d.opcode=3;
	t1.d.block_no=0;
	while(1)
	{
		t1.d.block_no++;
		bzero(t1.d.data,sizeof(t1.d.data));
       		if(read(fd,t1.d.data,512) == 0)
               		break;
		sendto(sfd,&t1,sizeof(t1),0,(struct sockaddr *)&v,len);
	}
	printf("file transfered\n");
}
else if(t1.e.opcode==5)
	printf("%s\n",strerror(t2.e.error_no));

close(fd);
}
//////////////////////////////////////////////////////////////////////

