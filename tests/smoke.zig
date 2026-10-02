const sys = @import("../arch/aarch64/syscalls.zig");

pub fn main() void {
    _ = sys.write(1, "flibc smoke test\n") catch {};
    sys.exit(0);
}
