#include "lvl.h"
#include "appsettings.h"
#include "ghost.h"
#include <QGLWidget>
#include <thread>

#include <QFile>
#include <QTextStream>
#include <QThread>



lvl::lvl()
{}

eField parseToField (QChar ch)
{
    switch (ch.toLatin1())
    {
        case '#':
        {
            return eField::WALL;
        }
        case '%':
        {
            return eField::PACMAN;
        }
        case '*':
        {
            return eField::GHOST;
        }
        case '.':
        {
            return eField::COIN;
        }
        case ',':
        {
            return eField::COOKIE;
        }
        case ' ':
        {
            return eField::EMPTY;
        }
        default: break;
    }
    return eField::WALL;
}

void lvl::load(int aLevel)
{
    const auto &lp = AppSettings::instance().levelsPath();

    QString lvl_path = lp + QString::number(aLevel) + ".lvl";

    QFile   file(lvl_path);

    cIsLoad = false;
    cIsComplete = false;
    areGhostsReleased = false;
    earnedPoints = 0;



    file.open(QIODevice::ReadOnly);

    if(file.isOpen())
    {
      cPlaySquare.clear();
      ghosts.clear();

      QTextStream in(&file);

      lines = 0;
      columns=0;

      std::vector<eField> cmPlaySquare;

      for (QString line = in.readLine();
           !line.isNull();
           line = in.readLine())
      {
        columns=line.size();

        for(int i=0;i<line.size();i++)
        {
            if(parseToField(line[i]) == eField::PACMAN)
            {
                cPlayerPosition.first = i;
                cPlayerPosition.second = lines;
            }

            if(parseToField(line[i])== eField::GHOST)
            {
                 ghosts.push_back(*new ghost(i, lines));
            }
            cmPlaySquare.push_back(parseToField(line[i]));
        }
        lines++;
      }

      cPlaySquare.swap(cmPlaySquare);
      cIsLoad = true;
      file.close();
    }

}

void lvl::load(std::string)
{

}

bool lvl::isComplete()
{
    return cIsComplete;
}
bool lvl::isLoad()
{
    return cIsLoad;
}
bool lvl::isOver()
{
    return cIsOver;
}



void lvl::pacman_up()
{
    move(0,-1);
}
void lvl::pacman_down()
{
    move(0,1);
}
void lvl::pacman_left()
{
    move(-1, 0);
}
void lvl::pacman_right()
{
    move(1, 0);
}

 void lvl::move(int aDX, int aDY)
 {

     auto &xPacman=cPlayerPosition.first;
     auto &yPacman =cPlayerPosition.second;
     auto nextX = xPacman +aDX;
     auto nextY = yPacman + aDY;

     auto cPositionVect = columns * yPacman + xPacman;
     auto nPositionVect = columns * nextY + nextX;

     auto &cField = cPlaySquare[cPositionVect];
     auto &nField = cPlaySquare[nPositionVect];

     bool isMoving = false;

      switch(nField)
        {
         case eField::WALL:
         {
             break;
         }
        case eField::GHOST:
        {
            cLives -=1;
            break;
       }

         case eField::COIN:
         {
             cField = eField::EMPTY;
             earnedPoints += 1;
             isMoving = true;
            break;
         }
         case eField::COOKIE:
         {
             cField = eField::EMPTY;
             earnedPoints += 5;
             isMoving = true;
             break;
         }
         case eField::EMPTY:
         {
            cField = eField::EMPTY;
            isMoving = true;
             break;
         }
         default:
         {
             break;
         }

     };
     if(isMoving)
     {
         xPacman = nextX;
         yPacman = nextY;

     }


     if(lvl::earnedPoints>=lvl::max)
     {
         lvl::cIsComplete=true;

     }

 }


 void lvl::releaseGhosts()
 {

    for(int i=0;i<ghosts.size();i++)
    {
        ghosts[i].move_ghost(columns, &cPlaySquare);

    }
}


