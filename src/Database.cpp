#include "Database.h"
#include <iostream>

Database::Database(const std::string& dbFile) : db(nullptr), dbFileName(dbFile) 
{
    connect();
}

Database::~Database() 
{
    if (db) 
    {
        sqlite3_close(db);
    }
}

bool Database::connect() 
{
    if (sqlite3_open(dbFileName.c_str(), &db) == SQLITE_OK)
    {
        std::cout << "Database is open!" << std::endl;
        return true;
    }
    std::cerr << "Error is open base: " << sqlite3_errmsg(db) << std::endl;
    return false;
}

bool Database::execute(const std::string& query) {
    char* errMsg = nullptr;
    if (sqlite3_exec(db, query.c_str(), nullptr, nullptr, &errMsg) != SQLITE_OK) {
        std::cerr << "Ошибка выполнения запроса: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return false;
    }
    return true;
}


std::vector<Agent> Database::fetchAgents() 
{
    std::vector<Agent> agents;
    std::string sql = "SELECT * FROM agents;";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) 
    {
        while (sqlite3_step(stmt) == SQLITE_ROW) 
        {
            agents.push_back({
                sqlite3_column_int(stmt, 0),
                reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)),
                reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)),
                reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3))
            });
        }
        sqlite3_finalize(stmt);
    }
    else
        std::cerr << "Error request: " << sqlite3_errmsg(db) << std::endl;

    return agents;
}

/*
bool Database::addAgent(const std::string& name, const std::string& contract_number, const std::string& date)
{

}*/

bool Database::deleteAgentById(int id)
{
    std::string sql = "delete from agents where id = " + std::to_string(id) + ";";
    return execute(sql);
}

bool Database::updateAgent(int id, const std::string& name, const std::string& contract_number, const std::string& date)
{
    std::string sql = "update agents set name = '" + name +
        "', contract_number = '" + contract_number +
        "', date = '" + date +
        "' where id = " + std::to_string(id) + ";";
    return execute(sql);
}
