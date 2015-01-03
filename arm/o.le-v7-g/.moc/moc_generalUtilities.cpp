/****************************************************************************
** Meta object code from reading C++ file 'generalUtilities.hpp'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/generalUtilities.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'generalUtilities.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_GeneralUtilities[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // methods: signature, parameters, type, tag, flags
      37,   31,   18,   17, 0x02,
      68,   31,   56,   17, 0x02,
      90,   86,   17,   17, 0x02,

       0        // eod
};

static const char qt_meta_stringdata_GeneralUtilities[] = {
    "GeneralUtilities\0\0QVariantList\0reply\0"
    "json2List(QString)\0QVariantMap\0"
    "json2Map(QString)\0msg\0createToast(QString)\0"
};

void GeneralUtilities::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        GeneralUtilities *_t = static_cast<GeneralUtilities *>(_o);
        switch (_id) {
        case 0: { QVariantList _r = _t->json2List((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = _r; }  break;
        case 1: { QVariantMap _r = _t->json2Map((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariantMap*>(_a[0]) = _r; }  break;
        case 2: _t->createToast((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData GeneralUtilities::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject GeneralUtilities::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_GeneralUtilities,
      qt_meta_data_GeneralUtilities, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &GeneralUtilities::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *GeneralUtilities::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *GeneralUtilities::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GeneralUtilities))
        return static_cast<void*>(const_cast< GeneralUtilities*>(this));
    return QObject::qt_metacast(_clname);
}

int GeneralUtilities::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
