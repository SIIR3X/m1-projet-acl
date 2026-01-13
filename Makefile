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
JAVA_BUILD_DIR  = build/java
JAVA_MAIN       = run.Main
JAVA_JAR        = $(BUILD_DIR)/programme-java.jar

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
	@$(CPP_BUILD_DIR)/programme-cpp

run-cpp-mem: build-cpp
	@valgrind --leak-check=full --show-leak-kinds=all $(CPP_BUILD_DIR)/programme-cpp

run-tests-cpp: build-cpp
	@cd $(CPP_BUILD_DIR) && $(CTEST) --output-on-failure

run-tests-cpp-mem: build-cpp
	@cd $(CPP_BUILD_DIR) && valgrind --leak-check=full --show-leak-kinds=all ./tests

doc-cpp:
	@cd $(CPP_DIR) && $(DOXYGEN) Doxyfile


###############################################################################
##################################### Java ####################################
###############################################################################

JAVA_SOURCES := $(shell find $(JAVA_SRC_DIR) -name "*.java")

build-java:
	@mkdir -p $(JAVA_BUILD_DIR)
	@javac -d $(JAVA_BUILD_DIR) $(JAVA_SOURCES)

run-java: build-java
	@java -cp $(JAVA_BUILD_DIR) $(JAVA_MAIN)

build-jar: build-java
	@mkdir -p $(BUILD_DIR)
	@jar cfe $(JAVA_JAR) $(JAVA_MAIN) -C $(JAVA_BUILD_DIR) .


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
