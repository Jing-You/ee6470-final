#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <fstream>
#include <cassert>
using namespace std;

extern "C" int get_id();
extern "C" {
  #include "acPthread.h"
}

struct point
{
    int x, y;
    point(int a, int b):x(a), y(b){};
    point(){};
   	point operator = (const point &a) {
   		point p;
   		p.x = a.x;
   		p.y = a.y;
   		return p;
   	}
};

const int UP = 1;
const int DOWN = 2;
const int RIGHT = 3;
const int LEFT = 4;

volatile mutex_t *mutex = (volatile mutex_t *)		0x52ff0000; // 4-byte: 0x52ff0000 - 0x52ff0003
volatile barrier_t *barr = (volatile barrier_t *)	0x52ff0004; // 16-byte: 0x52ff0004 - 0x52ff0013
volatile int *w = (volatile int *) 					0x52ff0014; // 4-byte: 0x52ff0014 - 0x52ff0017;
volatile int *h = (volatile int *) 					0x52ff0018; // 4-byte: 0x52ff0018 - 0x52ff001b;
volatile char *maze = (volatile char *) 			0x52ff001c; // 0x52ff001c - 0x52ff001c;
volatile int *Q_x = (volatile int*) 				0x54000001; // 0x5400001 - 0x5500001;
volatile int *Q_y = (volatile int*) 				0x54800001; // 0x5400001 - 0x5500001;
volatile char *his = (volatile char* )				0x54f00001;
volatile bool *idles = (volatile bool *) 			0x59000000;
volatile int *start = (volatile int *) 				0x59000004; // 4-byte: 0x52ff0014 - 0x52ff0017;
volatile int *last = (volatile int *)  				0x59000008; // 4-byte: 0x52ff0018 - 0x52ff001b;
volatile int *_q_size = (volatile int *) 			0x5900000c;

const int Q_MAXSIZE = 30000;

bool bfs();
bool is_valid(const int x, const int y);
void read_maze_map();
void push(int, int);
void pop();
point front();
int size();
void show_result();
int main() {
    int PROCESSORS = 4;
    barrier_init(barr,PROCESSORS);
	mutex_init(mutex, NULL);
	*start = 0;
	*last = 0;
	*_q_size = 0;

	if (get_id() == 1) {
	    read_maze_map();
	    push(1, 1);
	    *(his + 1 * (*w) + 1) = 1;
	    printf("first %d size = %d\n", front().x, size());
	}
    barrier(barr);
	cout << "----start bfs -----\n";
	bfs();
    barrier(barr);
    // if (get_id() == 2) {
    // 	show_result();
    // }
    return 0;
}

bool is_valid(const int x, const int y) {
    if (x < 0 || y < 0 || x >= *h || y >= *w) {
        return false;
    }
    return true;
}

bool bfs() {
    int nextx, nexty;
    while (1) {
		mutex_lock(mutex);  
        if (size()) {
	        nextx = front().x;
	        nexty = front().y;
        	idles[get_id()] = false;
	        pop();
        }
        else {
        	idles[get_id()] = true;
        	nextx = -1;
        	nexty = -1;
        }
		mutex_unlock(mutex); 
        if (nextx == *h -2 && nexty == *w -2) {
            idles[0] = true;
            idles[1] = true;
            idles[2] = true;
            idles[3] = true;
        }
        barrier(barr);
        if (idles[0] && idles[1] && idles[2] && idles[3]) {
            return true;
        }
        // else if (idles[0] == false && idles[1] == false &&idles[2] == false && idles[3] == false) {
        // 	cout << "full working\n";
        // }
        if (is_valid(nextx + 1, nexty) && !*(his +  (*w) * (nextx+1)  + nexty)  && *(maze + (nextx+1) * (*w) + nexty) == ' ') {
			mutex_lock(mutex);   
            push(nextx + 1, nexty);
            *(his + (nextx+1) * (*w) + nexty) = DOWN;
			mutex_unlock(mutex); 
        }
        if (is_valid(nextx, nexty + 1) && !*(his +  (*w) * (nextx) + nexty + 1) && *(maze + (nextx) * (*w) + nexty + 1) == ' ') {
			mutex_lock(mutex);  
            push(nextx, nexty + 1);
            *(his + (nextx) * (*w) + nexty + 1) = RIGHT;
			mutex_unlock(mutex); 
        }
        if (is_valid(nextx - 1, nexty) && !*(his + (*w) * (nextx-1) + nexty)&& *(maze + (nextx-1) * (*w) + nexty) == ' ') {
			mutex_lock(mutex);  
            push(nextx - 1, nexty);
            *(his + (nextx-1) * (*w) + nexty)= UP;
			mutex_unlock(mutex); 
        }
        if (is_valid(nextx, nexty - 1) && !*(his +  (*w) * (nextx) + nexty - 1)&& *(maze + (nextx) * (*w) + nexty - 1) == ' ') {
			mutex_lock(mutex);  
            push(nextx, nexty - 1);
            *(his + (nextx) * (*w) + nexty - 1) = LEFT;
			mutex_unlock(mutex); 
        }
    }
    return 0;
}
void read_maze_map() {
	cout << "my id" << get_id() << endl;
    ifstream mazefile ("mazemap.txt");
    int t_w, t_h;
    char c;
    mazefile >> t_w >> t_h;
    *w = 2*t_w+1;
    *h = 2*t_h+1;
    // cout << *w <<  ' ' << *h << endl;
    for(int i=0; i < *h; i++)
        for (int j=0; j< *w; j++)
        	*(his+i* (*w)+j)= 0;
    for (int i=0; i< *h; i=i+1) {
        for (int j=0; j< *w; j=j+1) {
            mazefile.get(c);
            *(maze+i* (*w)+j) = c;
            if (*(maze+i* (*w)+j) == '\n')
                j--; 
            // else
            //     cout << *(maze+i* (*w)+j) ;
        }
        // cout << endl;
    }
}


void push(int x, int y) {
	assert(*_q_size + 1 < Q_MAXSIZE);
	*(Q_x + *last) = x;
	*(Q_y + *last) = y;
	*last = (*last + 1) % Q_MAXSIZE;
	*_q_size += 1;
}

void pop() {
	assert(*_q_size > 0);
	*start = (*start + 1) % Q_MAXSIZE;
	*_q_size -= 1;
}

point front() {
	point p;
	p.x = Q_x[*start];
	p.y = Q_y[*start];
	return p;
}

int size() {
	return (int) *_q_size;
}

void show_result() {
	vector< vector<string> >result(*h, vector<string> (*w));
	for(int i=0; i<*h; i++){
		for (int j=0;j<*w;j++) {
			if (i == 1 && j == 1)
				printf("S");
			else if (*(maze+i* (*w)+j) != ' ')
				printf("%c", *(maze+i* (*w)+j));
			else if (*(his+i* (*w)+j) == UP)
				printf("↑");
			else if (*(his+i* (*w)+j) == DOWN)
				printf("↓");
			else if (*(his+i* (*w)+j) == RIGHT)
				printf("→");
			else if (*(his+i* (*w)+j) == LEFT)
				printf("←");
			else
				printf(" ");
		}
		printf("\n");
	}
}