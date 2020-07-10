#include <stdio.h> 
#include <string.h> 
#include <unistd.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <arpa/inet.h> 
#define PORT 8011

int main(void)
{ 
    int sock;
    struct sockaddr_in addr, client_addr; 
    char recv_buffer[1024]; 
    int recv_len; 
    int addr_len; 
   	char *exit = "bye";

    if((sock = socket(AF_INET, SOCK_DGRAM, 0)) <0)
    { 
        perror("socket "); return 1;
    }
    
    memset(&addr, 0x00, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(PORT);
    if(bind(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("bind ");
        return 1;
    } 
    
    printf("waiting for messages, if you want program close, send to bye\n");
	
	while(1){
		addr_len = sizeof(client_addr);
		if ((recv_len = recvfrom(sock, recv_buffer, 1024, 0, 
			(struct sockaddr *)&client_addr, &addr_len)) < 0)
		{ 
			perror("recvfrom "); 
			return 1;
		} 
    
	    recv_buffer[recv_len] = '\0';
    
    	printf("ip : %s\n", inet_ntoa(client_addr.sin_addr)); 
	
		int ret = strcmp(recv_buffer, exit);
		int end = 0;

		if(ret==0){			
			printf("Goodbye User! \n");
			end = 1;
			if (end==1) {
				break;			
			}			
		}
		else {
			printf("received data >>>>>>>   %s \n", recv_buffer); 
			sendto(sock, recv_buffer, strlen(recv_buffer), 0, 
			(struct sockaddr *)&client_addr, sizeof(client_addr));
		}
	}	
	close(sock);
    //return 0; 
}
