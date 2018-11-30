#include "types.h"
#include "user.h"

int main(int argc, char *argv[])
{
    const char *str = "Hello world!";
    int pgsize = getpagesize();
    printf(1, "int * 10 Bytes: ");
    printf(1, "%s: %d\n", "System call number of alloc", alloc("int", 10));

    printf(1, "Page Size: %d\n", pgsize);
    int fd;
    if(!(fd = open("README", 0)))
        printf(1, "Fail to open file!\n");

    char *text1 = mmap(pgsize, fd, 0);
    if (text1 != (void *)-1)
        printf(1, "first map: file is mapped to 0x%x\n", text1);

    if(close(fd))
        printf(1, "File is closed\n");
    
    
    printf(1, "mapping: %s\n\n", text1);
    printf(1, "----------------------------\n");

    fd = open("README", 0);
    char *text2 = mmap(pgsize, fd, 2000);
    if (text1 != (void *)-1)
        printf(1, "second map: file is mapped to 0x%x\n", text2);
    
    printf(1, "mapping: %s\n\n", text2);
    printf(1, "----------------------------\n");

    printf(1, "first map still works!\n%s", text1);

    strcpy(text1, str);
    printf(1, "%s\n\n", text1);

    
    
    exit();
}