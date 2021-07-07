#include "drawer.h"
#include "lvl.h"
#include "appsettings.h"
#include "pacman_game.h"

drawer::drawer()
{

}



void drawer::draw(const lvl &aLevel, QGLWidget &aGLWidget)
{
    if(!aLevel.cIsLoad)
    {
        return;
    }
    draw_grid(aLevel, aGLWidget);
    draw_objects(aLevel, aGLWidget);
    draw_stastics(aLevel, aGLWidget);

}

void drawer::draw_pacman(const lvl &aLevel, QGLWidget &aGLWidget, AppSettings &app, float x, float y, float fw)
{
     auto idPacman   = app.textureID(AppSettings::TexturesId::PACMAN);
     auto &[xPacman, yPacman]=aLevel.cPlayerPosition;

     aGLWidget.drawTexture(QRectF{x+ xPacman*fw, y+ yPacman*fw, fw, fw}, idPacman);
}

void drawer::draw_grid(const lvl&aLevel, QGLWidget &aGLWidget)
{
    static auto sw = AppSettings::instance().screenWidth()-50;

    auto &lines   = aLevel.lines;
    auto &columns = aLevel.columns;

    float fh    = (float)sw / (float)columns;
    float map_w = sw;
    float map_h = fh*lines;

    float x{25.0f};
    float y{150.0f};

    if(aLevel.columns >=1)
    {
        aGLWidget.qglColor(Qt::darkGray);
        glBegin(GL_LINES);
          for(int r = 0; r <= lines; ++r)
          {
            glVertex2i(x,         y + fh*r);
            glVertex2i(x + map_w, y + fh*r);
          }

          for(int c = 0.f; c <= columns; ++c)
          {
            glVertex2i(x + fh*c, y );
            glVertex2i(x + fh*c, y + map_h);
          }
        glEnd();
    }


}

void drawer::draw_objects(const lvl &aLevel, QGLWidget &aGLWidget)
{
    auto &app = AppSettings::instance();
    static auto sw=app.screenWidth() -50;

    auto &lines = aLevel.lines;
    auto &columns=aLevel.columns;

    float fw = (float) sw/(float) columns;//ширина поля

    float x(25.0f);

    auto idCoin      = app.textureID(AppSettings::TexturesId::COIN);
    auto idCookie      = app.textureID(AppSettings::TexturesId::COOKIE);
    auto idWall     = app.textureID(AppSettings::TexturesId::WALL);
    auto idGhost      = app.textureID(AppSettings::TexturesId::GHOST);
    auto idEmpty = app.textureID(AppSettings::TexturesId::EMPTY);

    const auto &map = aLevel.cPlaySquare;
    float y{150.f};

    glEnable(GL_TEXTURE_2D);

    aGLWidget.qglColor(Qt::white);

    for(int i=0; i<lines; i++)
        for(int j=0;j<columns;j++)
        {
            unsigned int textureID =0;
            switch(map[i*columns + j])
            {
                case lvl::eField::COOKIE:
                    {
                        textureID=idCookie;
                         break;
                     }
                 case lvl::eField::COIN:
                    {
                        textureID=idCoin;
                        break;
                     }
                 case lvl::eField::GHOST:
                      {
                          textureID=idGhost;
                          break;
                      }

                 case lvl::eField::WALL:
                        {
                            textureID=idWall;
                            break;
                        }
                  case lvl::eField::EMPTY:
                         {
                            textureID=idEmpty;
                            break;
                         }
                default:
                {
                    textureID=idEmpty;
                }
             }

            if(textureID !=0)
            {
                aGLWidget.drawTexture(QRectF{x+ j*fw, y+ i*fw, fw, fw}, textureID);
            }
        }

    draw_pacman(aLevel, aGLWidget, app, x, y, fw);
    glDisable(GL_TEXTURE_2D);
}
void drawer::draw_stastics(const lvl &aLevel, QGLWidget &aGLWidget)
{
    static auto font=QFont("Comic Sans", 15);
    aGLWidget.qglColor(Qt::black);

    QString str;

    str ="Lives ";
    str += QString::number(aLevel.cLives);
    aGLWidget.renderText(15,20, str, font);

    QString strr;
    strr ="Points ";
    strr +=QString::number(aLevel.earnedPoints);
    strr +="/";
    strr +=QString::number(aLevel.max);
    aGLWidget.renderText(15,40,strr,font);

}
