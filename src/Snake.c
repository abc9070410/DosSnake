/*�g���D : �ݨϥΥ[��conio-2.0-1mol.DevPak�᪺Dev C++�ӽsĶ 
  
  �w�˨B�J : 1.�� Dev C++
             2.�� conio-2.0-1mol.DevPak ( ��k:��Dev-Cpp��Ƨ�����Packman.exe�w�� )
             3.�u��->�s�边�ﶵ->�b�s�����R�O�C���[�J�H�U�R�O : -lconio 
             
  �Y�n�ϥ�gcc�sĶ�A�B�J�p�U�G
  
  gcc -c Snake.c
  gcc -o Snake Snake.o -lconio
  
  �Y�n�A�s���ϥ���(���]�ϥ��ɤw�g�sĶ��.o�ɡA�B�ɦW��123.o)
  �h�ĤG��令�U���o��
  
  gcc -o Snake Snake.o 123.o -lconio
  
           
  �C���y�{ : ����V��}�l�C���A�t�׷|�̤��ƪ��e�ӼW�[�A 
  �@�@   �@�@�I����ɩΧ��ڳ��|�ɭP�C�������A�����ɥi�H����~������� 
  
  ��@��� : 2007.3.10 
*/ 

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>

#define EQU ==
#define X_SPACE 2  //x���첾�q 
#define Y_SPACE 1  //y���첾�q 
#define RIGHT 40
#define LEFT 3
#define UP 3
#define DOWN 20
#define WALKED 50000  //���W�L50000��N�|�� 
#define TAIL_NUM 500 //���ڶW�L500�ӴN�|�� 

int delayTime = 150;  //�D���t�� 
int x = 20;  //��� 
int y = 10;
int starX = 0;  //�P�P����m 
int starY = 0;
int move = 0; //�첾
int point = -5; //�o�� 
int tail[TAIL_NUM] = {0}; //���� 
int currentAspect = 0; //�ثe��V
int walkX[WALKED] = {0};  //���L�� 
int walkY[WALKED] = {0};
int walkNext[WALKED] = {0}; //���ܧ��ڭn������ 
int tailX[TAIL_NUM] = {0};  //���ڪ���m  
int tailY[TAIL_NUM] = {0};
int isBump = 0; //�O�_�I�� 


int Move(int,int,int);  //���ʦ�m 
void Star(int*,int*,int,int,int*);  //�e�X�P�P������y���H�� 
void PrintBorder(int );  //�e�X�~�� 
void Play();  //�C���D�n�M�� 
void PrintSnake();  //�e�X�D���y�� 
void Start(); //�}�l�B�z 
int End();  //�����B�z 
void GetTail();  //�p��ثe�D�����ڦ��h�� 
void PrintTail();  //�e�X�D������ 
void PrintAspect();  //�ХX�ثe����V 
void Restart(); //���s�����k�s�ʧ@ 
int IsAgain();  //�O�_���s�� 
void Walked(); //���L���� 
int IsBumpTail(); //�Y������� 
void Speed(); //�̤��ƽո`�t�� 
void EndView(); //�̫᪺���ݵe�� 

int main()
{
    int over = 0;
    while(over EQU 0)
    {
        Start();  //�}�l 
	
	    PrintSnake();  //�e�X�C���e���öi��C�� 
    
        over = End();  //���� 
    }
    
    clrscr();  //�M�ŵe�� 
    
    EndView();  //�ݤ����ʵe... 
    
    gotoxy(20,10);
    
    printf("Bye Bey  !!          "); 
    
    system("PAUSE");
    
	return 0;
}

void GetTail(int p)
//�p��ثe�D�����ڦ��h��  
{
    int i;
    
    for(i=0 ; i<(p/5) ; i++)
        tail[i] = 1;
}

int KeyIn()
// �ˬd��J���O�W�U���k���@��
{
	int keyIn = 0;
	int rightKey = 0;

	while( rightKey EQU 0 )
	{
		while(!kbhit()) ;

		keyIn = getch();

		if( keyIn EQU 72 || keyIn EQU 75 || 
			keyIn EQU 77 || keyIn EQU 80 )
			/*�@�w�n�O�W�U���k�~����X�j��  */
			rightKey = 1;
	}
	return keyIn; 
}

void Walked()
//�������L���� 
{
    int i = 0;
    
    while(walkX[i] != 0)
        i = i + 1;
    
    walkX[i] = x;
    walkY[i] = y; 
}

void PrintTail()
//�e�X�D������ 
{
    int i = 0;
    int no = 0;
    int j = WALKED-1;
	   
	GetTail(point);
    
    while(walkX[j] EQU 0 )  //�q�᭱�}�l��w�g���L���I 
        j = j - 1;
       
    while(tail[i] EQU 1){  //tail[]�������ڪ��Ӽ� 
        tailX[i] = walkX[j];
        tailY[i] = walkY[j];
        gotoxy(walkX[j],walkY[j]);
        printf("o");
        i = i + 1;
        j = j - 1;
    }  
}
    
