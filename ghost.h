#ifndef GHOST_H
#define GHOST_H
#include <vector>
#include "lvl.h"
#include <QGLWidget>
#include "appsettings.h"

class ghost
{
    friend class lvl;
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


   void move_ghost(const lvl &);
   std::pair<int,int> chooseDirect(const lvl &);


};

#endif // GHOST_H
