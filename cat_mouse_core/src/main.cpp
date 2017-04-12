#include <QtGui>
#include <QApplication>
#include "mainwindow.h"

/*****************************************************************************
** Main
*****************************************************************************/

int main(int argc, char **argv)
{
    ros::init(argc, argv, "referee");

    /*********************
    ** Qt
    **********************/
    QApplication app(argc, argv);
    MainWindow w(argc, argv);
    w.show();
    int result = app.exec();
    return result;
}
