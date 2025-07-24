#ifndef ROOTLESS_H
#define ROOTLESS_H

#ifdef __cplusplus
extern "C" {
#endif

void RootlessInstall(void);
void RootlessNewWindow(uint32,uint32,uint32,uint32,uint32,uint32,uint32,uint32);
void RootlessPaintRgn(uint32,uint32,uint32,uint32,uint32,uint32,uint32,uint32);
void RootlessDragGrayRgn(uint32,uint32,uint32,uint32,uint32,uint32,uint32,uint32);
void RootlessQDFlushPortBuffer(uint32,uint32,uint32,uint32,uint32,uint32,uint32,uint32);

#ifdef __cplusplus
}
#endif

#endif
