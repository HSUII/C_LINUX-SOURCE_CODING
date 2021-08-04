#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
    struct tm *tm_ptr;
    time_t timeval;

    (void)time(&timeval);
    printf("THE date is : %s", ctime(&timeval));
    tm_ptr = localtime(&timeval);

    printf("date: %02d/%02d/%02d\n",tm_ptr->tm_year,tm_ptr->tm_mon+1,tm_ptr->tm_mday) ;
    printf("time: %02d:%02d:%02d\n",tm_ptr->tm_hour,tm_ptr->tm_min, tm_ptr->tm_sec) ;

    exit(0);

}
