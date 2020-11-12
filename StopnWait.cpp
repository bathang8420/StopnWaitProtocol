#include <stdio.h>
#include <conio.h>
#include <graphics.h>
#include <stdlib.h>
//#include <dos.h>
#include <time.h>
#define RTT 5
#define TIMEOUT 9
#define N 5

unsigned long begTime;
int count; //chi so goi
int key, r1, r2;

void bong(int x, int y, int r, int mau) {
	setcolor(mau);
	setfillstyle(1, mau);
	pieslice(x, y, 0, 360, r);
}

void veHinh() {
	setcolor(WHITE);
	rectangle(50, 50, 150, 100);
	rectangle(450, 50, 560, 100);
	setcolor(YELLOW); // set text color
	settextstyle(8, 0, 2);
	outtextxy(140, 10, "===STOP-AND-WAIT-PROTOCOL===");
	outtextxy(65, 60, "SENDER"); // print text in window graphics
	outtextxy(460, 60, "RECEIVER");
}

//Sinh so ngau nhien trong khoang [min,max]
int random(int minN, int maxN) {
	return minN + rand() % (maxN + 1 - minN);
}

void timer() {
	unsigned long elapsedTime;
	elapsedTime = ((unsigned long)clock() - begTime) / CLOCKS_PER_SEC;
	char digit[1];
	setcolor(YELLOW);
	outtextxy(50, 120, "Timeout in: ");
	for (unsigned long j = TIMEOUT - elapsedTime; j > 0; j--) {
		sprintf(digit, "%lu", j);
		outtextxy(190, 120, digit);
		delay(1000);
	}
	settextstyle(4, 0, 2);
	outtextxy(50, 120, "TIMEOUT!");	delay(1000);
}

void send() {
	int x, y = 50;
	for (x = 170; x < 440;) {

		bong(x, y, 11, BLACK);
		x += 10;
		bong(x, y, 10, RED);
		delay(100);
	}
	bong(x, y, 10, BLACK);
}

void lostSend() {
	int x, y = 50;
	int r = random(200, 400);
	for (x = 170; x < r;) {

		bong(x, y, 11, BLACK);
		x += 10;
		bong(x, y, 10, RED);
		delay(100);
	}
	bong(x, y, 10, BLACK);
	setcolor(RED);
	outtextxy(x, y, "X");
}

void reply() {
	int x, y = 100;
	for (x = 440; x > 170;) {
		bong(x, y, 11, BLACK);
		x -= 10;
		bong(x, y, 10, RED);
		delay(100);
	}
	bong(x, y, 10, BLACK);
}

void lostReply() {
	int x, y = 100;
	int r = random(200, 400);
	for (x = 440; x > r;) {
		bong(x, y, 11, BLACK);
		x -= 10;
		bong(x, y, 10, RED);
		delay(100);
	}
	bong(x, y, 10, BLACK);
	setcolor(RED);
	outtextxy(x, y, "X");
}

int main() {
	initwindow(650, 300);			// init window graphics
	setbkcolor(0);					// set background
	srand(time(NULL));
	printf("So goi tin: %d", N);
	for (int i = 1; i <= N; i++) {
		cleardevice();
		veHinh();
		printf("\nSending packet %d", i);
		r1 = rand() % 2;
		if (r1 == 1) {
			send();
			key = getch();
			reply();
			if (key == 49) { //a=1
				printf("\nACK%d",i);
				
			}
			else if (key == 48) { //a=0
				printf("\nNAK%d",i);
				i--;
			}
		}
		else {
			r2 = rand() % 2;
			begTime = clock();
			if (r2 == 1) {
				lostSend();
			}
			//TH2.2 Mat tin tra loi
			if (r2 == 0) {
				send();
				key = getch();
				lostReply();
			}
			timer();
			i--;
		}
	} 
	return 0;
}
