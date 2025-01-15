#ifndef CONTEXT_H
#define CONTEXT_H
#include <iostream>
#include <ostream>
#include <qevent.h>
#include <qpainter.h>
#include <QPolygonF>
#include <vector>

struct Vec2{
    float first,second;
    float& operator[](int i){if (i==0) return first; if (i==1) return second; else throw std::invalid_argument( "out of range" ); };
    float operator[](int i) const {if (i==0) return first; if (i==1) return second; else throw std::invalid_argument( "out of range" ); };

    Vec2 operator+(Vec2& b){return Vec2{first+b[0],second+b[1]};};
    Vec2 operator+(const Vec2& b) const {return Vec2{first+b[0],second+b[1]};};

    Vec2 operator-(Vec2& b){return Vec2{first-b[0],second-b[1]};};
    Vec2 operator-(const Vec2& b) const {return Vec2{first-b[0],second-b[1]};};

    Vec2& operator=(const Vec2& other) = default;
    //Vec2(const Vec2& other)=default;

    Vec2 operator*(float a){return Vec2{first*a,second*a};};
    Vec2 operator*(float a) const {return Vec2{first*a,second*a};};

    float operator*(Vec2& b){return first*b[0] + second*b[1];};//dot product | produit scalaire
    float operator*(const Vec2& b) const {return first*b[0] + second*b[1];};
};

struct Particule
{
    Vec2 pos;
    Vec2 velocity;
    float radius;
    float mass;
    Vec2 pos_;//future pos

    bool checkContact(const Particule& particule);

    Particule(Vec2 pos_, Vec2 v_, float r, float m) {
        pos=pos_;
        velocity=v_;
        radius=r;
        mass=m;
    }
};

struct Collider
{
    virtual ~Collider() = default;
    virtual bool checkContact(const Particule& collider) = 0;
    virtual void draw(QPainter* painter,float height) const = 0;
    virtual Vec2 normale(const Particule& particule) const = 0 ;
    virtual Vec2 origine() const = 0 ;
    virtual Vec2 pc(const Particule& particule) = 0;

};

struct StaticConstraint
{
    Particule& particule;
    std::shared_ptr<Collider> collider;

    StaticConstraint(Particule& p, std::shared_ptr<Collider> c):particule(p), collider(c){};
};


struct PlanCollider : Collider
{
    Vec2 n;
    Vec2 p;
    Vec2 origine() const override {return p;}
    QColor color = Qt::black;
    float largeur;
    Vec2 normale(const Particule& particule) const override {return n;}
    Vec2 normale() {return n;}
    Vec2 normale() const {return n;}
    bool checkContact(const Particule& collider) override;
    void draw(QPainter* painter, float height) const override;
    Vec2 pc(const Particule& particule) override {return p;};

    PlanCollider(Vec2 normale_,Vec2 origine_, float largeur_, QColor color_): n(normale_), p(origine_), largeur(largeur_), color(color_) {};
};

struct SphereCollider : Collider
{
    Vec2 p;
    Vec2 origine() const override {return p;}
    QColor color = Qt::black;
    float r;
    Vec2 normale(const Particule& particule) const override;
    bool checkContact(const Particule& collider) override;
    void draw(QPainter* painter, float height) const override;
    Vec2 pc(const Particule& particule) override;

    SphereCollider(Vec2 origine_, float rayon,QColor color_):p(origine_), r(rayon),color(color_) {};
};

struct DynamicConstraint
{
    Particule& particule1;
    Particule& particule2;

    DynamicConstraint(Particule& p, Particule& p2): particule1(p), particule2(p2){};
};

struct LinkConstraint
{
    Particule& particule1;
    Particule& particule2;

    float L;
    float stiffness;

    LinkConstraint(Particule& p1, Particule& p2, float L_, float stiffness_)
        : particule1(p1), particule2(p2), L(L_), stiffness(stiffness_) {}

    void draw(QPainter* painter, float height);
};

class Context
{
    void applyExternalForce(float dt);
    void updateVelocityAndPosition(float dt);
    void updateExpectedPosition(float dt);
    void addDynamicContactConstraints(float dt);
    void addStaticContactConstraints(float dt);
    void projectConstraints();
    void applyFriction(float dt);
    void deleteContactConstraints();
    void applyLinkConstraints(float dt);

    void addPlanCollider(Vec2 a, Vec2 b, bool c,QColor color);
    void addSphereCollider(Vec2 centre, float rayon,QColor color);
public:
    Context();
    std::vector<std::shared_ptr<Particule>> particules;
    std::vector<StaticConstraint> staticConstraints;
    std::vector<DynamicConstraint> dynamicConstraints;
    std::vector<std::shared_ptr<Collider>> CollidersPtr;
    std::vector<LinkConstraint> linkConstraints;
    std::string mode = "particule";
    Vec2 gravity = Vec2{0,-9.81};
    void create_solid(Vec2 pos, Vec2 v, float r, float m);

    void updatePhysicalSystem(float dt);
};

#endif // CONTEXT_H

