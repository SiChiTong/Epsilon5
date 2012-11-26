#pragma once

#include <QObject>
#include <QString>
#include <QStringList>
#include <QHash>

class USettings: public QObject
{
    Q_OBJECT
public:
    USettings(QObject* parent = 0);
    virtual ~USettings() {}
    void Load(const QString& fname, const QStringList& required = QStringList());
    QString GetParameter(const QString& parameter);
private:
    QHash<QString, QString> Parameters;
};
