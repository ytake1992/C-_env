#include <string>
#include <vector>

#include "database_searcher.h"
#include "data.h"
#include "judge.h"
class DecisionMaker {
public:
    DecisionMaker(DatabaseSearcher* searcher) : searcher_(searcher), judge_(new Judge()) {}
    ~DecisionMaker() { delete judge_; } // C++98 では手動解放
    bool makeDecision(const std::string& query);
private:
    DatabaseSearcher* searcher_;
    Judge* judge_; // 動的に作成
};