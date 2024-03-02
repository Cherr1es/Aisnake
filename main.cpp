#include <graphics.h>
#include <conio.h>
#include <queue>

#define width 40 //横向40格子
#define height 30 // 纵向30格子
#define size 20 //格子尺寸

int Sblocks [ width ] [ height ] = { 0 } ; //蛇区块,赋予的值代表此坐标是蛇的第个？区块
char moveDirection ; //移动方向
int foodX , foodY ; //食物坐标
bool isFailure = false ; //失败判定
bool shouldExit = false ; //结束游戏

typedef struct Snakeandfood
{

}Saf;

using namespace std ;

void initGame ( void ) //游戏初始化
{
    initgraph ( width * size , height * size ) ; //初始化窗口
    setbkcolor ( LIGHTGRAY ) ; //颜色
    cleardevice ( ) ;
    setlinecolor ( WHITE ) ; //划线
    int i ;
    for ( i = size ; i < width * size ; i += size )
    {
        line( i , 0 , i , width * size ) ;

    }
    for ( i = size ; i < height * size ; i += size )
    {
        line ( 0 , i , width * size , i ) ;
    }
    moveDirection = 'd' ; //默认向右走
    Sblocks [width / 2 ] [height / 2 ] = 1 ; //初始化蛇头位于中心
    for ( i = 1 ; i < 4 ; i ++ ) //蛇初始长度为4
    {
        Sblocks [width / 2 - i ] [height / 2 ] = 1 + i ;
    }
    foodX = rand ( ) % ( width - 2 ) + 1 ; // 横坐标取值为0-38，最外一圈不生成食物
    foodY = rand ( ) % ( height - 2 ) + 1 ;
}

void show ( void ) // 绘制图像
{
    for ( int i = 0 ; i < width ; i ++ )
    {
        for ( int t = 0 ; t < height ; t ++ )
        {
            if (Sblocks [ i ] [ t ] != 0 )
            {
                setfillcolor ( LIGHTRED ) ;
            }
            else
            {
                setfillcolor ( LIGHTGRAY ) ;
            }
            fillrectangle ( i * size , t * size , ( i + 1 ) * size , ( t + 1 ) * size ) ;
        }
    }
    setfillcolor ( LIGHTGREEN ) ;
    fillrectangle ( foodX * size , foodY * size , ( foodX + 1 ) * size , ( foodY + 1 ) * size ) ;
    if ( isFailure )
    {
        exit ( 0 ) ;
    }
}

void movesnake ( void ) //移动逻辑
{
    int i, t;
    for (i = 0; i < width; i++) //蛇身自主移动
    {
        for (t = 0; t < height; t++) {
            if (Sblocks[i][t] != 0) {
                Sblocks[i][t]++;
            }
        }
    }
    int oldheadX, oldheadY, oldtailX, oldtailY; //移动后旧蛇头和蛇尾的坐标
    int tailSblocks = 0; //蛇尾区块
    //更新蛇头与蛇尾的坐标
    for (i = 0; i < width; i++) {
        for (t = 0; t < height; t++) {
            if (tailSblocks < Sblocks[i][t]) {
                tailSblocks = Sblocks[i][t]; //赋值
                oldtailX = i;
                oldtailY = t;
            }
            if (Sblocks[i][t] == 2) //旧的蛇头区块的值一定是2
            {
                oldheadX = i;
                oldheadY = t;
            }
        }
    }
    int newheadX = oldheadX, newheadY = oldheadY;
    switch (moveDirection) //键盘操作逻辑
    {
        case 'w' :
            newheadY -= 1;
            break;
        case 's' :
            newheadY += 1;
            break;
        case 'a' :
            newheadX -= 1;
            break;
        case 'd' :
            newheadX += 1;
            break;
    }
    if (newheadX >= width || newheadX < 0 || newheadY >= height || newheadY < 0 || Sblocks[newheadX][newheadY] != 0) {
        isFailure = 1;
        return;
    }
    Sblocks[newheadX][newheadY] = 1; //更新蛇头坐标
    if ( newheadX == foodX && newheadY == foodY ) //若吃到食物则不更改蛇尾坐标，而重新生成食物
    {
        foodX = rand ( ) % ( width - 2 ) + 1 ;
        foodY = rand ( ) % ( height - 2 ) + 1 ;
    }
    else //反之则不重新生成新的食物，而更新蛇尾
    {
        Sblocks [ oldtailX ] [ oldtailY ] = 0 ;
    }
}

void BFS ( void ) //自动寻路
{

}

void updateWithInput ( void ) //输入有关的更新
{
    if ( _kbhit ( ) && isFailure == 0 ) //检测键盘输入和游戏状态
    {
        char input = _getch ( ) ;
        if ( input == 'w' || input == 's' || input == 'a' || input == 'd' ) //移动相关
        {
            moveDirection = input ;
            movesnake ( ) ;
        }
        if ( input == 'f' )
        {
            BFS ( ) ;
        }
        if (input == 27) // ESC键
        {
            shouldExit = 1 ;
        }
    }
}

void updateWithoutInput ( void ) //与输入无关的更新
{
    if ( isFailure )
    {
        return ;
    }
    Sleep ( 50 ) ; // 每50ms检测一次游戏状态
    movesnake ( ) ;
}

int main ( void )
{
    initGame ( ) ;
    show ( ) ;
    movesnake() ;
    while ( !shouldExit )
    {
        show ( ) ;
        BFS ( ) ;
        updateWithoutInput ( ) ;
        updateWithInput ( ) ;
    }
    return 0 ;
}