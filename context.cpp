#include "context.h"

Context::Context() {
    // Cadre intérieur
    addPlanCollider(Vec2{50,50},Vec2{50,400}, true,Qt::black);
    addPlanCollider(Vec2{50,400},Vec2{650,400}, true,Qt::black);
    addPlanCollider(Vec2{650,400},Vec2{650,50}, true,Qt::black);
    addPlanCollider(Vec2{650,50},Vec2{50,50}, true,Qt::black);

    // Cadre extérieur
    addPlanCollider(Vec2{20,20},Vec2{20,650}, true,Qt::black);
    addPlanCollider(Vec2{20,650},Vec2{1500,650}, true,Qt::black);
    addPlanCollider(Vec2{1500,650},Vec2{1500,20}, true,Qt::black);
    addPlanCollider(Vec2{1500,20},Vec2{20,20}, true,Qt::black);

    // Structure haut gauche
    addSphereCollider(Vec2{100,320},25,Qt::blue);
    addSphereCollider(Vec2{145,320},20,Qt::magenta);
    addSphereCollider(Vec2{180,320},15,Qt::red);
    addSphereCollider(Vec2{205,320},10,Qt::yellow);
    addSphereCollider(Vec2{220,320},5,Qt::green);

    // Structure milieu gauche
    addPlanCollider(Vec2{50,250},Vec2{250,200}, false,Qt::blue);
    addSphereCollider(Vec2{249,199},1,Qt::blue);
    addPlanCollider(Vec2{250,200},Vec2{230,180}, false,Qt::blue);
    addSphereCollider(Vec2{229,181},1,Qt::blue);
    addPlanCollider(Vec2{230,180},Vec2{50,230}, false,Qt::blue);

    // Structure milieu
    addPlanCollider(Vec2{250,110},Vec2{350,300}, false,Qt::green);
    addSphereCollider(Vec2{351,299},1,Qt::green);
    addPlanCollider(Vec2{350,300},Vec2{380,280}, false,Qt::green);
    addSphereCollider(Vec2{379,279},1,Qt::green);
    addPlanCollider(Vec2{380,280},Vec2{280,120}, false,Qt::green);
    addSphereCollider(Vec2{279,121},1,Qt::green);
    addPlanCollider(Vec2{280,120},Vec2{250,100}, false,Qt::green);
    addSphereCollider(Vec2{249,101},1,Qt::green);
    addPlanCollider(Vec2{250,100},Vec2{200,90}, false,Qt::green);
    addSphereCollider(Vec2{201,91},1,Qt::green);
    addPlanCollider(Vec2{200,90},Vec2{200,100}, false,Qt::green);
    addSphereCollider(Vec2{201,99},1,Qt::green);
    addPlanCollider(Vec2{200,100},Vec2{250,110}, false,Qt::green);
    addSphereCollider(Vec2{251,109},1,Qt::green);

    // Ronds droite
    addSphereCollider(Vec2{350,130},20,Qt::yellow);
    addSphereCollider(Vec2{580,180},10,Qt::magenta);
    addSphereCollider(Vec2{510,330},20,Qt::cyan);

    // Structure bas droite
    addPlanCollider(Vec2{600,80},Vec2{550,80}, false,Qt::magenta);
    addSphereCollider(Vec2{551,81},1,Qt::magenta);
    addPlanCollider(Vec2{550,80},Vec2{550,90}, false,Qt::magenta);
    addSphereCollider(Vec2{551,89},1,Qt::magenta);
    addPlanCollider(Vec2{550,90},Vec2{590,90}, false,Qt::magenta);
    addSphereCollider(Vec2{591,89},1,Qt::magenta);
    addPlanCollider(Vec2{590,90},Vec2{590,150}, false,Qt::magenta);
    addSphereCollider(Vec2{591,149},1,Qt::magenta);
    addPlanCollider(Vec2{590,150},Vec2{600,150}, false,Qt::magenta);
    addSphereCollider(Vec2{599,149},1,Qt::magenta);
    addPlanCollider(Vec2{600,150},Vec2{600,80}, false,Qt::magenta);
    addSphereCollider(Vec2{599,81},1,Qt::magenta);

    // 42 easter-egg
    //4
    addPlanCollider(Vec2{900,550},Vec2{900,340}, true,Qt::black);
    addPlanCollider(Vec2{900,340},Vec2{990,340}, true,Qt::black);
    addPlanCollider(Vec2{990,340},Vec2{990,200}, true,Qt::black);
    addPlanCollider(Vec2{990,200},Vec2{1010,200}, true,Qt::black);
    addPlanCollider(Vec2{1010,200},Vec2{1010,340}, true,Qt::black);
    addPlanCollider(Vec2{1010,340},Vec2{1100,340}, true,Qt::black);
    addPlanCollider(Vec2{1100,340},Vec2{1100,360}, true,Qt::black);
    addPlanCollider(Vec2{1100,360},Vec2{1010,360}, true,Qt::black);
    addPlanCollider(Vec2{1010,360},Vec2{1010,400}, true,Qt::black);
    addPlanCollider(Vec2{1010,400},Vec2{990,400}, true,Qt::black);
    addPlanCollider(Vec2{990,400},Vec2{990,360}, true,Qt::black);
    addPlanCollider(Vec2{990,360},Vec2{920,360}, true,Qt::black);
    addPlanCollider(Vec2{920,360},Vec2{920,550}, true,Qt::black);
    addPlanCollider(Vec2{920,550},Vec2{900,550}, true,Qt::black);


    //2
    addPlanCollider(Vec2{1200,550},Vec2{1400,550}, false,Qt::black);
    addPlanCollider(Vec2{1400,550},Vec2{1400,365}, false,Qt::black);
    addPlanCollider(Vec2{1400,365},Vec2{1220,365}, false,Qt::black);
    addPlanCollider(Vec2{1220,365},Vec2{1220,220}, false,Qt::black);
    addPlanCollider(Vec2{1220,220},Vec2{1400,220}, false,Qt::black);
    addPlanCollider(Vec2{1400,220},Vec2{1400,200}, false,Qt::black);
    addPlanCollider(Vec2{1400,200},Vec2{1200,200}, false,Qt::black);
    addPlanCollider(Vec2{1200,200},Vec2{1200,385}, false,Qt::black);
    addPlanCollider(Vec2{1200,385},Vec2{1380,385}, false,Qt::black);
    addPlanCollider(Vec2{1380,385},Vec2{1380,530}, false,Qt::black);
    addPlanCollider(Vec2{1380,530},Vec2{1200,530}, false,Qt::black);
    addPlanCollider(Vec2{1200,530},Vec2{1200,550}, false,Qt::black);

}

