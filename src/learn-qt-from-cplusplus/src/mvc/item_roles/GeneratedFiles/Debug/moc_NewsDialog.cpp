/****************************************************************************
** Meta object code from reading C++ file 'NewsDialog.h'
**
** Created: Wed Apr 25 11:01:48 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../NewsDialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'NewsDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_NewsDialog[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      29,   12,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_NewsDialog[] = {
    "NewsDialog\0\0current,previous\0"
    "changeNews(QListWidgetItem*,QListWidgetItem*)\0"
};

void NewsDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        NewsDialog *_t = static_cast<NewsDialog *>(_o);
        switch (_id) {
        case 0: _t->changeNews((*reinterpret_cast< QListWidgetItem*(*)>(_a[1])),(*reinterpret_cast< QListWidgetItem*(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData NewsDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject NewsDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_NewsDialog,
      qt_meta_data_NewsDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &NewsDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *NewsDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *NewsDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_NewsDialog))
        return static_cast<void*>(const_cast< NewsDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int NewsDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
