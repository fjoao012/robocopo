#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(int argc, char *argv[], QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    jf = new Player("JF", 1, 1);
    jo = new Player("JO", 1, 10);
    tc = new Player("TC", 10, 1);
    xa = new Player("XA", 10, 10);
    catIsPlayer = 0;

    pubRole = n.advertise<std_msgs::String>("role", 1);

    ros_update_timer_ = new QTimer(this);
    ros_update_timer_->setInterval(100); //100 ms
    ros_update_timer_->start();

    update_timer_ = new QTimer(this);
    update_timer_->setInterval(1000); //1 s
    update_timer_->start();

    connect(ros_update_timer_, SIGNAL(timeout()), this, SLOT(onUpdate()));
    connect(update_timer_, SIGNAL(timeout()), this, SLOT(onUpdateScore()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onUpdate()
{
  std::stringstream ss;

  switch ( timerCount % 1000 )
  {
    case 1:
      catIsPlayer = 1;
      ss << "JF";
      break;
    case 250:
      catIsPlayer = 2;
      ss << "JO";
      break;
    case 500:
      catIsPlayer = 3;
      ss << "TC";
      break;
    case 750:
      catIsPlayer = 4;
      ss << "XA";
      break;
  }
  timerCount++;

  checkCollision();

  if (!ros::ok())
  {
    close();
  }
  else
  {
    std_msgs::String msg;
    msg.data = ss.str();
    pubRole.publish(msg);
    ros::spinOnce();
  }
}

void MainWindow::checkCollision()
{
    if(catIsPlayer == 1)
    {
        if( abs(jf->x - jo->x) <= 0.5 && abs(jf->y - jo->y) <= 0.5 ||
            abs(jf->x - tc->x) <= 0.5 && abs(jf->y - tc->y) <= 0.5 ||
            abs(jf->x - xa->x) <= 0.5 && abs(jf->y - xa->y) <= 0.5 )
        {
            jf->increaseScore();
        }
    }
    else if(catIsPlayer == 2)
    {
        if( abs(jo->x - jf->x) <= 0.5 && abs(jo->y - jf->y) <= 0.5 ||
            abs(jo->x - tc->x) <= 0.5 && abs(jo->y - tc->y) <= 0.5 ||
            abs(jo->x - xa->x) <= 0.5 && abs(jo->y - xa->y) <= 0.5 )
        {
            jo->increaseScore();
        }
    }
    else if(catIsPlayer == 3)
    {
        if( abs(tc->x - jf->x) <= 0.5 && abs(tc->y - jf->y) <= 0.5 ||
            abs(tc->x - jo->x) <= 0.5 && abs(tc->y - jo->y) <= 0.5 ||
            abs(tc->x - xa->x) <= 0.5 && abs(tc->y - xa->y) <= 0.5 )
        {
            tc->increaseScore();
        }
    }
    else if(catIsPlayer == 4)
    {
        if( abs(xa->x - jf->x) <= 0.5 && abs(xa->y - jf->y) <= 0.5 ||
            abs(xa->x - jo->x) <= 0.5 && abs(xa->y - jo->y) <= 0.5 ||
            abs(xa->x - tc->x) <= 0.5 && abs(xa->y - tc->y) <= 0.5 )
        {
            xa->increaseScore();
        }
    }
}

void MainWindow::onUpdateScore()
{
    ui->jfScoreboard->setText(QString::number(jf->score));
    ui->joScoreboard->setText(QString::number(jo->score));
    ui->tcScoreboard->setText(QString::number(tc->score));
    ui->xaScoreboard->setText(QString::number(xa->score));

    ui->catLabel->setText(QString::number(catIsPlayer));
}
