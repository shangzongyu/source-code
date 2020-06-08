/****************************************************************************
** Meta object code from reading C++ file 'widgetgallery.h'
**
** Created: Wed Apr 25 09:30:03 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../widgetgallery.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'widgetgallery.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_WidgetGallery[] = {

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

 // slots: signature, parameters, type, tag, flags
      25,   15,   14,   14, 0x08,
      46,   14,   14,   14, 0x08,
      62,   14,   14,   14, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_WidgetGallery[] = {
    "WidgetGallery\0\0styleName\0changeStyle(QString)\0"
    "changePalette()\0advanceProgressBar()\0"
};

void WidgetGallery::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        WidgetGallery *_t = static_cast<WidgetGallery *>(_o);
        switch (_id) {
        case 0: _t->changeStyle((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->changePalette(); break;
        case 2: _t->advanceProgressBar(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData WidgetGallery::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject WidgetGallery::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_WidgetGallery,
      qt_meta_data_WidgetGallery, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &WidgetGallery::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *WidgetGallery::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *WidgetGallery::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_WidgetGallery))
        return static_cast<void*>(const_cast< WidgetGallery*>(this));
    return QDialog::qt_metacast(_clname);
}

int WidgetGallery::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
