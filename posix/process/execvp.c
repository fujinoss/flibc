#include <unistd.h>
#include <string.h>

int execve(const char *path, char *const argv[], char *const envp[]);

extern char **environ;

static int try_path(const char *file, char *const argv[], char *const envp[]) {
    execve(file, argv, envp);
    return -1;
}

int execvp(const char *file, char *const argv[]) {
    if (strchr(file, '/')) {
        return try_path(file, argv, environ);
    }

    const char *path = "PATH=/usr/local/bin:/usr/bin:/bin:/usr/local/sbin:/usr/sbin:/sbin";
    char buf[1024];
    const char *p = path + 5;

    while (*p) {
        const char *end = p;
        while (*end && *end != ':') end++;
        size_t dlen = (size_t)(end - p);

        if (dlen + 1 + strlen(file) + 1 < sizeof buf) {
            size_t i;
            for (i = 0; i < dlen; i++) buf[i] = p[i];
            buf[i++] = '/';
            const char *f = file;
            while (*f) buf[i++] = *f++;
            buf[i] = 0;

            try_path(buf, argv, environ);
        }

        if (!*end) break;
        p = end + 1;
    }
    return -1;
}

int execv(const char *path, char *const argv[]) {
    return execve(path, argv, environ);
}
