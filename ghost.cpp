#include "ghost.h"
#include "lvl.h"
#include <cstdlib>
#include <ctime>

ghost::ghost()
{

}

ghost::ghost(int x, int y)
{
    ghostPos.first=x;
    ghostPos.second=y;
}


void ghost::move_ghost(const lvl &aLevel)
{

    auto newDirection = chooseDirect(aLevel);

    ghostPos.first = newDirection.first;
    ghostPos.second = newDirection.second;


}
std::pair<int,int> ghost::chooseDirect(const lvl &aLevel)
{
    auto &[xGhost, yGhost]=ghostPos;
    int nextX;
    int nextY;
    auto nFieldinVector = lvl::eField::WALL;

    while(nFieldinVector == lvl::eField::WALL)
    {
        srand(time(0));
        auto nextDir= rand() % 4;

        switch(nextDir)
        {
          case (int)Directions::Up:
          {
            nextX = xGhost;
            nextY = yGhost - 1;
            break;
          }
          case (int)Directions::Down:
          {
            nextX = xGhost;
            nextY = yGhost + 1;
            break;
          }
          case (int)Directions::Left:
          {
            nextX = xGhost - 1;
            nextY = yGhost;
            break;
          }
          case (int)Directions::Right:
          {
            nextX = xGhost +1;
            nextY = yGhost;
            break;
          }
        }

        auto nPositionVect = aLevel.columns * nextY + nextX; //индекс следующего поля в векторе
        nFieldinVector = aLevel.cPlaySquare[nPositionVect];
    }

    return std::pair<int,int>(nextX,nextY);
}

