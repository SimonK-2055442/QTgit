#ifndef WELCOME_H
#define WELCOME_H

#include <QGraphicsScene>
#include <QPushButton>
//#include <QGridLayout>

class Welcome: public QGraphicsScene
{
    Q_OBJECT

public:
    Welcome(QWidget *parent = nullptr);

private slots:
    void slotButtonDameo();
    void slotButtonChaturaji();

private:
    //QGridLayout *rooster;
    QPushButton *buttonDameo;
    QPushButton *buttonChaturaji;
    //QPushButton *buttonSoortSpel; //met of zonder AI
    //QPushButton *buttonBegginersModus; //met rode vakjes
};

#endif // WELCOME_H
