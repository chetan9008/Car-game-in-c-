#include<iostream>
#include<cstdlib>
#include<conio.h>
#include<dos.h>
#include<windows.h>
#include<time.h>

//marcos

#define SCREEN_WIDTH 90
#define SCREEN_HEIGHT 26
#define WIN_WIDTH 63

using namespace std;


//global variables 
 int car[4][3] = {4, 4, 4,
                     4, 4, 4,
                     4, 4, 4,
                     4, 4, 4};
                     
                 

int carposition = WIN_WIDTH/2;
int score = 0;
int enemyY[3];
int enemyX[3];
int enemyFlag[3];                     


//console handling variables and funcions 
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;


void color()
{
	SetConsoleTextAttribute(console,3);
}

void setcursor(bool visible, DWORD size)
{
    if (size == 0)
        size = 20;

    CONSOLE_CURSOR_INFO lpCursor;
    lpCursor.bVisible = visible;
    lpCursor.dwSize = size;
    SetConsoleCursorInfo(console, &lpCursor);
}

void gotoxy(int x,int y)
{
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console,CursorPosition);
}
//console handling variables and funcions 

// draw border for game 

void drawBorder()
{
	for(int i=0;i<SCREEN_HEIGHT;i++)
	{
		for(int j=0;j<17;j++)
		{
			gotoxy(j,i);
			cout << "±";
			gotoxy(WIN_WIDTH-j,i);
			cout << "±";
		}
	}
	for(int i=0;i<SCREEN_HEIGHT;i++)
	{
		gotoxy(SCREEN_WIDTH,i);
		cout << "±";
	}
}

void updateScore()
{
	SetConsoleTextAttribute(console,3);
	gotoxy(WIN_WIDTH+7,5);
	cout << "Score : " << score << endl;
}

void drawCar()
{
	SetConsoleTextAttribute(console,2);
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<4;j++)
		{
			gotoxy(j+carposition,i+22);
			cout << char(car[i][j]);
		}
	}
}

void eraseCar()
{
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<4;j++)
		{
			gotoxy(j+carposition,i+22);
			cout << " ";
		}
	}
}

void drawEnemy(int x)
{
	SetConsoleTextAttribute(console,4);
	if(enemyFlag[x] == true)
	{
		gotoxy(enemyX[x],enemyY[x]);
		cout << "++++";
		gotoxy(enemyX[x],enemyY[x]+1);
		cout << " ++ ";
		gotoxy(enemyX[x],enemyY[x]+2);
		cout << "++++";
		gotoxy(enemyX[x],enemyY[x]+3);
		cout << " ++ ";
	}
}

void eraseEnemy(int x)
{
	if(enemyFlag[x] == true)
	{
		gotoxy(enemyX[x],enemyY[x]);
		cout << "    ";
		gotoxy(enemyX[x],enemyY[x]+1);
		cout << "    ";
		gotoxy(enemyX[x],enemyY[x]+2);
		cout << "    ";
		gotoxy(enemyX[x],enemyY[x]+3);
		cout << "    ";
	}
}
void genEnemy(int x)
{
//    enemyX[ind] = 17 + rand() % (33);
	enemyX[x] = 17 + rand() % (40 -17 +1);
}

void resetEnemy(int x)
{
	eraseEnemy(x);
	enemyY[x] = 1;
	genEnemy(x);
}

	int collision()
		{
			if(enemyY[0] + 4 >= 23)
			{
				if(enemyX[0] + 4 - carposition >= -1 && enemyX[0] + 4 -carposition < 10)
				{
					return 1;
				}
			}
			return 0;
		}

void gameOver()
{
	SetConsoleTextAttribute(console,4);
	system("cls");
	gotoxy(20,1);
	cout << "-----------------------------------------------------------------------------" << endl;
	gotoxy(20,2);
	cout << "-----------------------------------------------------------------------------" << endl;
	gotoxy(20,3);
	cout << "--------------------------------GAMEOVER-------------------------------------" << endl;
	gotoxy(20,4);
	cout << "-----------------------------------------------------------------------------" << endl;
	gotoxy(20,5);
	cout << "-----------------------------------------------------------------------------" << endl;
	gotoxy(20,6);
	cout << "-----------------------------------------------------------------------------" << endl;
	gotoxy(42,8);
	cout << "Press any key to go back to menu" << endl;
	SetConsoleTextAttribute(console,3);
	getch();
}


