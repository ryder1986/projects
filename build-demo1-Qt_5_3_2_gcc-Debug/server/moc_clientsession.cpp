/****************************************************************************
** Meta object code from reading C++ file 'clientsession.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../demo1-v5/server/clientsession.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'clientsession.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ClientSession_t {
    QByteArrayData data[28];
    char stringdata0[273];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ClientSession_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ClientSession_t qt_meta_stringdata_ClientSession = {
    {
QT_MOC_LITERAL(0, 0, 13), // "ClientSession"
QT_MOC_LITERAL(1, 14, 17), // "get_server_config"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 5), // "char*"
QT_MOC_LITERAL(4, 39, 3), // "buf"
QT_MOC_LITERAL(5, 43, 12), // "socket_error"
QT_MOC_LITERAL(6, 56, 14), // "ClientSession*"
QT_MOC_LITERAL(7, 71, 1), // "c"
QT_MOC_LITERAL(8, 73, 17), // "session_operation"
QT_MOC_LITERAL(9, 91, 3), // "req"
QT_MOC_LITERAL(10, 95, 4), // "addr"
QT_MOC_LITERAL(11, 100, 3), // "len"
QT_MOC_LITERAL(12, 104, 9), // "cam_index"
QT_MOC_LITERAL(13, 114, 4), // "int&"
QT_MOC_LITERAL(14, 119, 8), // "ret_size"
QT_MOC_LITERAL(15, 128, 14), // "handle_alg_out"
QT_MOC_LITERAL(16, 143, 3), // "out"
QT_MOC_LITERAL(17, 147, 14), // "error_happened"
QT_MOC_LITERAL(18, 162, 10), // "handle_msg"
QT_MOC_LITERAL(19, 173, 7), // "process"
QT_MOC_LITERAL(20, 181, 7), // "src_buf"
QT_MOC_LITERAL(21, 189, 7), // "dst_buf"
QT_MOC_LITERAL(22, 197, 4), // "size"
QT_MOC_LITERAL(23, 202, 13), // "update_client"
QT_MOC_LITERAL(24, 216, 12), // "displayError"
QT_MOC_LITERAL(25, 229, 28), // "QAbstractSocket::SocketError"
QT_MOC_LITERAL(26, 258, 11), // "socketError"
QT_MOC_LITERAL(27, 270, 2) // "ip"

    },
    "ClientSession\0get_server_config\0\0char*\0"
    "buf\0socket_error\0ClientSession*\0c\0"
    "session_operation\0req\0addr\0len\0cam_index\0"
    "int&\0ret_size\0handle_alg_out\0out\0"
    "error_happened\0handle_msg\0process\0"
    "src_buf\0dst_buf\0size\0update_client\0"
    "displayError\0QAbstractSocket::SocketError\0"
    "socketError\0ip"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ClientSession[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   64,    2, 0x06 /* Public */,
       5,    1,   67,    2, 0x06 /* Public */,
       8,    6,   70,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      15,    1,   83,    2, 0x0a /* Public */,
      17,    0,   86,    2, 0x0a /* Public */,
      18,    0,   87,    2, 0x0a /* Public */,
      19,    3,   88,    2, 0x0a /* Public */,
      23,    0,   95,    2, 0x0a /* Public */,
      24,    1,   96,    2, 0x0a /* Public */,
      27,    0,   99,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Int, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, QMetaType::Int, QMetaType::VoidStar, QMetaType::Int, QMetaType::Int, 0x80000000 | 3, 0x80000000 | 13,    9,   10,   11,   12,    4,   14,

 // slots: parameters
    QMetaType::Void, QMetaType::QByteArray,   16,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Int, 0x80000000 | 3, 0x80000000 | 3, QMetaType::Int,   20,   21,   22,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 25,   26,
    QMetaType::QString,

       0        // eod
};

void ClientSession::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ClientSession *_t = static_cast<ClientSession *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: { int _r = _t->get_server_config((*reinterpret_cast< char*(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 1: _t->socket_error((*reinterpret_cast< ClientSession*(*)>(_a[1]))); break;
        case 2: _t->session_operation((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< void*(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< char*(*)>(_a[5])),(*reinterpret_cast< int(*)>(_a[6]))); break;
        case 3: _t->handle_alg_out((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 4: _t->error_happened(); break;
        case 5: _t->handle_msg(); break;
        case 6: { int _r = _t->process((*reinterpret_cast< char*(*)>(_a[1])),(*reinterpret_cast< char*(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 7: _t->update_client(); break;
        case 8: _t->displayError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 9: { QString _r = _t->ip();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< ClientSession* >(); break;
            }
            break;
        case 8:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSocket::SocketError >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef int (ClientSession::*_t)(char * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ClientSession::get_server_config)) {
                *result = 0;
            }
        }
        {
            typedef void (ClientSession::*_t)(ClientSession * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ClientSession::socket_error)) {
                *result = 1;
            }
        }
        {
            typedef void (ClientSession::*_t)(int , void * , int , int , char * , int & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ClientSession::session_operation)) {
                *result = 2;
            }
        }
    }
}

const QMetaObject ClientSession::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ClientSession.data,
      qt_meta_data_ClientSession,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ClientSession::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ClientSession::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ClientSession.stringdata0))
        return static_cast<void*>(const_cast< ClientSession*>(this));
    return QObject::qt_metacast(_clname);
}

int ClientSession::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
int ClientSession::get_server_config(char * _t1)
{
    int _t0 = int();
    void *_a[] = { const_cast<void*>(reinterpret_cast<const void*>(&_t0)), const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
    return _t0;
}

// SIGNAL 1
void ClientSession::socket_error(ClientSession * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ClientSession::session_operation(int _t1, void * _t2, int _t3, int _t4, char * _t5, int & _t6)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)), const_cast<void*>(reinterpret_cast<const void*>(&_t6)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
