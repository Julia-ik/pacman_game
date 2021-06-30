#include "pacman_game.h"
#include <QKeyEvent>
#include "appsettings.h"
#include <QGLWidget>



pacman_game::pacman_game()
{
    mvMenu.push_back({eMenu::PLAY, "Play"});
    mvMenu.push_back({eMenu::BEST_SCORE, "Best Score"});
    mvMenu.push_back({eMenu::SELECT_LEVEL, "Select lvl"});
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
    qglClearColor(Qt::darkYellow);
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

        static auto font = QFont("Fantasy",25);
        static auto font_selected = QFont("Fantasy",30);
        font_selected.setBold(true);

        auto x = app_w -500;
        auto y= app_h-300;
        auto dy=55.f;
        int end = mvMenu.size();

        for(int i=0;i< end;i++)
        {
            if (i==menuStateToInt(mCurrentMenu))
            {
                qglColor(Qt::green);
                renderText(x, y, mvMenu[i].second.c_str(), font_selected);
            }
            else
            {
                qglColor(Qt::black);
                renderText(x, y, mvMenu[i].second.c_str(), font);
            }

            y += dy;
        }
};



void pacman_game::draw_menu_new_game()
{

}
void pacman_game::draw_menu_continue_game()
{

}
void pacman_game::draw_menu_select_level()
{

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
             break;
        }
        case Qt::Key_Down:
        {
             break;
        }
        case Qt::Key_Enter:
        case Qt::Key_Return:
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

void pacman_game::key_released_menu_select_lvl(int aKey)
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
        case Qt::Key_Enter:
        case Qt::Key_Return:
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




