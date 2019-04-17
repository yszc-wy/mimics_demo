/****************************************************************************
** Meta object code from reading C++ file 'qFourViewWidget.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../qFourViewWidget.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qFourViewWidget.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QFourViewWidget_t {
    QByteArrayData data[21];
    char stringdata0[382];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QFourViewWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QFourViewWidget_t qt_meta_stringdata_QFourViewWidget = {
    {
QT_MOC_LITERAL(0, 0, 15), // "QFourViewWidget"
QT_MOC_LITERAL(1, 16, 18), // "currentMaskChanged"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 19), // "std::weak_ptr<Mask>"
QT_MOC_LITERAL(4, 56, 21), // "changeStatusLabelText"
QT_MOC_LITERAL(5, 78, 20), // "updateMaskListWidget"
QT_MOC_LITERAL(6, 99, 13), // "pickImageDims"
QT_MOC_LITERAL(7, 113, 12), // "QVector<int>"
QT_MOC_LITERAL(8, 126, 13), // "editMaskClick"
QT_MOC_LITERAL(9, 140, 17), // "editMaskClickMove"
QT_MOC_LITERAL(10, 158, 36), // "updateLookUpTableForCreateMas..."
QT_MOC_LITERAL(11, 195, 3), // "min"
QT_MOC_LITERAL(12, 199, 3), // "max"
QT_MOC_LITERAL(13, 203, 28), // "OnFourViewSpaceKeyPressEvent"
QT_MOC_LITERAL(14, 232, 9), // "viewIndex"
QT_MOC_LITERAL(15, 242, 5), // "model"
QT_MOC_LITERAL(16, 248, 32), // "updateSliceFromImagePlaneWidget0"
QT_MOC_LITERAL(17, 281, 32), // "updateSliceFromImagePlaneWidget1"
QT_MOC_LITERAL(18, 314, 32), // "updateSliceFromImagePlaneWidget2"
QT_MOC_LITERAL(19, 347, 21), // "showOrHidePlaneWidget"
QT_MOC_LITERAL(20, 369, 12) // "volumeRender"

    },
    "QFourViewWidget\0currentMaskChanged\0\0"
    "std::weak_ptr<Mask>\0changeStatusLabelText\0"
    "updateMaskListWidget\0pickImageDims\0"
    "QVector<int>\0editMaskClick\0editMaskClickMove\0"
    "updateLookUpTableForCreateMaskDialog\0"
    "min\0max\0OnFourViewSpaceKeyPressEvent\0"
    "viewIndex\0model\0updateSliceFromImagePlaneWidget0\0"
    "updateSliceFromImagePlaneWidget1\0"
    "updateSliceFromImagePlaneWidget2\0"
    "showOrHidePlaneWidget\0volumeRender"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QFourViewWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   79,    2, 0x06 /* Public */,
       4,    1,   82,    2, 0x06 /* Public */,
       5,    1,   85,    2, 0x06 /* Public */,
       6,    1,   88,    2, 0x06 /* Public */,
       8,    2,   91,    2, 0x06 /* Public */,
       9,    3,   96,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    2,  103,    2, 0x08 /* Private */,
      13,    2,  108,    2, 0x08 /* Private */,
      16,    0,  113,    2, 0x08 /* Private */,
      17,    0,  114,    2, 0x08 /* Private */,
      18,    0,  115,    2, 0x08 /* Private */,
      19,    0,  116,    2, 0x08 /* Private */,
      20,    0,  117,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, 0x80000000 | 7,    2,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 7,    2,    2,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 7, 0x80000000 | 7,    2,    2,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   11,   12,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   14,   15,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void QFourViewWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QFourViewWidget *_t = static_cast<QFourViewWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->currentMaskChanged((*reinterpret_cast< std::weak_ptr<Mask>(*)>(_a[1]))); break;
        case 1: _t->changeStatusLabelText((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->updateMaskListWidget((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->pickImageDims((*reinterpret_cast< QVector<int>(*)>(_a[1]))); break;
        case 4: _t->editMaskClick((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QVector<int>(*)>(_a[2]))); break;
        case 5: _t->editMaskClickMove((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QVector<int>(*)>(_a[2])),(*reinterpret_cast< QVector<int>(*)>(_a[3]))); break;
        case 6: _t->updateLookUpTableForCreateMaskDialog((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 7: _t->OnFourViewSpaceKeyPressEvent((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 8: _t->updateSliceFromImagePlaneWidget0(); break;
        case 9: _t->updateSliceFromImagePlaneWidget1(); break;
        case 10: _t->updateSliceFromImagePlaneWidget2(); break;
        case 11: _t->showOrHidePlaneWidget(); break;
        case 12: _t->volumeRender(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<int> >(); break;
            }
            break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<int> >(); break;
            }
            break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 2:
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<int> >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (QFourViewWidget::*_t)(std::weak_ptr<Mask> );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QFourViewWidget::currentMaskChanged)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (QFourViewWidget::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QFourViewWidget::changeStatusLabelText)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (QFourViewWidget::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QFourViewWidget::updateMaskListWidget)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (QFourViewWidget::*_t)(QVector<int> );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QFourViewWidget::pickImageDims)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (QFourViewWidget::*_t)(int , QVector<int> );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QFourViewWidget::editMaskClick)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (QFourViewWidget::*_t)(int , QVector<int> , QVector<int> );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QFourViewWidget::editMaskClickMove)) {
                *result = 5;
                return;
            }
        }
    }
}

const QMetaObject QFourViewWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_QFourViewWidget.data,
      qt_meta_data_QFourViewWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *QFourViewWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QFourViewWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_QFourViewWidget.stringdata0))
        return static_cast<void*>(const_cast< QFourViewWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int QFourViewWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void QFourViewWidget::currentMaskChanged(std::weak_ptr<Mask> _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QFourViewWidget::changeStatusLabelText(const QString & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void QFourViewWidget::updateMaskListWidget(const QString & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void QFourViewWidget::pickImageDims(QVector<int> _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void QFourViewWidget::editMaskClick(int _t1, QVector<int> _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void QFourViewWidget::editMaskClickMove(int _t1, QVector<int> _t2, QVector<int> _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
