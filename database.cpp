#include "database.h"

QSqlDatabase Database::connect() {
    if ( !QFile("./" DATABASE_NAME).exists() ) {
        if ( this -> openDatabase() ) {
            return this -> restoreDatabase();
        }
        qDebug() << "Database Error: failed to restore database";
        return false;
    }
    return this->openDatabase();
}

void Database::remove() {
    _db.close();
    if (QFile("./" DATABASE_NAME).exists() ) {
        QFile("./" DATABASE_NAME).remove();
    } else {
        qDebug() << "Database Error: cannot remove database file";
    }
}

bool Database::openDatabase() {
    _db = QSqlDatabase::addDatabase("QSQLITE");
    _db.setHostName("threeThingsDatabase");
    _db.setDatabaseName(DATABASE_NAME);

    return _db.open();
}

bool Database::restoreDatabase() {
    QSqlQuery query;
    query.prepare("CREATE TABLE todoTable ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
            "item VARCHAR(255) NOT NULL, "
            "today BOOL DEFAULT FALSE, "
            "completed BOOL DEFAULT FALSE "
        "); ");

    if ( !query.exec() ) {
        qDebug() << "Database Error: failed to create table";
        qDebug() << query.lastError().text();
        return false;
    }
    return true;
}
