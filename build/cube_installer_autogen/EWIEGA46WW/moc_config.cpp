/****************************************************************************
** Meta object code from reading C++ file 'config.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../config.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'config.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSConfigENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSConfigENDCLASS = QtMocHelpers::stringData(
    "Config",
    "scriptPath_updated",
    "",
    "path",
    "archivePath_updated",
    "portIPs_updated",
    "portRoles_updated",
    "portCycleInstalls_updated",
    "rolesList_updated",
    "ipList_updated",
    "masterFiles_updated",
    "slaveFiles_updated",
    "installPassword_updated",
    "parse_Started",
    "parse_Finished",
    "parse_Archive",
    "import_Config",
    "export_Config",
    "set_MainPath",
    "update_AfterParse",
    "set_ConfigPath",
    "set_ArchivePath",
    "ch",
    "set_ScriptPath",
    "set_MasterFiles",
    "set_SlaveFiles",
    "saveEditConfigFile",
    "cancelEditConfigFile",
    "change_InstallPassword",
    "password",
    "change_PortIP",
    "PortNames",
    "port_name",
    "new_ip",
    "change_PortRole",
    "new_role",
    "change_PortCycleInstall",
    "new_check",
    "clear_SameRole"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSConfigENDCLASS_t {
    uint offsetsAndSizes[78];
    char stringdata0[7];
    char stringdata1[19];
    char stringdata2[1];
    char stringdata3[5];
    char stringdata4[20];
    char stringdata5[16];
    char stringdata6[18];
    char stringdata7[26];
    char stringdata8[18];
    char stringdata9[15];
    char stringdata10[20];
    char stringdata11[19];
    char stringdata12[24];
    char stringdata13[14];
    char stringdata14[15];
    char stringdata15[14];
    char stringdata16[14];
    char stringdata17[14];
    char stringdata18[13];
    char stringdata19[18];
    char stringdata20[15];
    char stringdata21[16];
    char stringdata22[3];
    char stringdata23[15];
    char stringdata24[16];
    char stringdata25[15];
    char stringdata26[19];
    char stringdata27[21];
    char stringdata28[23];
    char stringdata29[9];
    char stringdata30[14];
    char stringdata31[10];
    char stringdata32[10];
    char stringdata33[7];
    char stringdata34[16];
    char stringdata35[9];
    char stringdata36[24];
    char stringdata37[10];
    char stringdata38[15];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSConfigENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSConfigENDCLASS_t qt_meta_stringdata_CLASSConfigENDCLASS = {
    {
        QT_MOC_LITERAL(0, 6),  // "Config"
        QT_MOC_LITERAL(7, 18),  // "scriptPath_updated"
        QT_MOC_LITERAL(26, 0),  // ""
        QT_MOC_LITERAL(27, 4),  // "path"
        QT_MOC_LITERAL(32, 19),  // "archivePath_updated"
        QT_MOC_LITERAL(52, 15),  // "portIPs_updated"
        QT_MOC_LITERAL(68, 17),  // "portRoles_updated"
        QT_MOC_LITERAL(86, 25),  // "portCycleInstalls_updated"
        QT_MOC_LITERAL(112, 17),  // "rolesList_updated"
        QT_MOC_LITERAL(130, 14),  // "ipList_updated"
        QT_MOC_LITERAL(145, 19),  // "masterFiles_updated"
        QT_MOC_LITERAL(165, 18),  // "slaveFiles_updated"
        QT_MOC_LITERAL(184, 23),  // "installPassword_updated"
        QT_MOC_LITERAL(208, 13),  // "parse_Started"
        QT_MOC_LITERAL(222, 14),  // "parse_Finished"
        QT_MOC_LITERAL(237, 13),  // "parse_Archive"
        QT_MOC_LITERAL(251, 13),  // "import_Config"
        QT_MOC_LITERAL(265, 13),  // "export_Config"
        QT_MOC_LITERAL(279, 12),  // "set_MainPath"
        QT_MOC_LITERAL(292, 17),  // "update_AfterParse"
        QT_MOC_LITERAL(310, 14),  // "set_ConfigPath"
        QT_MOC_LITERAL(325, 15),  // "set_ArchivePath"
        QT_MOC_LITERAL(341, 2),  // "ch"
        QT_MOC_LITERAL(344, 14),  // "set_ScriptPath"
        QT_MOC_LITERAL(359, 15),  // "set_MasterFiles"
        QT_MOC_LITERAL(375, 14),  // "set_SlaveFiles"
        QT_MOC_LITERAL(390, 18),  // "saveEditConfigFile"
        QT_MOC_LITERAL(409, 20),  // "cancelEditConfigFile"
        QT_MOC_LITERAL(430, 22),  // "change_InstallPassword"
        QT_MOC_LITERAL(453, 8),  // "password"
        QT_MOC_LITERAL(462, 13),  // "change_PortIP"
        QT_MOC_LITERAL(476, 9),  // "PortNames"
        QT_MOC_LITERAL(486, 9),  // "port_name"
        QT_MOC_LITERAL(496, 6),  // "new_ip"
        QT_MOC_LITERAL(503, 15),  // "change_PortRole"
        QT_MOC_LITERAL(519, 8),  // "new_role"
        QT_MOC_LITERAL(528, 23),  // "change_PortCycleInstall"
        QT_MOC_LITERAL(552, 9),  // "new_check"
        QT_MOC_LITERAL(562, 14)   // "clear_SameRole"
    },
    "Config",
    "scriptPath_updated",
    "",
    "path",
    "archivePath_updated",
    "portIPs_updated",
    "portRoles_updated",
    "portCycleInstalls_updated",
    "rolesList_updated",
    "ipList_updated",
    "masterFiles_updated",
    "slaveFiles_updated",
    "installPassword_updated",
    "parse_Started",
    "parse_Finished",
    "parse_Archive",
    "import_Config",
    "export_Config",
    "set_MainPath",
    "update_AfterParse",
    "set_ConfigPath",
    "set_ArchivePath",
    "ch",
    "set_ScriptPath",
    "set_MasterFiles",
    "set_SlaveFiles",
    "saveEditConfigFile",
    "cancelEditConfigFile",
    "change_InstallPassword",
    "password",
    "change_PortIP",
    "PortNames",
    "port_name",
    "new_ip",
    "change_PortRole",
    "new_role",
    "change_PortCycleInstall",
    "new_check",
    "clear_SameRole"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSConfigENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      29,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      12,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,  188,    2, 0x06,    1 /* Public */,
       4,    1,  191,    2, 0x06,    3 /* Public */,
       5,    0,  194,    2, 0x06,    5 /* Public */,
       6,    0,  195,    2, 0x06,    6 /* Public */,
       7,    0,  196,    2, 0x06,    7 /* Public */,
       8,    0,  197,    2, 0x06,    8 /* Public */,
       9,    0,  198,    2, 0x06,    9 /* Public */,
      10,    1,  199,    2, 0x06,   10 /* Public */,
      11,    1,  202,    2, 0x06,   12 /* Public */,
      12,    0,  205,    2, 0x06,   14 /* Public */,
      13,    0,  206,    2, 0x06,   15 /* Public */,
      14,    0,  207,    2, 0x06,   16 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      15,    0,  208,    2, 0x0a,   17 /* Public */,
      16,    1,  209,    2, 0x0a,   18 /* Public */,
      17,    1,  212,    2, 0x0a,   20 /* Public */,
      18,    1,  215,    2, 0x0a,   22 /* Public */,
      19,    0,  218,    2, 0x08,   24 /* Private */,
      20,    1,  219,    2, 0x08,   25 /* Private */,
      21,    1,  222,    2, 0x08,   27 /* Private */,
      23,    1,  225,    2, 0x08,   29 /* Private */,
      24,    1,  228,    2, 0x08,   31 /* Private */,
      25,    1,  231,    2, 0x08,   33 /* Private */,
      26,    0,  234,    2, 0x08,   35 /* Private */,
      27,    0,  235,    2, 0x08,   36 /* Private */,
      28,    1,  236,    2, 0x08,   37 /* Private */,
      30,    2,  239,    2, 0x08,   39 /* Private */,
      34,    2,  244,    2, 0x08,   42 /* Private */,
      36,    2,  249,    2, 0x08,   45 /* Private */,
      38,    1,  254,    2, 0x08,   48 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::Bool,   22,
    QMetaType::Void, QMetaType::Bool,   22,
    QMetaType::Void, QMetaType::Bool,   22,
    QMetaType::Void, QMetaType::Bool,   22,
    QMetaType::Bool,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   29,
    QMetaType::Void, 0x80000000 | 31, QMetaType::QString,   32,   33,
    QMetaType::Void, 0x80000000 | 31, QMetaType::QString,   32,   35,
    QMetaType::Void, 0x80000000 | 31, QMetaType::Bool,   32,   37,
    QMetaType::Void, 0x80000000 | 31,   32,

       0        // eod
};

