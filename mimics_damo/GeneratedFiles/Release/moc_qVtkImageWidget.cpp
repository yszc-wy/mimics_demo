/****************************************************************************
** Meta object code from reading C++ file 'qVtkImageWidget.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../qVtkImageWidget.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qVtkImageWidget.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QVTKImageWidget_t {
    QByteArrayData data[20];
    char stringdata0[281];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QVTKImageWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QVTKImageWidget_t qt_meta_stringdata_QVTKImageWidget = {
    {
QT_MOC_LITERAL(0, 0, 15), // "QVTKImageWidget"
QT_MOC_LITERAL(1, 16, 15), // "showCursorActor"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 15), // "hideCursorActor"
QT_MOC_LITERAL(4, 49, 15), // "mouseWheelEvent"
QT_MOC_LITERAL(5, 65, 5), // "delta"
QT_MOC_LITERAL(6, 71, 33), // "rightButtonPress_MouseMoveHap..."
QT_MOC_LITERAL(7, 105, 14), // "startPositionX"
QT_MOC_LITERAL(8, 120, 14), // "startPositionY"
QT_MOC_LITERAL(9, 135, 16), // "currentPositionX"
QT_MOC_LITERAL(10, 152, 16), // "currentPositionY"
QT_MOC_LITERAL(11, 169, 7), // "initalW"
QT_MOC_LITERAL(12, 177, 7), // "initalL"
QT_MOC_LITERAL(13, 185, 18), // "spaceKeyPressEvent"
QT_MOC_LITERAL(14, 204, 5), // "index"
QT_MOC_LITERAL(15, 210, 5), // "model"
QT_MOC_LITERAL(16, 216, 22), // "leftButtonPressHappend"
QT_MOC_LITERAL(17, 239, 1), // "x"
QT_MOC_LITERAL(18, 241, 1), // "y"
QT_MOC_LITERAL(19, 243, 37) // "leftButtonPressOrNot_MouseMov..."

    },
    "QVTKImageWidget\0showCursorActor\0\0"
    "hideCursorActor\0mouseWheelEvent\0delta\0"
    "rightButtonPress_MouseMoveHappend\0"
    "startPositionX\0startPositionY\0"
    "currentPositionX\0currentPositionY\0"
    "initalW\0initalL\0spaceKeyPressEvent\0"
    "index\0model\0leftButtonPressHappend\0x\0"
    "y\0leftButtonPressOrNot_MouseMoveHappend"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QVTKImageWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x06 /* Public */,
       3,    0,   50,    2, 0x06 /* Public */,
       4,    1,   51,    2, 0x06 /* Public */,
       6,    6,   54,    2, 0x06 /* Public */,
      13,    2,   67,    2, 0x06 /* Public */,
      16,    2,   72,    2, 0x06 /* Public */,
      19,    3,   77,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Double, QMetaType::Double,    7,    8,    9,   10,   11,   12,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   14,   15,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   17,   18,
    QMetaType::Void, QMetaType::Bool, QMetaType::Int, QMetaType::Int,    2,   17,   18,

       0        // eod
};

void QVTKImageWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QVTKImageWidget *_t = static_cast<QVTKImageWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->showCursorActor(); break;
        case 1: _t->hideCursorActor(); break;
        case 2: _t->mouseWheelEvent((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->rightButtonPress_MouseMoveHappend((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< double(*)>(_a[5])),(*reinterpret_cast< double(*)>(_a[6]))); break;
        case 4: _t->spaceKeyPressEvent((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 5: _t->leftButtonPressHappend((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 6: _t->leftButtonPressOrNot_MouseMoveHappend((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (QVTKImageWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QVTKImageWidget::showCursorActor)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (QVTKImageWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QVTKImageWidget::hideCursorActor)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (QVTKImageWidget::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QVTKImageWidget::mouseWheelEvent)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (QVTKImageWidget::*_t)(int , int , int , int , double , double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QVTKImageWidget::rightButtonPress_MouseMoveHappend)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (QVTKImageWidget::*_t)(int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QVTKImageWidget::spaceKeyPressEvent)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (QVTKImageWidget::*_t)(int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QVTKImageWidget::leftButtonPressHappend)) {
                *result = 5;
                return;
            }
        }
        {
            typedef void (QVTKImageWidget::*_t)(bool , int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QVTKImageWidget::leftButtonPressOrNot_MouseMoveHappend)) {
                *result = 6;
                return;
            }
        }
    }
}

const QMetaObject QVTKImageWidget::staticMetaObject = {
    { &QVTKWidget::staticMetaObject, qt_meta_stringdata_QVTKImageWidget.data,
      qt_meta_data_QVTKImageWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *QVTKImageWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QVTKImageWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_QVTKImageWidget.stringdata0))
        return static_cast<void*>(const_cast< QVTKImageWidget*>(this));
    return QVTKWidget::qt_metacast(_clname);
}

int QVTKImageWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QVTKWidget::qt_metacall(_c, _id, _a);
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
void QVTKImageWidget::showCursorActor()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void QVTKImageWidget::hideCursorActor()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void QVTKImageWidget::mouseWheelEvent(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void QVTKImageWidget::rightButtonPress_MouseMoveHappend(int _t1, int _t2, int _t3, int _t4, double _t5, double _t6)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)), const_cast<void*>(reinterpret_cast<const void*>(&_t6)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void QVTKImageWidget::spaceKeyPressEvent(int _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void QVTKImageWidget::leftButtonPressHappend(int _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void QVTKImageWidget::leftButtonPressOrNot_MouseMoveHappend(bool _t1, int _t2, int _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
