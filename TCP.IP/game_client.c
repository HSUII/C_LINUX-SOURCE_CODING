//client-server client가 랜덤 동물중에 hint를 듣고 맞추는 게임  

#include <stdio.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>

#define PORT 8000
#define IPADDR "127.0.0.1"

char buffer[BUFSIZ];

main()
{
        int c_socket;
        struct sockaddr_in c_addr;
        int len;
        int n;

        char rcvBuffer[BUFSIZ];

        c_socket = socket(PF_INET, SOCK_STREAM, 0);

        memset(&c_addr,0,sizeof(c_addr));
        c_addr.sin_addr.s_addr = inet_addr(IPADDR);
        c_addr.sin_family = AF_INET;
        c_addr.sin_port = htons(PORT);

        if(connect(c_socket,( struct sockaddr *) &c_addr, sizeof(c_addr)) == -1){
                printf("can not connect\n");
                close(c_socket);
                return -1;
        }
        printf("설명하는 동물을 맞춰보세요! \n");
        printf("시작하려면 '시작'을 입력해주세요 \n");
        while(1){
        if((n=read(0,buffer,BUFSIZ))>0){
        scanf("%s",buffer);
        if(!strcmp(buffer,"end\n"))break;

        buffer[strlen(buffer)] = '\0';
        write(c_socket,buffer,strlen(buffer)+1);

        if((n = read(c_socket, rcvBuffer,sizeof(rcvBuffer)))<0){
                return(-1);
        }

        rcvBuffer[n] = '\0';
        printf("received Data : %s\n",rcvBuffer);

        }       }
        close(c_socket);


}

