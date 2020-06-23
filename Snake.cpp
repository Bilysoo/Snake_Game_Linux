#include <stdio.h>
#include <time.h>
#include <vector>
#include <cstdlib>

int gridsize = 20;
typedef enum {
    up,
    down,
    left,
    right
} directionT;
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
	bool collided();
    bool collidedWithApple();
    void createTarget();
	void grow();
    void move();
    void moveupdate(directionT);
    void print();
};

cdT::cdT(){};

Snake::Snake(int length){
    int i;
    this->snake_body_vector = new std::vector <cdT*> ();
	for (i = 1; i <= length; i++){
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

void Snake::createTarget()
{
    srand(time(NULL));
    bool same = true;
    int i = 0;
    while(same)
    {
        this->apple.x = rand() % (gridsize-1) + 2;
        this->apple.y = rand() % (gridsize-1) + 2;
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
    if (this->direction == up){
        coordinate->x = this->head.x;
        coordinate->y = this->head.y - 1;
    }
    else if (this->direction == down){
        coordinate->x = this->head.x;
        coordinate->y = this->head.y + 1;
    }
    else if (this->direction == right){
        coordinate->x = this->head.x + 1;
        coordinate->y = this->head.y;
    }
    else{
        coordinate->x = this->head.x - 1;
        coordinate->y = this->head.y;
    }
    this->snake_body_vector->push_back(coordinate);
    this->head = *(this->snake_body_vector->at(this->snake_body_vector->size()-1));
    this->snake_body_vector->erase(this->snake_body_vector->begin());
}

void Snake::moveupdate(directionT newdirection){
    this->direction = newdirection;
}

bool Snake::collided(){
    for (int i = 0; i < this->snake_body_vector->size()-1; i++)
    {
        if (this->head.x == this->snake_body_vector->at(i)->x
            && this->head.y == this->snake_body_vector->at(i)->y) return true;
    }
	if ((this->head.x == 0 || this->head.y == 0)) return true;
    else if ((this->head.x == gridsize-1 || this->head.y == gridsize-1)) return true;
    else return false;
}

bool Snake::collidedWithApple()
{
    if (this->head.x == this->apple.x
        && this->head.y == this->apple.y) return true;
    else return false;
}

void Snake::grow(){
    cdT* coordinate = new cdT();
    if (this->direction == up){
        coordinate->x = this->head.x;
        coordinate->y = this->head.y - 1;
    }
    else if (this->direction == down){
        coordinate->x = this->head.x;
        coordinate->y = this->head.y + 1;
    }
    else if (this->direction == right){
        coordinate->x = this->head.x + 1;
        coordinate->y = this->head.y;
    }
    else{
        coordinate->x = this->head.x - 1;
        coordinate->y = this->head.y;
    }
    this->snake_body_vector->push_back(coordinate);
    this->head = *(this->snake_body_vector->at(this->snake_body_vector->size()-1));
}

void Snake::print()
{
    int i = 0;//column
    int j = 0;//row
    int v = 0;
    bool found;
    while (j != gridsize-1)
    {
        found = false;
        //reached the end of the grid
        if (i == gridsize)
        {
            printf("\n");
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
                    printf("o");
                    found = true;
                    break;
                }
                else if (i == this->apple.x && j == this->apple.y)
                {
                    printf("A");
                    found = true;
                    break;
                }
                else v++;
            }
        }
        if (!found) printf("-");
        i++;
    }
}

void clrScreen(int stuff){
    printf("Press q to quit\n");
    for (int i = 0; i < stuff; i++){
        printf("\n");
    }
}

int main(void){
    Snake* Fred_The_Snake = new Snake(8);
    Fred_The_Snake->createTarget();
    directionT dir;
    while (!Fred_The_Snake->collided()){
        Fred_The_Snake->print();
        char input;
        scanf("%s", &input);
        if (input == 'w'){
            dir = up;
            Fred_The_Snake->moveupdate(dir);
        }
        else if(input == 'a'){
            dir = left;
            Fred_The_Snake->moveupdate(dir);
        }
        else if(input == 's'){
            dir = down;
            Fred_The_Snake->moveupdate(dir);
        }
        else if(input == 'd'){
            dir = right;
            Fred_The_Snake->moveupdate(dir);
        }
        else{
            printf("Ended\n");
            return 1;
        }
        Fred_The_Snake->move();
        if (Fred_The_Snake->collidedWithApple())
        {
            Fred_The_Snake->grow();
            Fred_The_Snake->createTarget();
        }
        clrScreen(120);
        printf("head   %d    %d\n", Fred_The_Snake->head.x, Fred_The_Snake->head.y);
        printf("apple  %d    %d\n", Fred_The_Snake->apple.x, Fred_The_Snake->apple.y);
        printf("length %d\n", (int)Fred_The_Snake->snake_body_vector->size());
    }
    printf("You died\n");
    return 0;
}