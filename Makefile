#THIS IS ENTIRELY WRITTEN BY AI.

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g
LDFLAGS = 

# Directories
SRC_DIR = .
TEST_DIR = tests
STATIC_DIR = static

# Source files (excluding main.c, app.c, parser.c and test files)
SOURCES = server.c client.c request.c response.c routes.c file_utils.c
OBJECTS = $(SOURCES:.c=.o)

# Parser object (separate from main objects since parser.c has main)
PARSER_OBJ = parser.o

# Main applications
MAIN_APP = app
PARSER_APP = parser

# Test executables
TEST_EXECUTABLES = tests/test_file_utils tests/test_parser tests/test_response tests/test_routes tests/test_server

# Default target (just build main app since parser may not have main)
all: $(MAIN_APP)

# Build everything including parser (if it has main function)
all-with-parser: $(MAIN_APP) $(PARSER_APP)

# Main application (depends on all objects including parser.o)
$(MAIN_APP): $(OBJECTS) parser.o app.c
	$(CC) $(CFLAGS) -o $@ app.c $(OBJECTS) parser.o $(LDFLAGS)

# Parser application (only if parser.c has main function)
$(PARSER_APP): $(OBJECTS) parser.c
	@echo "Building parser executable..."
	@if grep -q "int main" parser.c; then \
		$(CC) $(CFLAGS) -o $@ parser.c $(OBJECTS) $(LDFLAGS); \
	else \
		echo "parser.c doesn't contain main function, skipping parser executable"; \
	fi

# Object files
%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< -o $@

# Special case for files without corresponding .h files
file_utils.o: file_utils.c file_utils.h
	$(CC) $(CFLAGS) -c $< -o $@

parser.o: parser.c parser.h
	$(CC) $(CFLAGS) -c $< -o $@

server.o: server.c server.h
	$(CC) $(CFLAGS) -c $< -o $@

client.o: client.c client.h
	$(CC) $(CFLAGS) -c $< -o $@

request.o: request.c request.h
	$(CC) $(CFLAGS) -c $< -o $@

response.o: response.c response.h
	$(CC) $(CFLAGS) -c $< -o $@

routes.o: routes.c routes.h
	$(CC) $(CFLAGS) -c $< -o $@

# Test targets
tests: $(TEST_EXECUTABLES)

tests/test_file_utils: tests/test_file_utils.c $(OBJECTS) parser.o
	$(CC) $(CFLAGS) -o $@ $< $(OBJECTS) parser.o $(LDFLAGS)

tests/test_parser: tests/test_parser.c $(OBJECTS) parser.o
	$(CC) $(CFLAGS) -o $@ $< $(OBJECTS) parser.o $(LDFLAGS)

tests/test_response: tests/test_response.c $(OBJECTS) parser.o
	$(CC) $(CFLAGS) -o $@ $< $(OBJECTS) parser.o $(LDFLAGS)

tests/test_routes: tests/test_routes.c $(OBJECTS) parser.o
	$(CC) $(CFLAGS) -o $@ $< $(OBJECTS) parser.o $(LDFLAGS)

tests/test_server: tests/test_server.c $(OBJECTS) parser.o
	$(CC) $(CFLAGS) -o $@ $< $(OBJECTS) parser.o $(LDFLAGS)

# Run all tests
run-tests: tests
	@echo "Running all tests..."
	@for test in $(TEST_EXECUTABLES); do \
		echo "Running $$test..."; \
		./$$test; \
		echo ""; \
	done

# Run individual tests
run-test-file-utils: tests/test_file_utils
	./tests/test_file_utils

run-test-parser: tests/test_parser
	./tests/test_parser

run-test-response: tests/test_response
	./tests/test_response

run-test-routes: tests/test_routes
	./tests/test_routes

run-test-server: tests/test_server
	./tests/test_server

# Clean targets
clean:
	rm -f $(OBJECTS)
	rm -f $(MAIN_APP) $(PARSER_APP)
	rm -f $(TEST_EXECUTABLES)

clean-objects:
	rm -f $(OBJECTS)

clean-tests:
	rm -f $(TEST_EXECUTABLES)

clean-all: clean
	rm -rf *.dSYM parser.dSYM

# Install/setup targets (optional)
install: $(MAIN_APP)
	@echo "Application built successfully"
	@echo "Static files are in $(STATIC_DIR)/"

# Development helpers
debug: CFLAGS += -DDEBUG -O0
debug: $(MAIN_APP)

release: CFLAGS += -O2 -DNDEBUG
release: clean $(MAIN_APP)

# Check for required files
check:
	@echo "Checking project structure..."
	@test -f config.h || echo "Warning: config.h not found"
	@test -d $(STATIC_DIR) || echo "Warning: static directory not found"
	@test -d $(TEST_DIR) || echo "Warning: tests directory not found"
	@echo "Structure check complete"

# Help target
help:
	@echo "Available targets:"
	@echo "  all               - Build main application only"
	@echo "  all-with-parser   - Build main application and parser"
	@echo "  app               - Build main application only"
	@echo "  parser            - Build parser application (if it has main)"
	@echo "  tests             - Build all test executables"
	@echo "  run-tests         - Build and run all tests"
	@echo "  run-test-*        - Run individual tests"
	@echo "  clean             - Remove object files and executables"
	@echo "  clean-objects     - Remove object files only"
	@echo "  clean-tests       - Remove test executables only"
	@echo "  clean-all         - Remove everything including debug symbols"
	@echo "  debug             - Build with debug flags"
	@echo "  release           - Build optimized release version"
	@echo "  check             - Check project structure"
	@echo "  install           - Build and setup application"
	@echo "  help              - Show this help message"

# Phony targets
.PHONY: all tests run-tests run-test-file-utils run-test-parser run-test-response run-test-routes run-test-server clean clean-objects clean-tests clean-all install debug release check help