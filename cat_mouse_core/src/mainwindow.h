#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

#include <sstream>

#ifndef Q_MOC_RUN  // See: https://bugreports.qt-project.org/browse/QTBUG-22829
    #include <ros/ros.h>
    #include <std_msgs/String.h>
    #include <geometry_msgs/Twist.h>
    #include <geometry_msgs/Pose.h>
#endif

#include "player.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(int argc, char* argv[], QWidget *parent = 0);
    ~MainWindow();
private slots:
    void onUpdate();
    void onUpdateScore();

private:
    Ui::MainWindow *ui;
    QTimer* ros_update_timer_;
    QTimer* update_timer_;
    int timerCount = 0;

    int catIsPlayer = 0;
    void checkCollision();

    Player *jf;
    Player *jo;
    Player *tc;
    Player *xa;

    ros::NodeHandle n;

    ros::Publisher pubRole;

    void roleCallback(const std_msgs::String::ConstPtr& msg);
};

#endif // MAINWINDOW_H
