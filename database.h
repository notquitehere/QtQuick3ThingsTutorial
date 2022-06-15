#ifndef DATABASE_H
#define DATABASE_H

#define DATABASE_NAME "threethings.db"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QCoreApplication>
#include <QFile>

class Database {

public:
    Database() = delete;
    static QSqlDatabase connect();
};

//class Database : public QObject {
//    Q_OBJECT

//public:
//    explicit Database(QObject *parent = 0);
//    ~Database();
//    bool connect();
//    void remove();
//    QSqlDatabase database();

//private:
//    QSqlDatabase _db;
//    bool openDatabase();
//    bool restoreDatabase();
//};

#endif
