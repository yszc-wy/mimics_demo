/****************************************************************************
** Meta object code from reading C++ file 'calculateObjThread.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../calculateObjThread.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'calculateObjThread.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CalculateObjThread_t {
    QByteArrayData data[7];
    char stringdata0[73];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CalculateObjThread_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CalculateObjThread_t qt_meta_stringdata_CalculateObjThread = {
    {
QT_MOC_LITERAL(0, 0, 18), // "CalculateObjThread"
QT_MOC_LITERAL(1, 19, 13), // "changeProcess"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 1), // "a"
QT_MOC_LITERAL(4, 36, 5), // "value"
QT_MOC_LITERAL(5, 42, 16), // "objectListChange"
QT_MOC_LITERAL(6, 59, 13) // "newObjectName"

    },
    "CalculateObjThread\0changeProcess\0\0a\0"
    "value\0objectListChange\0newObjectName"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CalculateObjThread[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   24,    2, 0x06 /* Public */,
       5,    1,   29,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::Int,    3,    4,
    QMetaType::Void, QMetaType::QString,    6,

       0        // eod
};

void CalculateObjThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CalculateObjThread *_t = static_cast<CalculateObjThread *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->changeProcess((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->objectListChange((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (CalculateObjThread::*_t)(const QString & , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CalculateObjThread::changeProcess)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (CalculateObjThread::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CalculateObjThread::objectListChange)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject CalculateObjThread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_CalculateObjThread.data,
      qt_meta_data_CalculateObjThread,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CalculateObjThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CalculateObjThread::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CalculateObjThread.stringdata0))
        return static_cast<void*>(const_cast< CalculateObjThread*>(this));
    return QThread::qt_metacast(_clname);
}

int CalculateObjThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void CalculateObjThread::changeProcess(const QString & _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CalculateObjThread::objectListChange(const QString & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
