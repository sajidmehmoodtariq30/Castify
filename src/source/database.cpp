#include "../header/Database.h"

Database::Database()
{
    connected = false;

    // Allocate the environment handle
    if (SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &env) == SQL_SUCCESS)
    {
        SQLSetEnvAttr(env, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0);
    }
    else
    {
        std::cerr << "Error allocating SQL environment." << std::endl;
    }
}

Database::~Database()
{
    disconnect();
    SQLFreeHandle(SQL_HANDLE_ENV, env);
}

bool Database::connect(const std::string &dsn, const std::string &user, const std::string &password)
{
    if (SQLAllocHandle(SQL_HANDLE_DBC, env, &dbc) != SQL_SUCCESS)
    {
        std::cerr << "Error allocating database connection handle." << std::endl;
        return false;
    }

    // Convert std::string to SQLCHAR*
    SQLCHAR connStr[1024];
    snprintf((char *)connStr, sizeof(connStr), "DSN=%s;UID=%s;PWD=%s;", dsn.c_str(), user.c_str(), password.c_str());

    // Connect to the database
    if (SQLDriverConnect(dbc, NULL, connStr, SQL_NTS, NULL, 0, NULL, SQL_DRIVER_COMPLETE) == SQL_SUCCESS)
    {
        std::cout << "Connected to the database successfully!" << std::endl;
        connected = true;
        return true;
    }
    else
    {
        displayError(dbc, SQL_HANDLE_DBC);
        return false;
    }
}

void Database::disconnect()
{
    if (connected)
    {
        SQLDisconnect(dbc);
        SQLFreeHandle(SQL_HANDLE_DBC, dbc);
        connected = false;
        std::cout << "Disconnected from the database." << std::endl;
    }
}

bool Database::executeQuery(const std::string &query)
{
    if (!connected)
    {
        std::cerr << "Database is not connected." << std::endl;
        return false;
    }

    if (SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt) != SQL_SUCCESS)
    {
        std::cerr << "Error allocating SQL statement handle." << std::endl;
        return false;
    }

    if (SQLExecDirect(stmt, (SQLCHAR *)query.c_str(), SQL_NTS) == SQL_SUCCESS)
    {
        std::cout << "Query executed successfully!" << std::endl;
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        return true;
    }
    else
    {
        displayError(stmt, SQL_HANDLE_STMT);
        return false;
    }
}

void Database::displayError(SQLHANDLE handle, SQLSMALLINT type)
{
    SQLCHAR sqlState[6], message[256];
    SQLINTEGER nativeError;
    SQLSMALLINT messageLen;

    if (SQLGetDiagRec(type, handle, 1, sqlState, &nativeError, message, sizeof(message), &messageLen) == SQL_SUCCESS)
    {
        std::cerr << "SQL Error: " << message << " (SQL State: " << sqlState << ")" << std::endl;
    }
}
