/****************************************************************************
** Meta object code from reading C++ file 'editDialog.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "editDialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'editDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_editDialog_t {
    const uint offsetsAndSize[6];
    char stringdata0[26];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_editDialog_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_editDialog_t qt_meta_stringdata_editDialog = {
    {
QT_MOC_LITERAL(0, 10), // "editDialog"
QT_MOC_LITERAL(11, 13), // "acceptChanges"
QT_MOC_LITERAL(25, 0) // ""

    },
    "editDialog\0acceptChanges\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_editDialog[] = {

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

void editDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<editDialog *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->acceptChanges(); break;
        default: ;
        }
    }
    (void)_a;
}

const QMetaObject editDialog::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_editDialog.offsetsAndSize,
    qt_meta_data_editDialog,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_editDialog_t
, QtPrivate::TypeAndForceComplete<editDialog, std::true_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>


>,
    nullptr
} };


const QMetaObject *editDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *editDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_editDialog.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int editDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
struct qt_meta_stringdata_nsDialog_t {
    const uint offsetsAndSize[8];
    char stringdata0[67];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_nsDialog_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_nsDialog_t qt_meta_stringdata_nsDialog = {
    {
QT_MOC_LITERAL(0, 8), // "nsDialog"
QT_MOC_LITERAL(9, 28), // "on_carica_collezione_clicked"
QT_MOC_LITERAL(38, 0), // ""
QT_MOC_LITERAL(39, 27) // "on_nuova_collezione_clicked"

    },
    "nsDialog\0on_carica_collezione_clicked\0"
    "\0on_nuova_collezione_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_nsDialog[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   26,    2, 0x08,    1 /* Private */,
       3,    0,   27,    2, 0x08,    2 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void nsDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<nsDialog *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->on_carica_collezione_clicked(); break;
        case 1: _t->on_nuova_collezione_clicked(); break;
        default: ;
        }
    }
    (void)_a;
}

const QMetaObject nsDialog::staticMetaObject = { {
    QMetaObject::SuperData::link<editDialog::staticMetaObject>(),
    qt_meta_stringdata_nsDialog.offsetsAndSize,
    qt_meta_data_nsDialog,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_nsDialog_t
, QtPrivate::TypeAndForceComplete<nsDialog, std::true_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>


>,
    nullptr
} };


const QMetaObject *nsDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *nsDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_nsDialog.stringdata0))
        return static_cast<void*>(this);
    return editDialog::qt_metacast(_clname);
}

int nsDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = editDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 2;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
