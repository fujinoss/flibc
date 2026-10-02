.global __flibc_restore_rt
.type __flibc_restore_rt, %function
__flibc_restore_rt:
    mov x8, #139
    svc #0
.size __flibc_restore_rt, . - __flibc_restore_rt
