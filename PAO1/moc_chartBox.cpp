/****************************************************************************
** Meta object code from reading C++ file 'chartBox.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "chartBox.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'chartBox.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_chartBox_t {
    const uint offsetsAndSize[6];
    char stringdata0[34];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_chartBox_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_chartBox_t qt_meta_stringdata_chartBox = {
    {
QT_MOC_LITERAL(0, 8), // "chartBox"
QT_MOC_LITERAL(9, 23), // "on_crea_grafico_clicked"
QT_MOC_LITERAL(33, 0) // ""

    },
    "chartBox\0on_crea_grafico_clicked\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_chartBox[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   20,    2, 0x08,    1 /* Private */,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void chartBox::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<chartBox *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->on_crea_grafico_clicked(); break;
        default: ;
        }
    }
    (void)_a;
}

const QMetaObject chartBox::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_chartBox.offsetsAndSize,
    qt_meta_data_chartBox,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_chartBox_t
, QtPrivate::TypeAndForceComplete<chartBox, std::true_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>


>,
    nullptr
} };


const QMetaObject *chartBox::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *chartBox::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_chartBox.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int chartBox::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 1;
    }
    return _id;
}
struct qt_meta_stringdata_chartTemp_t {
    const uint offsetsAndSize[6];
    char stringdata0[35];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_chartTemp_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_chartTemp_t qt_meta_stringdata_chartTemp = {
    {
QT_MOC_LITERAL(0, 9), // "chartTemp"
QT_MOC_LITERAL(10, 23), // "on_crea_grafico_clicked"
QT_MOC_LITERAL(34, 0) // ""

    },
    "chartTemp\0on_crea_grafico_clicked\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_chartTemp[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   20,    2, 0x08,    1 /* Private */,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void chartTemp::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<chartTemp *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->on_crea_grafico_clicked(); break;
        default: ;
        }
    }
    (void)_a;
}

const QMetaObject chartTemp::staticMetaObject = { {
    QMetaObject::SuperData::link<chartBox::staticMetaObject>(),
    qt_meta_stringdata_chartTemp.offsetsAndSize,
    qt_meta_data_chartTemp,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_chartTemp_t
, QtPrivate::TypeAndForceComplete<chartTemp, std::true_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>


>,
    nullptr
} };


const QMetaObject *chartTemp::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *chartTemp::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_chartTemp.stringdata0))
        return static_cast<void*>(this);
    return chartBox::qt_metacast(_clname);
}

int chartTemp::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = chartBox::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 1;
    }
    return _id;
}
struct qt_meta_stringdata_chartAria_t {
    const uint offsetsAndSize[6];
    char stringdata0[35];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_chartAria_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_chartAria_t qt_meta_stringdata_chartAria = {
    {
QT_MOC_LITERAL(0, 9), // "chartAria"
QT_MOC_LITERAL(10, 23), // "on_crea_grafico_clicked"
QT_MOC_LITERAL(34, 0) // ""

    },
    "chartAria\0on_crea_grafico_clicked\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_chartAria[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   20,    2, 0x08,    1 /* Private */,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void chartAria::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<chartAria *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->on_crea_grafico_clicked(); break;
        default: ;
        }
    }
    (void)_a;
}

const QMetaObject chartAria::staticMetaObject = { {
    QMetaObject::SuperData::link<chartTemp::staticMetaObject>(),
    qt_meta_stringdata_chartAria.offsetsAndSize,
    qt_meta_data_chartAria,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_chartAria_t
, QtPrivate::TypeAndForceComplete<chartAria, std::true_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>


>,
    nullptr
} };


const QMetaObject *chartAria::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *chartAria::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_chartAria.stringdata0))
        return static_cast<void*>(this);
    return chartTemp::qt_metacast(_clname);
}

int chartAria::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = chartTemp::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 1;
    }
    return _id;
}
struct qt_meta_stringdata_chartVent_t {
    const uint offsetsAndSize[6];
    char stringdata0[35];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_chartVent_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_chartVent_t qt_meta_stringdata_chartVent = {
    {
QT_MOC_LITERAL(0, 9), // "chartVent"
QT_MOC_LITERAL(10, 23), // "on_crea_grafico_clicked"
QT_MOC_LITERAL(34, 0) // ""

    },
    "chartVent\0on_crea_grafico_clicked\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_chartVent[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   20,    2, 0x08,    1 /* Private */,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void chartVent::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<chartVent *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->on_crea_grafico_clicked(); break;
        default: ;
        }
    }
    (void)_a;
}

const QMetaObject chartVent::staticMetaObject = { {
    QMetaObject::SuperData::link<chartAria::staticMetaObject>(),
    qt_meta_stringdata_chartVent.offsetsAndSize,
    qt_meta_data_chartVent,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_chartVent_t
, QtPrivate::TypeAndForceComplete<chartVent, std::true_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>


>,
    nullptr
} };


const QMetaObject *chartVent::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *chartVent::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_chartVent.stringdata0))
        return static_cast<void*>(this);
    return chartAria::qt_metacast(_clname);
}

int chartVent::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = chartAria::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 1;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
