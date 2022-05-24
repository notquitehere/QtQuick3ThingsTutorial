#ifndef DATAOBJECT_H
#define DATAOBJECT_H

#include <QObject>

class DataObject : public QObject {
    Q_OBJECT

    Q_PROPERTY(QString item READ item WRITE setitem NOTIFY itemChanged)
    Q_PROPERTY(bool today READ today WRITE setToday NOTIFY todayChanged)
    Q_PROPERTY(bool completed READ completed WRITE setCompleted NOTIFY completedChanged)

public:
    DataObject(QObject *parent=0);
    DataObject(const QString &item, const bool &today, const bool &completed, QObject *parent=0);

    QString item() const;
    void setitem(const QString &item);

    bool today() const;
    void setToday(const bool &today);

    bool completed() const;
    void setCompleted(const bool &completed);

signals:
    void itemChanged();
    void todayChanged();
    void completedChanged();

private:
    QString _item;
    bool _today;
    bool _completed;
};

#endif
