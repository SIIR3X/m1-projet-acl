###############################################################################
#                                                                             #
#   Makefile                                                                  #
#                                                                             #
#   Projet ACL                                                                #
#                                                                             #
###############################################################################


###############################################################################
################################ CONFIGURATION ################################
###############################################################################

# Dossiers
BUILD_DIR     = build

# C
CC          = gcc
C_STD       = -std=c17
C_WARN      = -Wall -Wextra -Wpedantic
C_OPT       = -O2
C_INC       = -I$(C_DIR)
C_BUILD_DIR = $(BUILD_DIR)/c
C_TARGET    = programme-c

# Cpp
CPP_BUILD_DIR = $(BUILD_DIR)/cpp
CPP_DIR       = code/cpp
CPP_DOC_DIR   = docs/cpp/code

# Java
JAVA_SRC_DIR    = code/java/src
JAVA_TEST_DIR   = code/java/src/test
JAVA_LIB 	 	= code/java/lib
JAVA_BUILD_DIR  = build/java
JAVA_MAIN       = run/Main
JAVA_DOC_DIR    = docs/java/code
JUNIT_JAR       = $(JAVA_LIB)/junit-platform-console-standalone-1.10.1.jar
JAVA_FORMAT 	= $(JAVA_LIB)/google-java-format-1.20.0-all-deps.jar

# Commandes génériques
CMAKE    = cmake
MAKE_CMD = $(MAKE)
DOXYGEN  = doxygen
CTEST    = ctest


###############################################################################
###################################### C ######################################
###############################################################################

C_SOURCES := $(shell find $(C_DIR) -name "*.c")
C_OBJECTS := $(patsubst $(C_DIR)/%.c,$(C_BUILD_DIR)/%.o,$(C_SOURCES))

build-c: $(C_BUILD_DIR)/$(C_TARGET)

$(C_BUILD_DIR)/$(C_TARGET): $(C_OBJECTS)
	@mkdir -p $(C_BUILD_DIR)
	@$(CC) $(C_STD) $(C_WARN) $(C_OPT) $^ -o $@

$(C_BUILD_DIR)/%.o: $(C_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(C_STD) $(C_WARN) $(C_OPT) $(C_INC) -c $< -o $@

run-c: build-c
	@$(C_BUILD_DIR)/$(C_TARGET) 2 10


###############################################################################
##################################### C++ #####################################
###############################################################################

build-cpp:
	@mkdir -p $(CPP_BUILD_DIR)
	@cd $(CPP_BUILD_DIR) && $(CMAKE) ../../$(CPP_DIR) && $(CMAKE) --build .

run-cpp: build-cpp
	@$(CPP_BUILD_DIR)/projet-acl

run-cpp-mem: build-cpp
	@valgrind --leak-check=full --show-leak-kinds=all $(CPP_BUILD_DIR)/projet-acl

run-tests-cpp: build-cpp
	@cd $(CPP_BUILD_DIR) && $(CTEST) --output-on-failure

run-tests-cpp-mem: build-cpp
	@cd $(CPP_BUILD_DIR) && valgrind --leak-check=full --show-leak-kinds=all ./tests

doc-cpp:
	@cd $(CPP_DIR) && $(DOXYGEN) Doxyfile


###############################################################################
##################################### Java ####################################
###############################################################################

build-java:
	@mkdir -p $(JAVA_BUILD_DIR)
	@find $(JAVA_SRC_DIR) -name "*.java" \
		-not -path "*/test/*" \
		-not -path "*/tests/*" \
		> $(JAVA_BUILD_DIR)/sources.txt
	@javac -d $(JAVA_BUILD_DIR) @$(JAVA_BUILD_DIR)/sources.txt

run-java: build-java
	@java -cp $(JAVA_BUILD_DIR) $(JAVA_MAIN)

build-java-all:
	@mkdir -p $(JAVA_BUILD_DIR)
	@find $(JAVA_SRC_DIR) -name "*.java" > $(JAVA_BUILD_DIR)/sources_all.txt
	@javac -d $(JAVA_BUILD_DIR) @$(JAVA_BUILD_DIR)/sources_all.txt

# usage: make run-test-java TEST=test.TestRequestBuilder
run-test-java: build-java-all
	@java -cp $(JAVA_BUILD_DIR) $(TEST)

doc-java:
	@mkdir -p $(JAVA_DOC_DIR)
	@javadoc -d $(JAVA_DOC_DIR) $(shell find $(JAVA_SRC_DIR) -name "*.java")


###############################################################################
################################## FORMATTERS #################################
###############################################################################

format-cpp:
	@clang-format -i $(shell find $(CPP_DIR) -name "*.cpp" -o -name "*.h")

format-java:
	@java -jar $(JAVA_FORMAT) --replace $(shell find $(JAVA_SRC_DIR) -name "*.java" -o -name "*.java")


###############################################################################
################################## NETTOYAGE ##################################
###############################################################################

clean:
	@rm -rf $(BUILD_DIR)

clean-doc:
	rm -rf $(CPP_DOC_DIR) $(JAVA_BUILD_DIR) 

clean-all: clean clean-doc
