//구조체에 시간을 담아 원하는 시간, 분, 초 날짜로 출력하는 프로그램

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
    struct tm *tm_ptr;
    time_t the_time;

    (void) time(&the_time);
    tm_ptr = gmtime(&the_time);

    printf("RAW TIME IS %1d\n", the_time);
    printf("gmtime gives \n");
    printf("date: %02d/%02d/%02d\n",tm_ptr->tm_year,tm_ptr->tm_mon+1, tm_ptr->tm_mday) ;

    printf("time: %02d:%02d:%02d\n",tm_ptr->tm_hour,tm_ptr->tm_min, tm_ptr->tm_sec) ;

    exit(0);

}
