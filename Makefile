PROJECT_ROOT = .
USER_DIR = .
GTEST_LIB_DIR = $(PROJECT_ROOT)/libs
PROJECT_HEADER_DIR = $(PROJECT_ROOT)/include

# CPPFLAGS += -isystem $(GTEST_DIR)/include
CPPFLAGS += -I$(PROJECT_HEADER_DIR)
CXXFLAGS += -g -Wall -Wextra -pthread
TESTS = test
CLEANS = $(TESTS) *.o

GTEST_HEADERS = $(PROJECT_HEADER_DIR)/*.h \
                $(PROJECT_HEADER_DIR)/internal/*.h
all : $(TESTS)
clean :
	rm -f $(CLEANS)

simple.o : $(USER_DIR)/simple.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $<

test : simple.o test.o 
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $(GTEST_LIB_DIR)/libgtest.a $^ -o $@
