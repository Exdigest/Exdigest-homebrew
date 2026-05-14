#include <gccore.h>
#include <wiiuse/wpad.h>
#include <pngu.h>
#include <malloc.h>
#include <fat.h>

static void *xfb = NULL;
static GXRModeObj *rmode = NULL;

int main(int argc, char **argv) {
    VIDEO_Init();
    WPAD_Init();

    rmode = VIDEO_GetPreferredMode(NULL);
    xfb = MEM_K0_TO_K1(SYS_AllocateFramebuffer(rmode));
    console_init(xfb,20,20,rmode->fbWidth,rmode->xfbHeight,rmode->fbWidth*VI_DISPLAY_PIX_SZ);

    VIDEO_Configure(rmode);
    VIDEO_SetNextFramebuffer(xfb);
    VIDEO_SetBlack(FALSE);
    VIDEO_Flush();
    VIDEO_WaitVSync();
    if(rmode->viTVMode&VI_NON_INTERLACE) VIDEO_WaitVSync();

    PNGUPROP imgProp;
    IMGCTX ctx = PNGU_SelectImageFromDevice("sd:/apps/imageviewer/image.png");

    if (!ctx) {
        while(1) VIDEO_WaitVSync();
    }

    PNGU_GetImageProperties(ctx, &imgProp);

    void *imgBuf = memalign(32, imgProp.imgWidth * imgProp.imgHeight * 4);

    PNGU_DecodeTo4x4RGBA8(ctx, imgProp.imgWidth, imgProp.imgHeight, imgBuf, 255);
    PNGU_ReleaseImageContext(ctx);

    VIDEO_ClearFrameBuffer(rmode, xfb, COLOR_BLACK);

    // crude fullscreen blit
    u32 *fb = (u32*)xfb;
    u32 *src = (u32*)imgBuf;

    int x, y;
    for (y = 0; y < rmode->xfbHeight; y++) {
        for (x = 0; x < rmode->fbWidth; x++) {
            int sx = x * imgProp.imgWidth / rmode->fbWidth;
            int sy = y * imgProp.imgHeight / rmode->xfbHeight;
            fb[y * rmode->fbWidth + x] = src[sy * imgProp.imgWidth + sx];
        }
    }

    VIDEO_Flush();

    while (1) {
        VIDEO_WaitVSync();
    }

    return 0;
}
