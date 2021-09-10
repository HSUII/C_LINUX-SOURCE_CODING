
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <arpa/inet.h>

#define BUF_LEN 128
#define h_addr h_addr_list[0]
#define PORT 80

int main(int argc,char *argv[]){

        int s,n,len_in,len_out,wn;
        struct sockaddr_in server_addr;
        char *haddr;
        char buf[BUF_LEN+1];
        int port=80;
        struct hostent *he;

        he = gethostbyname(argv[1]);
        if(!he){
                printf("gethostname failed\n");
                return -1;
        }
        if((s=socket(PF_INET,SOCK_STREAM,0))<0){
                printf("can not create socket\n");
                return -1;
        }
        memset(&server_addr, 0, sizeof(server_addr));
        server_addr.sin_family=AF_INET;
        server_addr.sin_addr =*((struct in_addr *)he->h_addr);
        //server_addr.sin_addr.s_addr = inet_addr(inet_ntoa(*(struct in_addr *)*he->h_addr_list));
        /*
        memcpy(haddr,he->h_addr,he->h_length);
        server_addr.sin_addr.s_addr=inet_addr(haddr)
        */
        server_addr.sin_port=htons(port);

        if(connect(s,(struct sockaddr *) &server_addr,sizeof(server_addr)) ==-1 ) {
                printf("fail\n");
                close(s);
                return -1;
        }

        sprintf(buf, "GET / HTTP/1.1 Host:server.example.com  Connection: Upgrade, HTTP2-Settings Upgrade: h2c HTTP2-Settings: <base64url encoding of HTTP/2 SETTINGS payload>");
        printf("%s\n",buf);
        if((wn= write(s,buf,strlen(buf)))<0) return -1;


        memset(buf,0,sizeof(buf));
        while((n=read(s,buf,BUF_LEN))>0){
                printf("%s",buf);
                memset(buf,0,sizeof(buf));

        }
        close(s);
}
