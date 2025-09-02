CC = g++
CFLAGS = -std=c++98 -I./src/include
COV_FLAGS = -fprofile-arcs -ftest-coverage
GTEST_FLAGS = -I/usr/local/include -L/usr/local/lib -lgmock -lgmock_main -lgtest -lgtest_main -pthread
SRC_DIR = src/main
INCLUDE_DIR = src/include
TEST_DIR = tests
BIN_DIR = bin
OBJ_DIR = obj
TEST_BIN_DIR = $(BIN_DIR)/tests
ANALYSIS_DIR = analysis
HTML_REPORT_DIR = $(ANALYSIS_DIR)/html
SOURCES = $(wildcard $(SRC_DIR)/*.cc)
HEADERS = $(wildcard $(INCLUDE_DIR)/*.h)
TEST_SOURCES = $(wildcard $(TEST_DIR)/*.cc)
OBJECTS = $(patsubst $(SRC_DIR)/%.cc, $(OBJ_DIR)/%.o, $(SOURCES))
TEST_OBJECTS = $(filter-out $(OBJ_DIR)/main.o, $(OBJECTS))
TEST_BINS = $(patsubst $(TEST_DIR)/%.cc, $(TEST_BIN_DIR)/%, $(TEST_SOURCES))
CPPCHECK_XML = $(ANALYSIS_DIR)/cppcheck.xml
COVERAGE_INFO = $(ANALYSIS_DIR)/coverage.info
COVERAGE_DIR = $(ANALYSIS_DIR)/coverage
COVERAGE_RAW = $(ANALYSIS_DIR)/raw_coverage.info

# デバッグ用
$(info SRC_DIR: $(SRC_DIR))
$(info Sources: $(SOURCES))
$(info INCLUDE_DIR: $(INCLUDE_DIR))
$(info Headers: $(HEADERS))
$(info TEST_DIR: $(TEST_DIR))
$(info Test Sources: $(TEST_SOURCES))
$(info Test Bins: $(TEST_BINS))

all: main test analysis

main: $(OBJECTS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $(BIN_DIR)/main $(OBJECTS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cc $(HEADERS)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(COV_FLAGS) -c $< -o $@

test: $(TEST_BINS)
	@echo "Running tests..."
	@$(foreach bin,$(TEST_BINS),$(bin) &&) true
	@echo "All tests completed."

$(TEST_BINS): $(TEST_BIN_DIR)/%: $(TEST_DIR)/%.cc $(TEST_OBJECTS) $(HEADERS)
	@mkdir -p $(TEST_BIN_DIR)
	$(CC) $(CFLAGS) $(COV_FLAGS) $(GTEST_FLAGS) -o $@ $< $(TEST_OBJECTS)

coverage: $(TEST_BINS)
	@mkdir -p $(COVERAGE_DIR) $(ANALYSIS_DIR)/temp_coverage
    # カウンタをリセット
	lcov --zerocounters --directory .
    # テストごとにカバレッジを収集
	$(foreach bin,$(TEST_BINS), \
		rm -f $(OBJ_DIR)/*.gcda $(SRC_DIR)/*.gcda; \
		$(bin) || { echo "Test $(bin) failed"; exit 1; }; \
		lcov --capture --directory . --output-file $(ANALYSIS_DIR)/temp_coverage/$(notdir $(bin)).info || { echo "lcov capture failed for $(bin)"; exit 1; }; \
	)
    # カバレッジデータをマージ
	@if ls $(ANALYSIS_DIR)/temp_coverage/*.info >/dev/null 2>&1; then \
		lcov $(foreach info,$(wildcard $(ANALYSIS_DIR)/temp_coverage/*.info),--add-tracefile $(info)) --output-file $(COVERAGE_RAW) || { echo "lcov merge failed"; exit 1; }; \
	else \
		echo "No coverage data files found in $(ANALYSIS_DIR)/temp_coverage"; exit 1; \
	fi
    # テストコードとシステムファイルを除外
	lcov --remove $(COVERAGE_RAW) '$(TEST_DIR)/*' '/usr/*' -o $(COVERAGE_INFO) || { echo "lcov remove failed"; exit 1; }
    # HTMLレポート生成
	genhtml $(COVERAGE_INFO) --output-directory $(COVERAGE_DIR) || { echo "genhtml failed"; exit 1; }
	@echo "Coverage report generated at $(COVERAGE_DIR)/index.html"

$(CPPCHECK_XML): $(SOURCES) $(HEADERS)
	@mkdir -p $(ANALYSIS_DIR)
	cppcheck --enable=all --std=c++03 --xml -I $(INCLUDE_DIR) $(SRC_DIR) $(INCLUDE_DIR) 2> $(CPPCHECK_XML)

analysis: $(CPPCHECK_XML)
	@mkdir -p $(HTML_REPORT_DIR)
	cppcheck-htmlreport --file=$(CPPCHECK_XML) --report-dir=$(HTML_REPORT_DIR) --source-dir=.

clean:
	rm -rf $(BIN_DIR) $(OBJ_DIR) $(HTML_REPORT_DIR) $(COVERAGE_DIR) $(CPPCHECK_XML) $(COVERAGE_INFO) $(COVERAGE_RAW) *.gcno *.gcda