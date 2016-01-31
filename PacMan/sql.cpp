#include "sql.h"

Sql::Sql(string database)
{
    dbSQLite=NULL;
    this->database=database;
    connect();
}

string Sql::query(string query)
{
    if(dbSQLite==false)
    {
//        throw(QString("SqlJson::query: database not connected: "+query.toString()));
    }
    int rc;
    sqlite3_stmt *stmt=NULL;
    rc=prepare(dbSQLite,query,&stmt);
    if(rc!=SQLITE_OK)
    {
 //       throw(errmsg(dbSQLite)+": "+query.toString());
    }
    rc=step(stmt);
    if(rc!=SQLITE_DONE) if(rc!=SQLITE_OK) if(rc!=SQLITE_ROW)
    {
   //     throw(errmsg(dbSQLite)+": "+query.toString());
    }
    int numCols=column_count(stmt);
    while(rc==SQLITE_ROW)
    {
        for(int i=0;i<numCols;i++)
        {
            column_text(stmt,i);
        }
        rc=step(stmt);
    }
    finalize(stmt);
    return("");
}

int Sql::open(string filename, sqlite3 **ppDb)
{
    return(sqlite3_open16(filename.data(),ppDb));
}

int Sql::prepare(sqlite3 *db, string zSql, sqlite3_stmt **ppStmt)
{
    return(sqlite3_prepare16_v2(db,zSql.data(),zSql.size()+1,ppStmt,0));
}

int Sql::step(sqlite3_stmt *pStmt)
{
    return(sqlite3_step(pStmt));
}

int Sql::finalize(sqlite3_stmt *pStmt)
{
    return(sqlite3_finalize(pStmt));
}

int Sql::close(sqlite3 *pDb)
{
    return(sqlite3_close(pDb));
}

int Sql::column_bytes(sqlite3_stmt *pStmt,int iCol)
{
    return(sqlite3_column_bytes16(pStmt,iCol));
}

int Sql::column_count(sqlite3_stmt *pStmt)
{
    return(sqlite3_column_count(pStmt));
}

string Sql::column_text(sqlite3_stmt *pStmt,int iCol)
{
    return(static_cast<char const *>(sqlite3_column_text16(pStmt, iCol)));
}

bool Sql::connect()
{
    if(dbSQLite==false)
    {
        int rc=open(database,&dbSQLite);
        if(rc!=SQLITE_OK)
        {
            close(dbSQLite);
            dbSQLite=NULL;
            return(false);
        }
    }
    return(true);
}

void Sql::disconnect()
{
    close(dbSQLite);
}
