/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../Frontend/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[23];
    char stringdata0[253];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 7), // "addNode"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 19), // "removeSelectedItems"
QT_MOC_LITERAL(4, 40, 12), // "undoLastNode"
QT_MOC_LITERAL(5, 53, 9), // "makeForce"
QT_MOC_LITERAL(6, 63, 11), // "makeSupport"
QT_MOC_LITERAL(7, 75, 5), // "clear"
QT_MOC_LITERAL(8, 81, 4), // "save"
QT_MOC_LITERAL(9, 86, 4), // "load"
QT_MOC_LITERAL(10, 91, 17), // "linearStateChange"
QT_MOC_LITERAL(11, 109, 7), // "updateE"
QT_MOC_LITERAL(12, 117, 7), // "updateA"
QT_MOC_LITERAL(13, 125, 5), // "solve"
QT_MOC_LITERAL(14, 131, 10), // "showResult"
QT_MOC_LITERAL(15, 142, 16), // "showDisplacement"
QT_MOC_LITERAL(16, 159, 12), // "showOriginal"
QT_MOC_LITERAL(17, 172, 15), // "graphicalExport"
QT_MOC_LITERAL(18, 188, 14), // "onButtonZoomIn"
QT_MOC_LITERAL(19, 203, 15), // "onButtonZoomOut"
QT_MOC_LITERAL(20, 219, 12), // "xFixedChange"
QT_MOC_LITERAL(21, 232, 12), // "yFixedChange"
QT_MOC_LITERAL(22, 245, 7) // "getInfo"

    },
    "MainWindow\0addNode\0\0removeSelectedItems\0"
    "undoLastNode\0makeForce\0makeSupport\0"
    "clear\0save\0load\0linearStateChange\0"
    "updateE\0updateA\0solve\0showResult\0"
    "showDisplacement\0showOriginal\0"
    "graphicalExport\0onButtonZoomIn\0"
    "onButtonZoomOut\0xFixedChange\0yFixedChange\0"
    "getInfo"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      21,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  119,    2, 0x08 /* Private */,
       3,    0,  120,    2, 0x08 /* Private */,
       4,    0,  121,    2, 0x08 /* Private */,
       5,    0,  122,    2, 0x08 /* Private */,
       6,    0,  123,    2, 0x08 /* Private */,
       7,    0,  124,    2, 0x08 /* Private */,
       8,    0,  125,    2, 0x08 /* Private */,
       9,    0,  126,    2, 0x08 /* Private */,
      10,    0,  127,    2, 0x08 /* Private */,
      11,    0,  128,    2, 0x08 /* Private */,
      12,    0,  129,    2, 0x08 /* Private */,
      13,    0,  130,    2, 0x08 /* Private */,
      14,    0,  131,    2, 0x08 /* Private */,
      15,    0,  132,    2, 0x08 /* Private */,
      16,    0,  133,    2, 0x08 /* Private */,
      17,    0,  134,    2, 0x08 /* Private */,
      18,    0,  135,    2, 0x08 /* Private */,
      19,    0,  136,    2, 0x08 /* Private */,
      20,    0,  137,    2, 0x08 /* Private */,
      21,    0,  138,    2, 0x08 /* Private */,
      22,    0,  139,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->addNode(); break;
        case 1: _t->removeSelectedItems(); break;
        case 2: _t->undoLastNode(); break;
        case 3: _t->makeForce(); break;
        case 4: _t->makeSupport(); break;
        case 5: _t->clear(); break;
        case 6: _t->save(); break;
        case 7: _t->load(); break;
        case 8: _t->linearStateChange(); break;
        case 9: _t->updateE(); break;
        case 10: _t->updateA(); break;
        case 11: _t->solve(); break;
        case 12: _t->showResult(); break;
        case 13: _t->showDisplacement(); break;
        case 14: _t->showOriginal(); break;
        case 15: _t->graphicalExport(); break;
        case 16: _t->onButtonZoomIn(); break;
        case 17: _t->onButtonZoomOut(); break;
        case 18: _t->xFixedChange(); break;
        case 19: _t->yFixedChange(); break;
        case 20: _t->getInfo(); break;
        default: ;
        }
    }
    (void)_a;
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 21)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 21;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 21)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 21;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
