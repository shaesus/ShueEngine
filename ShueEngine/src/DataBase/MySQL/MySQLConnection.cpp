#include "MySQLConnection.h"

#include <iomanip>

namespace Shue {

    const char separator = ' ';
    const int width = 12;

    void MySQLConnection::MakeConnection(const sql::SQLString& hostName, const sql::SQLString& username, 
        const sql::SQLString& password, const sql::SQLString& databaseName)
    {
        try 
        {
            s_Driver = get_driver_instance();
            s_Connection = s_Driver->connect(hostName, username, password);
            s_Connection->setSchema(databaseName);
        }
        catch (sql::SQLException& e) 
        {
        }
    }

    void MySQLConnection::ExecuteQuery(const sql::SQLString& queryStr)
    {
        try
        {
            s_Statement = s_Connection->createStatement();
            s_ResultSet = s_Statement->executeQuery(queryStr);
            sql::ResultSetMetaData* rsMetaData = s_ResultSet->getMetaData();

            int columnCount = rsMetaData->getColumnCount();
            for (int i = 0; i < columnCount; i++)
                std::cout << std::left << std::setw(width) << std::setfill(separator) << rsMetaData->getColumnName(i + 1) << ' ';
            std::cout << '\n';

            while (s_ResultSet->next())
            {
                for (int i = 0; i < columnCount; i++)
                    std::cout << std::left << std::setw(width) << std::setfill(separator) << s_ResultSet->getString(i + 1) << ' ';
                std::cout << '\n';
            }
            std::cout << '\n';
        }
        catch (sql::SQLException& e)
        {
        }
    }

    void MySQLConnection::CloseConnection()
    {
        delete s_ResultSet;
        delete s_Statement;
        delete s_Connection;
    }

}