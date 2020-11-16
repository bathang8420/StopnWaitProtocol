#include <stdio.h>
#include <conio.h>
#include <graphics.h>
#include <stdlib.h>
#include <time.h>

#define RTT 5
#define TIMEOUT 9
#define N 5

unsigned long begTime;
int key, r1, r2;
char info[20];
int mau;

//Hình gói tin
void bong(int x, int y, int r, int mau) {
	setcolor(mau);
	setfillstyle(1, mau);
	pieslice(x, y, 0, 360, r);
}

//Hình khung 
void veHinh() {
	setcolor(WHITE);
	rectangle(50, 50, 150, 100);
	rectangle(450, 50, 560, 100);
	setcolor(YELLOW); // set text color
	settextstyle(8, 0, 2);
	outtextxy(140, 10, "===STOP-AND-WAIT-PROTOCOL===");
	outtextxy(65, 60, "SENDER"); // print text in window graphics
	outtextxy(460, 60, "RECEIVER");
	bong(470, 130, 10, GREEN);
	outtextxy(490, 120, "ACK(1)");
	bong(470, 160, 10, RED);
	outtextxy(490, 150, "NAK(0)");
}

//Sinh so ngau nhien trong khoang [min,max]
int random(int minN, int maxN) {
	return minN + rand() % (maxN + 1 - minN);
}

//Timeout
void timer() {
	unsigned long elapsedTime;
	elapsedTime = ((unsigned long)clock() - begTime) / CLOCKS_PER_SEC;
	char digit[1];
	setcolor(YELLOW);
	outtextxy(30, 150, "Timeout in: ");
	for (unsigned long j = TIMEOUT - elapsedTime; j > 0; j--) {
		sprintf(digit, "%lu", j);
		outtextxy(170, 150, digit);
		delay(1000);
	}
	settextstyle(4, 0, 2);
	outtextxy(30, 150, "TIMEOUT!");	delay(1000);
}

//Hình tin gui di
void send() {
	int x, y = 50;
	for (x = 170; x < 440;) {
		bong(x, y, 11, BLACK);
		x += 10;
		bong(x, y, 10, WHITE);
		delay(100);
	}
	bong(x, y, 10, BLACK);
}

//Mat tin gui di
void lostSend() {
	int x, y = 50;
	int r = random(200, 400);
	for (x = 170; x < r;) {
		bong(x, y, 11, BLACK);
		x += 10;
		bong(x, y, 10, WHITE);
		delay(100);
	}
	bong(x, y, 10, BLACK);
	setcolor(RED);
	outtextxy(x, y - 5, "X");
}

//Tin tra loi
void reply(int mau) {
	int x, y = 100;
	for (x = 439; x > 170;) {
		bong(x, y, 11, BLACK);
		x -= 10;
		bong(x, y, 10, mau);
		delay(100);
	}
	bong(x, y, 10, BLACK);
}

//Mat tin tra loi
void lostReply(int mau) {
	int x, y = 100;
	int r = random(200, 400);
	for (x = 439; x > r;) {
		bong(x, y, 11, BLACK);
		x -= 10;
		bong(x, y, 10, mau);
		delay(100);
	}
	bong(x, y, 10, BLACK);
	setcolor(RED);
	outtextxy(x, y - 5, "X");
}
/*****************************************/
int main() {
	// Thiet lap moi truong do hoa
	initwindow(650, 300);			
	setbkcolor(0);					
	srand(time(NULL));
	
	for (int i = 1; i <= N; i++) {
		cleardevice();
		veHinh();
		setcolor(YELLOW);
		outtextxy(30, 120, "Sending pkt: ");
		sprintf(info, "%d", i);
		outtextxy(180, 120, info);
		r1 = rand() % 2;
		//TH1: Mat tin trong qua trinh gui, nhan
		if (r1 == 0) {
			r2 = rand() % 2;
			begTime = clock();
			//Mat tin gui
			if (r2 == 1) {
				lostSend();
			}
			//Mat tin tra loi
			if (r2 == 0) {
				send();
				key = getch();
				if (key == 49) mau = GREEN; //ACK
				if (key == 48) mau = RED; //NAK
				lostReply(mau);
			}
			timer();
			i--;
		}
		else {
		//TH2: Khong bi mat tin trong qua trinh gui, nhan
			send();
			key = getch();
			if (key == 49) { //ACK
				reply(GREEN);
			}
			else if (key == 48) { //NAK
				reply(RED);
				i--;
			}
		}
	}
	return 0;
}
