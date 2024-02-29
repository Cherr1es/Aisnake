#include <graphics.h>
#include <conio.h>

#define width 40 //横向40格子
#define height 30 // 纵向30格子
#define size 20 //格子尺寸

int Sbody [ width ] [ height ] = {0 } ; //蛇身
char moveDirection ; //移动方向
int foodX , foodY ; //食物坐标
bool isFailure = false ; //失败判定

using namespace std ;

void initGame ( void ) //游戏初始化
{
    initgraph ( width * size , height * size ) ; //初始化窗口
    setbkcolor ( LIGHTGRAY ) ; //颜色
    cleardevice ( ) ;
    setlinecolor ( WHITE ) ; //划线
    int i = 0 ;
    for ( i = size ; i < width * size ; i += size )
    {
        line( i , 0 , i , width * size ) ;

    }
    for ( i = size ; i < height * size ; i += size )
    {
        line ( 0 , i , width * size , i ) ;
    }
    moveDirection = 'd' ; //默认向右走
    Sbody [width / 2 ] [height / 2 ] = 1 ; //初始化蛇头位于中心
    for ( i = 1 ; i < 4 ; i ++ ) //蛇初始长度为4
    {
        Sbody [width / 2 - i ] [height / 2 ] =  1 ;
    }
    foodX = rand ( ) % ( width - 2 ) + 1 ; // 横坐标取值为0-38，最外一圈不生成食物
    foodY = rand ( ) % ( height - 2 ) + 1 ;
}

void show ( void ) // 显示
{
    for ( int i = 0 ; i < width ; i ++ )
    {
        for ( int t = 0 ; t < height ; t ++ )
        {
            if (Sbody [ i ] [ t ] != 0 )
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


int main ( void )
{
    initGame ( ) ;
    show ( ) ;
    while (1)
    {
        show () ; //检测
    }
    return 0 ;
}