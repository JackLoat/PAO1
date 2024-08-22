#ifndef VISITOR_H
#define VISITOR_H

#include "chartvent.h"

class sensore_temp;
class sensore_fumo;
class sensore_aria;
class sensore_vent;

class visitor
{
public:
    virtual void visit(sensore_temp* temp) = 0;
    virtual void visit(sensore_fumo* fumo) = 0;
    virtual void visit(sensore_aria* aria) = 0;
    virtual void visit(sensore_vent* vent) = 0;
    virtual ~visitor() = default;
};

class visitor_grafico : public visitor{
private:
    chartBox* widget;
public:
    void visit(sensore_temp* temp) override;
    void visit(sensore_fumo* fumo) override;
    void visit(sensore_aria* aria) override;
    void visit(sensore_vent* vent) override;

    chartBox* getWidget();
};

#endif // VISITOR_H
