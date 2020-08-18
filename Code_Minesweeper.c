#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <conio.h>
#include<windows.h>
int side=9,mines=10;
void initialise(char realboard[][9],char myboard[][9])
{
	//intiating the random number generator so that same config doesn't arises
	srand(time(NULL));
	//assigning all cells mines free
	int i,j;
	for(i=0;i<side;i++)
	{
		for(j=0;j<side;j++)
			myboard[i][j]=realboard[i][j]='-';
	}
	return;
}
//Function To place mines randomly
void placemines(int mine[][2],char realboard[][9])
{
	int *mark;
	mark=(int *)calloc(82,sizeof(int));
	//place mines randomly
	int i;
	for(i=0;i<mines;)
	{
		int random=rand()%(side*side);
		int xf=random/side;
		int yf=random%side;
		// if there is no mine there, add one
		if(mark[random]==0)
		{
			//mine coordinates
			mine[i][0]=xf;
			mine[i][1]=yf;
			// place mine
			realboard[mine[i][0]][mine[i][1]]='*';
			mark[random]=1;
			i++;
		}
	}
	return;
}
//function to print board
void printboard(char myboard[][9])
{

	int i,j;
	printf("\t\t\t\t    ");
	for(i=0;i<side;i++)
		printf("%d ",i);
	printf("\n\n");
	for(i=0;i<side;i++)
	{
		printf("\t\t\t\t%d|  ",i);
		for(j=0;j<side;j++)
			printf("%c ",myboard[i][j]);
		printf("\n");
	}
}
// Input User Moves
void makemove(int *x,int *y)
{
	printf("Enter Your Move: ");
	scanf("%d %d",x,y);
	system("cls");

}
//Function to check validity of cell
int isvalid(int row,int col)
{
	if((row>=0 && row<side) && (col>=0 && col<side))
        return 1;
    else
        return 0;
}
//function to check for mine
int ismine(int row,int col,char board[][9])
{
	if(board[row][col]=='*')
		return 1;
	else
		return 0;
}

void replacemine(int row,int col,char realboard[][9])
{
	int i,j;
    for(i=0;i<side;i++)
    {
        for(j=0;j<side;j++)
        {
            if(realboard[i][j]!='*')/* Find the first location in the board
                 which is not having a mine and put a mine there.*/
            {
                realboard[i][j]='*';
                realboard[row][col]='-';
                break;
            }
        }
    }
}
// Count mines around a cell

