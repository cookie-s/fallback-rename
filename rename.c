#define _GNU_SOURCE
#define _FILE_OFFSET_BITS 64
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>

int rename(const char *oldpath, const char *newpath)
{

    int oldfd = open(oldpath, O_RDONLY);
    if (oldfd == -1) {
        return -1;
    }
    int newfd = open(newpath, O_WRONLY | O_CREAT);
    if (newfd == -1) {
        return -1;
    }

    struct stat st;
    if (fstat(oldfd, &st) == -1) {
        return -1;
    }

    size_t sz = st.st_size;

    int ret = copy_file_range(oldfd, NULL, newfd, NULL, sz, 0);
    if (ret == -1) {
        return -1;
    }

    dprintf(2, "rename: copied %s -> %s (%d bytes)\n", oldpath, newpath, ret);

    unlink(oldpath);

    return 0;
}
