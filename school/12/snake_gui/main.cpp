#include "snake.hh"

#include <QApplication>
#include <iostream>

using std::cout;
using std::endl;

int main(int argc, char *argv[])
{
    QApplication app(argc,argv);
    Snake main = Snake();
    main.drawSnake();


    return app.exec();
}
