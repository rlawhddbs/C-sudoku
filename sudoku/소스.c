#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

#define GREEN 10
#define YELLOW 14
#define RED 12
#define WHITE 15
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define ENTER 13
#define F2 60

//������ ��
int game[9][9] = {
	7, 5, 3, 2, 1, 8, 6, 9, 4,
	1, 9, 8, 4, 7, 6, 3, 2, 5,
	6, 4, 2, 9, 3, 5, 8, 1, 7,
	3, 1, 6, 7, 4, 9, 2, 5, 8,
	4, 2, 5, 1, 8, 3, 9, 7, 6,
	8, 7, 9, 5, 6, 2, 4, 3, 1,
	5, 8, 4, 3, 2, 7, 1, 6, 9,
	9, 3, 1, 6, 5, 4, 7, 8, 2,
	2, 6, 7, 8, 9, 1, 5, 4, 3
}, gameJudge[9][9];
int ranNumRemove[81] = { -1 }, count = 0, error, null;
char difficult[20], inputKey;

//�ؽ�Ʈ ���� �ٲٴ� �Լ�
void colorSet(int textColor) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, textColor);
}

//�ܼ� Ŀ�� ��ġ �ٲٴ� �Լ�
void gotoxy(int x, int y)
{
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

//���� �����Ҷ� ȣ���ϴ� �Լ�
void startGame();

//������ �� �����ϴ� �Լ�
void sudokuAlgorithm();

//���̵� ����
void difficultSelect();

//ȭ�� ���
void printScreen();

//������ ���� �Լ�
void sudokuMain();

//n�� Ʋ�� �� ����
void defeat();

int main() {

	//����
	system("title ������");
	system("mode con cols=48 lines=20");
	
	startGame();

}

void startGame() {

	//CLI
	colorSet(YELLOW);
	printf("                     ����\n\n");
	colorSet(WHITE);
	printf("����Ű�� ĭ�� �̵��� �� �ֽ��ϴ�\n���͸� ������ �Է� ���� ���ϴ�\n������ ������ ��� ĭ�� �ùٸ��� ä�����մϴ�\n\n");

	colorSet(YELLOW);
	printf("                      ��Ģ\n\n");
	colorSet(WHITE);

	printf("1. 3 X 3ĭ���� ���� ���ڰ� �� �� ����\n2. ���� ������ ���� ���ڰ� �� �� ����\n3. ���� �࿡�� ���� ���ڰ� �� �� ����\n\n\n");

	int x = 22, y = 13;
	gotoxy(x - 4, y);
	printf("��");
	gotoxy(x, y);
	colorSet(GREEN);
	printf("����");
	colorSet(WHITE);
	gotoxy(x, y + 1);
	colorSet(YELLOW);
	printf("����");
	colorSet(WHITE);
	gotoxy(x - 1, y + 2);
	colorSet(RED);
	printf("�����");
	colorSet(WHITE);

	while (1) {
		if (_kbhit()) {
			inputKey = _getch();
			if (inputKey == -32) {
				inputKey = _getch();
				switch (inputKey) {
				case UP:
					if (y > 13) {
						gotoxy(x - 4, y);
						printf("   ");
						gotoxy(x - 4, --y);
						printf("��");
					}
					break;
				case DOWN:
					if (y < 15) {
						gotoxy(x - 4, y);
						printf("   ");
						gotoxy(x - 4, ++y);
						printf("��");
					}
					break;
				}
			}
			else if (inputKey == ENTER) {
				if (y == 13) strcpy(difficult, "����");
				else if (y == 14) strcpy(difficult, "����");
				else if (y == 15) strcpy(difficult, "�����");
				break;
			}
			else if (inputKey == 104) {
				strcpy(difficult, "???");
				break;
			}
		}
	}

	srand(time(NULL));

	error = 0;

	sudokuAlgorithm();

	difficultSelect();

	printScreen();

}

void sudokuAlgorithm() {

	//���� ���� �˰���
	for (int i = 0; i < 9; i++) {
		int first_num = rand() % 8 + 1, second_num = rand() % 8 + 1;

		for (int j = 0; j < 9; j++) {
			for (int k = 0; k < 9; k++) {
				if (first_num == game[k][j]) {
					game[k][j] = second_num;
				}
				else if (second_num == game[k][j]) {
					game[k][j] = first_num;
				}
			}
		}
	}

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			gameJudge[j][i] = game[j][i];
		}
	}

}

