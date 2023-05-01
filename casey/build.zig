const std = @import("std");
//const Builder = std.build.Builder;

pub fn build(b: *std.build.Builder) void {
    // Standard target options allows the person running `zig build` to choose
    // what target to build for. Here we do not override the defaults, which
    // means any target is allowed, and the default is native. Other options
    // for restricting supported target set are available.
    const target = b.standardTargetOptions(.{});

    // Standard optimization options allow the person running `zig build` to select
    // between Debug, ReleaseSafe, ReleaseFast, and ReleaseSmall. Here we do not
    // set a preferred release mode, allowing the user to decide how to optimize.
    const mode = b.standardReleaseOptions();
    //const optimize = b.standardOptimizeOption(.{});

    const exe = b.addExecutable("example", "src/helper.zig");
    exe.addCSourceFiles(&.{"src/main.c"}, &.{"-std=c99"});
    exe.addIncludePath("src");
    exe.setTarget(target);
    exe.setBuildMode(mode);
    exe.linkLibC();

    //    const exe = b.addExecutable(.{
    //        .name = "example",
    //        .target = target,
    //        .mode = mode,
    //        // In this case the main source file is merely a path, however, in more
    //        // complicated build scripts, this could be a generated file.
    //        .root_source_file = .{ .path = "helper.zig" },
    //    }, null);
    //    exe.addCSourceFiles(&.{"src/main.c"}, &.{"-std=c99"});
    //    exe.linkLibC();

    // This declares intent for the executable to be installed into the
    // standard location when the user invokes the "install" step (the default
    // step when running `zig build`).
    exe.install();
}
