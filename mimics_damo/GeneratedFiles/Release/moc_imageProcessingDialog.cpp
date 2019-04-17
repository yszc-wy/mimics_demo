/****************************************************************************
** Meta object code from reading C++ file 'imageProcessingDialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../imageProcessingDialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'imageProcessingDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ImageProcessingDialog_t {
    QByteArrayData data[4];
    char stringdata0[58];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ImageProcessingDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ImageProcessingDialog_t qt_meta_stringdata_ImageProcessingDialog = {
    {
QT_MOC_LITERAL(0, 0, 21), // "ImageProcessingDialog"
QT_MOC_LITERAL(1, 22, 17), // "processingRequest"
QT_MOC_LITERAL(2, 40, 0), // ""
QT_MOC_LITERAL(3, 41, 16) // "QVector<QString>"

    },
    "ImageProcessingDialog\0processingRequest\0"
    "\0QVector<QString>"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ImageProcessingDialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   19,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, 0x80000000 | 3,    2,    2,

       0        // eod
};

void ImageProcessingDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ImageProcessingDialog *_t = static_cast<ImageProcessingDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->processingRequest((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QVector<QString>(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<QString> >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ImageProcessingDialog::*_t)(QString , QVector<QString> );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ImageProcessingDialog::processingRequest)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject ImageProcessingDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_ImageProcessingDialog.data,
      qt_meta_data_ImageProcessingDialog,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ImageProcessingDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ImageProcessingDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ImageProcessingDialog.stringdata0))
        return static_cast<void*>(const_cast< ImageProcessingDialog*>(this));
    if (!strcmp(_clname, "Ui::ImageProcessingDialog"))
        return static_cast< Ui::ImageProcessingDialog*>(const_cast< ImageProcessingDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int ImageProcessingDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void ImageProcessingDialog::processingRequest(QString _t1, QVector<QString> _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
