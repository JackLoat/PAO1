#include "visitor_grafico.h"
#include "sensorevent.h"
#include "sensorefumo.h"
#include "chartvent.h"

void visitor_grafico::visit(sensore_temp* temp){
    widget = new chartTemp(nullptr,temp);
}

void visitor_grafico::visit(sensore_fumo* fumo){
    widget = new chartBox(nullptr,fumo);
}

void visitor_grafico::visit(sensore_aria* aria){
    widget = new chartAria(nullptr,aria);
}

void visitor_grafico::visit(sensore_vent* vent){
    widget = new chartVent(nullptr,vent);
}

chartBox* visitor_grafico::getWidget(){
    return widget;
}
