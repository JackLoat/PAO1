#ifndef VISITOR_GRAFICO_H
#define VISITOR_GRAFICO_H

#include "visitor.h"

class chartBox;

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

#endif // VISITOR_GRAFICO_H
