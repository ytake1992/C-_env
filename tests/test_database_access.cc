#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "database_access.h"

// Google Mockを使ったモッククラス
class MockDatabaseAccess : public DatabaseAccess {
public:
    MockDatabaseAccess(const std::string& connection_string) : DatabaseAccess(connection_string) {}
    // C++98ではMOCK_METHODマクロを使用（引数と戻り値を明示）
    MOCK_METHOD1(executeQuery, std::vector<std::string>(const std::string&));
    MOCK_METHOD0(commit, void());
    MOCK_METHOD0(rollback, void());
};

// DatabaseAccessのテストフィクスチャ
class DatabaseAccessTest : public ::testing::Test {
protected:
    void SetUp() {
        db_access_ = new MockDatabaseAccess("valid_connection");
    }
    void TearDown() {
        delete db_access_;
    }
    MockDatabaseAccess* db_access_;
};

// SearchServiceのテストフィクスチャ
class SearchServiceTest : public ::testing::Test {
protected:
    void SetUp() {
        db_access_ = new MockDatabaseAccess("valid_connection");
        search_service_ = new SearchService(db_access_);
    }
    void TearDown() {
        delete search_service_;
        delete db_access_;
    }
    MockDatabaseAccess* db_access_;
    SearchService* search_service_;
};

// DatabaseAccessのテストケース
TEST_F(DatabaseAccessTest, ConstructorThrowsOnEmptyConnectionString) {
    EXPECT_THROW(DatabaseAccess(""), std::runtime_error);
}

TEST_F(DatabaseAccessTest, ExecuteQueryReturnsExpectedResult) {
    // モックの期待値を設定
    std::vector<std::string> expected_result;
    expected_result.push_back("test_result");
    
    EXPECT_CALL(*db_access_, executeQuery("SELECT * FROM table"))
        .Times(1)
        .WillOnce(::testing::Return(expected_result));

    // テスト実行
    std::vector<std::string> result = db_access_->executeQuery("SELECT * FROM table");
    EXPECT_EQ(1U, result.size());
    EXPECT_EQ("test_result", result[0]);
}

TEST_F(DatabaseAccessTest, ExecuteQueryThrowsOnFailure) {
    // モックで例外をスローするように設定
    EXPECT_CALL(*db_access_, executeQuery("SELECT * FROM table"))
        .Times(1)
        .WillOnce(::testing::Throw(std::runtime_error("Query failed")));

    // 例外がスローされることを検証
    EXPECT_THROW(db_access_->executeQuery("SELECT * FROM table"), std::runtime_error);
}

TEST_F(DatabaseAccessTest, CommitSuccess) {
    // commitが1回呼ばれることを期待
    EXPECT_CALL(*db_access_, commit())
        .Times(1);

    // テスト実行
    db_access_->commit();
}

TEST_F(DatabaseAccessTest, CommitThrowsOnFailure) {
    // commitで例外をスローするように設定
    EXPECT_CALL(*db_access_, commit())
        .Times(1)
        .WillOnce(::testing::Throw(std::runtime_error("Commit failed")));

    // 例外がスローされることを検証
    EXPECT_THROW(db_access_->commit(), std::runtime_error);
}

TEST_F(DatabaseAccessTest, RollbackSuccess) {
    // rollbackが1回呼ばれることを期待
    EXPECT_CALL(*db_access_, rollback())
        .Times(1);

    // テスト実行
    db_access_->rollback();
}

// SearchServiceのテストケース
TEST_F(SearchServiceTest, ConstructorThrowsOnNullDatabaseAccess) {
    EXPECT_THROW(SearchService(0), std::runtime_error);
}

TEST_F(SearchServiceTest, SearchReturnsExpectedResult) {
    // モックの期待値を設定
    std::vector<std::string> expected_result;
    expected_result.push_back("search_result");
    
    EXPECT_CALL(*db_access_, executeQuery("SELECT * FROM table WHERE condition = 'test_query'"))
        .Times(1)
        .WillOnce(::testing::Return(expected_result));

    // テスト実行
    std::vector<std::string> result = search_service_->search("test_query");
    EXPECT_EQ(1U, result.size());
    EXPECT_EQ("search_result", result[0]);
}

TEST_F(SearchServiceTest, SearchThrowsOnQueryFailure) {
    // モックで例外をスローするように設定
    EXPECT_CALL(*db_access_, executeQuery("SELECT * FROM table WHERE condition = 'test_query'"))
        .Times(1)
        .WillOnce(::testing::Throw(std::runtime_error("Query failed")));

    // 例外がスローされることを検証
    EXPECT_THROW(search_service_->search("test_query"), std::runtime_error);
}