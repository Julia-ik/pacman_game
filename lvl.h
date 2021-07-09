#ifndef LVL_H
#define LVL_H
#include <string>
#include <vector>
#include "ghost.h"

class lvl
{
    friend class drawer;
    friend class ghost;
public:
    enum class  eField
    {
        EMPTY=0,
        WALL,
        PACMAN,
        GHOST,
        COOKIE,
        COIN
    };
  public:
    lvl();
    void load(int);//ноемр уровня
    void load(std::string);//старт с прошлого места
    bool isComplete();//завершен ли уровень
    bool isLoad();//загрузилась ли игра
    bool isOver();//проиграл

    void pacman_up();
    void pacman_down();
    void pacman_left();
    void pacman_right();

    int goal();//максимум очков
    int leftToGoal();//сколько осталось до максимума
    int lives();//сколько всего
    int livesLeft();//сколько осталось


  private:
    int cLvl{-1};//загрузился уровень или нет итд
    int earnedPoints{0};
    int cLives{3};
    int columns{0};
    int lines{0};

    int max{500};
    void move(int, int);

    bool cIsComplete{false};
    bool cIsLoad{false};
    bool cIsOver{false};
public:
    std::pair<int,int> cPlayerPosition;
    std::vector<eField> cPlaySquare;

    std::vector<ghost> ghosts;

   void move_ghost();
   void releaseGhosts();


};
#endif // LVL_H