int countmines(int row,int col,char realboard[][9])
{
	int i;
	int count=0;
	/* coordinates of all 8 adjacent cell to choosen cell
	(row-1,col),(row+1,col),(row,col+1),(row,col-1),(row-1,col+1),(row-1,col-1),(row+1,col+1)(row+1,col-1)*/
            if(isvalid(row-1,col)==1)
			{
				if(ismine(row-1,col,realboard)==1)
					count++;
			}
			if(isvalid(row+1,col)==1)
			{
				if(ismine(row+1,col,realboard)==1)
					count++;
			}
			if(isvalid(row,col+1)==1)
			{
				if(ismine(row,col+1,realboard)==1)
					count++;
			}
			if(isvalid(row,col-1)==1)
			{
				if(ismine(row,col-1,realboard)==1)
					count++;
			}
			if(isvalid(row-1,col+1)==1)
			{
				if(ismine(row-1,col+1,realboard)==1)
					count++;
			}
			if(isvalid(row-1,col-1)==1)
			{
				if(ismine(row-1,col-1,realboard)==1)
					count++;
			}
			if(isvalid(row+1,col+1)==1)
			{
				if(ismine(row+1,col+1,realboard)==1)
					count++;
			}
			if(isvalid(row+1,col-1)==1)
			{
				if(ismine(row+1,col-1,realboard)==1)
					count++;
			}
	return(count);
}
//Function to Play Game
int playminesweeper(char myboard[][9],char realboard[][9],int mine[][2],int row,int col,int *movesremain)
{
	// base case
	if(myboard[row][col]!='-')//This function is used to  store count of nearby cells in myboard so if the cell already have a count stored then this function do not need to work..
		return 0;
	int i,j;
	//check for mine
	if(realboard[row][col]=='*')
	{
		myboard[row][col]='*';
		for(i=0;i<mines;i++)
			myboard[mine[i][0]][mine[i][1]]='*';
		printboard(myboard);
		printf("\n\n");
		printf("\t\t\t\t        You Lost\n\n\n");
		return 1;
	}
	else
	{
		//calculate adjacent mines
		int count=countmines(row,col,realboard);
		(*movesremain)--;
		myboard[row][col]=count+'0';
		//recursive function to check for adjacent cells
		if(count==0)
		{
			if(isvalid(row-1,col)==1)
			{
					playminesweeper(myboard,realboard,mine,row-1,col,movesremain);
			}
			if(isvalid(row+1,col)==1)
			{
					playminesweeper(myboard,realboard,mine,row+1,col,movesremain);
			}
			if(isvalid(row,col+1)==1)
			{
					playminesweeper(myboard,realboard,mine,row,col+1,movesremain);
			}
			if(isvalid(row,col-1)==1)
			{
					playminesweeper(myboard,realboard,mine,row,col-1,movesremain);
			}
			if(isvalid(row-1,col+1)==1)
			{
					playminesweeper(myboard,realboard,mine,row-1,col+1,movesremain);
			}
			if(isvalid(row-1,col-1)==1)
			{
					playminesweeper(myboard,realboard,mine,row-1,col-1,movesremain);
			}
			if(isvalid(row+1,col+1)==1)
			{
					playminesweeper(myboard,realboard,mine,row+1,col+1,movesremain);
			}
			if(isvalid(row+1,col-1)==1)
			{
					playminesweeper(myboard,realboard,mine,row+1,col-1,movesremain);
			}
		}
		return 0;
	}
}
void playgame()
{
	int gameover=0;// initialising game as not over i.e. 0
	char realboard[9][9],myboard[9][9];
	int movesremain=side*side-mines;
	int x,y;//coordinates of mines
	// initialise the game
	int mine[mines][2];
	initialise(realboard,myboard);
	//placing mines randomly
	placemines(mine,realboard);
	//To see where are Mines for First Move
	//printboard(realboard);
    int current_move_index=0;
	while(gameover==0)
{
		printf("Current Status of Game: \n");
		printboard(myboard);
		makemove(&x,&y);

		if(current_move_index==0)
		{
		    if(ismine(x,y,realboard)==1)
            {
                replacemine(x,y,realboard);
            }
		}
		current_move_index++;

		gameover=playminesweeper(myboard,realboard,mine,x,y,&movesremain);
		if(gameover==0 && movesremain==0)
		{
			printf("\n\n");
		printf("\t\t\t\t           You Won\n\n\n");
			gameover=1;
		}
}
}
void fordelay(int j)
{
    int i,k;
    for(i=0;i<j;i++)
    {
        k=i;
    }
}
int main(){
    printf("Welcome To Minesweeper Game\n\nPress any Key to Play:");
    _getch();
    int i;
    system("cls");
    int choice=1;
    while(choice==1)
    {
    printf("\n\n\n\n\n\t\t\t\t\t");
        system("color 9");
        char a=177,b=178;
        printf("Loading.....");
        printf("\n\n");
        printf("\t\t\t\t\t");
        for(i=0;i<30;i++)
        {
        	printf("%c",a);
		}
		printf("\r");
		printf("\t\t\t\t\t");
		for(i=0;i<30;i++)
		{
			fordelay(39999977);
			printf("%c",b);

		}
		system("cls");
	playgame();
	printf(" If you want to play again press 1 else 0:");
	scanf("%d",&choice);
	system("cls");
    }
	return 0;
}
