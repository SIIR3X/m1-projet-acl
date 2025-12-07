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

# Cpp
CPP_BUILD_DIR = $(BUILD_DIR)/cpp
CPP_DIR       = code/cpp
CPP_DOC_DIR   = docs/cpp/code

# Java
JAVA_SRC_DIR    = code/java/src
JAVA_TEST_DIR   = code/java/tests
JAVA_LIB 	 	= code/java/lib
JAVA_BUILD_DIR  = build/java
JAVA_MAIN       = Main
JAVA_DOC_DIR    = docs/java/code
JUNIT_JAR       = $(JAVA_LIB)/junit-platform-console-standalone-1.10.1.jar
JAVA_FORMAT 	= $(JAVA_LIB)/google-java-format-1.20.0-all-deps.jar

# Commandes génériques
CMAKE    = cmake
MAKE_CMD = $(MAKE)
DOXYGEN  = doxygen
CTEST    = ctest


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
	@find $(JAVA_SRC_DIR) -name "*.java" > $(JAVA_BUILD_DIR)/sources_main.txt
	@find $(JAVA_TEST_DIR) -name "*.java" >> $(JAVA_BUILD_DIR)/sources_main.txt
	@javac -cp "$(JUNIT_JAR):$(JAVA_BUILD_DIR)" -d $(JAVA_BUILD_DIR) @$(JAVA_BUILD_DIR)/sources_main.txt

run-java:
	@mkdir -p $(JAVA_BUILD_DIR)
	@find $(JAVA_SRC_DIR) -name "*.java" > $(JAVA_BUILD_DIR)/sources_run.txt
	@javac -d $(JAVA_BUILD_DIR) @$(JAVA_BUILD_DIR)/sources_run.txt
	@java -cp $(JAVA_BUILD_DIR) Main

run-tests-java: build-java
	@java -jar $(JUNIT_JAR) \
		--class-path $(JAVA_BUILD_DIR) \
		--scan-class-path

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
