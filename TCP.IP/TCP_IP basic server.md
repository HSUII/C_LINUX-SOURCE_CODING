## 리눅스 기반의 c언어 TCP/IP 기초 소켓프로그래밍 

```C
  #include <stdio.h>
  #include <netinet/in.h>
  #include <sys/socket.h>
  #include <string.h>

  #define PORT 8080

   char buffer[BUFSIZ] = "hello world";
   char rBuffer[BUFSIZ];

   main(){
          int c_socket,s_socket;
          struct sockaddr_in s_addr,c_addr;
          int len;
          int n,i;

          char *temp;
          int length;

          s_socket = socket(PF_INET, SOCK_STREAM, 0); //TCP용 스트림 소켓생성 
          //서버 IP주소와 포트를 설정 
          memset(&s_addr,0,sizeof(s_addr)); 
          s_addr.sin_addr.s_addr = htonl(INADDR_ANY);
          s_addr.sin_family = AF_INET;
          s_addr.sin_port = htons(PORT);

          //소켓을 포트에 연결 
          if(bind(s_socket, (struct sockaddr *) &s_addr, sizeof(s_addr)) == -1) {
                  printf("can not bind\n");
                  return -1;

          }
          
          //커널에 개통을 요청 
          if(listen(s_socket,5) ==-1){
                  printf("liste Fail\n");
                  return -1;
          }
          //연결요청을 받아 처리하는 작업 반복 
          while(1){
                  len = sizeof(c_addr);
                  c_socket = accept(s_socket, (struct sockaddr *) &c_addr, &len);

                  n = strlen(buffer);
                  write(c_socket, buffer,n);
                  close(c_socket);

          }
          close(s_socket);
  }
```

출처: *정석용의 TCP/IP 소켓 프로그래밍*
