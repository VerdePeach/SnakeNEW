#include "pch.h"
#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <fstream>

#define COLOMS 40
#define ROWS 20

using namespace std;


class Fruit {
private:
	int fruitX;
	int fruitY;
public:

	void setFruitRandX() {
		fruitX = rand() % (COLOMS - 2) + 1;
	}

	void setFruitRandY() {
		fruitY = rand() % (ROWS - 2) + 1;
	}

	int getFruitX() {
		return fruitX;
	}

	int getFruitY() {
		return fruitY;
	}

};

class Snake {
private:
	int snakeHeadX;
	int snakeHeadY;
	int snakeElem = 1;
	int *snakeTailX = new int[100];
	int *snakeTailY = new int[100];
public:

	void setSnakeHeadX(int snakeHeadX) {
		this->snakeHeadX = snakeHeadX;
	}

	int getSnakeHeadX() {
		return snakeHeadX;
	}

	void setSnakeHeadY(int snakeHeadY) {
		this->snakeHeadY = snakeHeadY;
	}

	int getSnakeHeadY() {
		return snakeHeadY;
	}

	void setSnakeElem(int snakeElem) {
		this->snakeElem = snakeElem;
	}

	int getSnakeElem() {
		return snakeElem;
	}

	int getSnakeTailX() {
		return snakeTailX[0];//*
	}

	int getSnakeTailY() {
		return snakeTailY[0];//*
	}
	/////////////////////
	void setSnakeTailX(int snakeTailX) {
		this->snakeTailX[0] = snakeTailX;//*
	}

	void setSnakeTailY(int snakeTailY) {
		this->snakeTailY[0] = snakeTailY;//*
	}
	//////////////////
	void setSnakeTailX(int index, int elem) {
		this->snakeTailX[index] = elem;
	}

	void setSnakeTailY(int index, int elem) {
		this->snakeTailY[index] = elem;
	}

	int getSnakeTailX(int index) {
		return snakeTailX[index];
	}

	int getSnakeTailY(int index) {
		return snakeTailY[index];
	}

};

class Play {
private:
	bool gameExit;
	int score = 0;
	char inHelpChar = ' ';
	Snake *snake;
	Fruit *fruit1;
	Fruit *fruit2;
	Fruit *fruit3;
	enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };
	Direction dir;
public:

	void setGameStatus(bool status) {
		gameExit = status;
	}

	bool getGameStatus() {
		return gameExit;
	}

	void setScore(int score) {
		this->score = score;
	}

	int getScore() {
		return score;
	}

	void run() {
		snake = new Snake();
		fruit1 = new Fruit();
		fruit2 = new Fruit();
		fruit3 = new Fruit();
		dir = STOP;
		setGameStatus(false);
		fruit1->setFruitRandX();
		fruit1->setFruitRandY();
		snake->setSnakeHeadX(COLOMS / 2);
		snake->setSnakeHeadY(ROWS / 2);
		while (!getGameStatus()) {
			Input();
			logic(snake, fruit1, fruit2, fruit3);
			draw(snake, fruit1, fruit2, fruit3);
		}
	}

