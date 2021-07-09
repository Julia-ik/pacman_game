#include "pacman_game.h"
#include <QKeyEvent>
#include "appsettings.h"
#include <QGLWidget>
//#include "drawer.h"



pacman_game::pacman_game()
{
   AppSettings::instance().setQGLWidget(*this);

    mvMenu.push_back({eMenu::PLAY, "Play"});
    mvMenu.push_back({eMenu::BEST_SCORE, "Select lvl" });
    mvMenu.push_back({eMenu::SELECT_LEVEL, "Best Score"});
    mvMenu.push_back({eMenu::START, "Start"});
    mvMenu.push_back({eMenu::EXIT, "Exit"});
}

pacman_game::eMenu operator ++ (pacman_game::eMenu &aMenu)
{
    aMenu = pacman_game::eMenu(int(aMenu)+1);
    if(aMenu == pacman_game::eMenu::END)
    {
        aMenu = pacman_game::eMenu::PLAY;
        return aMenu;
    }
    return aMenu;
}

pacman_game::eMenu operator -- (pacman_game::eMenu &aMenu)
{
    aMenu = pacman_game::eMenu(int(aMenu)-1);
    if(aMenu == pacman_game::eMenu::BEGIN)
    {
        aMenu = pacman_game::eMenu::EXIT;
        return aMenu;
    }
    return aMenu;
}




int pacman_game::menuStateToInt(const pacman_game::eMenu &aMenu)
{
    switch(aMenu)
    {
        case pacman_game::eMenu::BEGIN: return (int)pacman_game::eMenu::BEGIN;
        case pacman_game::eMenu::PLAY: return (int)pacman_game::eMenu::PLAY;
        case pacman_game::eMenu::BEST_SCORE: return (int)pacman_game::eMenu::BEST_SCORE;
        case pacman_game::eMenu::SELECT_LEVEL: return (int)pacman_game::eMenu::SELECT_LEVEL;
        case pacman_game::eMenu::START: return (int)pacman_game::eMenu::START;
        case pacman_game::eMenu::EXIT: return (int)pacman_game::eMenu::EXIT;
        case pacman_game::eMenu::END: return (int)pacman_game::eMenu::END;
    }
    return  -1;
}


pacman_game::eState menuStateToGameState(const pacman_game::eMenu &aMenu)
{
    switch(aMenu)
    {
         case pacman_game::eMenu::BEGIN:
         case pacman_game::eMenu::END: return pacman_game::eState::MENU;
         case pacman_game::eMenu::SELECT_LEVEL: return pacman_game::eState::SELECT_LEVEL;
         case pacman_game::eMenu::START: return pacman_game::eState::CONTINUE_GAME;
         case pacman_game::eMenu::BEST_SCORE: return pacman_game::eState::BEST_SCORE;
         case pacman_game::eMenu::PLAY: return pacman_game::eState::NEW_GAME;
         case pacman_game::eMenu::EXIT: return pacman_game::eState::EXIT;

    }
    return pacman_game::eState::MENU;
}


void pacman_game::draw()
{

}

void pacman_game::initializeGL()
{
    static auto sw = AppSettings::instance().screenWidth();
    static auto sh = AppSettings::instance().screenHeight();
    glOrtho(0, sw, sh, 0, 0, 1);
    glEnable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_SMOOTH);
    glEnable(GL_TEXTURE_2D);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

    AppSettings::instance().load();
}
void pacman_game::resizeGL(int w, int h)
{
    static auto sw = AppSettings::instance().screenWidth();
    static auto sh = AppSettings::instance().screenHeight();
    glLoadIdentity();
    glViewport(0,0,(GLint)w,(GLint)h);
    glOrtho(0, sw, sh, 0, 0, 1);
}


void pacman_game::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    qglClearColor(QColor(123,104,238));

    proccesing();

    draw();

}

void pacman_game::keyReleaseEvent(QKeyEvent *apEvent)
{
     switch(mState)
     {
      case eState::MENU:
       {
         key_released_menu(apEvent->key());
         break;
       }
      case eState::NEW_GAME:
       {
        key_released_new_game(apEvent->key());
         break;
       }
      case eState::CONTINUE_GAME:
      {
        key_released_new_game(apEvent->key());
        break;
      }
      case eState::SELECT_LEVEL:
        {
           key_released_menu_select_lvl(apEvent->key());
            break;
        }
       case eState::BEST_SCORE:
        {
            key_released_best_score(apEvent->key());
            break;
        }
     case eState::EXIT:
        {
            //close();
            break;
        }

      }
     //if(apEvent->key()==Qt::Key_Escape)
     //{
        // close();
     //}
}

void pacman_game::draw_menu()
{
        static auto app_w = AppSettings::instance().screenWidth();
        static auto app_h = AppSettings::instance().screenHeight();

        static auto font = QFont("Sans",25);
        static auto font_selected = QFont("Fantasy",30);
        //font_selected.setBold(true);

        auto x = app_w -500;
        auto y= app_h-300;
        auto dy=55.f;
        int end = mvMenu.size();

        for(int i=0;i< end;i++)
        {
            if (i==menuStateToInt(mCurrentMenu))
            {
                qglColor(QColor(25,25,112));
                renderText(x, y, mvMenu[i].second.c_str(), font_selected);
            }
            else
            {
                qglColor(Qt::white);
                renderText(x, y, mvMenu[i].second.c_str(), font);
            }

            y += dy;
        }
};



