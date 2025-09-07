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
        goto err3;
    }
    int newfd = open(newpath, O_WRONLY | O_CREAT | O_TRUNC);
    if (newfd == -1) {
        goto err2;
    }

    struct stat st;
    if (fstat(oldfd, &st) == -1) {
        goto err1;
    }

    size_t sz = st.st_size;

    int ret = copy_file_range(oldfd, NULL, newfd, NULL, sz, 0);
    if (ret == -1) {
        goto err1;
    }

    dprintf(2, "rename: copied %s -> %s (%d bytes)\n", oldpath, newpath, ret);

    unlink(oldpath);

    return 0;

err1:
    close(newfd);
err2:
    close(oldfd);
err3:
    return -1;
}
