#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <linux/input.h>

#include <X11/Xlib.h>
#include <X11/Intrinsic.h>
#include <X11/extensions/XTest.h>
#include <unistd.h>


void get_input(char *input);
void keys_down(int key1, int key2);
void keys_up();


int key_code, repetitions = 0;
Display *display;
int keys_pressed[2] = {0, 0};


int
main(int argc, char *argv[])
{
  char input_path[32];
  get_input(input_path);

  int file;
  if ((file = open(input_path, O_RDONLY)) < 0)
  {
    perror("Couldn't open input device");
    return 1;
  }


  struct input_event event[64];
  size_t read_bytes;
  int i;

  display = XOpenDisplay (NULL);

  while(1)
  {
    read_bytes = read(file, event, sizeof(event));
    if (read_bytes < (int) sizeof(struct input_event)) {
      perror("short read");
      return 1;
    }
    
    for (i = 0; i < (int) (read_bytes / sizeof(struct input_event)); i++) {
      fflush(stdout);
      if(event[i].type != EV_KEY) continue;
      //printf("%d\n", event[i].value);
      switch(event[i].value)
      {
        case 0:
	  XSync (display, False);
	  XTestGrabControl (display, False);
          switch(event[i].code)
	  {
            case KEY_NEXTSONG:
	      printf("forwards\n");
              break;
            case KEY_PREVIOUSSONG:
	      printf("backwards\n");
              break;
            default:
	      perror("unknown key");
	      return 1;
          }
          printf("%d up\n", event[i].code);
	  break;
        case 1:
          XTestGrabControl (display, True);
          printf("%d down\n", event[i].code);
	  break;
        case 2:
          printf("%d held\n", event[i].code);
	  break;
        default:
    	  perror("Unknown event value");
      }
    }
  }

  return 0;
}

void
get_input(char *input)
{
  struct dirent *node;
  const char *dev_input_string = "/dev/input";
  const int dev_input_strlen = strlen(dev_input_string);
  DIR *input_dir = opendir(dev_input_string);
  int count = 0;
  const char *event_string = "event";
  const int event_strlen = strlen(event_string);
  char inputs[32][32];

  printf("Select input device:\n");

  int fd = -1;
  char name[256]= "Unknown";

  while((node = readdir(input_dir)) != NULL)
  {
    if(strncmp(node->d_name, event_string, event_strlen) != 0)
      continue;
    inputs[count][0] = '\0';
    strncat(inputs[count], dev_input_string, dev_input_strlen);
    strncat(inputs[count], "/", 1);
    strncat(inputs[count], node->d_name, strlen(node->d_name));

    if ((fd = open(inputs[count], O_RDONLY)) < 0) {
      perror("evdev open");
      exit(1);
    }
    if(ioctl(fd, EVIOCGNAME(sizeof(name)), name) < 0)
      perror("evdev ioctl");
    printf("  %d. %s\n", count + 1, name);

    close(fd);
    count++;
  }

  closedir(input_dir);

  int input_number;
  printf(" :");
  scanf("%d", &input_number);

  input[0] = '\0';
  strncat(input, inputs[input_number - 1], strlen(inputs[input_number - 1]));
}


void keys_down(int key1, int key2)
{
  
}
