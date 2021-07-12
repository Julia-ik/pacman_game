#ifndef DRAWER_H
#define DRAWER_H

#include "lvl.h"
#include "appsettings.h"
#include "GameEnums.h"
#include <vector>
#include <QGLWidget>


class drawer
{
public:
    drawer();
    void draw(const lvl &, QGLWidget &);

private:
    void draw_grid(const lvl&, QGLWidget &);
    void draw_objects(const lvl&, QGLWidget &);
    void draw_stastics(const lvl&, QGLWidget &);
    static void draw_pacman(const lvl&, QGLWidget & , AppSettings &, qreal, qreal, qreal);
    static void draw_ghost(const lvl&, QGLWidget & , AppSettings &, qreal, qreal, qreal, std::pair<int, int>);

    bool TextureIsLoad{false};
};

#endif // DRAWER_H
