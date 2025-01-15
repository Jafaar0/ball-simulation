#include "drawarea.h"
#include "QPainter"
#include "QMouseEvent"
#include <qtimer.h>

DrawArea::DrawArea(QWidget *parent)
    : QOpenGLWidget{parent}
{
    timer = new QTimer();
    QTimer::connect(timer, &QTimer::timeout, this, &DrawArea::animate);
    timer->start(dt);
}


Vec2 DrawArea::worldToView(Vec2 worldCoord){return Vec2{worldCoord[0],this->height()-worldCoord[1]};}
Vec2 DrawArea::viewToWorld(Vec2 viewCoord){return Vec2{viewCoord[0],this->height()-viewCoord[1]};}



void DrawArea::animate(){
    context.updatePhysicalSystem(dt);
    update();
}

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

void DrawArea::paintEvent(QPaintEvent *e){
    QPainter p(this);
    QRectF target( 0,0,this->width(),this->height());
    p.setBrush(QBrush(Qt::white));
    p.drawRect(target);
    affichage(&p,e,context,*this);
}


void DrawArea::resetSimulation(){
    context.linkConstraints.clear();
    context.particules.clear();
    context.gravity=Vec2{0,-9.81};
}

void DrawArea::changeMode(){
    if (context.mode =="solid"){context.mode ="particule";}
    else if(context.mode =="particule"){context.mode = "solid";}
}

void DrawArea::changeGravity(){context.gravity=Vec2{-context.gravity[1],context.gravity[0]};}

void DrawArea::mouseDoubleClickEvent(QMouseEvent *e){
    x_ = e->position().x();
    y_ = e->position().y();

    if (context.mode=="solid"){context.create_solid(worldToView(Vec2{x_,y_}),Vec2{vx,vy},r,m);}
    else if (context.mode=="particule"){context.particules.push_back(std::make_shared<Particule>(Particule{this->worldToView(Vec2{x_,y_}),Vec2{vx,vy},r,m}));}
}
