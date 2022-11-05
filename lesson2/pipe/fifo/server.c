#include <stdio.h>
#include <sys/types.h>

#include <sys/stat.h>

#define  FILE_NAME  "myfifo "
int main()
{
  if(mkfifo(FILE_NAME,0644) <0)
  {
    perror("mkfifo");
    return 1;
  }
}
