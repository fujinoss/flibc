const std = @import("std");

pub fn build(b: *std.Build) void {
    const target = b.standardTargetOptions(.{
        .default_target = .{
            .cpu_arch = .aarch64,
            .os_tag = .linux,
            .abi = .android,
        },
    });
    const optimize = b.standardOptimizeOption(.{
        .preferred_optimize_mode = .ReleaseSmall,
    });

    const c_sources = [_][]const u8{
        "io/write.c",
        "io/read.c",
        "io/open.c",
        "io/openat.c",
        "io/close.c",
        "io/lseek.c",
        "misc/errno.c",
        "misc/stack_chk.c",
        "posix/process/getpid.c",
        "posix/fs/chdir.c",
        "posix/fs/getcwd.c",
        "stdlib/exit/exit.c",
        "stdlib/exit/_exit.c",
        "stdio-common/printf/printf.c",
        "stdio-common/printf/snprintf.c",
        "stdio-common/printf/engine/printf_engine.c",
        "stdio-common/output/puts.c",
        "stdio-common/output/fputs.c",
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
    };

    const lib = b.addStaticLibrary(.{
        .name = "flibc",
        .target = target,
        .optimize = optimize,
    });

    lib.addIncludePath(b.path("include"));
    lib.addCSourceFiles(.{
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
    lib.addAssemblyFile(b.path("arch/aarch64/crt/_start.S"));
    lib.root_module.addImport("syscalls", b.createModule(.{
        .root_source_file = b.path("arch/aarch64/syscalls.zig"),
        .target = target,
        .optimize = optimize,
    }));
    lib.linkLibC();

    b.installArtifact(lib);

    const tests = b.addTest(.{
        .root_source_file = b.path("arch/aarch64/syscalls.zig"),
        .target = target,
        .optimize = optimize,
    });
    const run_tests = b.addRunArtifact(tests);
    b.step("test", "Run unit tests").dependOn(&run_tests.step);
}
