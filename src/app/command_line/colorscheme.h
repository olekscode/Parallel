#ifndef COLORSCHEME_H
#define COLORSCHEME_H

#include <QObject>
#include <QString>

class ColorScheme : public QObject
{
    Q_OBJECT

public:
    explicit ColorScheme(QObject *parent = 0)
        : QObject(parent) {}

    virtual QString background() const = 0;
    virtual QString text() const = 0;
    virtual QString prompt() const = 0;
    virtual QString responseSuccessful() const = 0;
    virtual QString responseCritical() const = 0;
};

class MainCLColorScheme : public ColorScheme
{
    Q_OBJECT

public:
    MainCLColorScheme(QObject *parent = 0)
        : ColorScheme(parent) {}

    QString background() const          { return "#272822"; }
    QString text() const                { return "#C0C0C0"; }
    QString prompt() const              { return "#99CCFF"; }
    QString responseSuccessful() const  { return "#99FF66"; }
    QString responseCritical() const    { return "#FF5050"; }
};

class SubCLColorScheme : public ColorScheme
{
    Q_OBJECT

public:
    SubCLColorScheme(QObject *parent = 0)
        : ColorScheme(parent) {}

    QString background() const          { return "#272822"; }
    QString text() const                { return "#C0C0C0"; }
    QString prompt() const              { return "#99CCFF"; }
    QString responseSuccessful() const  { return "#99FFCC"; }
    QString responseCritical() const    { return "#FF5050"; }
};

#endif // COLORSCHEME_H