private:
	void logic(Snake *snake, Fruit *fruit, Fruit *fruitKill, Fruit *fruit_5) {
		int LastX = snake->getSnakeTailX();
		int LastY = snake->getSnakeTailY();
		int Last2X, Last2Y;
		snake->setSnakeTailX(snake->getSnakeHeadX());//?
		snake->setSnakeTailY(snake->getSnakeHeadY());//?
		for (int i = 0; i < snake->getSnakeElem(); i++) {
			Last2X = snake->getSnakeTailX(i);
			Last2Y = snake->getSnakeTailY(i);
			snake->setSnakeTailX(i, LastX);
			snake->setSnakeTailY(i, LastY);
			LastX = Last2X;
			LastY = Last2Y;
		}

		switch (dir) {
		case UP: snake->setSnakeHeadY(snake->getSnakeHeadY() - 1); break;
		case DOWN: snake->setSnakeHeadY(snake->getSnakeHeadY() + 1); break;
		case LEFT: snake->setSnakeHeadX(snake->getSnakeHeadX() - 1); break;
		case RIGHT: snake->setSnakeHeadX(snake->getSnakeHeadX() + 1); break;
		}

		if (snake->getSnakeHeadX() == 0) {
			snake->setSnakeHeadX(COLOMS - 2);
		}
		if (snake->getSnakeHeadY() == 0) {
			snake->setSnakeHeadY(ROWS - 2);
		}
		if (snake->getSnakeHeadX() == COLOMS - 1) {
			snake->setSnakeHeadX(1);
		}
		if (snake->getSnakeHeadY() == ROWS - 1) {
			snake->setSnakeHeadY(1);
		}

		for (int i = 0; i < snake->getSnakeElem(); i++) {
			if (snake->getSnakeTailX(i) == snake->getSnakeHeadX() && snake->getSnakeTailY(i) == snake->getSnakeHeadY()) {
				setGameStatus(true);
				break;
			}
		}

		if (snake->getSnakeHeadX() == fruit->getFruitX() && snake->getSnakeHeadY() == fruit->getFruitY()) {
			cout << '\a';
			fruit->setFruitRandX();
			fruit->setFruitRandY();
			score += 2;
			snake->setSnakeElem(snake->getSnakeElem() + 1);

			fruitKill->setFruitRandX();
			fruitKill->setFruitRandY();

			fruit_5->setFruitRandX();
			fruit_5->setFruitRandY();

			if (snake->getSnakeElem() == 10) {
				system("cls");
				system("color a5");
				cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n                               New Level 2";
				_getch();
			}

			if (snake->getSnakeElem() == 20) {
				system("cls");
				system("color 4f");
				cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n                               New Level 3";
				_getch();
			}

			if (snake->getSnakeElem() == 50) {
				system("cls");
				system("color 18");
				cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n                               New Level 4";
				_getch();
			}

			if (snake->getSnakeElem() == 90) {
				system("cls");
				system("color 9d");
				cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n                               New Level X";
				_getch();
			}
		}
		else if (snake->getSnakeElem() >= 10 && snake->getSnakeHeadX() == fruitKill->getFruitX()
			&& snake->getSnakeHeadY() == fruitKill->getFruitY()) {
			setGameStatus(true);
		}
		else if (snake->getSnakeElem() >= 20 && snake->getSnakeHeadX() == fruit_5->getFruitX()
			&& snake->getSnakeHeadY() == fruit_5->getFruitY() && (score % 11 == 0)) {
			cout << '\a';
			score += 5;
			snake->setSnakeElem(snake->getSnakeElem() + 1);
			fruit_5->setFruitRandX();
			fruit_5->setFruitRandY();
		}

	}

	void Input() {
		if (_kbhit()) {
			fflush(stdin);
			char s = _getch();
			switch (s) {
			case 'a':
				if (inHelpChar != 'd') {
					dir = LEFT;
					inHelpChar = s;
				}
				break;
			case 'w':
				if (inHelpChar != 's') {
					dir = UP;
					inHelpChar = s;
				}
				break;
			case 'd':
				if (inHelpChar != 'a') {
					dir = RIGHT;
					inHelpChar = s;
				}
				break;

			case 's':
				if (inHelpChar != 'w') {
					dir = DOWN;
					inHelpChar = s;
				}
				break;
			case 'p':
				system("pause");
				break;
			case '0': setGameStatus(true);
			}
		}
	}


	void draw(Snake *snake, Fruit *fruit, Fruit *fruitKill, Fruit *fruit_5) {
		system("cls");
		cout << "SCORE: " << score << endl;
		for (int i = 0; i < ROWS; i++) {
			for (int j = 0; j < COLOMS; j++) {
				if (snake->getSnakeHeadX() == j && snake->getSnakeHeadY() == i) {
					cout << "O";
				}
				else if (j == COLOMS - 1 || j == 0 || i == ROWS - 1 || i == 0) {
					cout << '#';
				}
				else if (fruit->getFruitX() == j && fruit->getFruitY() == i) {
					cout << "$";
				}
				else if (snake->getSnakeElem() >= 10 && fruitKill->getFruitX() == j && fruitKill->getFruitY() == i) {
					cout << "%";
				}
				else if (snake->getSnakeElem() >= 20 && fruit_5->getFruitX() == j && fruit_5->getFruitY() == i && (score % 11 == 0)) {
					cout << "@";
				}
				else {

					bool print = true;

					for (int k = 1; k <= snake->getSnakeElem(); k++) {
						if ((snake->getSnakeTailX(k) == j && snake->getSnakeTailY(k) == i)) {
							cout << "o";
							print = false;
						}
					}
					if (print)
						cout << ' ';
				}
			}
			cout << '\n';
		}

	}
public:
	void scoreToFile() {
		int bestScore = scoreFromFile();
		if (score > bestScore) {
			ofstream outF("bestScore.txt");
			if (outF) {
				outF << score;
			}
			outF.close();
		}

	}

	int scoreFromFile() {
		int bestScore = 0;
		ifstream inF("bestScore.txt");
		if (inF) {
			inF >> bestScore;
		}
		inF.close();
		return bestScore;
	}

	void rules() {
		system("color 0a");
		system("title Snake");
		system("mode con cols=70 lines=34");
		cout << "*****control*****\n w = UP\n s = DOWN\n a = LEFT\n d = RIGHT\n 0 = exit\n p = pause\n"
			"*****elements*****\n O - Head of snake\n o - tail of snake\n $ - gives + 2 points\n % - kills you (game over)\n"
			" @ - gives you + 5 points\n"
			"Use only English language to play.\nIf you are ready press any key to start game.";
		_getch();
	}

	void endGame() {
		system("cls");
		cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n                    **********GAME OVER**********";
		cout << "\n                           Your Score = " << getScore() << '\n';
		int bestScore = scoreFromFile();

		if (bestScore >= getScore()) {
			cout << "\n                           Best score = " << bestScore << '\n';
		}
		else {
			cout << "\n                      You set a new record = " << getScore() << '\n';
			scoreToFile();
		}
	}

	void newGame() {
		score = 0;
		system("color 0a");
	}
};





int main() {
	srand(time(NULL));
	Play play;
	play.rules();

	char wantToPlay = 'y';
	while (wantToPlay == 'y' || wantToPlay == 'Y') {
		play.run();
		play.endGame();
		play.newGame();
		cout << "\n If you want to play one more time press 'y' and after 'Enter'.\n For exit enter any other key." << endl;
		cin >> wantToPlay;

	}
	_getch();
	return 0;
}