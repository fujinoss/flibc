#include <stddef.h>

char **environ = 0;

extern char *__flibc_envp;

static char *fake_env[] = { (char *)"PATH=/usr/bin:/bin", 0 };

char **__flibc_get_environ(void) {
    if (environ) return environ;
    return fake_env;
}
