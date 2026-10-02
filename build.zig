const std = @import("std");

pub fn build(b: *std.Build) void {
    const target = b.standardTargetOptions(.{
        .default_target = .{
            .cpu_arch = .aarch64,
            .os_tag = .linux,
            .abi = .android,
        },
    });
    const optimize = b.standardOptimizeOption(.{});

    const c_sources = [_][]const u8{
        "io/write.c",
        "io/read.c",
        "io/open.c",
        "io/openat.c",
        "io/close.c",
        "io/lseek.c",
        "misc/errno.c",
        "misc/stack_chk.c",
        "misc/environ.c",
        "posix/process/getpid.c",
        "posix/process/fork.c",
        "posix/process/execve.c",
        "posix/process/execvp.c",
        "posix/process/wait.c",
        "posix/process/pipe.c",
        "posix/process/dup.c",
        "posix/fs/chdir.c",
        "posix/fs/getcwd.c",
        "stdlib/exit/exit.c",
        "stdlib/exit/_exit.c",
        "stdio-common/printf/printf.c",
        "stdio-common/printf/snprintf.c",
        "stdio-common/printf/fprintf.c",
        "stdio-common/printf/engine/printf_engine.c",
        "stdio-common/file/file.c",
        "stdio-common/output/puts.c",
        "stdio-common/output/fputs.c",
        "stdio-common/output/putchar.c",
        "string/mem/memcpy.c",
        "string/mem/memmove.c",
        "string/mem/memset.c",
        "string/mem/memcmp.c",
        "string/str/strlen.c",
        "string/str/strcmp.c",
        "string/str/strncmp.c",
        "string/str/strcpy.c",
        "string/str/strncpy.c",
        "string/str/strchr.c",
        "string/str/strrchr.c",
        "malloc/malloc.c",
        "signal/sigaction.c",
        "signal/signal.c",
        "signal/sigset.c",
        "signal/sigprocmask.c",
        "signal/kill.c",
        "time/clock/clock_gettime.c",
        "time/clock.c",
        "time/gettimeofday.c",
        "time/nanosleep.c",
        "time/gmtime.c",
        "time/strftime/strftime.c",
    };

    const lib_module = b.createModule(.{
        .root_source_file = b.path("arch/aarch64/syscalls.zig"),
        .target = target,
        .optimize = optimize,
    });

    lib_module.addIncludePath(b.path("include"));
    lib_module.addCSourceFiles(.{
        .files = &c_sources,
        .flags = &.{
            "-std=c17",
            "-fno-stack-protector",
            "-fno-sanitize=undefined",
            "-Wall",
            "-Wextra",
            "-Wno-unused-parameter",
        },
    });
    lib_module.addAssemblyFile(b.path("arch/aarch64/crt/_start.S"));
    lib_module.addAssemblyFile(b.path("signal/restore.S"));

    const lib = b.addLibrary(.{
        .name = "flibc",
        .linkage = .static,
        .root_module = lib_module,
    });

    b.installArtifact(lib);

    const test_module = b.createModule(.{
        .root_source_file = b.path("arch/aarch64/syscalls.zig"),
        .target = target,
        .optimize = optimize,
    });

    const tests = b.addTest(.{
        .root_module = test_module,
    });

    const install_tests = b.addInstallArtifact(tests, .{
        .dest_dir = .{ .override = .{ .custom = "bin" } },
    });
    const test_step = b.step("test-bin", "Build the test binary (run it manually)");
    test_step.dependOn(&install_tests.step);
}
