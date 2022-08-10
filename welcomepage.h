#ifndef WELCOMEPAGE_H
#define WELCOMEPAGE_H

#include <QDialog>

namespace Ui {
class welcomePage;
}

class welcomePage : public QDialog
{
    Q_OBJECT

public:
    explicit welcomePage(QWidget *parent = 0);
    ~welcomePage();

private:
    Ui::welcomePage *ui;
};

#endif // WELCOMEPAGE_H
