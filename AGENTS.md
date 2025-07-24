# Rootless SheepShaver development notes

This repository forks `kanjitalk755/macemu` with the goal of bringing the
"rootless" window-forwarding feature (as seen in zydeco's Basilisk II patches)
to SheepShaver.

## Progress so far
- Added a new `call_macos8` trampoline and `CallMacOS8` macros to allow calling
  Toolbox routines that take up to eight arguments.
- Created `rootless_ppc.cpp` and `rootless.h` containing stub implementations
  for rootless hooks (`RootlessInstall`, `RootlessNewWindow`,
  `RootlessPaintRgn`, `RootlessDragGrayRgn`, `RootlessQDFlushPortBuffer`).
  These currently just log and forward calls to the original toolbox vectors.
- Extended the native-op table in `thunks.h`/`thunks.cpp` and invoke
  `NATIVE_ROOTLESS_INSTALL` from `PatchAfterStartup` so the stubs are installed
  automatically after system startup.
- Included `debug.h` in the new source to fix compile errors.

The actual SDL window management for per-window rendering is not yet
implemented; this branch only sets up the infrastructure for patching
InterfaceLib.

## Building
Run the normal build steps described in the README. On a Unix-like system:

```sh
cd SheepShaver/src/Unix
./autogen.sh
make
```

Use the equivalent commands for macOS or Windows as documented in the
repository README.
