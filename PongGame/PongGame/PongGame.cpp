#include <iostream>
#include <time.h>
#include <conio.h>

using namespace std;
enum eDirection {
	STOP = 0, LEFT = 1, UPLEFT = 2, DOWNLEFT = 3, RIGHT = 4, UPRIGHT = 5, DOWNRIGHT = 6
};

class Ball
{
private:
	int x, y;
	int originalX, originalY;
	eDirection direction;

public:

	inline int getX() {
		return x;
	}
	inline int getY() {
		return y;
	}
	inline eDirection getDirection() {
		return direction;
	}

	Ball(int positionX, int positionY)
	{
		originalX = positionX;
		originalY = positionY;
		x = positionX;
		y = positionY;
		direction = STOP;
	}

	void Reset()
	{
		x = originalX;
		y = originalY;
		direction = STOP;
	}

	void changeDIrection(eDirection pDirection)
	{
		direction = pDirection;
	}
	void randomDirection()
	{
		direction = (eDirection)((rand() % 6) + 1);
	}

	void Move()
	{
		switch (direction)
		{
			case STOP:
				break;
			case LEFT:
				x--;
				break;
			case RIGHT:
				x++;
				break;
			case UPLEFT:
				x--; y--;
				break;
			case DOWNLEFT:
				x--; y++;
				break;
			case UPRIGHT:
				x++; y--;
				break;
			case DOWNRIGHT:
				x++; y++;
				break;
			default:
				break;
		}
	}

	friend ostream & operator<<(ostream& o, Ball ball)
	{
		o << "Ball[" << ball.x << "," << ball.y << "][" << ball.direction << "]";
		return o;
	}
};

class Paddle
{
private:
	int x, y;
	int originalX, originalY;

public:
	Paddle()
	{
		x = y = 0;
	}
	Paddle(int positionX, int positionY) : Paddle()
	{
		originalX = positionX;
		originalY = positionY;
		x = positionX;
		y = positionY;
	}
	inline void Reset() {x = originalX, y = originalY;}
	inline int getX() {return x;}
	inline int getY() {return y;}
	inline void moveUp() { y--;}
	inline void moveDown() { y++;}

	friend ostream & operator << (ostream & o, Paddle paddle)
	{
		o << "Paddle[" << paddle.x << "," << paddle.y << "]";
		return o;
	}
};

class GameManager
{
	private:
		int width, height;
		int score1, score2;
		char up1, down1, up2, down2;
		bool quit;
		Ball *ball;
		Paddle *player1;
		Paddle *player2;
	public:
		GameManager(int pWidth, int pHeight)
		{
			srand(time(NULL));
			quit = false;
			up1 = 'w'; up2 = 'i';
			down1 = 's'; down2 = 'k';
			score1 = score2 = 0;
			width = pWidth; height = pHeight;
			ball = new Ball(width / 2, height / 2);
			player1 = new Paddle(1, height / 2 - 3);
			player2 = new Paddle(width - 2, height / 2 - 3);
		}
		~GameManager() 
		{
			delete ball, player1, player2;
		}
		void ScoreUp(Paddle* player)
		{
			if (player == player1)
				score1++;
			else if (player == player2)
				score2++;

			ball->Reset();
			player1->Reset();
			player2->Reset();
		}
		void Draw()
		{
			//system("clear") //lixus
			system("cls"); // windows
			for (int i = 0; i < width + 2; i++)			
				cout << "\xB2";
			cout << endl;

			for (int i = 0; i < height; i++)
			{
				for (int j = 0; j < width; j++)
				{
					int ballX = ball->getX();
					int ballY = ball->getY();

					int player1X = player1->getX();
					int player1Y = player1->getY();

					int player2X = player2->getX();
					int player2Y = player2->getY();

					if (j == 0)
						cout << "\xB2";

					if (ballX == j && ballY == i)
						cout << "0";//ball
					else if (player1X == j && player1Y == i)
						cout << "\xDB";//player 1
					else if (player2X == j && player2Y == i)
						cout << "\xDB";//player 2

					else if (player1X == j && player1Y + 1 == i)
						cout << "\xDB";
					else if (player1X == j && player1Y + 2 == i)
						cout << "\xDB";
					else if (player1X == j && player1Y + 3 == i)
						cout << "\xDB";

					else if (player2X == j && player2Y + 1 == i)
						cout << "\xDB";
					else if (player2X == j && player2Y + 2 == i)
						cout << "\xDB";
					else if (player2X == j && player2Y + 3 == i)
						cout << "\xDB";


					else
						cout << " ";

					if (j == width - 1)
						cout << "\xB2";
				}
				cout << endl;
			}

			for (int i = 0; i < width + 2; i++)
				cout << "\xB2";
			cout << endl;

			cout << "PLAYER1 SCORE >>" << score1 << "<<" << endl;
			cout << "PLAYER2 SCORE >>" << score2 << "<<" << endl;
		}
		void Input()
		{
			ball->Move();

			int ballX = ball->getX();
			int ballY = ball->getY();

			int player1X = player1->getX();
			int player1Y = player1->getY();

			int player2X = player2->getX();
			int player2Y = player2->getY();

			if (_kbhit())
			{
				char current = _getch();
				if (current == up1)
					if (player1Y > 0)
						player1->moveUp();
				if (current == up2)
					if (player2Y > 0)
						player2->moveUp();
				if (current == down1)
					if (player1Y + 4 < height)
						player1->moveDown();
				if (current == down2)
					if (player2Y + 4 < height)
						player2->moveDown();

				if (ball->getDirection() == STOP)
					ball->randomDirection();

				if (current == 'q')
					quit = true;
			}
		}
		void Logic()
		{
			int ballX = ball->getX();
			int ballY = ball->getY();

			int player1X = player1->getX();
			int player1Y = player1->getY();

			int player2X = player2->getX();
			int player2Y = player2->getY();

			//left player
			for (int i = 0; i < 4; i++)			
				if (ballX == player1X + 1)
					if (ballY == player1Y + i)
						ball->changeDIrection((eDirection)((rand() % 3) + 4));	

			//right player
			for (int i = 0; i < 1; i++)
				if (ballX == player2X - 1)
					if (ballY == player2Y + i)
						ball->changeDIrection((eDirection)((rand() % 3) + 1));

			//bottom wall
			if (ballY == height - 1)
				ball->changeDIrection(ball->getDirection() == DOWNRIGHT ? UPRIGHT : UPLEFT);

			//top wall
			if (ballY == 0)
				ball->changeDIrection(ball->getDirection() == UPRIGHT ? DOWNRIGHT: DOWNLEFT);

			//right wall
			if (ballX == width - 1)
				ScoreUp(player1);

			//left wall
			if (ballX == 0)
				ScoreUp(player2);
		}
		void Run()
		{
			while (!quit)
			{
				Draw();
				Input();
				Logic();
			}
		}
};

int main()
{
	GameManager gameManager(40, 20);
	gameManager.Run();
	return 0;
}
