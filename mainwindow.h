#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "drawarea.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    DrawArea* draw_area;



    void updateVx(int value);

    void updateVy(int value);

    void updateR(int value);

    void updateM(int value);

    void updateVxFromInput(const QString &text);

    void updateVyFromInput(const QString &text);

    void updateRFromInput(const QString &text);

    void updateMFromInput(const QString &text);

    void reset();
    void mode();
    void gravity();

};
#endif // MAINWINDOW_H
