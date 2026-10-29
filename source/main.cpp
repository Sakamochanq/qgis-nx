#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Include the main libnx system header, for Switch development
#include <switch.h>

int main(int argc, char* argv[])
{
    // コンソールの初期化
    consoleInit(NULL);
    padConfigureInput(1, HidNpadStyleSet_NpadStandard);

    PadState pad;
    padInitializeDefault(&pad);

    // Hello World! を表示
    printf("\nHello World!\n");
    printf("\nPress + (plus) to exit.\n");


    while (appletMainLoop())
    {
        padUpdate(&pad);

        u64 kDown = padGetButtonsDown(&pad);

        // ＋ボタンで終了
        if (kDown & HidNpadButton_Plus)
            break;

        // 更新
        consoleUpdate(NULL);
    }

    // クリーンアップ
    consoleExit(NULL);
    return 0;
}
