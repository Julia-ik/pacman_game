#include "drawer.h"
#include "lvl.h"
#include "appsettings.h"
#include <vector>

drawer::drawer() = default;



void drawer::draw(const lvl &aLevel, QGLWidget &aGLWidget)
{
    if(!aLevel.cIsLoad)
    {
        return;
    }
    if(aLevel.cIsComplete)
    {
        QFont font = QFont("Comic Sans", 48);
        aGLWidget.qglColor(Qt::green);
        QString str = "YOU WON";
        aGLWidget.renderText(250,250, str, font);


        aGLWidget.qglColor(Qt::black);
        font=QFont("Comic Sans", 15);

        str ="Press any key...";
        aGLWidget.renderText(280,299, str, font);
    }
    else
    {
        draw_grid(aLevel, aGLWidget);
        draw_objects(aLevel, aGLWidget);
        draw_stastics(aLevel, aGLWidget);
    }


}

void drawer::draw_ghost(const lvl &aLevel, QGLWidget &aGLWidget, AppSettings &app, qreal x, qreal y, qreal fw,
                       std::pair<int, int> cGhost)
{
    const auto idGhost   = app.textureID(AppSettings::TexturesId::GHOST);
    int &xGhost = cGhost.first;
    int &yGhost = cGhost.second;

    aGLWidget.drawTexture(QRectF{x+ xGhost*fw, y+ yGhost*fw, fw, fw}, idGhost);

}

void drawer::draw_pacman(const lvl &aLevel, QGLWidget &aGLWidget, AppSettings &app, qreal x, qreal y, qreal fw)
{
     const auto idPacman   = app.textureID(AppSettings::TexturesId::PACMAN);
     auto &xPacman= aLevel.cPlayerPosition.first;
     auto &yPacman= aLevel.cPlayerPosition.second;
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

    qreal fw = (float) sw/(float) columns;//ширина поля

    qreal x(25.0);

    auto idCoin      = app.textureID(AppSettings::TexturesId::COIN);
    auto idCookie      = app.textureID(AppSettings::TexturesId::COOKIE);
    auto idWall     = app.textureID(AppSettings::TexturesId::WALL);
    auto idEmpty = app.textureID(AppSettings::TexturesId::EMPTY);

    const auto &map = aLevel.cPlaySquare;
    qreal y{150.0};

    glEnable(GL_TEXTURE_2D);

    aGLWidget.qglColor(Qt::white);

    for(int i=0; i<lines; i++)
        for(int j=0;j<columns;j++)
        {
            unsigned int textureID =0;
            switch(map[i*columns + j])
            {
                case eField::COOKIE:
                    {
                        textureID=idCookie;
                         break;
                     }
                 case eField::COIN:
                    {
                        textureID=idCoin;
                        break;
                     }
                 case eField::WALL:
                        {
                            textureID=idWall;
                            break;
                        }
                  case eField::EMPTY:
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

    for(int i=0;i<aLevel.ghosts.size();i++)
    {
        std::pair<int, int> cGhosts = aLevel.ghosts[i].ghostPos;
        draw_ghost(aLevel, aGLWidget, app, x,  y, fw, cGhosts);
    }

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

    if(aLevel.cIsComplete==true)
    {
        QString strrr;


    }

}
