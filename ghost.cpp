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


void ghost::move_ghost(int columns, std::vector<eField> *cPlaySquare)
{
   auto newDirection = chooseDirect(columns, cPlaySquare);

   ghostPos.first = newDirection.first;
   ghostPos.second = newDirection.second;

}
std::pair<int,int> ghost::chooseDirect(int columns, std::vector<eField> *cPlaySquare)
{
    auto &xGhost = ghostPos.first;
    auto &yGhost = ghostPos.second;
    int nextX;
    int nextY;
    auto nFieldinVector = eField::WALL;

    while(nFieldinVector == eField::WALL)
    {
        srand(time(0));
        auto nextDir= rand() % 4;

        switch(nextDir)
        {
          case static_cast<int>(Directions::Up):
          {
            nextX = xGhost;
            nextY = yGhost - 1;
            break;
          }
          case static_cast<int>(Directions::Down):
          {
            nextX = xGhost;
            nextY = yGhost + 1;
            break;
          }
          case static_cast<int>(Directions::Left):
          {
            nextX = xGhost - 1;
            nextY = yGhost;
            break;
          }
          case static_cast<int>(Directions::Right):
          {
            nextX = xGhost +1;
            nextY = yGhost;
            break;
          }
        }

        auto nPositionVect = columns * nextY + nextX; //индекс следующего поля в векторе
        nFieldinVector = cPlaySquare->at(nPositionVect);
    }

    return std::pair<int,int>(nextX,nextY);
}

