#include <bits/stdc++.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
using namespace std;
#define portno 5000

int main(){
	
	struct sockaddr_in serv_addr,cli_addr;
	int sfd = socket(AF_INET,SOCK_DGRAM,0);
	if(sfd<0)
	{
		cout<<"socket error"<<endl;
		exit(0);
	}	
	// to initialie the server address
	bzero((char *) &serv_addr,sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(portno);
	serv_addr.sin_addr.s_addr=INADDR_ANY;
	

	char rbuf[256],temp[256];
	
	while(1)
	{
		socklen_t cllength;
/*		int nsfd=accept(sfd,(struct sockaddr *)&cli_addr,(socklen_t *)&cllength);
		if(nsfd<0)
		{
			cout<<"Accept error"<<endl;
			exit(0);
		}
*/
		bzero(rbuf,256);
		bzero(temp,256);
		if(recvfrom(sfd,rbuf,255,0,(struct sockaddr*)&cli_addr,&cllength)<0)
		{
			cout<<"Read error"<<endl;
			exit(0);
		}
		int i=0;
		for(i=0;i<strlen(rbuf);i++)
		{
			if(rbuf[i]>=97)
				temp[i] = rbuf[i]-32;
			else
				temp[i]=rbuf[i];
//			cout<<temp[i]<<endl;
		}
		if(sendto(sfd,temp,255,0,(struct sockaddr*)&serv_addr,sizeof(serv_addr))<0)
		{
			cout<<"Send error"<<endl;
			exit(0);
		}
	}

}