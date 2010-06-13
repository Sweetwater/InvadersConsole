#include "stdio.h"
#include "conio.h"
#include "windows.h"

#define PUT_CHAR_FIELD(field, x, y, cha) (memcpy(&field[y][x * 2], cha, 2))

const char* fieldChar = "Å@";
const char* playerChar = "ì ";
const char* enemyChar = "Ñw";
const char* bulletChar = "ÅE";



struct Bullet {
	int x;
	int y;
	char isActive;
};

struct Enemy {
	int x;
	int y;
	char isActive;
};


#define bulletMaxNum (16)
struct Bullet bullets[bulletMaxNum];


#define enemyNum (16)
struct Enemy enemys[enemyNum];


#define fieldSize (16)
#define fieldStringNum (fieldSize * 2 + 1)

char field[fieldSize][fieldStringNum];

int playerX;
int playerY;




void ClearField();
void DrawField();

void InitializePlayer(int x, int y);
void UpdatePlayer(char key);
void DrawPlayer();


void ClearBullets();
void FireBullet(int x, int y);
void UpdateBullets();
void DrawBullets();


void InitializeEnemys();
int CountActiveEnemy();
void DrawEnemys();


void CheckHit();


void main(void) {
	char keyInput = ' ';
	char isEnd = FALSE;
	char isInputEndKey = TRUE;
	char isClearsEnemy = FALSE;

	ClearField();
	ClearBullets();
	InitializePlayer(fieldSize / 2, fieldSize - 1);
	InitializeEnemys();

	DrawPlayer();
	DrawField();


	do {
		if (_kbhit()){
			keyInput = _getch();
			UpdatePlayer(keyInput);
		}

		UpdateBullets();
		CheckHit();

		ClearField();
		DrawPlayer();
		DrawBullets();
		DrawEnemys();
		DrawField();

		Sleep(50);

		isInputEndKey = (keyInput == '0');
		isClearsEnemy = (CountActiveEnemy() == 0);
		isEnd = isInputEndKey || isClearsEnemy;
	}
	while (isEnd == FALSE);


	//printf("Hellow Word\n");
	//
	//std::cout << "Hellow Word" << std::endl;

	//int testArray[] = {2,9,7,1,3,2,1,6,2,6,2,4,1,6,1,4,6,8, -1};

	//int index = 0;
	//while (testArray[index] != -1) {
	//	printf("%d,", testArray[index]);
	//	index++;
	//}
	//printf("Å°\n");

	//for (int i = 0; testArray[i] != -1; i++) {
	//	int minIndex = i;
	//	for (int j = i; testArray[j] != -1; j++) {
	//		if (testArray[minIndex] > testArray[j]) {
	//			minIndex = j;
	//		}
	//	}

	//	int temp = testArray[i];
	//	testArray[i] = testArray[minIndex];
	//	testArray[minIndex] = temp;
	//}

	//index = 0;
	//while (testArray[index] != -1) {
	//	printf("%d,", testArray[index]);
	//	index++;
	//}
	//printf("\n");

	////system("cls");

	//char c = getchar();
}



void ClearField() {
	int i;
	int j;

	for (i = 0; i < fieldSize; i++) {
		for (j = 0; j < fieldSize; j++) {
			PUT_CHAR_FIELD(field, i, j, fieldChar);
		}
		field[i][fieldStringNum-1] = '\0';
	}
}
void DrawField() {
	int i;

	system("cls");
	for (i = 0; i < fieldSize; i++) {
		printf("%s", field[i]);
		printf("\n");
	}
}


void InitializePlayer(int x, int y) {
	playerX = x;
	playerY = y;
}
void UpdatePlayer(char key) {
	switch (key) {
		case '4': playerX--; break;
		case '6': playerX++; break;
		//case '8': playerY--; break;
		//case '2': playerY++; break;
		case '5': FireBullet(playerX, playerY-1); break;
		default:
			break;
	}

	if (playerX < 0) {
		playerX = 0;
	}
	else if (playerX > fieldSize-1) {
		playerX = fieldSize-1;
	}

	if (playerY < 0) {
		playerY = 0;
	}
	else if (playerY > fieldSize-1) {
		playerY = fieldSize-1;
	}
}
void DrawPlayer() {
	PUT_CHAR_FIELD(field, playerX, playerY, playerChar);
}





void ClearBullets() {
	int i;
	for (i = 0; i < bulletMaxNum; i++) {
		bullets[i].isActive = FALSE;
	}
}

void FireBullet(int x, int y) {
	int i;
	for (i = 0; i < bulletMaxNum; i++) {
		if (bullets[i].isActive) continue;

		bullets[i].x = x;
		bullets[i].y = y;
		bullets[i].isActive = TRUE;
		return;
	}
}
void UpdateBullets() {
	int i;
	for (i = 0; i < bulletMaxNum; i++) {
		if (bullets[i].isActive == FALSE) continue;

		bullets[i].y--;
		if (bullets[i].y < 0) {
			bullets[i].isActive = FALSE;
		}
	}
}
void DrawBullets() {
	int i;
	int x;
	int y;
	for (i = 0; i < bulletMaxNum; i++) {
		if (bullets[i].isActive == FALSE) continue;

		x = bullets[i].x;
		y = bullets[i].y;
		PUT_CHAR_FIELD(field, x, y, bulletChar);
	}
}



void InitializeEnemys() {
	int i;
	for (i = 0; i < enemyNum; i++) {
		enemys[i].isActive = TRUE;
		enemys[i].x = i;
		enemys[i].y = 0;
	}
}
int CountActiveEnemy() {
	int activeEnemyNum = 0;
	int i;
	for (i = 0; i < enemyNum; i++) {
		if (enemys[i].isActive == FALSE) continue;
		activeEnemyNum++;
	}

	return activeEnemyNum;
}
void DrawEnemys() {
	int i;
	int x;
	int y;
	for (i = 0; i < enemyNum; i++) {
		if (enemys[i].isActive == FALSE) continue;

		x = enemys[i].x;
		y = enemys[i].y;
		PUT_CHAR_FIELD(field, x, y, enemyChar);
	}
}


void CheckHit() {
	int enemy;
	int bullet;
	for (enemy = 0; enemy < enemyNum; enemy++) {
		if (enemys[enemy].isActive == FALSE) continue;

		for (bullet = 0; bullet < bulletMaxNum; bullet++) {
			if (bullets[bullet].isActive == FALSE) continue;

			if (enemys[enemy].x == bullets[bullet].x &&
				enemys[enemy].y == bullets[bullet].y) {
				
				enemys[enemy].isActive = FALSE;
				bullets[bullet].isActive = FALSE;
				continue;
			}
		}
	}
}