void PrintSnake()
//���D�X�ɩμ������,�_�h�|�̷Ӥ�V�s��ø�X�D�����ʭy�� 
{
    int over = 0;  //����P�_ 
    int keyIn = 0;   
    int i = 0;
    int bump = 0;
    
    while( over EQU 0 )
    {
        keyIn = KeyIn();
        while(!kbhit()){
	       move = Move(x,y, keyIn);

	       printf("*");
	       
	       Walked();  //�������L����
	       
           PrintTail(); //�e�X���ڪ��y�� 
	       
	       if(keyIn EQU 72 || keyIn EQU 80 )
	           y = move ;
	       else if(keyIn EQU 75 || keyIn EQU 77 )
	           x = move ;
	                     
	       Play();  //�C���M��  
	        
           if(x > RIGHT || y > DOWN ||  //�X�� 
              x < LEFT  || y < UP     ){
                printf(" �I �� �� ��  !!!!   \n\n\n");
                over = 1;
	            break;
           }
           else if(isBump EQU 1 ){
                printf(" �� �� �� ��  !!!!   \n\n\n");
                over = 1;
	            break;
           }

        }
    }
}

int Move(int x,int y,int way)
//���ʦ�m 
{
    
    if(way EQU 72){   //�V�W 
        y -= Y_SPACE;
        gotoxy(x,y);
        return y;
    }
    else if(way EQU 80){  //�V�U 
        y += Y_SPACE;
        gotoxy(x,y);
        return y;
    }
    else if(way EQU 75){  //�V�� 
        x -= X_SPACE;
        gotoxy(x,y);
        return x;
    }
    else if(way EQU 77){  //�V�k 
        x += X_SPACE;
        gotoxy(x,y);
        return x;
    }
    else
        printf("Imposible !! \n");
}

void Star(int* starX,int* starY,int snakeX,int snakeY,int * point)
//�H���X�{�D�i�H�Y���P�P 
{
    srand(time(NULL));
    
    if( ( *starX EQU 0 && *starY EQU 0 ) ||
        ( snakeX EQU *starX && snakeY EQU *starY) ){  //�p�G�D�٨S�Y��P�P
        *starX = rand()%35 + 4;
        *starY = rand()%15 + 4;
        *point += 5;
        
        if(*starX % 2 EQU 1) //�]���D������V�@�������A�ҥH����X�{��� 
            *starX = *starX + 1;
    }
    
    gotoxy(*starX,*starY);
    printf("+");
    gotoxy(*starX+1,*starY+1);
    printf("%d,%d",*starX,*starY);    
}

void PrintBorder(int point)
//�e�X�~�� 
{
    int i; 
    
    gotoxy(1,1); //�^����I�~�i�H�T�w�e��
    
    printf("�w��Ө�g���D�@�� !!      �ثe���� : %d ��  \n",point);
     
    printf("-----------------------------"  //�W�������u 
            "----------------       ");
    
    printf("\n|\n|\n|\n|\n|\n|\n|\n|\n|\n"    //���䨺���u 
           "|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n");
    
    for(i=3 ; i<21 ; i++){       //�k�䨺���u 
        gotoxy(45,i);
        printf("|");
    }
    
    gotoxy(1,21);
    printf("-----------------------------"  //�U�������u 
            "---------------- \n");
}

void Play()
//�D�n�C���M�� 
{ 
    gotoxy(x+1,y+1);  //�\�b�D���S�U�� 
    //printf("( %d , %d )",x,y);   
	        
	Star(&starX,&starY,x,y,&point);  //�e�X�P�P
	PrintBorder(point);  //�e�X��� 
	
	isBump = IsBumpTail();
	
	Speed();  //�ո`�t�� 
	        
	Sleep(delayTime); //���ydelayTime��
    clrscr();  //�M�ŵe��            
}

int IsBumpTail()
//�O�_�D�Y������� 
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
//�ո`�t��
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
//�}�l�e�� 
{ 
    Restart();  //���s�����k�s�ʧ@ 
    gotoxy(x,y);
    printf("����V��}�l�C��");
}

void Restart()
//���s�}�l�ݧ�����ܼ��k�s 
{
    int i;
    
    delayTime = 150;
    isBump = 0;
    x = 20;  //��� 
    y = 10;
    starX = 0;  //�P�P����m 
    starY = 0;
    move = 0; //�첾
    point = -5; //�o�� 
    for(i=0 ; i<TAIL_NUM ; i = i+1){
        tail[i] = 0; //���ڼƶq 
        tailX[i] = 0; //�������ڪ��y�� 
        tailY[i] = 0;
    }
    
    for(i=0 ; i<WALKED ; i = i+1)
    {
        walkX[i] = 0;  //���L�� 
        walkY[i] = 0;
        walkNext[i] = 0; //���ܧ��ڭn������ 
    }
    
    currentAspect = 0; //�ثe��V   
    clrscr();  //�M�ŵe��
}

int End()
//�����e�� 
{
    printf("     GAME OVER   !!\n\n");
    printf("  �@ �����o���@�G�@%d   ��\n\n",point); 
    
    return IsAgain();
}

void EndView()
//�����]�w�����T�� 
{
    int wait = 3;  //�O�_���X�� 
    
    while( wait > 0)
	{
        gotoxy(7-wait,5-wait);
        
        printf("�˼� %d �� \n",wait);
        Sleep(500); //���y0.5�� 
        clrscr();  //�M�ŵe�� 
        
	    wait = wait - 1;
    }
}

int IsAgain()
/*�O�_�A���@�� */ 
{
    int keyIn = 0;
    int over = 0;
    
    gotoxy(6,8);
    
    printf("�Q�A���@���� ?  ( y or n ) : ");
    
    while(over EQU 0){
        while(!kbhit()) ;
	    keyIn = getch();
    
        if(keyIn EQU 121)
            return 0;  //�~�� 
        else if(keyIn EQU 110)
            return 1;  //���n���F 
        else
            over = 0;
    } 
}
