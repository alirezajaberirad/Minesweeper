#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#define cellSize  20
#include <QMainWindow>
#include <QTimer>
#include <QPushButton>
#include<QtWidgets>
#include<vector>
#include "CustomizedPushButton.h"
//#include "game.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void tableMaker(int x, int y);
    const static int width=30;
    const static int height=16;
    void buttonClicked(QPushButton*button);
    int NumOfWins=0;
    int NumOfLose=0;
    void showdesk();
    QString playerName;
    std::vector<QLabel*> labels;
    int NumOfGuideFlags=20;
        bool endgame=false;

public slots:
    void on_pushButton_clicked();
//signals:
private slots:
    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

private:
   void on_Tile_click();
   void buttonRightClicked();
   void endGame();
   bool wonTheGame();
   void finishTheGame();
   void GuideTheMan();
   void flagTheTile(QPushButton*button);
   QPushButton*guidePushButt;



private:
    int seconds=0;

    Ui::MainWindow *ui;
    void pushButtonLander(int x, int y );
    void bombLander();
    bool bombCheck(int x,int y);
    bool bombField[width][height];
    bool revealedField[width][height];
    bool flaggedField[width][height];
    void setFieldToZero(int x,int y);
    int howManyBombAround(int x,int y);
    void revealNeighbors(int x,int y);
    std::vector<QPushButton*>fieldButtons;
    int NumOfDetectedBombs;
    int NumOfRevealedTiles;
    int NumOfBombs=100;
    void timer(QLabel*lbl);
};

#endif // MAINWINDOW_H
