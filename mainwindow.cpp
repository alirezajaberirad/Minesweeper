#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextStream>
#include <QString>
#include <QPixmap>
#include <QDebug>
#include <QIcon>
#include <iostream>
#include <time.h>
#include <string>
#include <ctime>
#include <QMessageBox>
#include "bombfield.h"
#include <QLabel>
#include <thread>
#include <chrono>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //time=2;
    //check=true;

    QPixmap pix(":/img/img/minesweeperlogo.jpg");
    int w=ui->labelPic->width();
    int h=ui->labelPic->height();

    ui->labelPic->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));

}

MainWindow::~MainWindow()
{
    delete ui;

}

/*void MainWindow::myFunction(bool check)
{
    if(check){
        time++;
        ui->label->setNum(time);
    }
    else time=0;
}*/


void MainWindow::on_pushButton_clicked()
{
    CustomizedPushButton* guide=new CustomizedPushButton(this);
    guide->setText("GUIDE");
    guide->setFixedWidth(cellSize*6);
    guide->setGeometry(cellSize*(width-6),cellSize*height,cellSize*(width-6),cellSize*height);
    guide->show();
    connect(guide, &CustomizedPushButton::clicked, this, [=] () {GuideTheMan();});
    guidePushButt=guide;
    QLabel* timeLabel=new QLabel(this);
    timeLabel->setFixedSize(5*cellSize,1*cellSize);
    timeLabel->setGeometry(cellSize*(width-6),cellSize*height,cellSize*(width-6),cellSize*height);
    timeLabel->show();
    timer(timeLabel);
    playerName= ui->nameLine->text();
    if(playerName==NULL)
        playerName="Unknown Player";
     showdesk();
    setFieldToZero(width, height);
    bombLander();







    MainWindow::tableMaker(width,height);
    MainWindow::resize(width*cellSize,height*(cellSize+4));
    //Game();
   // MainWindow::myFunction(check);
   // stack<int> playerGamingRecord;//this will save the history of the player achieved points
   // QTextStream stream(&inFile);
   // QFile inFile("playerInfo.txt");
   // inFile.open(QIODevice::WriteOnly);
   // stream<<playerName<<endl;
   // inFile.flush();
}

void MainWindow::pushButtonLander(int x, int y)
{
    CustomizedPushButton *button=new CustomizedPushButton(this);
    QIcon icon;
    icon.addFile(QString::fromUtf8(":/img/img/gameBottons.png"), QSize(), QIcon::Normal);

    button->setObjectName("button");
    button->setIcon(icon);
    button->setFixedSize(cellSize,cellSize);
    button->setGeometry(cellSize*x,cellSize*y,cellSize*x,cellSize*y);
    button->show();
    connect(button, &CustomizedPushButton::clicked, this, [=] () {on_Tile_click();});
    connect(button, &CustomizedPushButton::rightClicked, this, &MainWindow::buttonRightClicked);
    fieldButtons.push_back(button);
}

void MainWindow::bombLander()
{
    srand(time(NULL));
    int xDist,yDist;
    for(int i=0;i<NumOfBombs;i++){
        do{
             xDist=rand()%width;
             yDist=rand()%height;
        }
        while(bombCheck(xDist,yDist));
        bombField[xDist][yDist]=1;
    }
}

bool MainWindow::bombCheck(int x,int y)
{
    if(bombField[x][y])
        return true;
    return false;
}

void MainWindow::setFieldToZero(int x, int y)
{
    for(int i=0;i<x;i++){
        for(int j=0;j<y;j++){
            bombField[i][j]=false;
            revealedField[i][j]=false;
            flaggedField[i][j]=false;
        }
    }
    NumOfDetectedBombs=0;
    NumOfRevealedTiles=0;
}

int MainWindow::howManyBombAround(int x, int y)
{
    int i,j;
    int cnt=0;
    if(x>0)
        i=x-1;
    else i=0;
    for(;i<=x+1&&i<width;i++){
        if(y>0)
             j=y-1;
        else  j=0;
        for(;j<=y+1&&j<height;j++){
            if(bombField[i][j])
                cnt++;
        }
    }
    return cnt;
}

void MainWindow::revealNeighbors(int x, int y)
{
    int i,j;
    if(y>0)
        j=y-1;
    else j=0;


    for(;j<=y+1 && j<height;j++){
        if(x>0)
            i=x-1;
        else i=0;
        for(;i<=x+1&&i<width;i++){
            QPushButton*button=fieldButtons[j*width+i];
            buttonClicked(button);
        }
    }
}



void MainWindow::tableMaker(int x, int y)
{
    for(int j=0;j<y;j++){
        for(int i=0;i<x;i++)
            pushButtonLander(i,j);
    }
}



void MainWindow::on_Tile_click(){
    QPushButton* button = (QPushButton*) sender();
    buttonClicked(button);

}
void MainWindow::GuideTheMan()
{
    QPushButton* guideButton=(QPushButton*)sender();
    guideButton->close();
    srand(time(NULL));
    int xDist,yDist;
    for(int i=0;i<NumOfGuideFlags;i++){
        do{
             xDist=rand()%width;
             yDist=rand()%height;
        }
        while(!bombField[xDist][yDist]);
        flagTheTile(fieldButtons[yDist*width+xDist]);

    }
}

