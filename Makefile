BUILD_DIR := ./
OBJ_DIR := obj

LOCATION := src
ASSEMBLY := testbed
# EXTENSION := .so
EXTENSION :=
COMPILER_FLAGS := -g -MD -Werror=vla -fPIC -fdeclspec
INCLUDE_FLAGS := 
# LINKER_FLAGS := -g -shared -lvulkan -lX11 -lX11-xcb -lxcb -lxkbcommon -L$(VULKAN_SDK)/lib -L/usr/X11R6/lib -lm
LINKER_FLAGS := -g
DEFINES := -D_DEBUG

SRC_FILES := $(shell find $(LOCATION) -name *.c)		# .c files
DIRECTORIES := $(shell find $(LOCATION) -type d)		# directories with .h files
OBJ_FILES := $(SRC_FILES:%=$(OBJ_DIR)/%.o)		# compiled .o objects

# On linux I need to use a command called bear to compile the compile_commands.json
# This let's me use bear without interferring with anyone else's compile commands
# Note: make prefix="bear --append -- "
PREFIX := $(prefix)

all: build

.PHONY: build
build: scaffold compile link

.PHONY: scaffold
scaffold: # create build directory
	@echo Scaffolding folder structure...
	@mkdir -p $(BUILD_DIR)/
	@mkdir -p $(addprefix $(OBJ_DIR)/,$(DIRECTORIES))
	@echo Done.

.PHONY: link
link: scaffold $(OBJ_FILES) # link
	@clang $(OBJ_FILES) -o $(BUILD_DIR)/$(ASSEMBLY)$(EXTENSION) $(LINKER_FLAGS) -v

.PHONY: compile
compile: #compile .c files
	@echo Compiling...

.PHONY: test
test: testbed tests/runtests
	(cd tests; chmod +x runtests; ./runtests)

.PHONY: clean
clean: # clean build directory
	rm -rf $(BUILD_DIR)/$(ASSEMBLY)
	rm -rf $(OBJ_DIR)/$(ASSEMBLY)
	rm -rf $(BUILD_DIR)/$(ASSEMBLY)$(EXTENSION)
	rm -rf compile_commands.json

$(OBJ_DIR)/%.c.o: %.c # compile .c to .o object
	@echo   $<...
	@$(PREFIX) clang $< $(COMPILER_FLAGS) -c -o $@ $(DEFINES) $(INCLUDE_FLAGS)

-include $(OBJ_FILES:.o=.d)

