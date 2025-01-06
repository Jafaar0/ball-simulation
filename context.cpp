#include "context.h"

Context::Context() {
    addPlanCollider(Vec2{100,100},Vec2{100,400}, false);
    addPlanCollider(Vec2{100,400},Vec2{500,400}, true);
    addPlanCollider(Vec2{500,400},Vec2{500,100}, false);
    addPlanCollider(Vec2{500,100},Vec2{100,100}, true);

    addSphereCollider(Vec2{100,200},50);
}

void Context::updatePhysicalSystem(float dt){
    applyExternalForce(dt);
    updateExpectedPosition(dt);

    addStaticContactConstraints(dt);
    addDynamicContactConstraints(dt);
    projectConstraints();
/*
    while(!(staticConstraints.empty() && dynamicConstraints.empty())){
        addStaticContactConstraints(dt);
        addDynamicContactConstraints(dt);
    }*/
    updateVelocityAndPosition(dt);
};

void Context::addPlanCollider(Vec2 a, Vec2 b, bool c) {
    Vec2 origine = (a+b)*(0.5);
    float largeur = sqrt((b-a)*(b-a));
    Vec2 normale{b[1]-a[1],b[0]-a[0]};
    normale = normale*(1/sqrt(normale*normale));
    if(c) normale = normale*(-1);
    CollidersPtr.push_back(std::make_shared<PlanCollider>(normale,origine,largeur));
}

void Context::addSphereCollider(Vec2 centre, float rayon) {
    CollidersPtr.push_back(std::make_shared<SphereCollider>(centre, rayon));
}

void Context::applyExternalForce(float dt){
    //gravity
    float g = 9.81;
    for(Particule &particule:particules){
        particule.velocity[1] -= g;
    }
/**/
    //air resistance
    float f = 2;
    for(Particule &particule:particules){
        particule.velocity = particule.velocity - particule.velocity*(f*dt);
    }
};

void Context::updateExpectedPosition(float dt){
    for(Particule &particule:particules){
        particule.pos_ = particule.pos+(particule.velocity*dt);
    }
};

void Context::updateVelocityAndPosition(float dt){
    for(Particule &particule:particules){
        particule.velocity = (particule.pos_ - particule.pos)*(1/dt);
        particule.pos = particule.pos_;
    }
};

bool PlanCollider::checkContact(const Particule& collider)  {

    Vec2 vecDirecteur = Vec2{-this->normale()[1],this->normale()[0]};


    return (collider.pos_-this->origine())*this->normale()-collider.radius<0 &&
           collider.velocity*normale()<0 &&
           abs((collider.pos_-origine())*vecDirecteur)<(largeur/2);
};

void PlanCollider::draw(QPainter* painter,float height) const {

    Vec2 vecDirecteur = Vec2{-normale()[1],normale()[0]};

    Vec2 coin1 = origine() + vecDirecteur * (largeur / 2);
    Vec2 coin2 = origine() - vecDirecteur * (largeur / 2);
    Vec2 coin3 = coin2 - normale()*2;
    Vec2 coin4 = coin1 - normale()*2;



    QPolygonF planPolygon;
    planPolygon << QPointF(coin1[0], height-coin1[1])
                << QPointF(coin2[0], height-coin2[1])
                << QPointF(coin3[0], height-coin3[1])
                << QPointF(coin4[0], height-coin4[1]);

    painter->setBrush(QBrush(Qt::black, Qt::Dense4Pattern));
    painter->setPen(Qt::black);
    painter->drawPolygon(planPolygon);
}

Vec2 SphereCollider::normale(const Particule& particule) const {
    return (particule.pos_-p)*(1/sqrt((particule.pos_-p)*(particule.pos_-p)));
}

bool SphereCollider::checkContact(const Particule& collider)  {
    return sqrt((collider.pos_ - p)*(collider.pos_ - p)) - collider.radius-r<0;
};

void SphereCollider::draw(QPainter* painter,float height) const {

    Vec2 coord = Vec2{p[0],height-p[1]};

    float x = coord[0];
    float y = coord[1];

    QRectF target(x-r, y-r, r*2, r*2);
    painter->setBrush(QBrush(Qt::black, Qt::Dense4Pattern));
    painter->drawEllipse(target);
}

