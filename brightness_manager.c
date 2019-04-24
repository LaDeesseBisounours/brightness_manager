#include<err.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>

void writeValue(int fd, long val){
  lseek(fd, 0, SEEK_SET);
  char buf[10];
  sprintf(buf, "%ld", val);
  if (write(fd, buf, 10) <= 0)
    errx(1, "could not write");

}

int main(int argc, char** argv){
  if (argc < 2){
    errx(1, "no argument");
  }
  char *value = argv[1];
  char *endptr;
  long val = strtol(value, &endptr, 10);

  if (endptr == argv[1])
    errx(1, "no argument");

  int fd = open("/sys/class/backlight/intel_backlight/brightness", O_RDWR);
  int fdmax = open("/sys/class/backlight/intel_backlight/max_brightness", O_RDONLY);

  if (fd < 0 || fdmax < 0)
    errx(1, "could not open files");

  char currentVal[10];
  read(fd, currentVal, 10);
  long currVal = strtol(currentVal, &endptr, 10);

  char maxvalue[10];
  read (fdmax, maxvalue, 10);
  long valmax = strtol(maxvalue, &endptr, 10);
  
  long newVal = currVal + val;
  if (newVal < 500)
    writeValue(fd, 500);
  else if (newVal > valmax)
    writeValue(fd, valmax);
  else
    writeValue(fd, newVal);

  

  close(fd);
  close(fdmax);
  return 0;
}
