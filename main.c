#include <stdio.h>
#include <dirent.h>
#include <string.h>

int
main(int argc, char *argv[])
{
  struct dirent *node;
  const char *dev_input_string = "/dev/input";
  const int dev_input_strlen = strlen(dev_input_string);
  DIR *input = opendir(dev_input_string);
  int count = 0;
  const char *event_string = "event";
  const int event_strlen = strlen(event_string);
  char inputs[32][32];

  while((node = readdir(input)) != NULL)
  {
    if(strncmp(node->d_name, event_string, event_strlen) != 0)
      continue;
    inputs[count][0] = '\0';
    strncat(inputs[count], dev_input_string, dev_input_strlen);
    strncat(inputs[count], "/", 1);
    strncat(inputs[count], node->d_name, strlen(node->d_name));
    printf("%s\n", inputs[count]);
    count++;
  }

  closedir(input);
  printf("h");
  return 0;
}
