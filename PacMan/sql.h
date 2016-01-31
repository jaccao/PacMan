#ifndef SQL_H
#define SQL_H

#include <string>

#include "sqlite3.h"
using namespace std;

class Sql
{

public:
    Sql(string database);
private:
    string database;
    sqlite3 *dbSQLite;
    int open(string filename, sqlite3 **ppDb);
    int prepare(sqlite3 *db, string zSql, sqlite3_stmt **ppStmt);
    int step(sqlite3_stmt *pStmt);
    int finalize(sqlite3_stmt *pStmt);
    int close(sqlite3 *pDb);
    int column_bytes(sqlite3_stmt *pStmt, int iCol);
    string column_text(sqlite3_stmt *pStmt, int iCol);
    string errmsg(sqlite3 *pDb);
    bool connect();
    void disconnect();
    int column_count(sqlite3_stmt *pStmt);
public:
    string query(string query);
};

#endif // SQLJSON_H
