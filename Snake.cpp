#include <stdio.h>
#include <time.h>
#include <vector>
#include <cstdlib>
#include <ncurses.h>
#include <unistd.h>
#include <random>

int gridsize = 30;
int upper = gridsize-4;
int lower = 4;
int gamecount = 0;

//game states (later used as arguments for a state machine)
typedef enum { start, pregame, controls, ingame, stopped, end } stateT;
//the four directions to indicate where the snake is moving 
//made for a 2 dimensional space
typedef enum { up, down, left, right } directionT;

class cdT{
private:
public:
    cdT();
    int x;
    int y;
};

class Snake{
private:
public:
    //the body of the snake is made up of coordinate types.
	Snake(int); //constructor that sets the length of the snake;
	directionT direction;
	cdT head;
	std::vector<cdT*> *snake_body_vector;
    cdT apple;
	bool CollidedIntoWall();
    bool AteApple();
    void createApple();
	void grow();
    void move();
    void changeDirection(directionT);
    /* The print function outputs what would be the screen for the game.
    It works by printing out the grid that the snake moves on, until it
    finds a coordinate in which any part of the snake's body exists.
    If the coordinate of the current place matches the snake's body,
    it prints out the snake with an "oh." */
    void print();
    int getScore();
};

cdT::cdT(){};

Snake::Snake(int length)
{
    int i;
    this->snake_body_vector = new std::vector <cdT*> ();
	for (i = 1; i <= length; i++)
    {
        cdT* coordinate = new cdT();
		coordinate->x = i;
		coordinate->y = 1;
		this->snake_body_vector->push_back(coordinate);
	}
	//default direction for the snake is going to the right, which is why when constructing a snake, 
	//we start with the assumption that the snake is going to the right.
	this->direction = right;
	this->head = *(this->snake_body_vector->at(this->snake_body_vector->size()-1));
}

void Snake::createApple()
{
    srand(time(NULL));
    bool same = true;
    int i = 0;
    while(same)
    {
        this->apple.x = (rand() % (upper - lower + 1)) + lower;
        this->apple.y = (rand() % (upper - lower + 1)) + lower;
        for (i = 0; i < this->snake_body_vector->size(); i++)
        {
            if (this->snake_body_vector->at(i)->x == this->apple.x
                && this->snake_body_vector->at(i)->y == this->apple.y)
            {
                i = 0;
                break;
            }
        }
        if (i == this->snake_body_vector->size())
        {
            same = false;
        }
    }
}

void Snake::move(){
	cdT* coordinate = new cdT();
    switch(this->direction)
    {
        case up:
            coordinate->x = this->head.x;
            coordinate->y = this->head.y - 1;
            break;
        case down:
            coordinate->x = this->head.x;
            coordinate->y = this->head.y + 1;
            break;
        case right:
            coordinate->x = this->head.x + 1;
            coordinate->y = this->head.y;
            break;
        case left:
            coordinate->x = this->head.x - 1;
            coordinate->y = this->head.y;
            break;
    }
    this->snake_body_vector->push_back(coordinate);
    this->head = *(this->snake_body_vector->at(this->snake_body_vector->size()-1));
    this->snake_body_vector->erase(this->snake_body_vector->begin());
}

void Snake::changeDirection(directionT newdirection)
{
    this->direction = newdirection;
}

bool Snake::CollidedIntoWall()
{
    for (int i = 0; i < this->snake_body_vector->size()-1; i++)
    {
        if (this->head.x == this->snake_body_vector->at(i)->x
            && this->head.y == this->snake_body_vector->at(i)->y) return true;
    }
	if ((this->head.x == 0 || this->head.y == 0)) return true;
    else if ((this->head.x == gridsize-1 || this->head.y == gridsize-1)) return true;
    else return false;
}

bool Snake::AteApple()
{
    if (this->head.y == this->apple.y && this->head.x == this->apple.x) return true;
    else return false;
}

void Snake::grow()
{
    cdT* coordinate = new cdT();
    switch(this->direction)
    {
        case up:
            coordinate->x = this->head.x;
            coordinate->y = this->head.y - 1;
            break;
        case down:
            coordinate->x = this->head.x;
            coordinate->y = this->head.y + 1;
            break;
        case right:
            coordinate->x = this->head.x + 1;
            coordinate->y = this->head.y;
            break;
        case left:
            coordinate->x = this->head.x - 1;
            coordinate->y = this->head.y;
            break;
    }
    this->snake_body_vector->push_back(coordinate);
    this->head = *(this->snake_body_vector->at(this->snake_body_vector->size()-1));
}

void Snake::print()
{
    int i = 0;//column
    int j = 0;//row
    int v = 0;//index of the vector
    bool found;//flag for body of the snake
    while (j != gridsize-1)
    {
        found = false;
        //reached the end of the grid
        if (i == gridsize-1)
        {
            printf("\n\r");
            j++;
            i = 0;
        }
        else
        {
            v = 0;
            while (v < this->snake_body_vector->size())
            {
                if (i == this->snake_body_vector->at(v)->x 
                    && j == this->snake_body_vector->at(v)->y)
                {
                    /* If the current coordinate if where the head
                       exists, then we print the big-oh instead to
                       indicate the head of the snake, separate
                       from the rest of the snake's body */
                    if (this->head.x == i && this->head.y == j)
                    {
                        printf("@ ");
                    }
                    /* If the current coordinate is not a head, 
                    then print a small-oh in order to indicate
                    that it's a body of the snake. */
                    else printf("o ");
                    found = true;
                    break;
                }
                else if (i == this->apple.x && j == this->apple.y)
                {
                    printf("A ");
                    found = true;
                    break;
                }
                else v++;
            }
        }
        /*If the coordinate neither has the body of the snake
        nor it is the first line, print the a dash in order
        to indicate that it's a grid not the snake. */
        if (!found && j != 0 && i != 0) printf("- ");
        i++;
    }
}

