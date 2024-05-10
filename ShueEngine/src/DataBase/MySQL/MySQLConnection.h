#pragma once

#include "Core.h"

#include <stdlib.h>
#include <iostream>

#include "mysql_connection.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

namespace Shue {

	class SHUE_API MySQLConnection
	{
	public:
		static void MakeConnection(const sql::SQLString& hostName, const sql::SQLString& username,
			const sql::SQLString& password, const sql::SQLString& databaseName);
		static void ExecuteQuery(const sql::SQLString& queryStr);
		static void CloseConnection();
		
	private:
		inline static sql::Driver* s_Driver;
		inline static sql::Connection* s_Connection;
		inline static sql::Statement* s_Statement;
		inline static sql::ResultSet* s_ResultSet;
	};

}