void difficultSelect() {

	if (strcmp(difficult, "����") == 0) null = 34;
	else if (strcmp(difficult, "����") == 0) null = 51;
	else if (strcmp(difficult, "�����") == 0) null = 64;
	else if (strcmp(difficult, "???") == 0) null = 64;

	//������ ���̵��� ���� �����
	for (int i = 0; i < null; i++) {
		int gameX = rand() % 9;
		int gameY = rand() % 9;
		for (int j = 0; j <= i; j++) {
			if (ranNumRemove[j] == gameX * 10 + gameY) {
				i--;
				break;
			}
			if (j == i) {
				ranNumRemove[count++] = gameX * 10 + gameY;
				game[gameX][gameY] = 0;
			}
		}
	}

	system("cls");

	gotoxy(10, 6);

	printf("���̵��� �ԷµǾ����ϴ� (");
	if (null == 34) {
		colorSet(GREEN);
		printf("%s", difficult);
		colorSet(WHITE);
	}
	else if (null == 51) {
		colorSet(YELLOW);
		printf("%s", difficult);
		colorSet(WHITE);
	}
	else if (null == 64) {
		colorSet(RED);
		printf("%s", difficult);
		colorSet(WHITE);
	}

	printf(")");
	gotoxy(12, 8);
	printf("3�� �ڿ� ������ �����մϴ�");

	Sleep(1000);
	gotoxy(24, 11);
	printf("3");
	Sleep(1000);
	gotoxy(24, 11);
	printf("2");
	Sleep(1000);
	gotoxy(24, 11);
	printf("1");
	Sleep(1000);

}

void printScreen() {

	int x = 2, y = 1;

	if (strcmp(difficult, "???") == 0) {
		if (error == 5) {

			for (int i = 0; i < 9; i++) {
				for (int j = 0; j < 9; j++) {
					gotoxy(x, y);
					printf(" ");
					x += 3;
					Sleep(30);
				}
				x = 2, y += 2;
			}

			defeat();
		}
	}
	else {
		if (error == 10) {

			for (int i = 0; i < 9; i++) {
				for (int j = 0; j < 9; j++) {
					gotoxy(x, y);
					printf(" ");
					x += 3;
					Sleep(30);
				}
				x = 2, y += 2;
			}

			defeat();
		}
	}

	system("cls");

	char screen[20][56] = {
	{ "��������������������������������������������������������" },
	{ "��  ��  ��  ��  ��  ��  ��  ��  ��  ��" },
	{ "��������������������������������������������������������" },
	{ "��  ��  ��  ��  ��  ��  ��  ��  ��  ��" },
	{ "��������������������������������������������������������" },
	{ "��  ��  ��  ��  ��  ��  ��  ��  ��  ��" },
	{ "��������������������������������������������������������" },
	{ "��  ��  ��  ��  ��  ��  ��  ��  ��  ��" },
	{ "��������������������������������������������������������" },
	{ "��  ��  ��  ��  ��  ��  ��  ��  ��  ��" },
	{ "��������������������������������������������������������" },
	{ "��  ��  ��  ��  ��  ��  ��  ��  ��  ��" },
	{ "��������������������������������������������������������" },
	{ "��  ��  ��  ��  ��  ��  ��  ��  ��  ��" },
	{ "��������������������������������������������������������" },
	{ "��  ��  ��  ��  ��  ��  ��  ��  ��  ��" },
	{ "��������������������������������������������������������" },
	{ "��  ��  ��  ��  ��  ��  ��  ��  ��  ��" },
	{ "��������������������������������������������������������" }
	};

	for (int i = 0; i < 19; i++) {
		for (int j = 0; j < 56; j++) {
			printf("%c", screen[i][j]);
		}
		printf("\n");
	}

	x = 2, y = 1;

	colorSet(WHITE);
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			gotoxy(x, y);
			if (game[i][j] == 0) {
				colorSet(YELLOW);
				printf("%d", game[i][j]);
				colorSet(WHITE);
			}
			else printf("%d", game[i][j]);
			x += 3;
		}
		x = 2, y += 2;
	}

	gotoxy(29, 0);
	printf("������������������������������������");
	gotoxy(29, 1);
	printf("��                ��");
	gotoxy(29, 2);
	printf("��                ��");
	gotoxy(29, 3);
	printf("��                ��");
	gotoxy(29, 4);
	printf("��                ��");
	gotoxy(29, 5);
	printf("������������������������������������");

	gotoxy(29, 6);
	printf("������������������������������������");
	gotoxy(29, 7);
	printf("��                ��");
	gotoxy(29, 8);
	printf("��                ��");
	gotoxy(29, 9);
	printf("��                ��");
	gotoxy(29, 10);
	printf("��                ��");
	gotoxy(29, 11);
	printf("��                ��");
	gotoxy(29, 12);
	printf("��                ��");
	gotoxy(29, 13);
	printf("��                ��");
	gotoxy(29, 14);
	printf("��                ��");
	gotoxy(29, 15);
	printf("������������������������������������");

	gotoxy(29, 16);
	printf("������������������������������������");
	gotoxy(29, 17);
	printf("��                ��");
	gotoxy(29, 18);
	printf("������������������������������������");

	gotoxy(31, 1);
	colorSet(YELLOW);
	printf("���۹�");
	colorSet(WHITE);
	gotoxy(31, 3);
	printf("�̵� : �����");
	gotoxy(31, 4);
	printf("���� : ENTER");

	gotoxy(31, 17);
	colorSet(RED);
	printf("Ʋ������ : %2d��", error);
	colorSet(WHITE);

	sudokuMain();

}

