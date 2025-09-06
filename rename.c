#define _GNU_SOURCE
#define _FILE_OFFSET_BITS 64
#include <fcntl.h>
#include <unistd.h>

int rename(const char *oldpath, const char *newpath)
{

    int oldfd = open(oldpath, O_RDONLY);
    if (oldfd == -1) {
        return -1;
    }
    int newfd = open(newpath, O_WRONLY | O_CREAT | O_EXCL);
    if (newfd == -1) {
        return -1;
    }

    int ret = copy_file_range(oldfd, NULL, newfd, NULL, 1000000, 0);
    if (ret == -1) {
        return -1;
    }

    unlink(oldpath);

    return 0;
}
