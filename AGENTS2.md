# Agent Notes – SheepShaver Build

## Context (Windows attempt)
- Tried building SheepShaver under MSYS2/MinGW‐32 following README Windows instructions.
- `make links` succeeded, `autogen.sh` ran, but `configure` failed because GNU `gcc` wasn’t seen in `$PATH` inside the generated shell.
- Mixing PowerShell ↔︎ msys2 shells caused repeated path / tool‐discovery issues (`make` not found, windres path confusion, etc.).
- Conclusion: the MinGW route is cumbersome here; switching to a full Linux environment (WSL or native) will be simpler.

## Plan for Linux build
1. Install deps (example for Ubuntu):
   ```bash
   sudo apt update
   sudo apt install build-essential autoconf automake libtool pkg-config \
                    libsdl2-dev libgtk2.0-dev git
   ```
2. Clone repo or reuse Windows checkout via `/mnt/c/...`.
3. Commands:
   ```bash
   cd macemu/SheepShaver
   make links            # bring BasiliskII shared sources
   cd src/Unix
   ./autogen.sh          # runs aclocal, autoconf, autoheader
   ./configure [--enable-gtk]  # configure options as needed
   make -j$(nproc)
   ```
4. Resulting binary: `SheepShaver/src/Unix/SheepShaver`.

## Follow-ups / TODO
- Verify build succeeds and run unit/manual tests.
- If GTK is not required, can omit to avoid extra packages.
- Consider cross-compiling a native Windows `.exe` later via `mingw-w64` inside Linux if needed.
- Keep documentation in `documentation/` in sync once the procedure is finalized. 