#include "drawarea.h"
#include "QPainter"
#include "QMouseEvent"
#include <iostream>
#include <ostream>
#include <qtimer.h>

DrawArea::DrawArea(QWidget *parent)
    : QOpenGLWidget{parent}
{
    timer = new QTimer();
    QTimer::connect(timer, &QTimer::timeout, this, &DrawArea::animate);
    timer->start(dt);


}

/**
 * @brief DrawArea::worldToView convert a world coordinate to a view coordinate
 */
Vec2 DrawArea::worldToView(Vec2 worldCoord){return Vec2{worldCoord[0],this->height()-worldCoord[1]};}
/**
 * @brief DrawArea::viewToWorld convert a view coordinate to a world coordinate
 */
Vec2 DrawArea::viewToWorld(Vec2 viewCoord){return Vec2{viewCoord[0],this->height()-viewCoord[1]};}


/**
 * @brief DrawArea::animate update the physical system and update the display
 */
void DrawArea::animate(){
    context.updatePhysicalSystem(dt);
    update();
}

/**
 * @brief DrawArea::affichage draw the particules, colliders and link constraints on the application
 */
void DrawArea::affichage(QPainter *painter, QPaintEvent *event, Context &context, DrawArea& drawArea){
    for(auto &particule:context.particules) {
        Vec2 coord = drawArea.worldToView(particule->pos);

        float x = coord[0];
        float y = coord[1];

        QRectF target(x-particule->radius, y-particule->radius, particule->radius*2, particule->radius*2);
        painter->setBrush(QBrush(Qt::red));
        painter->drawEllipse(target);
    }

    for (auto &colliderPtr:context.CollidersPtr){
        colliderPtr->draw(painter,drawArea.height());
    }

    for (auto& link:context.linkConstraints){
        link.draw(painter,drawArea.height());
    }
};

/**
 * @brief DrawArea::paintEvent define the QPainter of the DrawArea and call the affichage method
 */
void DrawArea::paintEvent(QPaintEvent *e){
    // dans la méthode pafloatEvent de votre nouveau Widget ajoutez :
    QPainter p(this);
    QRectF target( 0,0,this->width(),this->height());
    p.setBrush(QBrush(Qt::white));
    p.drawRect(target);

    affichage(&p,e,context,*this);
}



/**
 * @brief DrawArea::mousePressEvent add a solid to the simulation when the user double-click on the DrawArea
 */
void DrawArea::mouseDoubleClickEvent(QMouseEvent *e){
    x_ = e->x();
    y_ = e->y();

    //context.particules.push_back(Particule{this->worldToView(Vec2{x_,y_}),Vec2{vx,vy},r,m});

    context.create_solid(worldToView(Vec2{x_,y_}),Vec2{vx,vy},r,m);
}






