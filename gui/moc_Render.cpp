/****************************************************************************
** Meta object code from reading C++ file 'Render.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "Render.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Render.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_RenderDialog[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      13,   43,   49,   49, 0x08,
      50,   85,   49,   49, 0x08,
     101,  138,   49,   49, 0x08,
     144,   49,   49,   49, 0x08,
     170,   49,   49,   49, 0x08,
     190,   49,   49,   49, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_RenderDialog[] = {
    "RenderDialog\0error(QProcess::ProcessError)\0"
    "error\0\0finished(int,QProcess::ExitStatus)\0"
    "exitCode,status\0stateChanged(QProcess::ProcessState)\0"
    "state\0readyReadStandardOutput()\0"
    "on_Return_clicked()\0on_Stop_clicked()\0"
};

void RenderDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        RenderDialog *_t = static_cast<RenderDialog *>(_o);
        switch (_id) {
        case 0: _t->error((*reinterpret_cast< QProcess::ProcessError(*)>(_a[1]))); break;
        case 1: _t->finished((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QProcess::ExitStatus(*)>(_a[2]))); break;
        case 2: _t->stateChanged((*reinterpret_cast< QProcess::ProcessState(*)>(_a[1]))); break;
        case 3: _t->readyReadStandardOutput(); break;
        case 4: _t->on_Return_clicked(); break;
        case 5: _t->on_Stop_clicked(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData RenderDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject RenderDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_RenderDialog,
      qt_meta_data_RenderDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &RenderDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *RenderDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *RenderDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_RenderDialog))
        return static_cast<void*>(const_cast< RenderDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int RenderDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE