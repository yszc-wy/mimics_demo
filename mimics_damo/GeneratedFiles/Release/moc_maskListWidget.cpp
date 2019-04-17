/****************************************************************************
** Meta object code from reading C++ file 'maskListWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../maskListWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'maskListWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MaskListWidget_t {
    QByteArrayData data[13];
    char stringdata0[149];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MaskListWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MaskListWidget_t qt_meta_stringdata_MaskListWidget = {
    {
QT_MOC_LITERAL(0, 0, 14), // "MaskListWidget"
QT_MOC_LITERAL(1, 15, 17), // "changeCurrentMask"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 4), // "mask"
QT_MOC_LITERAL(4, 39, 10), // "deleteMask"
QT_MOC_LITERAL(5, 50, 9), // "mask_name"
QT_MOC_LITERAL(6, 60, 21), // "changeCurrentMaskName"
QT_MOC_LITERAL(7, 82, 3), // "row"
QT_MOC_LITERAL(8, 86, 6), // "column"
QT_MOC_LITERAL(9, 93, 11), // "maskVisible"
QT_MOC_LITERAL(10, 105, 7), // "visible"
QT_MOC_LITERAL(11, 113, 10), // "setChanges"
QT_MOC_LITERAL(12, 124, 24) // "updateCurrentNameAndMask"

    },
    "MaskListWidget\0changeCurrentMask\0\0"
    "mask\0deleteMask\0mask_name\0"
    "changeCurrentMaskName\0row\0column\0"
    "maskVisible\0visible\0setChanges\0"
    "updateCurrentNameAndMask"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MaskListWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x06 /* Public */,
       4,    1,   52,    2, 0x06 /* Public */,
       6,    3,   55,    2, 0x06 /* Public */,
       9,    2,   62,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      11,    2,   67,    2, 0x08 /* Private */,
      12,    2,   72,    2, 0x08 /* Private */,
       4,    0,   77,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::QString, QMetaType::Int, QMetaType::Int,    5,    7,    8,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool,    5,   10,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    7,    8,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    7,    8,
    QMetaType::Void,

       0        // eod
};

void MaskListWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MaskListWidget *_t = static_cast<MaskListWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->changeCurrentMask((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->deleteMask((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->changeCurrentMaskName((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 3: _t->maskVisible((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 4: _t->setChanges((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 5: _t->updateCurrentNameAndMask((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 6: _t->deleteMask(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MaskListWidget::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MaskListWidget::changeCurrentMask)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (MaskListWidget::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MaskListWidget::deleteMask)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (MaskListWidget::*_t)(QString , int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MaskListWidget::changeCurrentMaskName)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (MaskListWidget::*_t)(QString , bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MaskListWidget::maskVisible)) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject MaskListWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_MaskListWidget.data,
      qt_meta_data_MaskListWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MaskListWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MaskListWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MaskListWidget.stringdata0))
        return static_cast<void*>(const_cast< MaskListWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int MaskListWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void MaskListWidget::changeCurrentMask(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MaskListWidget::deleteMask(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void MaskListWidget::changeCurrentMaskName(QString _t1, int _t2, int _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void MaskListWidget::maskVisible(QString _t1, bool _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
