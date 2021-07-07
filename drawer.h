#ifndef DRAWER_H
#define DRAWER_H

#include "lvl.h"
#include <QGLWidget>
#include "appsettings.h"

class drawer
{
public:
    drawer();
    void draw(const lvl &, QGLWidget &);

private:
    void draw_grid(const lvl&, QGLWidget &);
    void draw_objects(const lvl&, QGLWidget &);
    void draw_stastics(const lvl&, QGLWidget &);
    void draw_pacman(const lvl&, QGLWidget & , AppSettings &, float, float, float);

    bool TextureIsLoad{false};
};

#endif // DRAWER_H