Vec2 SphereCollider::pc(const Particule& particule) {//closest point on the collider
    return p+normale(particule)*r;
}

void Context::addStaticContactConstraints(float dt){
    staticConstraints.clear();
    for( auto& particule:particules){
        for(auto &colliderptr:CollidersPtr){
            if (colliderptr->checkContact(particule)) {
                staticConstraints.push_back(StaticConstraint(particule,colliderptr));
            }
        }
    }
}

void enforceStaticGrouneConstraint(StaticConstraint& constraint) {

    Particule& particule = constraint.particule;
    const Vec2& nc = constraint.collider->normale(particule);
    const Vec2& pc = constraint.collider->pc(particule);

    Vec2 qc = particule.pos_ - (nc*((particule.pos_ - pc)*nc));
    float C = (particule.pos_ - qc)*nc-particule.radius;
    Vec2 delta = nc*(-C);

    particule.pos_ = particule.pos_ + delta;
}




bool Particule::checkContact(const Particule& collider)  {
    return sqrt((collider.pos_ - this->pos_)*(collider.pos_ - this->pos_)) - collider.radius-this->radius<0;
};

void solveDynamicConstraint(DynamicConstraint& constraint){
    Particule& p1 = constraint.particule1;
    Particule& p2 = constraint.particule2;

    Vec2 x_ji = p1.pos_ - p2.pos_;
    float C = sqrt(x_ji*x_ji) - (p1.radius+p2.radius);
    float sigma_i = (C/p1.mass)/((1/p1.mass)+(1/p2.mass));

    Vec2 delta_i = x_ji * (-sigma_i/sqrt(x_ji*x_ji));
    p1.pos_ = p1.pos_ + delta_i;

    Vec2 delta_j = x_ji * ((sigma_i*p1.mass/p2.mass)/sqrt(x_ji*x_ji));
    p2.pos_ = p2.pos_ + delta_j;
}

void Context::addDynamicContactConstraints(float dt) {
    dynamicConstraints.clear();
    for (int i = 0; i < particules.size(); ++i) {
        for (int j = i + 1; j < particules.size(); ++j) {
            if(particules[i].checkContact(particules[j])) {
                dynamicConstraints.push_back(DynamicConstraint(particules[i],particules[j]));
            }
        }
    }
};


void Context::projectConstraints(){
    for(auto& staticConstraint:staticConstraints){
        enforceStaticGrouneConstraint(staticConstraint);
    }
    for(auto& dynamicConstraint:dynamicConstraints){
        solveDynamicConstraint(dynamicConstraint);
    }
}

/*
void DrawArea::animate(){
    for(auto& center:context.particules){
        gravity(center);
        airResistance(center);

        center.at(0) += center.at(2);
        center.at(1) += center.at(3);

        //if(center.at(1)+r>=this->height()) center.at(1)=this->height()-r;
    }

    for(auto& center:vec){
        interaction(center);
    }
    update();
}

void interaction(std::vector<float> &self){
    for(auto& other:vec){
        if(other!=self) {
            float dist2 = (self.at(0)-other.at(0))*(self.at(0)-other.at(0)) + (self.at(1)-other.at(1))*(self.at(1)-other.at(1));

            //std::cout<<self.at(1)<<other.at(1)<<std::endl;
            //std::cout<<dist2<<std::endl;
            if (dist2<(4*r*r)) {
                float midpofloatx = std::round((double)(self.at(0)+other.at(0))/2);
                float midpofloaty = std::round((double)(self.at(1)+other.at(1))/2);

                std::pair<double,double> dir((double)(self.at(0)-other.at(0))/sqrt(dist2),(double)(self.at(1)-other.at(1))/sqrt(dist2));
                //std::cout<<dir.at(0)<<","<<dir.at(1)<<std::endl;

                self.at(0) = std::round(midpofloatx + std::round(r * dir.first));
                self.at(1) = std::round(midpofloaty + std::round(r * dir.second));
                other.at(0) = std::round(midpofloatx - std::round(r * dir.first));
                other.at(1) = std::round(midpofloaty - std::round(r * dir.second));

                //std::cout<<self.at(0)<<","<<self.at(1)<<std::endl;
                //std::cout<<other.at(0)<<","<<other.at(1)<<std::endl;


            }
        }
    }
}
*/
