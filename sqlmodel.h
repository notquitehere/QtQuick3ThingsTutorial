#ifndef SQLMODEL_H
#define SQLMODEL_H

#include <QSqlTableModel>
#include <QSqlDatabase>

class SqlModel : public QSqlTableModel {
    Q_OBJECT

public:
    enum Roles {
        IdRole = Qt::UserRole + 1,
        ItemRole,
        TodayRole,
        CompletedRole,
        DeleteRole,
    };

    explicit SqlModel(QObject *parent = nullptr, QSqlDatabase db = QSqlDatabase());
    ~SqlModel();

    Q_INVOKABLE void add();

    bool setData(const QModelIndex &index, const QVariant &value, int role);
    QVariant data(const QModelIndex &index, int role) const;

protected:
    QHash<int, QByteArray> roleNames() const;

};

#endif