void Context::updatePhysicalSystem(float dt){


    applyExternalForce(dt);
    updateExpectedPosition(dt);


    addStaticContactConstraints(dt);
    addDynamicContactConstraints(dt);
    projectConstraints();

    applyLinkConstraints(dt);

    updateVelocityAndPosition(dt);
};

void Context::addPlanCollider(Vec2 a, Vec2 b, bool c,QColor color) {
    Vec2 origine = (a+b)*(0.5);
    float largeur = sqrt((b-a)*(b-a));
    Vec2 normale{-b[1]+a[1],b[0]-a[0]};
    normale = normale*(1/sqrt(normale*normale));
    if(c) normale = normale*(-1);
    CollidersPtr.push_back(std::make_shared<PlanCollider>(normale,origine,largeur,color));
}

void Context::addSphereCollider(Vec2 centre, float rayon, QColor color) {
    CollidersPtr.push_back(std::make_shared<SphereCollider>(centre, rayon,color));
}

void Context::applyExternalForce(float dt){
    for(auto &particule:particules){
        particule->velocity[0] += gravity[0];
        particule->velocity[1] += gravity[1];
    }
/**/
    //air resistance
    float f = 2;
    for(auto &particule:particules){
        particule->velocity = particule->velocity - particule->velocity*(f*dt);
    }
};

void Context::updateExpectedPosition(float dt){
    for(auto &particule:particules){
        particule->pos_ = particule->pos+(particule->velocity*dt);
    }
};

void Context::updateVelocityAndPosition(float dt){
    for(auto &particule:particules){
        particule->velocity = (particule->pos_ - particule->pos)*(1/dt);
        particule->pos = particule->pos_;
    }
};

bool PlanCollider::checkContact(const Particule& collider)  {

    Vec2 vecDirecteur = Vec2{-this->normale()[1],this->normale()[0]};


    return abs((collider.pos_-this->origine())*this->normale())<collider.radius &&
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

    painter->setBrush(QBrush(color, Qt::Dense4Pattern));
    painter->setPen(color);
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
    painter->setBrush(QBrush(color, Qt::Dense4Pattern));
    painter->setPen(color);
    painter->drawEllipse(target);
}

Vec2 SphereCollider::pc(const Particule& particule) {//closest point on the collider
    return p+normale(particule)*r;
}

