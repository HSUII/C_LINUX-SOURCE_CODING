#include <stdio.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>

#define PORT 8000

 char buffer[BUFSIZ] = "hello world";
 char rBuffer[BUFSIZ];

 main(){

         int c_socket,s_socket;
         struct sockaddr_in s_addr,c_addr;
         int len;
         int n,i;
        int randnum;

        char *temp;
        int length;

        s_socket = socket(PF_INET, SOCK_STREAM, 0);
        memset(&s_addr,0,sizeof(s_addr));
        s_addr.sin_addr.s_addr = htonl(INADDR_ANY);
        s_addr.sin_family = AF_INET;
        s_addr.sin_port = htons(PORT);

        if(bind(s_socket, (struct sockaddr *) &s_addr, sizeof(s_addr)) == -1) {
                printf("can not bind\n");
                return -1;

        }

        if(listen(s_socket,5) ==-1){
                printf("liste Fail\n");
                return -1;
        }
        while(1){
                len = sizeof(c_addr);
                c_socket = accept(s_socket, (struct sockaddr *) &c_addr, &len);

                length =0;
                temp = rBuffer;

                randnum = (rand()%8+1);

                while((n=read(c_socket,temp,1))>0){
                if(*temp == '\r') continue;
				
                if(*temp == '\n') break;
                if(*temp == '\0') break;

                if(length == BUFSIZ) break;
                temp++; length++;
                }
                rBuffer[length] = '\0';

                if(!strcmp(rBuffer,"print")){
                n = strlen(rBuffer);
                write(c_socket, rBuffer,n);
              }
                close(c_socket);

        }
        close(s_socket);
}

  write(c_socket,buffer,b);






                                                
