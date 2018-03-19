/****************************************************************************
** Meta object code from reading C++ file 'serverinfosearcher.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../client-demo/serverinfosearcher.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'serverinfosearcher.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ServerReplyCheckRouting_t {
    QByteArrayData data[7];
    char stringdata0[88];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ServerReplyCheckRouting_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ServerReplyCheckRouting_t qt_meta_stringdata_ServerReplyCheckRouting = {
    {
QT_MOC_LITERAL(0, 0, 23), // "ServerReplyCheckRouting"
QT_MOC_LITERAL(1, 24, 11), // "resultReady"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 6), // "result"
QT_MOC_LITERAL(4, 44, 11), // "check_reply"
QT_MOC_LITERAL(5, 56, 11), // "QUdpSocket*"
QT_MOC_LITERAL(6, 68, 19) // "udp_skt_find_server"

    },
    "ServerReplyCheckRouting\0resultReady\0"
    "\0result\0check_reply\0QUdpSocket*\0"
    "udp_skt_find_server"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ServerReplyCheckRouting[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   24,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   27,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 5,    6,

       0        // eod
};

void ServerReplyCheckRouting::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ServerReplyCheckRouting *_t = static_cast<ServerReplyCheckRouting *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->resultReady((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->check_reply((*reinterpret_cast< QUdpSocket*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QUdpSocket* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ServerReplyCheckRouting::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ServerReplyCheckRouting::resultReady)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject ServerReplyCheckRouting::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ServerReplyCheckRouting.data,
      qt_meta_data_ServerReplyCheckRouting,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ServerReplyCheckRouting::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ServerReplyCheckRouting::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ServerReplyCheckRouting.stringdata0))
        return static_cast<void*>(const_cast< ServerReplyCheckRouting*>(this));
    return QObject::qt_metacast(_clname);
}

int ServerReplyCheckRouting::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void ServerReplyCheckRouting::resultReady(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
struct qt_meta_stringdata_ServerInfoSearcher_t {
    QByteArrayData data[8];
    char stringdata0[85];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ServerInfoSearcher_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ServerInfoSearcher_t qt_meta_stringdata_ServerInfoSearcher = {
    {
QT_MOC_LITERAL(0, 0, 18), // "ServerInfoSearcher"
QT_MOC_LITERAL(1, 19, 12), // "begin_search"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 11), // "QUdpSocket*"
QT_MOC_LITERAL(4, 45, 19), // "udp_skt_find_server"
QT_MOC_LITERAL(5, 65, 7), // "find_ip"
QT_MOC_LITERAL(6, 73, 2), // "ip"
QT_MOC_LITERAL(7, 76, 8) // "ip_found"

    },
    "ServerInfoSearcher\0begin_search\0\0"
    "QUdpSocket*\0udp_skt_find_server\0find_ip\0"
    "ip\0ip_found"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ServerInfoSearcher[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x06 /* Public */,
       5,    1,   32,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    1,   35,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::QString,    6,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    6,

       0        // eod
};

void ServerInfoSearcher::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ServerInfoSearcher *_t = static_cast<ServerInfoSearcher *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->begin_search((*reinterpret_cast< QUdpSocket*(*)>(_a[1]))); break;
        case 1: _t->find_ip((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->ip_found((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QUdpSocket* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ServerInfoSearcher::*_t)(QUdpSocket * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ServerInfoSearcher::begin_search)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (ServerInfoSearcher::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ServerInfoSearcher::find_ip)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject ServerInfoSearcher::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ServerInfoSearcher.data,
      qt_meta_data_ServerInfoSearcher,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ServerInfoSearcher::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ServerInfoSearcher::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ServerInfoSearcher.stringdata0))
        return static_cast<void*>(const_cast< ServerInfoSearcher*>(this));
    return QObject::qt_metacast(_clname);
}

int ServerInfoSearcher::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void ServerInfoSearcher::begin_search(QUdpSocket * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ServerInfoSearcher::find_ip(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
