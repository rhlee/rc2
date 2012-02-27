#include <stdio.h>
#include <dirent.h>

int
main(int argc, char *argv[])
{
  struct dirent *node;
  DIR *input = opendir("/dev/input");

  while((node = readdir(input)) != NULL)
  {
    printf("x");
  }

  closedir(input);
  printf("h");
  return 0;
}
