#ifndef PLAYER_H
#define PLAYER_H

#ifndef Q_MOC_RUN  // See: https://bugreports.qt-project.org/browse/QTBUG-22829
    #include <ros/ros.h>
    #include <std_msgs/String.h>
    #include <geometry_msgs/Twist.h>
    #include <geometry_msgs/Pose.h>
#endif

#include <string>
#include "cat_mouse_core/Pose.h"

class Player
{
public:
    Player(const char* name, float startX, float startY);

    float x;
    float y;

    int score = 0;
    void increaseScore();

private:
    ros::NodeHandle n;

    ros::Subscriber inVel;
    ros::Publisher outVel;

    ros::Subscriber pose;

    void updateSimVelocity(const geometry_msgs::Twist::ConstPtr& vel);
    void updateOwnPosition(const cat_mouse_core::Pose::ConstPtr& pose);
};

#endif // PLAYER_H
