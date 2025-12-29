#include <bits/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include <stdint.h>
#include <stdint.h>

#define NS_PER_MS 1000000ULL
#define NS_PER_SEC 1000000000ULL
#define NS_PER_MIN (60ULL* NS_PER_SEC)
#define NS_PER_HOUR (60ULL * NS_PER_MIN)
#define NS_PER_DAY (24ULL * NS_PER_HOUR)

#define LABEL_WIDTH 17

int main(int argc, char* argv[]) {
  struct timespec start, end;
  clock_gettime(CLOCK_MONOTONIC, &start);
  
  pid_t pid = fork();

  if(pid == 0) {
    execvp(argv[1], &argv[1]);
    perror("execv failed");
    exit(1); 
  } else if (pid > 0) {
    int status;
    waitpid(pid, &status, 0);
    clock_gettime(CLOCK_MONOTONIC, &end);
    
    uint64_t start_ns = (uint64_t)start.tv_sec * NS_PER_SEC + (uint64_t)start.tv_nsec;
    uint64_t end_ns = (uint64_t)end.tv_sec * NS_PER_SEC + (uint64_t)end.tv_nsec;
    uint64_t nanoseconds = end_ns - start_ns;
    uint64_t ticks = nanoseconds / 100ULL;
    uint64_t remainder;

    uint64_t days = nanoseconds / NS_PER_DAY;
    remainder = nanoseconds % NS_PER_DAY;

    uint64_t hours = remainder / NS_PER_HOUR;
    remainder %= NS_PER_HOUR;

    uint64_t minutes = remainder / NS_PER_MIN;
    remainder %= NS_PER_MIN;

    uint64_t seconds = remainder / NS_PER_SEC;
    remainder %= NS_PER_SEC;

    uint64_t milliseconds = remainder / NS_PER_MS;
    remainder %= NS_PER_MS;
    
    double total_days = (double)nanoseconds / NS_PER_DAY;
    double total_hours = (double)nanoseconds / NS_PER_HOUR;
    double total_minutes = (double)nanoseconds / NS_PER_MIN;
    double total_seconds = (double)nanoseconds / NS_PER_SEC;
    double total_ms = (double)nanoseconds / NS_PER_MS;

    printf("Days              : %lu\n", days);
    printf("Hours             : %lu\n", hours);
    printf("Minutes           : %lu\n", minutes);
    printf("Seconds           : %lu\n", seconds);
    printf("Milliseconds      : %lu\n", milliseconds);
    printf("Ticks             : %lu\n", ticks);
    printf("TotalDays         : %.15g\n", total_days);
    printf("TotalHours        : %.15g\n", total_hours);
    printf("TotalMinutes      : %.15g\n", total_minutes);
    printf("TotalSeconds      : %.15g\n", total_seconds);
    printf("TotalMilliseconds : %.15g\n", total_ms);
    
  } else {
    perror("fork failed");
    exit(1);
  }
  
  return 0;
}
