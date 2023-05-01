const std = @import("std");
const emulator_8086 = @cImport({
    @cInclude("8086.c");
});

export fn setup_debug_handlers() void {
    std.debug.maybeEnableSegfaultHandler();
}

export fn dump_stack_trace() void {
    std.debug.dumpCurrentStackTrace(@returnAddress());
}
/// Communicate to zig that main() will be provided elsewhere.
//pub const _main = void;

//pub fn main() anyerror!void {
//    const args: c_int = 1;
//    const argc: [*c]u8 = null;
//    emulator_8086.run_8086(args, argc);
//}

pub const _start = {};