int Snake::getScore()
{
    return (int)this->snake_body_vector->size();
}

void clrScreen(int stuff)
{
    printf("Press q to quit\n");
    for (int i = 0; i < stuff; i++)
    {
        printf("\n");
    }
    printf("\r");
}

void printgamename()
{
    printf("           OOOOOOOO0  O       O  OOOOOOOOO\n\r");
    printf("               O      O       O  O        \n\r");
    printf("               O      OOOOOOOOO  OOOOOOOOO\n\r");
    printf("               O      O       O  O        \n\r");
    printf("               O      O       O  OOOOOOOOO\n\r");
    printf("\n\r");
    printf("     OOOOOOOO  O    O      O      O   O  OOOOOOO\n\r");
    printf("     O         OO   O     O O     O  O   O      \n\r");
    printf("     OOOOOOOO  O O  O    O   O    O O    OOOOOOO\n\r");
    printf("            O  O  O O   O     O   O  O   O      \n\r");
    printf("     OOOOOOOO  O   OO  O       O  O   O  OOOOOOO\n\r");
    printf("\n\r\n\r");
    printf("                    By John Jung\n\r");
    printf("\n\r\n\r\n\r\n\r");
}

stateT controlsMenu()
{
    clrScreen(120);
    printf("    Controls:\n\r");
    printf("    UP:    w\n\r");
    printf("    DOWN:  s\n\r");
    printf("    LEFT:  a\n\r");
    printf("    RIGHT: d\n\r");
    printf("    QUIT:  q\n\r");
    printf("\n\r\n\r");
    printf("    Press 1 to return to menu\n\r");
    char input;
    input = getchar();
    while (true)
    {
        switch(input)
        {
            case '1':
                return start;
            default:
                input = getchar();
                break;
        }    
    }
}

stateT initGame()
{
    clrScreen(120);
    printgamename();
    printf("                Main Menu:\n\r");
    printf("    Start Game       Quit       Controls\n\r");
    printf("      Press 1       Press 2      Press 3\n\r");
    char input;
    input = getchar();
    while (true)
    {
        switch(input)
        {
            case '1':
                return pregame;
            case '2':
                return end;
            case '3':
                return controls;
            default:
            	input = getchar();
            	break;
        }
    }
}

stateT initPauseScreen()
{
    printf("                   Pause Menu:\n\r");
    printf("    Continue        Quit          Return To Start\n\r");
    printf("    Press 1        Press 2            Press 3\n\r");

    char input;
    input = getch();
    while (true)
    {
        switch(input)
        {
        case '1':
            return ingame;
        case '2':
            return end;
        case '3':
            return start;
        default:
            input = getch();
            break;
        }    
    }
    
}

int main(void)
{
    stateT gamestate = start;
    Snake* Fred_The_Snake = new Snake(8);
    cbreak();
    initscr();
    while (true)
    {
        switch(gamestate)
        {
            case start:
            {
                if (gamecount > 0) Fred_The_Snake = new Snake(8);
                gamestate = initGame();
                gamecount = 1;
                break;
            }

            case controls:
            {
                gamestate = controlsMenu();
                break;
            }

            case pregame:
            {
                /* Create the snake here with the default starting length of 8. */
                Fred_The_Snake->createApple();
                Fred_The_Snake->print();
                gamestate = ingame;
                break;
            }

            case ingame:
            {
                directionT dir;
                nodelay(stdscr, TRUE);
                while (!Fred_The_Snake->CollidedIntoWall())
                {
                    Fred_The_Snake->print();
                    char input;
                    usleep(100000);
                    if ((input = getch()) != ERR)
                    {
                        /* Here, I devised cases for keyboard inputs
                        For instance, the controls coming from the user
                        include w, a, s, d and they denote the direction
                        that the snake will travel after the input has 
                        been received. */
                        switch(input)
                        {
                            case 'w':
                                dir = up;
                                break;
                            case 'a':
                                dir = left;
                                break;
                            case 's':
                                dir = down;
                                break;
                            case 'd':
                                dir = right;
                                break;
                            case 'q': //press q to quit.
                                gamestate = end;
                                break;
                            case 'p':
                            {
                                gamestate = stopped;
                                break;
                            }
                        }
                        //if the user chooses to end the game, then exit the while loop
                        if (gamestate == end || gamestate == stopped) break;
                        Fred_The_Snake->changeDirection(dir);
                    }
                    Fred_The_Snake->move();
                    if (Fred_The_Snake->AteApple())
                    {
                        Fred_The_Snake->grow();
                        Fred_The_Snake->createApple();
                    }
                    clrScreen(120);
                    printf("\n\r");
                    printf("head   %d    %d\n\r", Fred_The_Snake->head.x, Fred_The_Snake->head.y);
                    printf("apple  %d    %d\n\r", Fred_The_Snake->apple.x, Fred_The_Snake->apple.y);
                    printf("length %d\n\r", (int)Fred_The_Snake->snake_body_vector->size());
                }
                if (gamestate != end && gamestate != stopped)
                {
                	clrScreen(120);
                    printf("Snake died\n\r");
                    printf("Score: %d\n\r", Fred_The_Snake->getScore());
                    gamestate = start;
                }
                nodelay(stdscr, FALSE);
                break;
            }

            case stopped:
            {
                nodelay(stdscr, FALSE);
                gamestate = initPauseScreen();
                break;
            }

            case end:
            {
                endwin();
                printf("Ended\n\r");
                printf("Score: %d\n\r", Fred_The_Snake->getScore());
                return 0;   
            }
        }
    }
    printf("Game Error: Halt\n\r");
    return 1;
}