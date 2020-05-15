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
        inline int getX(){return x;}
        inline int getY(){return y;}
        inline eDirection getDirection(){return direction;}
};

int main()
{
    return 0;   
}
