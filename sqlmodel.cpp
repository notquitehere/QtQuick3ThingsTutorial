#include "sqlmodel.h"

SqlModel::SqlModel(QObject *parent, QSqlDatabase db) :
    QSqlTableModel(parent, db) {
//	empty
}

SqlModel::~SqlModel() {
//    empty
}

QHash<int, QByteArray> SqlModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[IdRole] = "id";
    roles[ItemRole] = "item";
    roles[TodayRole] = "today";
    roles[CompletedRole] = "completed";
    roles[DeleteRole] = "remove";
    return roles;
}

void SqlModel::add() {
    this->insertRows(this->rowCount(), 1);
    this->submitAll();
}

bool SqlModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    bool updated = false;

    if ( index.isValid() && roleNames().contains(role)) {
        if ( role == DeleteRole ) {
            this->removeRows(index.row(), 1);
            this->submitAll();
        } else if (value != this->data(index, role)) {
            QSqlTableModel::setData(this->index(index.row(), role - Qt::UserRole - 1), value);
            this->submitAll();
            updated = true;
        }
    }

    if (updated) emit dataChanged(index, index, { role });
    return updated;
}

QVariant SqlModel::data (const QModelIndex &index, int role) const {
    if ( !index.isValid() || index.row() > QSqlTableModel::rowCount() ) {
        return QVariant();
    } else if ( role <= Qt::UserRole ) {
        return QSqlTableModel::data(index, role);
    }

    QVariant d = QSqlTableModel::data(this->index(index.row(), role - Qt::UserRole - 1), Qt::DisplayRole);

    switch (role) {
        case TodayRole:
        case CompletedRole:
            return d.toBool();
        default:
            return d;
    }
}
