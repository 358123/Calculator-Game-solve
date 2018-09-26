/*
 * 这是一个用来计算一个叫Calculator游戏的小程序
 * Calculator是一个萌萌的计算器游戏
 * 通过限定次数，和用指定的按键来得到最终的结果
 * 这是一个数学游戏
 * 程序通过穷尽所有的组合来得到结果
 * Code by LittleMing
 * Updated 2018.8.27
 */

#include <stdio.h>
#include <string.h>
#include "game_input.h"
#include "game_process.h"
#include "game_output.h"
#include "game.h"

int main(int argc, char **argv)
{

    if ( argc == 1 )
    {
        unsigned int counter[2] = {0};
        struct GameStruct *gameP;
        printWelcome();
        char isContinue;
        do
        {
            puts("-------------------新的一关开始啦-------------------");
            gameP = getGameLevelInfo();
            solveIt(counter);
            gameOver();
            printSolutionInfo(counter, gameP);
            puts("温馨提示：退出请按Ctrl+C");
            do {
                printf("Continue?(y/n):");
            }while ( (isContinue = (char) getchar()) == '\n' );
        } while (isContinue != 'n');
    }
    else if ( argc == 2 && !strcmp(argv[1], "debug") )
    {
        puts("请注意，这是一个程序计算过程观察测试程序！");
        puts("-------------------Debug模式已开启-------------------");
        getGameLevelInfo();
        int buttonIndex;
        int result = Game.startNum;
        for (int i = 0; i < Game.allowMaxStep; i++)
        {
            printf("输入按钮编号：");
            scanf("%d", &buttonIndex);
            printf("按下按钮：【%s】\n", buttonStr(Game.buttons[buttonIndex]));
            if (Game.buttons[buttonIndex].type == MODIFY)
            {
                pressButton(Game.buttons[buttonIndex], result);
                printButtons(Game.buttons, Game.buttonNum);
            }
            else if (Game.buttons[buttonIndex].type == STORE)
            {
                short choose;
                printf("Enter your choose [1.store 2.append]:");
                scanf("%hi", &choose);
                if (choose == 1)
                {
                    storeNumberToButton(result, &Game.buttons[buttonIndex]);
                    printf("Stored %d\n", Game.buttons[buttonIndex].attachedInfo.storeNum);
                    i--;
                }
                else if (choose == 2)
                {
                    goto normalButtonPress;
                }
                else
                {
                    fprintf(stderr, "You enter a invalid value!\n");
                }
            }
            else
            {
                normalButtonPress:
                printf("%d -> ", result);
                result = pressButton(Game.buttons[buttonIndex], result);
                printf("%d status:%s\n", result, Game.isOnError ? "ERROR" : "OK");
            }
            puts("-----------------------------------------------------");
        }
        gameOver();
    }
    else
    {
        fprintf(stderr, "Error arguments!\n");
    }
    return 0;
}