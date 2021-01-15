#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <time.h>
#include <string.h>

void timer_func(char *filename, int interval)
{
  // while (1)
  // {
  printf("Starting timer...");
  int fdes = open(filename, O_CREAT | O_APPEND | O_WRONLY);

  char buff[24];
  time_t now = time(0);
  struct tm *t = localtime(&now);
  strftime(buff, 24, "%Y-%m-%d %H:%M:%S", t);
  char text[50];
  sprintf(text, "%s\n", buff);
  write(fdes, text, strlen(text));
  close(fdes);
  // }
}

int main(int argc, char **argv)
{
  {
    if (argc == 3)
    {
      timer_func(argv[1], atoi(argv[2]));
    }
    else
      printf("Not enough parameters provided...");

    return 0;
  }
}