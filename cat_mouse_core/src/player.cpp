#include "player.h"

Player::Player(const char *name, float startX, float startY)
{
    inVel = n.subscribe(std::string(name)+std::string("/vel"), 10, &Player::updateSimVelocity, this);

    outVel = n.advertise<geometry_msgs::Twist>(std::string(name) + std::string("/cmd_vel"), 1);

    pose = n.subscribe(std::string(name)+std::string("/pose"), 10, &Player::updateOwnPosition, this);

    score = 0;
    x = startX;
    y = startY;
}

void Player::increaseScore()
{
    score += 1;
}

void Player::updateSimVelocity(const geometry_msgs::Twist::ConstPtr& vel)
{
    outVel.publish(vel);
}

void Player::updateOwnPosition(const cat_mouse_core::Pose::ConstPtr& pose)
{
    x = pose->x;
    y = pose->y;

}
