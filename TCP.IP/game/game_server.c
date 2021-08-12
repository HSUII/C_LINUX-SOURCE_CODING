//client-server client가 랜덤 동물중에 hint를 듣고 맞추는 게임  

#include <stdio.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define PORT 8000


 main(){

         int c_socket,s_socket;
         struct sockaddr_in s_addr,c_addr;
         int len;
         int n,i;
        int randnum;
                char animal[6][10] = {"cat","dog","rabbit","bird","dolphin","wolf"};
        char *temp;
        int length;
                char *answer;
                srand((unsigned)time(NULL));
                char Buffer[BUFSIZ];
                char rBuffer[BUFSIZ];
                char *hint;


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
                randnum = (rand()%5);
                answer = animal[randnum];
                len = sizeof(c_addr);
                c_socket = accept(s_socket, (struct sockaddr *) &c_addr, &len);

        while(1){
                                length =0;
                                temp = rBuffer;
                                while((n=read(c_socket,temp,1))>0){
                                                if(*temp == '\r') continue;
                                                if(*temp == '\n') break;
                                                if(*temp == '\0') break;
                                                if(length ==BUFSIZ)break;
                                                temp++;length++;
                                }

                                printf("정답은 %s 이다",answer);
                                if(randnum==0){
                                        hint = "힌트: 이 동물은 집사를 거느리고 있다.\n";
                                        strcpy(Buffer,hint);
                        n = strlen(Buffer);
                                        write(c_socket,Buffer,n);
                                }
                rBuffer[length] = '\0';
                write(c_socket, rBuffer,n);
                if(!strcmp(rBuffer,answer)){
                                        hint = "정답입니다!\n";
                                        strcpy(Buffer,hint);
                                        write(c_socket,Buffer,strlen(Buffer));
                                        break;
                                }
              }
                close(c_socket);
}