//important function of program 

void play()
{
	carposition =  (WIN_WIDTH/2) - 1;
	score = 0;
	enemyFlag[0] = 1;
	enemyFlag[1] = 0;
	enemyY[0] = enemyY[1]  = 1;
	
	system("cls");
	drawBorder();
	updateScore();
	genEnemy(0);
	genEnemy(1);
	
	gotoxy(WIN_WIDTH+7,3);
	cout << "Car game" << endl;
	gotoxy(WIN_WIDTH+7,4);
	cout << "----------" << endl;
	gotoxy(WIN_WIDTH+7,6);
	cout << "----------" << endl;
	gotoxy(WIN_WIDTH+7,13);
	cout << "Controls" << endl;	
	gotoxy(WIN_WIDTH+7,14);
	cout << "--------" << endl;
	gotoxy(WIN_WIDTH+5,15);
	cout << "A Key - Left" << endl;
	gotoxy(WIN_WIDTH+5,16);
	cout << "D Key - Right" << endl;
	
	gotoxy(24,10);
	cout << "Press any key to start" << endl;
	getch();
	gotoxy(24,10);
	cout << "                      " << endl;
	while(1)
	{
		if(kbhit())
		{
			char ch = getch();
			if(ch == 'a' || ch == 'A')
			{
				if(carposition > 20)
				{
					carposition -= 4;
				}
			}
			if(ch == 'd' || ch == 'D')
			{
				if(carposition < 40)
				{
					carposition += 4;
				}
			}
			if(ch == 27)
			{
				break;
			}
		}	
		
		drawCar();
		drawEnemy(0);
		drawEnemy(1);
		
		if(collision() == 1)
		{
			gameOver();
			return;
		}
		Sleep(20);
		eraseCar();
		eraseEnemy(0);
		eraseEnemy(1);
		
		if(enemyY[0] == 10)
		{
			if(enemyFlag[1]==0)
			{
				enemyFlag[1] = 1;
			}
		}
		
		if(enemyFlag[0] == 1)
		{
			enemyY[0] += 1;
		}
		if(enemyFlag[1] == 1)
		{
			enemyY[1]  += 1;
		}
		if(enemyY[0] > SCREEN_HEIGHT - 4)
		{
			resetEnemy(0);
			score++;
			updateScore();
		}
		if(enemyY[1] > SCREEN_HEIGHT - 4)
		{
			resetEnemy(1);
			score++;
			updateScore();
		}	
	}
}

//write insturctions 

void instructions()
{
	system("cls");
	gotoxy(25,1);
	cout << "-----------INSTRUCIONS---------------" << endl;
	gotoxy(25,4);
	cout << "Avoid cars for moving left or right"<< endl;
	gotoxy(25,6);
	cout << "Press 'a' to move left " << endl;
	gotoxy(25,7);
	cout << "Press 'd' to move right" << endl;
	gotoxy(25,8);
	cout << "Press 'escape' to exit " << endl;
	gotoxy(25,10);
	cout << "Press any key to go back" << endl;
	getch();
}


//main function

int main()
{
	color();
	setcursor(0,0);
    srand((unsigned)time(NULL));
    
    
    while(1)
    {
    system("cls");
	gotoxy(25,6);
	cout << "------------------------" << endl;
	gotoxy(25,7);
	cout << "|        Car game       |"<< endl;
	gotoxy(25,8);
	cout << "------------------------" << endl;
	gotoxy(25,10);
	cout  << "1. START GAME " << endl;
	gotoxy(25,11);
	cout << "2. INSTRUCTIONS" << endl;
	gotoxy(25,12);
	cout << "3. QUIT " << endl;
	gotoxy(25,14);
	cout << "Select option : " << endl;	
	
			char ch ;
			ch = getch();
			if(ch == '1')
			{
				play();
			}
			else
			if(ch == '2')
			{
				instructions();
			}
			else
			if( ch == '3')
			{
				exit(0);
			}
		    	
	}
	
	
	return 0;
}
