#include <stdlib.h>

void _exit(int code);

void exit(int code) {
    _exit(code);
}
