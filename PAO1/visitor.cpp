#include "visitor.h"
#include "sensori.h"

void visitor_grafico::visit(sensore_temp* temp){
    //qDebug()<<"visitor_grafico::visit temp";
    widget = new chartTemp(nullptr,temp);
}

void visitor_grafico::visit(sensore_fumo* fumo){
    //qDebug()<<"visitor_grafico::visit fumo";
    widget = new chartBox(nullptr,fumo);
}

void visitor_grafico::visit(sensore_aria* aria){
    //qDebug()<<"visitor_grafico::visit aria";
    widget = new chartAria(nullptr,aria);
}

void visitor_grafico::visit(sensore_vent* vent){
    //qDebug()<<"visitor_grafico::visit vent";
    widget = new chartVent(nullptr,vent);
}

chartBox* visitor_grafico::getWidget(){
    //qDebug()<<"visitor_grafico::getwidget";
    return widget;
}
