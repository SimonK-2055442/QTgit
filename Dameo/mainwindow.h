    #ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "bordview.h"
#include "chaturajibordview.h"
#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
private slots:
    void DameoButtonPressed();
    void ChaturajiButtonPressed();
private:
    BordView *dameoBord{};
    ChaturajiBordView* chaturajiBord{};
    QGraphicsView *view{};
};
#endif // MAINWINDOW_H
