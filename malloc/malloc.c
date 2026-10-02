#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stddef.h>

extern long __flibc_syscall6(unsigned long n,
                             unsigned long a1, unsigned long a2,
                             unsigned long a3, unsigned long a4,
                             unsigned long a5, unsigned long a6);

#define __NR_mmap 222

#define PROT_READ     0x1
#define PROT_WRITE    0x2
#define MAP_PRIVATE   0x02
#define MAP_ANONYMOUS 0x20

#define ALIGN      16
#define MIN_SPLIT  64
#define HEAP_CHUNK (1024 * 1024)

typedef struct block {
    size_t size;
    int    free;
    struct block *next;
    struct block *prev;
} block_t;

static block_t *head;

static size_t align_up(size_t n) {
    return (n + (ALIGN - 1)) & ~((size_t)(ALIGN - 1));
}

static void *sys_mmap(size_t len) {
    long ret = __flibc_syscall6(__NR_mmap,
                                0, len,
                                PROT_READ | PROT_WRITE,
                                MAP_PRIVATE | MAP_ANONYMOUS,
                                (unsigned long)-1, 0);
    if (ret < 0 && ret > -4096) return 0;
    return (void *)ret;
}

static block_t *grow_heap(size_t need) {
    size_t len = need;
    if (len < HEAP_CHUNK) len = HEAP_CHUNK;
    len = align_up(len);

    void *p = sys_mmap(len);
    if (!p) return 0;

    block_t *b = (block_t *)p;
    b->size = len;
    b->free = 1;
    b->next = head;
    b->prev = 0;
    if (head) head->prev = b;
    head = b;
    return b;
}

static block_t *find_free(size_t size) {
    block_t *b = head;
    while (b) {
        if (b->free && b->size >= size) return b;
        b = b->next;
    }
    return 0;
}

static void split(block_t *b, size_t size) {
    if (b->size < size + MIN_SPLIT + sizeof(block_t)) return;

    block_t *rest = (block_t *)((char *)b + size);
    rest->size = b->size - size;
    rest->free = 1;
    rest->next = b->next;
    rest->prev = b;
    if (b->next) b->next->prev = rest;
    b->next = rest;
    b->size = size;
}

void *malloc(size_t size) {
    if (size == 0) size = 1;
    size = align_up(size) + sizeof(block_t);
    size = align_up(size);

    block_t *b = find_free(size);
    if (!b) {
        b = grow_heap(size);
        if (!b) { errno = ENOMEM; return 0; }
    }
    split(b, size);
    b->free = 0;
    return (void *)((char *)b + sizeof(block_t));
}

void free(void *p) {
    if (!p) return;
    block_t *b = (block_t *)((char *)p - sizeof(block_t));
    b->free = 1;

    if (b->next && b->next->free) {
        block_t *n = b->next;
        b->size += n->size;
        b->next = n->next;
        if (n->next) n->next->prev = b;
    }
    if (b->prev && b->prev->free) {
        block_t *pr = b->prev;
        pr->size += b->size;
        pr->next = b->next;
        if (b->next) b->next->prev = pr;
    }
}

void *calloc(size_t n, size_t size) {
    if (n && size > (size_t)-1 / n) { errno = ENOMEM; return 0; }
    size_t total = n * size;
    void *p = malloc(total);
    if (p) memset(p, 0, total);
    return p;
}

void *realloc(void *p, size_t size) {
    if (!p) return malloc(size);
    if (size == 0) { free(p); return 0; }

    block_t *b = (block_t *)((char *)p - sizeof(block_t));
    size_t old = b->size - sizeof(block_t);
    if (old >= size) return p;

    void *np = malloc(size);
    if (!np) return 0;
    memcpy(np, p, old);
    free(p);
    return np;
}
