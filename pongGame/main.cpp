#include <iostream>

using namespace std;
enum eDirection {STOP = 0, LEFT = 1, UPLEFT = 2, DOWNLEFT = 3, RIGHT = 4, UPRIGHT = 5, DOWNRIGHT = 6};

class cBall
{
    private:
        int x,y;
        int originalX, originalY;
        eDirection direction;

    public:

        inline int getX(){return x;}
        inline int getY(){return y;}
        inline eDirection getDirection(){return direction;}    

        cBall(int positionX, int positionY)
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
            direction = (eDirection)((rand()% 6) + 1);
        }

        void Move()
        {
            switch(direction)
            {
                case STOP:
                    break;
                case LEFT:
                    x--;
                    break;
                case RIGHT
                    x++;
                    break;
                case UPLEFT
                    x--; y--;
                    break;
                case DOWNLEFT
                    x--; y++;
                    break;
                case UPRIGHT
                    x++; y--;
                    break;
                case DOWNRIGHT
                    x++; y++;
                    break;
                default:
                    break;
            }
        }

        friend ostream & operator<<(ostream & o, cBall ball)
        {
            o << "Ball[" << ball.x<< "," << ball.y << "][" << ball.direction << "]";
            return o;
        }
};

int main()
{
    //like a mock
    cBall ball(0, 0);
    cout << ball << endl;
    ball.randomDirection();
    cout << ball << endl;
    ball.Move();
    cout << ball << endl;
    ball.randomDirection();
    ball.Move();
    cout << ball << endl;
    ball.randomDirection();
    ball.Move();
    cout << ball << endl;
    return 0;   
}
