extern long write(int fd, const void *buf, unsigned long count);
extern void exit(int code);

int main(int argc, char **argv, char **envp) {
    (void)argc; (void)argv; (void)envp;
    write(1, "hello from C, no libc\n", 22);
    return 0;
}
