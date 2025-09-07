#include "database_access.h"

DatabaseAccess::DatabaseAccess(const std::string& connection_string) throw(std::runtime_error) {
    if (connection_string.empty()) {
        throw std::runtime_error("Invalid connection string");
    }
}

std::vector<std::string> DatabaseAccess::executeQuery(const std::string& sql) throw(std::runtime_error) {
    if (sql.empty()) {
        throw std::runtime_error("Empty SQL query");
    }
    // 実際のDB処理はモックで置き換えるため、仮実装
    std::vector<std::string> result;
    result.push_back("Result for: " + sql);
    return result;
}

void DatabaseAccess::commit() throw(std::runtime_error) {
    // 仮実装
}

void DatabaseAccess::rollback() throw(std::runtime_error) {
    // 仮実装
}

SearchService::SearchService(DatabaseAccess* db_access) : db_access_(db_access) {
    if (!db_access) {
        throw std::runtime_error("Null database access");
    }
}

std::vector<std::string> SearchService::search(const std::string& query) throw(std::runtime_error) {
    std::string sql = "SELECT * FROM table WHERE condition = '" + query + "'";
    return db_access_->executeQuery(sql);
}