#ifndef VISITOR_H
#define VISITOR_H

class chartBox;

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

#endif // VISITOR_H
