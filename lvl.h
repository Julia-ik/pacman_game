#ifndef LVL_H
#define LVL_H
#include <string>
#include <vector>
#include "ghost.h"
#include  "GameEnums.h"
#include <thread>


class lvl
{
    friend class drawer;
    friend class ghost;
  public:
    lvl();
    bool cIsComplete{false};
    bool areGhostsReleased{false};
    bool cIsLoad{false};
    bool cIsOver{false};
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

    int max{400};
    void move(int, int);
    void youWon_Lose();


public:
    std::pair<int,int> cPlayerPosition;
    std::vector<eField> cPlaySquare;

    std::vector<ghost> ghosts;
    std::vector<std::thread> thread_vector;

   void move_ghost();
   void releaseGhosts();


};
#endif // LVL_H
