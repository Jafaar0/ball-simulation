#ifndef DRAWAREA_H
#define DRAWAREA_H

#include <QWidget>
#include <QtOpenGLWidgets/qopenglwidget.h>
#include <qtimer.h>
#include "context.h"


/**
 * @brief The DrawArea class is the class that contains the display of the application
 * @details It contains the physical system and the display of the particules, colliders and link constraints
 */
class DrawArea : public QOpenGLWidget
{

public:
    explicit DrawArea(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *e) override;

    void mouseDoubleClickEvent(QMouseEvent *event) override;

    void animate();

    void affichage(QPainter *painter, QPaintEvent *event, Context &context, DrawArea& drawArea);

    Vec2 worldToView(Vec2 world_pos);
    Vec2 viewToWorld(Vec2 view_pos);

    void setVx(float vx_) { vx = vx_; }
    void setVy(float vy_) { vy = vy_; }
    void setR(float r_) { r = r_; }
    void setM(float m_) { m = m_; }

    void resetSimulation();
    void changeMode();
    void changeGravity();
signals:
private:
    float dt = 1e-3;
    float m;
    float vx;
    float vy;
    float r;
    QTimer *timer;
    Context context;
    float x_, y_;
};

#endif // DRAWAREA_H

