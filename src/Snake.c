/*貪食蛇 : 需使用加裝conio-2.0-1mol.DevPak後的Dev C++來編譯 
  
  安裝步驟 : 1.裝 Dev C++
             2.裝 conio-2.0-1mol.DevPak ( 方法:用Dev-Cpp資料夾中的Packman.exe安裝 )
             3.工具->編輯器選項->在連結器命令列中加入以下命令 : -lconio 
             
  若要使用gcc編譯，步驟如下：
  
  gcc -c Snake.c
  gcc -o Snake Snake.o -lconio
  
  若要再連結圖示檔(假設圖示檔已經編譯為.o檔，且檔名為123.o)
  則第二行改成下面這行
  
  gcc -o Snake Snake.o 123.o -lconio
  
           
  遊戲流程 : 按方向鍵開始遊戲，速度會依分數門檻而增加， 
  　　   　　碰到邊界或尾巴都會導致遊戲結束，結束時可以選擇繼續或關閉 
  
  實作日期 : 2007.3.10 
*/ 

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>

#define EQU ==
#define X_SPACE 2  //x的位移量 
#define Y_SPACE 1  //y的位移量 
#define RIGHT 40
#define LEFT 3
#define UP 3
#define DOWN 20
#define WALKED 50000  //走超過50000格就會當掉 
#define TAIL_NUM 500 //尾巴超過500個就會當掉 

int delayTime = 150;  //蛇的速度 
int x = 20;  //方位 
int y = 10;
int starX = 0;  //星星的位置 
int starY = 0;
int move = 0; //位移
int point = -5; //得分 
int tail[TAIL_NUM] = {0}; //尾巴 
int currentAspect = 0; //目前方向
int walkX[WALKED] = {0};  //走過的 
int walkY[WALKED] = {0};
int walkNext[WALKED] = {0}; //指示尾巴要走的路 
int tailX[TAIL_NUM] = {0};  //尾巴的位置  
int tailY[TAIL_NUM] = {0};
int isBump = 0; //是否碰撞 


int Move(int,int,int);  //移動位置 
void Star(int*,int*,int,int,int*);  //畫出星星並讓其軌跡隨機 
void PrintBorder(int );  //畫出外框 
void Play();  //遊戲主要套件 
void PrintSnake();  //畫出蛇的軌跡 
void Start(); //開始處理 
int End();  //結束處理 
void GetTail();  //計算目前蛇的尾巴有多長 
void PrintTail();  //畫出蛇的尾巴 
void PrintAspect();  //標出目前的方向 
void Restart(); //重新玩的歸零動作 
int IsAgain();  //是否重新玩 
void Walked(); //走過的路 
int IsBumpTail(); //頭撞到尾巴 
void Speed(); //依分數調節速度 
void EndView(); //最後的等待畫面 

int main()
{
    int over = 0;
    while(over EQU 0)
    {
        Start();  //開始 
	
	    PrintSnake();  //畫出遊戲畫面並進行遊戲 
    
        over = End();  //結束 
    }
    
    clrscr();  //清空畫面 
    
    EndView();  //看片尾動畫... 
    
    gotoxy(20,10);
    
    printf("Bye Bey  !!          "); 
    
    system("PAUSE");
    
	return 0;
}

void GetTail(int p)
//計算目前蛇的尾巴有多長  
{
    int i;
    
    for(i=0 ; i<(p/5) ; i++)
        tail[i] = 1;
}

int KeyIn()
// 檢查輸入的是上下左右哪一個
{
	int keyIn = 0;
	int rightKey = 0;

	while( rightKey EQU 0 )
	{
		while(!kbhit()) ;

		keyIn = getch();

		if( keyIn EQU 72 || keyIn EQU 75 || 
			keyIn EQU 77 || keyIn EQU 80 )
			/*一定要是上下左右才能跳出迴圈  */
			rightKey = 1;
	}
	return keyIn; 
}

void Walked()
//紀錄走過的路 
{
    int i = 0;
    
    while(walkX[i] != 0)
        i = i + 1;
    
    walkX[i] = x;
    walkY[i] = y; 
}

void PrintTail()
//畫出蛇的尾巴 
{
    int i = 0;
    int no = 0;
    int j = WALKED-1;
	   
	GetTail(point);
    
    while(walkX[j] EQU 0 )  //從後面開始找已經走過的點 
        j = j - 1;
       
    while(tail[i] EQU 1){  //tail[]紀錄尾巴的個數 
        tailX[i] = walkX[j];
        tailY[i] = walkY[j];
        gotoxy(walkX[j],walkY[j]);
        printf("o");
        i = i + 1;
        j = j - 1;
    }  
}
    
void PrintSnake()
//除非出界或撞到尾巴,否則會依照方向連續繪出蛇的移動軌跡 
{
    int over = 0;  //停止與否 
    int keyIn = 0;   
    int i = 0;
    int bump = 0;
    
    while( over EQU 0 )
    {
        keyIn = KeyIn();
        while(!kbhit()){
	       move = Move(x,y, keyIn);

	       printf("*");
	       
	       Walked();  //紀錄走過的路
	       
           PrintTail(); //畫出尾巴的軌跡 
	       
	       if(keyIn EQU 72 || keyIn EQU 80 )
	           y = move ;
	       else if(keyIn EQU 75 || keyIn EQU 77 )
	           x = move ;
	                     
	       Play();  //遊戲套件  
	        
           if(x > RIGHT || y > DOWN ||  //出界 
              x < LEFT  || y < UP     ){
                printf(" 碰 到 邊 界  !!!!   \n\n\n");
                over = 1;
	            break;
           }
           else if(isBump EQU 1 ){
                printf(" 撞 到 尾 巴  !!!!   \n\n\n");
                over = 1;
	            break;
           }

        }
    }
}

