/****************************************************************************
** Meta object code from reading C++ file 'Send.hpp'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/Send.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Send.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Send[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       1,   69, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       6,    5,    5,    5, 0x0a,
      21,    5,    5,    5, 0x0a,
      40,   34,    5,    5, 0x0a,
     100,   79,    5,    5, 0x0a,

 // methods: signature, parameters, type, tag, flags
     136,    5,    5,    5, 0x02,
     149,    5,    5,    5, 0x02,
     162,    5,    5,    5, 0x02,
     176,  169,    5,    5, 0x02,
     198,  169,    5,    5, 0x02,
     229,  220,    5,    5, 0x02,
     249,    5,    5,    5, 0x02,

 // properties: name, type, flags
     296,  266, 0x00095409,

       0        // eod
};

static const char qt_meta_stringdata_Send[] = {
    "Send\0\0finishedSlot()\0sendFinish()\0"
    "event\0handleTouch(bb::cascades::TouchEvent*)\0"
    "bytesSent,bytesTotal\0"
    "SlotSetProgressLevel(qint64,qint64)\0"
    "addDevices()\0getDevices()\0test()\0"
    "device\0sendText(QVariantMap)\0"
    "sendFile(QVariantMap)\0fileName\0"
    "filePicker(QString)\0setSaveMessage()\0"
    "bb::cascades::GroupDataModel*\0model\0"
};

void Send::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Send *_t = static_cast<Send *>(_o);
        switch (_id) {
        case 0: _t->finishedSlot(); break;
        case 1: _t->sendFinish(); break;
        case 2: _t->handleTouch((*reinterpret_cast< bb::cascades::TouchEvent*(*)>(_a[1]))); break;
        case 3: _t->SlotSetProgressLevel((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        case 4: _t->addDevices(); break;
        case 5: _t->getDevices(); break;
        case 6: _t->test(); break;
        case 7: _t->sendText((*reinterpret_cast< QVariantMap(*)>(_a[1]))); break;
        case 8: _t->sendFile((*reinterpret_cast< QVariantMap(*)>(_a[1]))); break;
        case 9: _t->filePicker((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 10: _t->setSaveMessage(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Send::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Send::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Send,
      qt_meta_data_Send, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Send::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Send::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Send::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Send))
        return static_cast<void*>(const_cast< Send*>(this));
    return QObject::qt_metacast(_clname);
}

int Send::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< bb::cascades::GroupDataModel**>(_v) = model(); break;
        }
        _id -= 1;
    } else if (_c == QMetaObject::WriteProperty) {
        _id -= 1;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 1;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}
QT_END_MOC_NAMESPACE
