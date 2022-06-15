#include "dbhelper.h"

namespace dbhelper {
    namespace {
    const char DATABASE_NAME[15] = "threeThings.db";
    QSqlDatabase _db;

    bool openDatabase(QString dbname) {
        _db = QSqlDatabase::addDatabase("QSQLITE");
        _db.setDatabaseName(dbname);

        return _db.open();
    }

    bool restoreDatabase() {
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

    void insertData() {
        QSqlQuery query;
        query.exec("insert into todoTable ( item, today, completed ) "
                   "values (\"Do 30 minutes of exercise\", true, false)");
        query.exec("insert into todoTable ( item, today, completed ) "
                   "values (\"Write blog post\", true, false)");
        query.exec("insert into todoTable ( item, today, completed ) "
                   "values (\"Bake a cake\", true, false)");
        query.exec("insert into todoTable ( item, today, completed ) "
                   "values (\"Get the car cleaned\", false, false)");
        query.exec("insert into todoTable ( item, today, completed ) "
                   "values (\"Learn how to knit\", false, false)");
    }

    } // end anonymous namespace

QSqlDatabase connectDB(bool test) {
    if (test) {
        if (!openDatabase(":memory:")) {
            qDebug() << "Database Error: failed to open test database";
        } else {
            restoreDatabase();
            insertData();
        }

    } else {
        if ( !QFile("./" + QString(DATABASE_NAME)).exists()) {
            if ( openDatabase(DATABASE_NAME) ) {
                restoreDatabase();
            }
        } else {
            openDatabase(DATABASE_NAME);
        }
    }

    return _db;
}

void removeDB() {
    _db.close();
    if (!QFile("./" + QString(DATABASE_NAME)).remove()) {
        qDebug() << "Database Error: cannot remove database file";
    }
}
} // end db helper namespace