void MainWindow::flagTheTile(QPushButton *button)
{
    int x=button->x()/cellSize;
    int y=button->y()/cellSize;
    if(!revealedField[x][y] && !flaggedField[x][y]){
        button->setIcon(QIcon(":/img/flag.png"));
        flaggedField[x][y]=true;
        if(bombField[x][y])
            NumOfDetectedBombs++;
    }
    else if(!revealedField[x][y] && flaggedField[x][y]){
        button->setIcon(QIcon(":/img/img/gameBottons.png"));
        flaggedField[x][y]=false;
    }
    else return;
}
void MainWindow::buttonRightClicked(){
    if(wonTheGame()){
        finishTheGame();
    }
    QPushButton* button = (QPushButton*) sender();
    flagTheTile(button);
}

void MainWindow::endGame()
{
    QPushButton* button;
    QLabel* label;
    for(int i=0;i<width;i++){
        for(int j=0;j<height;j++){
            button=fieldButtons[j*width+i];
            if(bombField[button->x()/cellSize][button->y()/cellSize]&&!flaggedField[button->x()/cellSize][button->y()/cellSize])
                button->setIcon(QIcon(":/img/bomb.png"));
            else if(!bombField[button->x()/cellSize][button->y()/cellSize]&&flaggedField[button->x()/cellSize][button->y()/cellSize])
                button->setIcon(QIcon(":/img/wrongflagged.png"));
        }
    }
    QMessageBox::StandardButton reply=QMessageBox::question(this,"You Lost","You lost! Do you want to play the game again?",QMessageBox::Yes | QMessageBox::No);
    if(reply==QMessageBox::Yes){
        for(int i=0;i<width*height;i++){
            button=fieldButtons[i];
            button->close();
        }
        for(int i=0;i<3;i++){
            label=labels[i];
            label->close();
        }
        endgame=true;
        seconds=0;
        guidePushButt->close();
        labels.clear();
        fieldButtons.clear();
        NumOfLose++;
        on_pushButton_clicked();
    }
    else
        QApplication::quit();
}

bool MainWindow::wonTheGame()
{
    if(NumOfDetectedBombs==NumOfBombs || NumOfRevealedTiles==(width*height)-NumOfBombs)
        return true;
    return false;
}

void MainWindow::finishTheGame()
{
    QPushButton* button;
    QMessageBox::StandardButton reply=QMessageBox::question(this,"You Won","You won! Do you want to play the game again?",QMessageBox::Yes | QMessageBox::No);
    if(reply==QMessageBox::Yes){
        for(int i=0;i<width*height;i++){
            button=fieldButtons[i];
            button->close();
        }
        fieldButtons.clear();
        NumOfWins++;
        on_pushButton_clicked();
    }
    else
        QApplication::quit();
}


void MainWindow::buttonClicked(QPushButton*button)
{
    if(wonTheGame()){
        finishTheGame();
    }
    int x=button->x()/cellSize;
    int y=button->y()/cellSize;
    if(bombField[x][y] && !flaggedField[x][y]){
        button->setIcon(QIcon(":/img/bomb.png"));
        endGame();
    }
    else if(!flaggedField[x][y] && !revealedField[x][y]){
        revealedField[x][y]=true;
        NumOfRevealedTiles++;

        switch (howManyBombAround(x,y)){
        case 0:
            button->setIcon(QIcon(":/img/revealed.png"));
            revealNeighbors(x,y);
            break;
        case 1:
            button->setIcon(QIcon(":/img/1.png"));
            break;
        case 2:
            button->setIcon(QIcon(":/img/2.png"));
            break;
        case 3:
            button->setIcon(QIcon(":/img/3.png"));
            break;
        case 4:
            button->setIcon(QIcon(":/img/4.png"));
            break;
        case 5:
            button->setIcon(QIcon(":/img/5.png"));
            break;
        case 6:
            button->setIcon(QIcon(":/img/6.png"));
            break;
        case 7:
            button->setIcon(QIcon(":/img/7.png"));
            break;
        case 8:
            button->setIcon(QIcon(":/img/8.png"));
            break;
        }
    }
}

void MainWindow::showdesk()
{
    QLabel *label1=new QLabel(this);
    QString PlayerName="Player Name:"+playerName;
    label1->setGeometry(cellSize,height*cellSize,cellSize,height*cellSize);
    label1->setText(PlayerName);
    label1->setFixedSize(cellSize*10,cellSize*4);
    label1->show();
    labels.push_back(label1);



    QLabel *label2=new QLabel(this);
    QString winMessage="win:"+QString::number(NumOfWins)+" times";
    label2->setGeometry((width-2)*(cellSize)/2,height*cellSize,(width-2)*cellSize/2,height*cellSize);
    label2->setText(winMessage);
    label2->setFixedSize(cellSize*8,cellSize*4);
    label2->show();
    labels.push_back(label2);




    QLabel *label3=new QLabel(this);
    QString loseMessage="lose:"+QString::number(NumOfLose)+" times";
    label3->setGeometry((width-4)*cellSize,height*cellSize,(width-4)*cellSize,height*cellSize);
    label3->setText(loseMessage);
    label3->setFixedSize(cellSize*8,cellSize*4);
    label3->show();
    labels.push_back(label3);

}


void MainWindow::timer(QEvent*timer,QLabel*lbl){

    assert(!endgame);
    time_t current_time;
    time_t baseTime=current_time;
    current_time = time(NULL);
    seconds=current_time-baseTime;
    lbl->setText("time: "+QString::number(seconds));
}

void MainWindow::on_pushButton_4_clicked()
{
    NumOfBombs=150;
}

void MainWindow::on_pushButton_3_clicked()
{
    NumOfBombs=90;
}

void MainWindow::on_pushButton_2_clicked()
{
    NumOfBombs=20;
}
