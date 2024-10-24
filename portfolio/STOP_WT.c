#include <stdio.h>
#include <time.h>
#include <unistd.h>


int main() {
    time_t current_time;
    int hours, minutes, seconds;

    printf("TAEKWONDO Watch\n\n");

    while (1) {
        time(&current_time);

        hours = localtime(&current_time)->tm_hour;
        minutes = localtime(&current_time)->tm_min;
        seconds = localtime(&current_time)->tm_sec;

        printf("%02d:%02d:%02d\n", hours, minutes, seconds);

        // Add a delay to control the update rate (adjust as needed)
        usleep(100000); // 100 milliseconds
    }

    return 0;
}