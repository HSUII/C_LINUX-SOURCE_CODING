//2초마다 시간출력하는 함수 

#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


int main()
{
    int i;
    struct tm *tm_ptr;
    time_t the_time;

    (void) time(&the_time);
    tm_ptr = gmtime(&the_time);

    for(i=1;i<=10;i++){
        the_time = time((time_t *)0);
        printf("The time is %d\n", the_time);
        sleep(2);

    }
    exit(0);

}
