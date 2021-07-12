#ifndef GHOST_H
#define GHOST_H
#include <vector>
#include "lvl.h"
#include <QGLWidget>
#include "appsettings.h"
#include "GameEnums.h"

class ghost
{

public:
    enum class Directions
    {
        Left=0,
        Right,
        Up,
        Down
    };

    ghost();
    ghost(int, int);

   std::pair<int,int> ghostPos;


   void move_ghost(int, std::vector<eField> *);
   std::pair<int,int> chooseDirect(int, std::vector<eField> *);


};

#endif // GHOST_H
