#ifndef TOOL_H
#define TOOL_H

#include <QString>
#include <QVector>
#include <QWidget>
#include <QColor>
#include <QPushButton>

class Tool
{
public:
    Tool();
public:
    static QVector<QString> splitQString(const QString &str, const QString &pattern);

    static void setUiElementColor(QWidget *wid, QColor color);
    static void setUiBackgroundColor(QWidget *wid, QColor color);

    static QString getDatabaseName();
    static QString getDatabaseDebugTableKay();
    static QString getDatabaseDetectTableKay();

    static QString getDatabaseDebugTableShowKay();
    static QString getDatabaseDetectTableShowKay();
};

// PropertyBuilderByName 用于生成类的成员变量
// 并生成set和get方法
// type 为变量类型
// access_permission 为变量的访问权限(public, priavte, protected)
#define PropertyBuilderByName(type, name, access_permission)\
    access_permission:\
        type m_##name;\
    public:\
    inline void set##name(type v) {\
        m_##name = v;\
    }\
    inline type get##name() {\
        return m_##name;\
    }\

// 指针类型
#define PointerPropertyBuilderByName(type, name, access_permission)\
    access_permission:\
        type* m_##name;\
    public:\
    inline void set##name(type* v){\
        m_##name = v;\
    }\
    inline type* get##name(){\
        return m_##name;\
    }\


#endif // TOOL_H
