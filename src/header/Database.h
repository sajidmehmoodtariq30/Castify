#ifndef DATABASE_H
#define DATABASE_H

#include <windows.h>
#include <sqlext.h>
#include <sqltypes.h>
#include <sql.h>
#include <iostream>

class Database {
private:
    SQLHENV env;
    SQLHDBC dbc;
    SQLHSTMT stmt;
    bool connected;

public:
    Database();
    ~Database();
    
    bool connect(const std::string& dsn, const std::string& user, const std::string& password);
    void disconnect();
    bool executeQuery(const std::string& query);
    void displayError(SQLHANDLE handle, SQLSMALLINT type);
};

#endif // DATABASE_H
