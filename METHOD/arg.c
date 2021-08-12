//매개변수를 입력받아 출력해주는 프로그램 , -으로 입력히면 option으로 없으면 argument로 

#include <stdio.h>

int main(int argc, char *argv[]){
        int arg;

        for(arg =0;arg<argc;arg++){
                if(argv[arg][0]=='-')
                        printf("option: %s\n",argv[arg]+1);
                else
                        printf("argument %d: %s\n",arg,argv[arg]);
        }
        return 0;
}
