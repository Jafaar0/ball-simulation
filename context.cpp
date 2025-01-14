#include "context.h"

Context::Context() {
    addPlanCollider(Vec2{100,100},Vec2{100,400}, false);
    addPlanCollider(Vec2{100,400},Vec2{500,400}, true);
    addPlanCollider(Vec2{500,400},Vec2{500,100}, false);
    addPlanCollider(Vec2{500,100},Vec2{100,100}, true);

    addSphereCollider(Vec2{100,200},50);
}

/**
 * @brief Context::updatePhysicalSystem update the physical system of the simulation
 * @param dt: time step
 * @details It applies the external forces, updates the expected position of the particules, adds the static and dynamic contact constraints,
 */
void Context::updatePhysicalSystem(float dt){
    applyExternalForce(dt);
    updateExpectedPosition(dt);

    addStaticContactConstraints(dt);
    addDynamicContactConstraints(dt);
    projectConstraints();

    applyLinkConstraints(dt);

    updateVelocityAndPosition(dt);
};

/**
 * @brief Context::addPlanCollider add a plan collider to the simulation
 * @param a: first point of the plan
 * @param b: second point of the plan
 * @param c: true for a normal pointing in one direction, false for the other direction
 */
void Context::addPlanCollider(Vec2 a, Vec2 b, bool c) {
    Vec2 origine = (a+b)*(0.5);
    float largeur = sqrt((b-a)*(b-a));
    Vec2 normale{b[1]-a[1],b[0]-a[0]};
    normale = normale*(1/sqrt(normale*normale));
    if(c) normale = normale*(-1);
    CollidersPtr.push_back(std::make_shared<PlanCollider>(normale,origine,largeur));
}

/**
 * @brief Context::addSphereCollider add a sphere collider to the simulation
 * @param centre: position of the sphere
 * @param rayon: radius of the sphere
 */
void Context::addSphereCollider(Vec2 centre, float rayon) {
    CollidersPtr.push_back(std::make_shared<SphereCollider>(centre, rayon));
}

/**
 * @brief Context::applyExternalForce apply the external forces to the particules
 * @param dt: time step
 * @details It applies the gravity and the air resistance to the particules
 */
void Context::applyExternalForce(float dt){
    //gravity
    float g = 9.81;
    for(auto &particule:particules){
        particule->velocity[1] -= g;
    }
/**/
    //air resistance
    float f = 2;
    for(auto &particule:particules){
        particule->velocity = particule->velocity - particule->velocity*(f*dt);
    }
};

/**
 * @brief Context::updateExpectedPosition update the expected position of the particules
 */
void Context::updateExpectedPosition(float dt){
    for(auto &particule:particules){
        particule->pos_ = particule->pos+(particule->velocity*dt);
    }
};

/**
 * @brief Context::updateVelocityAndPosition update the velocity and the position of the particules
 */
void Context::updateVelocityAndPosition(float dt){
    for(auto &particule:particules){
        particule->velocity = (particule->pos_ - particule->pos)*(1/dt);
        particule->pos = particule->pos_;
    }
};


bool PlanCollider::checkContact(const Particule& particule)  {

    Vec2 vecDirecteur = Vec2{-this->normale()[1],this->normale()[0]};


    return abs((particule.pos_-this->origine())*this->normale())<particule.radius &&
           particule.velocity*normale()<0 &&
           abs((particule.pos_-origine())*vecDirecteur)<(largeur/2);
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

bool SphereCollider::checkContact(const Particule& particule)  {
    return sqrt((particule.pos_ - p)*(particule.pos_ - p)) - particule.radius-r<0;
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

/**
 * @brief Context::addStaticContactConstraints check for contacts and add the static contact constraints to the simulation
 * @param dt: time step
 */
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

/**
 * @brief Context::enforceStaticGroundConstraint resolve the static contact constraints
 * @param constraint: static contact constraint
 * @details It applies the reaction force to the particule to enforce the static ground constraint
 *         It also applies a solid friction to the particule
 */
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

/**
 * @brief Context::solveDynamicConstraint resolve the dynamic contact constraints
 * @param constraint: dynamic contact constraint
 * @details It applies the reaction force to the particules to enforce the dynamic contact constraint
 */
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

/**
 * @brief Context::addDynamicContactConstraints check for contacts between particules and add the dynamic contact constraints to the simulation
 * @param dt: time step
 */
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

/**
 * @brief Context::projectConstraints solve all constraints
 */
void Context::projectConstraints(){
    for(auto& staticConstraint:staticConstraints){
        enforceStaticGroundConstraint(staticConstraint);
    }
    for(auto& dynamicConstraint:dynamicConstraints){
        solveDynamicConstraint(dynamicConstraint);
    }
}

/**
 * @brief Context::create_solid create a solid with 4 particules and 6 link constraints between them
 */
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

/**
 * @brief Context::applyLinkConstraints apply the link constraints to the particules
 * @param dt: time step
 */
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
