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
  int thread;
  int interval;
  char filename[40];
};

pthread_mutex_t lock;

void *timer_func(void *options)
{
  struct LogOptions *my_option = (struct LogOptions *)options;
  printf("Starting timer... file:%s - time:%d\n", my_option->filename, my_option->interval);
  while (1)
  {
    pthread_mutex_lock(&lock);
    //open file
    FILE *fp = fopen(my_option->filename, "aw");

    if (fp == NULL)
    {
      perror("Error: File open failure.");
    }
    else
    {
      //get time & format
      char buff[24];
      time_t now = time(0);
      struct tm *t = localtime(&now);
      strftime(buff, 24, "%Y-%m-%d %H:%M:%S", t);
      char text[50];
      sprintf(text, "thread %d - %s\n", my_option->thread, buff);
      printf("%s - %s", my_option->filename, text);

      //write & close file
      fwrite(text, strlen(text), 1, fp);
      fclose(fp);
      pthread_mutex_unlock(&lock);
      sleep(my_option->interval);
    }
  }
  free(my_option);
  return NULL;
}

int main(int argc, char **argv)
{
  {
    if (argc > 3)
    {
      int i = 0;
      int *index = NULL;
      int num = argc - 2;
      pthread_t *threads;

      threads = malloc(sizeof(pthread_t) * num);

      struct LogOptions *option;
     
      for (i = 0; i < num; i++)
      {
        option = malloc(sizeof(struct LogOptions));
        strcpy(option->filename, argv[1]);
        option->interval = atoi(argv[2 + i]);
        option->thread = i;
        pthread_create(&threads[i], NULL, timer_func, (void *)option);
      }
      for (i = 0; i < num; i++)
        pthread_join(threads[i], NULL);
      
      free(threads);

      pthread_mutex_destroy(&lock);

      printf("After Threads\n");
    }
    else
      printf("Not enough parameters provided...");

    return 0;
  }
}