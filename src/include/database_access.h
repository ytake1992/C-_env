#ifndef DATABASE_ACCESS_H
#define DATABASE_ACCESS_H

#include <string>
#include <vector>
#include <stdexcept>

class DatabaseAccess {
public:
    DatabaseAccess(const std::string& connection_string) throw(std::runtime_error);
    virtual ~DatabaseAccess() {}
    virtual std::vector<std::string> executeQuery(const std::string& sql) throw(std::runtime_error);
    virtual void commit() throw(std::runtime_error);
    virtual void rollback() throw(std::runtime_error);
};

class SearchService {
public:
    SearchService(DatabaseAccess* db_access);
    std::vector<std::string> search(const std::string& query) throw(std::runtime_error);
private:
    DatabaseAccess* db_access_;
};

#endif