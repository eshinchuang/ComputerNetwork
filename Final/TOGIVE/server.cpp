#include<bits/stdc++.h>
#include<unistd.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<fstream>
#include<sys/socket.h> 
#include<arpa/inet.h>
#include<netdb.h>
using namespace std;

int i = 0;
struct hostent *hent;
string ID[100], mail[100];

void handle_client(int stream){
	bool doing = true;
	char buf[100], buffer[1024];
	int n;
	int j;
	bool Find;
	char **pptr;
	string IP;
	while(doing) {
			
		
		bzero(buf, sizeof(buf) );
		read(stream, buf, sizeof(buf) );
		int req = atoi(buf);

		bzero(buf, sizeof(buf) );
		n = 0;	
		switch(req){
		case 1:
			read(stream, buf, sizeof(buf) );
			
			if( (hent = gethostbyname(buf)) == NULL){
				write(stream, "ERROR", sizeof(buf) );
				break;			
			}
			
			for(pptr=hent->h_addr_list;*pptr!=NULL;pptr++){
				IP = inet_ntop(hent->h_addrtype, *pptr, buffer, sizeof buffer);
			}
			
			strcpy(buf, IP.c_str() );
			
			write(stream, buf, sizeof(buf) );
			break;
		case 2:	
			read(stream, buf, sizeof(buf) );
			Find = false;
			for(j = 0; j < i && !Find; j++){
				if(buf == ID[j] ){
					Find = true;
					strcpy(buf,mail[j].c_str() );
				}
			}
			if(Find)		
				write(stream, buf , 100);
			else 
				write(stream, "No such student ID",100);
			break;
		case 3:
			doing = false;
			break;
		}
	}
	return;
}

int main (){
	
	fstream file;
	file.open("query.txt", ios::in);
	while( file >> ID[i] >> mail[i] ){
		i++;
	}
	
	struct sockaddr_in myaddr;
	struct sockaddr_in client_addr;	
	int sockfd, streamfd, port, status;
	socklen_t addr_size;;	
	char str_buf[100];		
	bzero(&myaddr, sizeof(myaddr));
			
	myaddr.sin_family = PF_INET;	
	myaddr.sin_port = htons(5000);	
	myaddr.sin_addr.s_addr = htonl(INADDR_ANY);	
	sockfd = socket (PF_INET, SOCK_STREAM, 0);	
	
	bind (sockfd, (struct sockaddr *) &myaddr, sizeof(struct sockaddr_in));

	listen(sockfd, 10);
	cout << "listening\n" ;	
	
	addr_size = sizeof (client_addr);
	

	while(1) {

	    streamfd = accept(sockfd, (struct sockaddr *) &client_addr, &addr_size);	
	    handle_client(streamfd); 
	
	    close(streamfd);	

	}

}





















