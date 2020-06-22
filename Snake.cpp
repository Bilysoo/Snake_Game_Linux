#include <stdio.h>
#include <iostream>
#include <vector>

//using namespace std;

int gridsize = 40;
typedef enum {
    up,
    down,
    left,
    right
} directionT;
class cdT{
private:
protected:
public:
    cdT();
    int x;
    int y;
};
class Snake{
private:
protected:
public:
    //the body of the snake if made up of coordinate types.
	Snake(int); //constructor that sets the length of the snake;
	directionT direction;
	cdT head;
	std::vector<cdT*> *snake_body_vector;
	bool collided();
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
        std::vector<cdT*>::iterator it = this->snake_body_vector->end();
        cdT* coordinate = new cdT();
		coordinate->x = i;
		coordinate->y = 1;
		this->snake_body_vector->push_back(coordinate);
	}
	this->direction = right;
	this->head = *(this->snake_body_vector->at(this->snake_body_vector->size()-1));
}

void Snake::move(){
    if (this->direction == up){
        //for (int i = 0; i < this->snake_body_vector->size(); i++){
        cdT* coordinate = new cdT();
        coordinate->x = this->head.x;
        coordinate->y = this->head.y - 1;
        this->snake_body_vector->push_back(coordinate);
        //}
    }
    else if (this->direction == down){
        cdT* coordinate = new cdT();
        coordinate->x = this->head.x;
        coordinate->y = this->head.y + 1;
        this->snake_body_vector->push_back(coordinate);
    }
    else if (this->direction == right){
        cdT* coordinate = new cdT();
        coordinate->x = this->head.x + 1;
        coordinate->y = this->head.y;
        this->snake_body_vector->push_back(coordinate);
    }
    else{
        //for (int i = 0; i < this->snake_body_vector->size(); i++){
        cdT* coordinate = new cdT();
        coordinate->x = this->head.x - 1;
        coordinate->y = this->head.y;
        this->snake_body_vector->push_back(coordinate);
            //this->snake_body_vector->at(this->snake_body_vector->size()-1)->x += this->direction;
        //}
    }
    this->head = *(this->snake_body_vector->at(this->snake_body_vector->size()-1));
    this->snake_body_vector->erase(this->snake_body_vector->begin());
}

void Snake::moveupdate(directionT newdirection){
    this->direction = newdirection;
}

bool Snake::collided(){
	if ((this->head.x == 0 || this->head.y == 0)) return true;
    else if ((this->head.x == gridsize-1 || this->head.y == gridsize-1)) return true;
	else return false;
}

void Snake::grow(){
    cdT* newcdr;
    if (this->direction == up || this->direction == down){
    newcdr->y = this->snake_body_vector->at(this->snake_body_vector->size()-1)->y + this->direction;
    }
    else if (this->direction == left || this->direction == right){
    newcdr->x = this->snake_body_vector->at(this->snake_body_vector->size()-1)->x + this->direction;
    }
	this->snake_body_vector->insert(this->snake_body_vector->end()-1,newcdr);
}

void Snake::print(){
    int i = 0;//column
    int j = 0;//row
    while (j != gridsize-1){
        //reached the end of the grid
        if (i == gridsize){
            printf("\n");
            j++;
            i = 0;
        }
        else if (i != gridsize){
            for (int v = 0; v < this->snake_body_vector->size(); v++){
                if (i == this->snake_body_vector->at(v)->x && j == this->snake_body_vector->at(v)->y){
                    printf("o");
                }
            }
        }
        else {
            printf("-");
        }
        i++;
        /*else if(i == this->snake_body_vector->at(k)->x && j == this->snake_body_vector->at(k)->y){
            printf("o");
            if (k < this->snake_body_vector->size()-1) k++;
        }*/
    }
}

void clrScreen(int stuff){
    for (int i = 0; i < stuff; i++){
        printf("\n");
    }
}

int main(void){
    Snake* oneBoi = new Snake(4);
    directionT dir;
    while (!oneBoi->collided()){
        oneBoi->print();
        char input;
        scanf("%s", &input);
        if (input == 'w'){
            dir = up;
            oneBoi->moveupdate(dir);
        }
        else if(input == 'a'){
            dir = left;
            oneBoi->moveupdate(dir);
        }
        else if(input == 's'){
            dir = down;
            oneBoi->moveupdate(dir);
        }
        else{
            dir = right;
            oneBoi->moveupdate(dir);
        }
        oneBoi->move();
        clrScreen(120);
        printf("\n");
    }
    return 0;
}