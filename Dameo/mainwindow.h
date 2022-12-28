    #ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "bordview.h"
#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
private slots:
    void buttonpressed();
private:
    BordView *sceneBord{};
    QGraphicsView *view{};
};
#endif // MAINWINDOW_H
