/****************************************************************************
** Meta object code from reading C++ file 'sensorBox.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "sensorBox.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sensorBox.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_sensorBox_t {
    const uint offsetsAndSize[22];
    char stringdata0[140];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_sensorBox_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_sensorBox_t qt_meta_stringdata_sensorBox = {
    {
QT_MOC_LITERAL(0, 9), // "sensorBox"
QT_MOC_LITERAL(10, 10), // "removeItem"
QT_MOC_LITERAL(21, 0), // ""
QT_MOC_LITERAL(22, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(39, 4), // "item"
QT_MOC_LITERAL(44, 22), // "modificaChartContainer"
QT_MOC_LITERAL(67, 9), // "chartBox*"
QT_MOC_LITERAL(77, 11), // "newChartBox"
QT_MOC_LITERAL(89, 13), // "resetChartBox"
QT_MOC_LITERAL(103, 19), // "on_modifica_clicked"
QT_MOC_LITERAL(123, 16) // "onRimuoviClicked"

    },
    "sensorBox\0removeItem\0\0QListWidgetItem*\0"
    "item\0modificaChartContainer\0chartBox*\0"
    "newChartBox\0resetChartBox\0on_modifica_clicked\0"
    "onRimuoviClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_sensorBox[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   44,    2, 0x06,    1 /* Public */,
       5,    1,   47,    2, 0x06,    3 /* Public */,
       8,    0,   50,    2, 0x06,    5 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       9,    0,   51,    2, 0x08,    6 /* Private */,
      10,    0,   52,    2, 0x08,    7 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void sensorBox::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<sensorBox *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->removeItem((*reinterpret_cast< std::add_pointer_t<QListWidgetItem*>>(_a[1]))); break;
        case 1: _t->modificaChartContainer((*reinterpret_cast< std::add_pointer_t<chartBox*>>(_a[1]))); break;
        case 2: _t->resetChartBox(); break;
        case 3: _t->on_modifica_clicked(); break;
        case 4: _t->onRimuoviClicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< chartBox* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (sensorBox::*)(QListWidgetItem * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&sensorBox::removeItem)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (sensorBox::*)(chartBox * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&sensorBox::modificaChartContainer)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (sensorBox::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&sensorBox::resetChartBox)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject sensorBox::staticMetaObject = { {
    QMetaObject::SuperData::link<QGroupBox::staticMetaObject>(),
    qt_meta_stringdata_sensorBox.offsetsAndSize,
    qt_meta_data_sensorBox,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_sensorBox_t
, QtPrivate::TypeAndForceComplete<sensorBox, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QListWidgetItem *, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<chartBox *, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>


>,
    nullptr
} };


const QMetaObject *sensorBox::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *sensorBox::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_sensorBox.stringdata0))
        return static_cast<void*>(this);
    return QGroupBox::qt_metacast(_clname);
}

int sensorBox::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGroupBox::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void sensorBox::removeItem(QListWidgetItem * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void sensorBox::modificaChartContainer(chartBox * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void sensorBox::resetChartBox()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
