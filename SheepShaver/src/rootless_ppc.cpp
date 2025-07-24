#include "sysdeps.h"
#include "macos_util.h"
#include "thunks.h"
#include "main.h"
#include "debug.h"

static uint32 tv_NewWindow = 0;
static uint32 tv_PaintRgn = 0;
static uint32 tv_DragGrayRgn = 0;
static uint32 tv_QDFlushPortBuffer = 0;

extern "C" uint32 call_macos8(uint32 tvect, uint32 a1, uint32 a2, uint32 a3, uint32 a4, uint32 a5, uint32 a6, uint32 a7, uint32 a8);

extern "C" void RootlessNewWindow(uint32 a1, uint32 a2, uint32 a3, uint32 a4, uint32 a5, uint32 a6, uint32 a7, uint32 a8)
{
    D(bug("RootlessNewWindow\n"));
    if (tv_NewWindow)
        call_macos8(tv_NewWindow, a1, a2, a3, a4, a5, a6, a7, a8);
}

extern "C" void RootlessPaintRgn(uint32 a1, uint32 a2, uint32 a3, uint32 a4, uint32 a5, uint32 a6, uint32 a7, uint32 a8)
{
    D(bug("RootlessPaintRgn\n"));
    if (tv_PaintRgn)
        call_macos8(tv_PaintRgn, a1, a2, a3, a4, a5, a6, a7, a8);
}

extern "C" void RootlessDragGrayRgn(uint32 a1, uint32 a2, uint32 a3, uint32 a4, uint32 a5, uint32 a6, uint32 a7, uint32 a8)
{
    D(bug("RootlessDragGrayRgn\n"));
    if (tv_DragGrayRgn)
        call_macos8(tv_DragGrayRgn, a1, a2, a3, a4, a5, a6, a7, a8);
}

extern "C" void RootlessQDFlushPortBuffer(uint32 a1, uint32 a2, uint32 a3, uint32 a4, uint32 a5, uint32 a6, uint32 a7, uint32 a8)
{
    D(bug("RootlessQDFlushPortBuffer\n"));
    if (tv_QDFlushPortBuffer)
        call_macos8(tv_QDFlushPortBuffer, a1, a2, a3, a4, a5, a6, a7, a8);
}

extern "C" void RootlessInstall(void)
{
    const char lib[] = "\014InterfaceLib"; // length-prefixed name
    tv_NewWindow = FindLibSymbol((char*)lib, "\011NewWindow");
    tv_PaintRgn = FindLibSymbol((char*)lib, "\010PaintRgn");
    tv_DragGrayRgn = FindLibSymbol((char*)lib, "\013DragGrayRgn");
    tv_QDFlushPortBuffer = FindLibSymbol((char*)lib, "\022QDFlushPortBuffer");

    if (tv_NewWindow) {
        WriteMacInt32(tv_NewWindow, NativeFunction(NATIVE_ROOTLESS_NEWWINDOW));
        WriteMacInt32(tv_NewWindow + 4, (uint32)(uintptr_t)TOC);
    }
    if (tv_PaintRgn) {
        WriteMacInt32(tv_PaintRgn, NativeFunction(NATIVE_ROOTLESS_PAINTRGN));
        WriteMacInt32(tv_PaintRgn + 4, (uint32)(uintptr_t)TOC);
    }
    if (tv_DragGrayRgn) {
        WriteMacInt32(tv_DragGrayRgn, NativeFunction(NATIVE_ROOTLESS_DRAGGRAYRGN));
        WriteMacInt32(tv_DragGrayRgn + 4, (uint32)(uintptr_t)TOC);
    }
    if (tv_QDFlushPortBuffer) {
        WriteMacInt32(tv_QDFlushPortBuffer, NativeFunction(NATIVE_ROOTLESS_QDFLUSHPORTBUFFER));
        WriteMacInt32(tv_QDFlushPortBuffer + 4, (uint32)(uintptr_t)TOC);
    }
}
