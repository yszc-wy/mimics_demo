/****************************************************************************
** Meta object code from reading C++ file 'createMaskDialog.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../createMaskDialog.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'createMaskDialog.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CreateMaskDialog_t {
    QByteArrayData data[9];
    char stringdata0[105];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CreateMaskDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CreateMaskDialog_t qt_meta_stringdata_CreateMaskDialog = {
    {
QT_MOC_LITERAL(0, 0, 16), // "CreateMaskDialog"
QT_MOC_LITERAL(1, 17, 21), // "thresholdValueChanged"
QT_MOC_LITERAL(2, 39, 0), // ""
QT_MOC_LITERAL(3, 40, 3), // "min"
QT_MOC_LITERAL(4, 44, 3), // "max"
QT_MOC_LITERAL(5, 48, 20), // "thresholdValueResult"
QT_MOC_LITERAL(6, 69, 22), // "emitValueChangedSignal"
QT_MOC_LITERAL(7, 92, 6), // "Accept"
QT_MOC_LITERAL(8, 99, 5) // "Close"

    },
    "CreateMaskDialog\0thresholdValueChanged\0"
    "\0min\0max\0thresholdValueResult\0"
    "emitValueChangedSignal\0Accept\0Close"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CreateMaskDialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   39,    2, 0x06 /* Public */,
       5,    2,   44,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   49,    2, 0x08 /* Private */,
       7,    0,   50,    2, 0x08 /* Private */,
       8,    0,   51,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    3,    4,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    3,    4,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void CreateMaskDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CreateMaskDialog *_t = static_cast<CreateMaskDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->thresholdValueChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->thresholdValueResult((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->emitValueChangedSignal(); break;
        case 3: _t->Accept(); break;
        case 4: _t->Close(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (CreateMaskDialog::*_t)(int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CreateMaskDialog::thresholdValueChanged)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (CreateMaskDialog::*_t)(int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CreateMaskDialog::thresholdValueResult)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject CreateMaskDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_CreateMaskDialog.data,
      qt_meta_data_CreateMaskDialog,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CreateMaskDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CreateMaskDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CreateMaskDialog.stringdata0))
        return static_cast<void*>(const_cast< CreateMaskDialog*>(this));
    if (!strcmp(_clname, "Ui::thresholdValueDialog"))
        return static_cast< Ui::thresholdValueDialog*>(const_cast< CreateMaskDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int CreateMaskDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void CreateMaskDialog::thresholdValueChanged(int _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CreateMaskDialog::thresholdValueResult(int _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