int Move(int x,int y,int way)
//移動位置 
{
    
    if(way EQU 72){   //向上 
        y -= Y_SPACE;
        gotoxy(x,y);
        return y;
    }
    else if(way EQU 80){  //向下 
        y += Y_SPACE;
        gotoxy(x,y);
        return y;
    }
    else if(way EQU 75){  //向左 
        x -= X_SPACE;
        gotoxy(x,y);
        return x;
    }
    else if(way EQU 77){  //向右 
        x += X_SPACE;
        gotoxy(x,y);
        return x;
    }
    else
        printf("Imposible !! \n");
}

void Star(int* starX,int* starY,int snakeX,int snakeY,int * point)
//隨機出現蛇可以吃的星星 
{
    srand(time(NULL));
    
    if( ( *starX EQU 0 && *starY EQU 0 ) ||
        ( snakeX EQU *starX && snakeY EQU *starY) ){  //如果蛇還沒吃到星星
        *starX = rand()%35 + 4;
        *starY = rand()%15 + 4;
        *point += 5;
        
        if(*starX % 2 EQU 1) //因為蛇水平方向一次移兩格，所以不能出現基數 
            *starX = *starX + 1;
    }
    
    gotoxy(*starX,*starY);
    printf("+");
    gotoxy(*starX+1,*starY+1);
    printf("%d,%d",*starX,*starY);    
}

void PrintBorder(int point)
//畫出外框 
{
    int i; 
    
    gotoxy(1,1); //回到原點才可以固定畫圖
    
    printf("歡迎來到貪食蛇世界 !!      目前分數 : %d 分  \n",point);
     
    printf("-----------------------------"  //上面那條線 
            "----------------       ");
    
    printf("\n|\n|\n|\n|\n|\n|\n|\n|\n|\n"    //左邊那條線 
           "|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n");
    
    for(i=3 ; i<21 ; i++){       //右邊那條線 
        gotoxy(45,i);
        printf("|");
    }
    
    gotoxy(1,21);
    printf("-----------------------------"  //下面那條線 
            "---------------- \n");
}

void Play()
//主要遊戲套件 
{ 
    gotoxy(x+1,y+1);  //擺在蛇的又下方 
    //printf("( %d , %d )",x,y);   
	        
	Star(&starX,&starY,x,y,&point);  //畫出星星
	PrintBorder(point);  //畫出邊界 
	
	isBump = IsBumpTail();
	
	Speed();  //調節速度 
	        
	Sleep(delayTime); //停頓delayTime秒
    clrscr();  //清空畫面            
}

int IsBumpTail()
//是否蛇頭撞到尾巴 
{
    int i = 0;
    int bump = 0;
    
    while(tail[i] EQU 1){
                if(tailX[i] EQU x && tailY[i] EQU y)
                    bump = 1;
                i = i + 1;
    }
    if(bump EQU 1)
        return 1;
    else
        return 0;
}

void Speed()
//調節速度
{
    if( point > 50 )
        delayTime = 100;
    else if( point > 100 )
        delayTime = 70;
    else if( point > 200)
        delayTime = 50;
    else if( point > 300)
        delayTime = 25;
} 

void Start()
//開始畫面 
{ 
    Restart();  //重新玩的歸零動作 
    gotoxy(x,y);
    printf("按方向鍵開始遊戲");
}

void Restart()
//重新開始需把全域變數歸零 
{
    int i;
    
    delayTime = 150;
    isBump = 0;
    x = 20;  //方位 
    y = 10;
    starX = 0;  //星星的位置 
    starY = 0;
    move = 0; //位移
    point = -5; //得分 
    for(i=0 ; i<TAIL_NUM ; i = i+1){
        tail[i] = 0; //尾巴數量 
        tailX[i] = 0; //紀錄尾巴的軌跡 
        tailY[i] = 0;
    }
    
    for(i=0 ; i<WALKED ; i = i+1)
    {
        walkX[i] = 0;  //走過的 
        walkY[i] = 0;
        walkNext[i] = 0; //指示尾巴要走的路 
    }
    
    currentAspect = 0; //目前方向   
    clrscr();  //清空畫面
}

int End()
//結束畫面 
{
    printf("     GAME OVER   !!\n\n");
    printf("  　 本次得分　：　%d   分\n\n",point); 
    
    return IsAgain();
}

void EndView()
//結束設定為等三秒 
{
    int wait = 3;  //是否等幾秒 
    
    while( wait > 0)
	{
        gotoxy(7-wait,5-wait);
        
        printf("倒數 %d 秒 \n",wait);
        Sleep(500); //停頓0.5秒 
        clrscr();  //清空畫面 
        
	    wait = wait - 1;
    }
}

int IsAgain()
/*是否再玩一次 */ 
{
    int keyIn = 0;
    int over = 0;
    
    gotoxy(6,8);
    
    printf("想再玩一次嗎 ?  ( y or n ) : ");
    
    while(over EQU 0){
        while(!kbhit()) ;
	    keyIn = getch();
    
        if(keyIn EQU 121)
            return 0;  //繼續玩 
        else if(keyIn EQU 110)
            return 1;  //不要玩了 
        else
            over = 0;
    } 
}
