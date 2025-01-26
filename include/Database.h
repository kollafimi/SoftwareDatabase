#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>
#include <string>
#include <vector>

struct Agent 
{
    int id;
    std::string name;
    std::string contract_number;
    std::string date;
};

class Database 
{
public:
    Database(const std::string& dbFile);
    ~Database();
    
    bool connect();
    bool execute(const std::string& query);
    std::vector<Agent> fetchAgents();
    bool addAgent(const std::string& name, const std::string& contract_number, const std::string& date);
    bool deleteAgentById(int id);
    bool updateAgent(int id, const std::string& name, const std::string& contract_number, const std::string& date);

private:
    sqlite3* db;
    std::string dbFileName;
};

#endif
