#ifndef MINESWEEPERPLAYFIELD_H
#define MINESWEEPERPLAYFIELD_H

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

private:
    void pushButtonLander(int x, int y );
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
#endif // MINESWEEPERPLAYFIELD_H
