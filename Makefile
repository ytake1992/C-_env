CC = g++
CFLAGS = -std=c++98 -I./src/include
GTEST_FLAGS = -I/usr/local/include -L/usr/local/lib -lgmock -lgmock_main -lgtest -lgtest_main -pthread
SRC_DIR = src/main
INCLUDE_DIR = src/include
TEST_DIR = tests
BIN_DIR = bin
TEST_BIN_DIR = $(BIN_DIR)/tests
ANALYSIS_DIR = analysis
HTML_REPORT_DIR = $(ANALYSIS_DIR)/html
SOURCES = $(wildcard $(SRC_DIR)/*.cc)
HEADERS = $(wildcard $(INCLUDE_DIR)/*.h)
TEST_SOURCES = $(wildcard $(TEST_DIR)/*.cc)
TEST_BINS = $(patsubst $(TEST_DIR)/%.cc, $(TEST_BIN_DIR)/%, $(TEST_SOURCES))
CPPCHECK_XML = $(ANALYSIS_DIR)/cppcheck.xml

# デバッグ用
$(info SRC_DIR: $(SRC_DIR))
$(info Sources: $(SOURCES))
$(info INCLUDE_DIR: $(INCLUDE_DIR))
$(info Headers: $(HEADERS))
$(info TEST_DIR: $(TEST_DIR))
$(info Test Sources: $(TEST_SOURCES))
$(info Test Bins: $(TEST_BINS))

all: main test analysis

main: $(SOURCES) $(HEA DERS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $(BIN_DIR)/main $(SOURCES)

test: $(TEST_BINS)

$(TEST_BINS): $(TEST_BIN_DIR)/%: $(TEST_SOURCES) $(SOURCES) $(HEADERS)
	@mkdir -p $(TEST_BIN_DIR)
	$(CC) $(CFLAGS) $(GTEST_FLAGS) -o $@ $< $(filter-out $(SRC_DIR)/main.cc, $(SOURCES))

$(CPPCHECK_XML): $(SOURCES) $(HEADERS)
	@mkdir -p $(ANALYSIS_DIR)
	cppcheck --enable=all --std=c++03 --xml -I $(INCLUDE_DIR) $(SRC_DIR) $(INCLUDE_DIR) 2> $(CPPCHECK_XML)

analysis: $(CPPCHECK_XML)
	@mkdir -p $(HTML_REPORT_DIR)
	cppcheck-htmlreport --file=$(CPPCHECK_XML) --report-dir=$(HTML_REPORT_DIR) --source-dir=.

clean:
	rm -rf $(BIN_DIR) $(HTML_REPORT_DIR) $(CPPCHECK_XML)