Q_CONSTINIT const QMetaObject Config::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_CLASSConfigENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSConfigENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSConfigENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<Config, std::true_type>,
        // method 'scriptPath_updated'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'archivePath_updated'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'portIPs_updated'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'portRoles_updated'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'portCycleInstalls_updated'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'rolesList_updated'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'ipList_updated'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'masterFiles_updated'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'slaveFiles_updated'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'installPassword_updated'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'parse_Started'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'parse_Finished'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'parse_Archive'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'import_Config'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'export_Config'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'set_MainPath'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'update_AfterParse'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'set_ConfigPath'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'set_ArchivePath'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'set_ScriptPath'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'set_MasterFiles'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'set_SlaveFiles'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'saveEditConfigFile'
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'cancelEditConfigFile'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'change_InstallPassword'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'change_PortIP'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<PortNames, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'change_PortRole'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<PortNames, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'change_PortCycleInstall'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<PortNames, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'clear_SameRole'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<PortNames, std::false_type>
    >,
    nullptr
} };

void Config::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Config *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->scriptPath_updated((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 1: _t->archivePath_updated((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 2: _t->portIPs_updated(); break;
        case 3: _t->portRoles_updated(); break;
        case 4: _t->portCycleInstalls_updated(); break;
        case 5: _t->rolesList_updated(); break;
        case 6: _t->ipList_updated(); break;
        case 7: _t->masterFiles_updated((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 8: _t->slaveFiles_updated((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 9: _t->installPassword_updated(); break;
        case 10: _t->parse_Started(); break;
        case 11: _t->parse_Finished(); break;
        case 12: _t->parse_Archive(); break;
        case 13: _t->import_Config((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 14: _t->export_Config((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 15: _t->set_MainPath((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 16: _t->update_AfterParse(); break;
        case 17: _t->set_ConfigPath((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 18: _t->set_ArchivePath((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 19: _t->set_ScriptPath((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 20: _t->set_MasterFiles((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 21: _t->set_SlaveFiles((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 22: { bool _r = _t->saveEditConfigFile();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 23: _t->cancelEditConfigFile(); break;
        case 24: _t->change_InstallPassword((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 25: _t->change_PortIP((*reinterpret_cast< std::add_pointer_t<PortNames>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 26: _t->change_PortRole((*reinterpret_cast< std::add_pointer_t<PortNames>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 27: _t->change_PortCycleInstall((*reinterpret_cast< std::add_pointer_t<PortNames>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[2]))); break;
        case 28: _t->clear_SameRole((*reinterpret_cast< std::add_pointer_t<PortNames>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Config::*)(QString );
            if (_t _q_method = &Config::scriptPath_updated; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Config::*)(QString );
            if (_t _q_method = &Config::archivePath_updated; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Config::*)();
            if (_t _q_method = &Config::portIPs_updated; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (Config::*)();
            if (_t _q_method = &Config::portRoles_updated; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (Config::*)();
            if (_t _q_method = &Config::portCycleInstalls_updated; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (Config::*)();
            if (_t _q_method = &Config::rolesList_updated; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (Config::*)();
            if (_t _q_method = &Config::ipList_updated; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (Config::*)(QString );
            if (_t _q_method = &Config::masterFiles_updated; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (Config::*)(QString );
            if (_t _q_method = &Config::slaveFiles_updated; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (Config::*)();
            if (_t _q_method = &Config::installPassword_updated; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (Config::*)();
            if (_t _q_method = &Config::parse_Started; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 10;
                return;
            }
        }
        {
            using _t = void (Config::*)();
            if (_t _q_method = &Config::parse_Finished; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 11;
                return;
            }
        }
    }
}

const QMetaObject *Config::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Config::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSConfigENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int Config::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 29)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 29;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 29)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 29;
    }
    return _id;
}

// SIGNAL 0
void Config::scriptPath_updated(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Config::archivePath_updated(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Config::portIPs_updated()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void Config::portRoles_updated()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void Config::portCycleInstalls_updated()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void Config::rolesList_updated()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void Config::ipList_updated()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void Config::masterFiles_updated(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void Config::slaveFiles_updated(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void Config::installPassword_updated()
{
    QMetaObject::activate(this, &staticMetaObject, 9, nullptr);
}

// SIGNAL 10
void Config::parse_Started()
{
    QMetaObject::activate(this, &staticMetaObject, 10, nullptr);
}

// SIGNAL 11
void Config::parse_Finished()
{
    QMetaObject::activate(this, &staticMetaObject, 11, nullptr);
}
QT_WARNING_POP
