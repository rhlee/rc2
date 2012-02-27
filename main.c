#include <stdio.h>
#include <dirent.h>
#include <string.h>

int
main(int argc, char *argv[])
{
  struct dirent *node;
  DIR *input = opendir("/dev/input");
  int count = 0;
  const char *event_string = "event";
  const int event_strlen = strlen(event_string);

  int temp;
  while((node = readdir(input)) != NULL)
  {
    if(strncmp(node->d_name, event_string, event_strlen) != 0)
      continue;
    printf("%s\n", node->d_name);
    count++;
  }

  closedir(input);
  printf("h");
  return 0;
}