void Context::addStaticContactConstraints(float dt){
    staticConstraints.clear();
    for( auto& particule:particules){
        for(auto &colliderptr:CollidersPtr){
            if (colliderptr->checkContact(*particule)) {
                staticConstraints.push_back(StaticConstraint(*particule,colliderptr));
            }
        }
    }
}

void enforceStaticGroundConstraint(StaticConstraint& constraint) {

    Particule& particule = constraint.particule;
    const Vec2& nc = constraint.collider->normale(particule);
    const Vec2& pc = constraint.collider->pc(particule);
    //Réaction normale du support
    Vec2 qc = particule.pos_ - (nc*((particule.pos_ - pc)*nc));
    float C = (particule.pos_ - qc)*nc-particule.radius;
    Vec2 delta = nc*(-C);

    particule.pos_ = particule.pos_ + delta;

    //Réaction tangentielle du support
    Vec2 currentv = particule.pos_ - particule.pos;
    Vec2 vt = currentv - (nc*(currentv*nc));
    float vt_norm = sqrt(vt*vt);
    Vec2 delta_t = Vec2{0,0};
    if(vt_norm>0){//si la composante tangentielle n'est pas nul, on applique un frottement solide
        float coef = 0.1f;
        delta_t = vt*(-coef*vt_norm);
    }
    if(vt_norm<0.05){//si la vitesse est assez faible, on l'annule complètement
        delta_t = vt*(-1);
    }
    particule.pos_ = currentv + delta_t + particule.pos;
    
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
            if(particules[i]->checkContact(*particules[j])) {
                dynamicConstraints.push_back(DynamicConstraint(*particules[i],*particules[j]));
            }
        }
    }
};


void Context::projectConstraints(){
    for(auto& staticConstraint:staticConstraints){
        enforceStaticGroundConstraint(staticConstraint);
    }
    for(auto& dynamicConstraint:dynamicConstraints){
        solveDynamicConstraint(dynamicConstraint);
    }
}

void Context::create_solid(Vec2 pos, Vec2 v, float r, float m){
    float x = pos[0];
    float y = pos[1];

    Particule p1(Vec2{(float)(x-1.1*r),(float)(y-1.1*r)},v,r,m);
    Particule p2(Vec2{(float)(x-1.1*r),(float)(y+1.1*r)},v,r,m);
    Particule p3(Vec2{(float)(x+1.1*r),(float)(y-1.1*r)},v,r,m);
    Particule p4(Vec2{(float)(x+1.1*r),(float)(y+1.1*r)},v,r,m);

    float L = 1.1*2*r;
    float stiffness = 0.1;

    particules.push_back(std::make_shared<Particule>(p4));
    particules.push_back(std::make_shared<Particule>(p3));
    particules.push_back(std::make_shared<Particule>(p2));
    particules.push_back(std::make_shared<Particule>(p1));

    linkConstraints.emplace_back(LinkConstraint{*particules[particules.size()-1],*particules[particules.size()-2],L,stiffness});
    linkConstraints.emplace_back(LinkConstraint{*particules[particules.size()-1],*particules[particules.size()-3],L,stiffness});
    linkConstraints.emplace_back(LinkConstraint{*particules[particules.size()-4],*particules[particules.size()-2],L,stiffness});
    linkConstraints.emplace_back(LinkConstraint{*particules[particules.size()-4],*particules[particules.size()-3],L,stiffness});
    linkConstraints.emplace_back(LinkConstraint{*particules[particules.size()-4],*particules[particules.size()-1],static_cast<float>(L*sqrt(2)),stiffness});
    linkConstraints.emplace_back(LinkConstraint{*particules[particules.size()-2],*particules[particules.size()-3],static_cast<float>(L*sqrt(2)),stiffness});
}

void Context::applyLinkConstraints(float dt){
    for(auto& link:linkConstraints){
        Particule& pi = link.particule1;
        Particule& pj = link.particule2;
        float L = link.L;
        float gam = link.stiffness;

        Vec2 xji = pi.pos_-pj.pos_;
        float C = sqrt(xji*xji) - L;

        Vec2 deltai = xji*(-1/sqrt(xji*xji))*gam*C*((1/pi.mass)/((1/pi.mass)+(1/pj.mass)));
        Vec2 deltaj = deltai*(-pi.mass/pj.mass);

        pi.pos_= pi.pos_+deltai;
        pj.pos_ = pj.pos_+deltaj;
    }
}

void LinkConstraint::draw(QPainter* painter, float height){

    painter->setPen(QPen(Qt::blue, 1, Qt::SolidLine, Qt::RoundCap));
    painter->drawLine(particule1.pos[0], height-particule1.pos[1], particule2.pos[0], height-particule2.pos[1]);
}