void sudokuMain() {

	int x = 0, y = 0;

	//����Ű�� �̵�
	while (1) {
		gotoxy(x + 2, y + 1);
		if (_kbhit()) {
			inputKey = _getch();
			if (inputKey == -32) {
				inputKey = _getch();
				switch (inputKey) {
				case LEFT:
					if (x == 0) continue;
					x -= 3;
					break;
				case RIGHT:
					if (x == 24) continue;
					x += 3;
					break;
				case UP:
					if (y == 0) continue;
					y -= 2;
					break;
				case DOWN:
					if (y == 16) continue;
					y += 2;
					break;
				}
			}
			else if (inputKey == ENTER) {
				if (game[y / 2][x / 3] != 0) {
					gotoxy(31, 7);
					printf("�Է� ����!");
					Sleep(1000);
					printScreen();
				}
				break;
			}
		}
	}

	int inputNum;
	char buffer;
	//�������� �ƴ��� �˻�
	while (1) {
		gotoxy(31, 7);
		printf("�Է� (1~9) : ");
		scanf("%d", &inputNum);
		scanf("%c", &buffer);
		if (gameJudge[y / 2][x / 3] != inputNum) {
			gotoxy(31, 8);
			colorSet(RED);
			printf("�����Դϴ�!");
			colorSet(WHITE);
			Sleep(1000);
			error++;
			printScreen();
		}
		break;
	}

	game[y / 2][x / 3] = inputNum;

	//������ �� ä�������� �˻�
	count = 0;
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (gameJudge[j][i] == game[j][i]) {
				count++;
			}
		}
		if (count == 81) {

			x = 26, y = 17;

			for (int i = 0; i < 9; i++) {
				for (int j = 0; j < 9; j++) {
					gotoxy(x, y);
					printf(" ");
					x -= 3;
					Sleep(30);
				}
				x = 26, y -= 2;
			}

			system("cls");
			gotoxy(7, 9);
			printf("�����մϴ�! Ŭ�����߽��ϴ� (");
			if (null == 34) {
				colorSet(GREEN);
				printf("����");
				colorSet(WHITE);
			}
			else if (null == 51) {
				colorSet(YELLOW);
				printf("����");
				colorSet(WHITE);
			}
			else if (null == 64) {
				colorSet(RED);
				printf("�����");
				colorSet(WHITE);
			}
			if (strcmp(difficult, "???") == 0) {
				gotoxy(7, 11);
				printf("���� ���̵��� ���˳׿�!");
			}
			printf(")\n");
			gotoxy(7, 10);
			printf("�ٽ� �����Ϸ��� F2�� �����ּ���\n");
			while (1) {
				if (_kbhit()) {
					inputKey = _getch();
					if (inputKey == 0x00) {
						inputKey = _getch();
						if (inputKey == F2) {
							system("cls");
							startGame();
						}
					}
				}
			}
		}
	}

	printScreen();

}

void defeat() {

	system("cls");

	gotoxy(9, 9);

	colorSet(RED);

	printf("%d�� Ʋ���� ������ ����Ǿ����ϴ�", error);

	colorSet(WHITE);

	Sleep(3000);

	exit(0);
}
