#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

struct LogOptions
{
  int interval;
  char filename[40];
};

void *timer_func(void *options)
{
  struct LogOptions *my_option = (struct LogOptions *)options;
  printf("Starting timer... file:%s - time:%d\n", my_option->filename, my_option->interval);
  while (1)
  {
    //open file
    int fdes = open(my_option->filename, O_CREAT | O_APPEND | O_WRONLY);

    //get time & format
    char buff[24];
    time_t now = time(0);
    struct tm *t = localtime(&now);
    strftime(buff, 24, "%Y-%m-%d %H:%M:%S", t);
    char text[50];
    sprintf(text, "%s\n", buff);
    printf("%s - %s", my_option->filename, text);

    //write & close file
    write(fdes, text, strlen(text));
    close(fdes);

    sleep(my_option->interval);
  }
  return NULL;
}

int main(int argc, char **argv)
{
  {
    if (argc == 5)
    {
      pthread_t thread_1;
      pthread_t thread_2;
      printf("Before Threads\n");
      //thread 1
      struct LogOptions l1;
      strcpy(l1.filename, argv[1]);
      l1.interval = atoi(argv[2]);

      //thread 2
      struct LogOptions l2;
      strcpy(l2.filename, argv[3]);
      l2.interval = atoi(argv[4]);

      pthread_create(&thread_1, NULL, timer_func, (void *)&l1);
      pthread_create(&thread_2, NULL, timer_func, (void *)&l2);

      pthread_join(thread_1, NULL);
      pthread_join(thread_2, NULL);
      printf("After Threads\n");
    }
    else
      printf("Not enough parameters provided...");

    return 0;
  }
}