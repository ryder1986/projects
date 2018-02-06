/****************************************************************************
** Meta object code from reading C++ file 'formdevicedetail.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../demo1-v5/client/formdevicedetail.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'formdevicedetail.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_FormDeviceDetail_t {
    QByteArrayData data[11];
    char stringdata0[170];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FormDeviceDetail_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FormDeviceDetail_t qt_meta_stringdata_FormDeviceDetail = {
    {
QT_MOC_LITERAL(0, 0, 16), // "FormDeviceDetail"
QT_MOC_LITERAL(1, 17, 15), // "camera_selected"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 8), // "Camera_t"
QT_MOC_LITERAL(4, 43, 3), // "cfg"
QT_MOC_LITERAL(5, 47, 14), // "config_arrived"
QT_MOC_LITERAL(6, 62, 3), // "ret"
QT_MOC_LITERAL(7, 66, 29), // "on_pushButton_connect_clicked"
QT_MOC_LITERAL(8, 96, 32), // "on_pushButton_get_config_clicked"
QT_MOC_LITERAL(9, 129, 34), // "on_treeWidget_device_doubleCl..."
QT_MOC_LITERAL(10, 164, 5) // "index"

    },
    "FormDeviceDetail\0camera_selected\0\0"
    "Camera_t\0cfg\0config_arrived\0ret\0"
    "on_pushButton_connect_clicked\0"
    "on_pushButton_get_config_clicked\0"
    "on_treeWidget_device_doubleClicked\0"
    "index"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FormDeviceDetail[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    2,   42,    2, 0x08 /* Private */,
       7,    0,   47,    2, 0x08 /* Private */,
       8,    0,   48,    2, 0x08 /* Private */,
       9,    1,   49,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool, QMetaType::QByteArray,    6,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QModelIndex,   10,

       0        // eod
};

void FormDeviceDetail::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        FormDeviceDetail *_t = static_cast<FormDeviceDetail *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->camera_selected((*reinterpret_cast< Camera_t(*)>(_a[1]))); break;
        case 1: _t->config_arrived((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< QByteArray(*)>(_a[2]))); break;
        case 2: _t->on_pushButton_connect_clicked(); break;
        case 3: _t->on_pushButton_get_config_clicked(); break;
        case 4: _t->on_treeWidget_device_doubleClicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (FormDeviceDetail::*_t)(Camera_t );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&FormDeviceDetail::camera_selected)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject FormDeviceDetail::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_FormDeviceDetail.data,
      qt_meta_data_FormDeviceDetail,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *FormDeviceDetail::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FormDeviceDetail::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_FormDeviceDetail.stringdata0))
        return static_cast<void*>(const_cast< FormDeviceDetail*>(this));
    return QWidget::qt_metacast(_clname);
}

int FormDeviceDetail::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
void FormDeviceDetail::camera_selected(Camera_t _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