void pacman_game::draw_menu_new_game()
{
    mDraw.draw(mLvl, *this);
    mLvl.releaseGhosts();
}
void pacman_game::draw_menu_continue_game()
{

}
void pacman_game::draw_menu_select_level()
{
    auto &app = AppSettings::instance();
    static auto app_w=app.screenWidth();
    static auto app_h=app.screenHeight();

    auto &levels = app.availableLevels();
    int lvl_count = (int)levels.size();

    static auto font = QFont("Helvetica", 15);
    static auto font_selected = QFont("Helvetica", 20);
    //font_selected.setBold(true);

    int tmp =(mSelectLevelIndex -2);
    int start = tmp<0 ? 0: tmp;

    tmp = (start +2);
    int end =(tmp<lvl_count)? tmp:lvl_count -1;

    auto x = app_w -500;
    auto y= app_h-300;
    auto dy=55.f;

    for(int i=start; i<=end;i++)
    {

        const auto &[lvl, isLock]= levels[i];
         QString item_str = "Level " + QString::number(lvl);
         QFont &rf = (i==mSelectLevelIndex) ? font_selected: font;
         Qt::GlobalColor color=Qt::cyan;
              if (isLock==true)
                  {
                    color = Qt::white;
                  }
        else
        {
            if(isLock ==false)
                color= Qt::yellow;
        }

        qglColor (color);
        renderText(x,y, item_str,rf);

        y+=dy;

    }


}
void pacman_game::draw_best_score()
{



}



void pacman_game::key_released_menu(int aKey)
{
    switch(aKey)
    {
       case Qt::Key_Up:
        {
           -- mCurrentMenu;
            break;
        }
       case Qt::Key_Down:
        {
        ++mCurrentMenu;
            break;
        }
       case Qt::Key_Enter:
       case Qt::Key_Return:
         {
              mState=menuStateToGameState(mCurrentMenu);

         }
    }
    updateGL();
}
void pacman_game::key_released_new_game(int aKey)
{

    switch(aKey)
  {
      case Qt::Key_Up:
        {
            mLvl.pacman_up();
             break;
        }
        case Qt::Key_Down:
        {
            mLvl.pacman_down();
             break;
        }
        case Qt::Key_Left:
          mLvl.pacman_left();
        break;
        case Qt::Key_Right:
         {
          mLvl.pacman_right();
            break;
         }
        case Qt::Key_Escape:
         {
            mState= eState::MENU;
            break;
          }
    }
        updateGL();
}

void pacman_game::key_released_menu_select_lvl(int aKey)
{

    const auto &levels = AppSettings::instance().availableLevels();
    int levels_count = (int) levels.size();

    switch(aKey)
  {
      case Qt::Key_Up:
        {
           --mSelectLevelIndex;
           if(mSelectLevelIndex<0)
           {
               mSelectLevelIndex =0;
           }
             break;
        }
        case Qt::Key_Down:
        {
            ++mSelectLevelIndex;
            if(mSelectLevelIndex>=levels_count)
            {
                mSelectLevelIndex= levels_count -1;
            }
             break;
        }
        case Qt::Key_Enter:
        case Qt::Key_Return:
         {
            if(mSelectLevelIndex>=0)
            {
                if(mSelectLevelIndex>= levels_count)
                {
                    break;
                }

                const auto &[lvl, islock]=levels[mSelectLevelIndex];

                if(islock)
                {
                    mLvl.load(lvl);

                    mState = eState::NEW_GAME;
                }
            }

            break;
         }
        case Qt::Key_Escape:
         {
            mState= eState::MENU;
            break;
          }
    }
        updateGL();
}
void pacman_game::key_released_best_score(int aKey)
{
    switch(aKey)
    {
        case Qt::Key_Escape:
            {
                mState=eState::MENU;
                  break;
            }
    }
    updateGL();
}
void pacman_game::key_released_continue_game(int aKey)
{

    switch(aKey)
  {
      case Qt::Key_Up:
        {
             break;
        }
        case Qt::Key_Down:
        {
             break;
        }
        case Qt::Key_Left:
        {
               break;
        }
        case Qt::Key_Right:
         {
            break;
         }
        case Qt::Key_Escape:
         {
            mState= eState::MENU;
            break;
         }
  }
        updateGL();

}




void pacman_game::proccesing()
{
 switch(mState)
 {
  case eState::MENU:
   {

     draw_menu();
     break;
   }
  case eState::NEW_GAME:
   {
     draw_menu_new_game();
     break;
   }
  case eState::CONTINUE_GAME:
  {

    draw_menu_continue_game();
    break;
  }
  case eState::SELECT_LEVEL:
    {
        draw_menu_select_level();
        break;
    }
   case eState::BEST_SCORE:
    {
        draw_best_score();
        break;
    }
 case eState::EXIT:
    {
        close();
        break;
    }
    }
}




