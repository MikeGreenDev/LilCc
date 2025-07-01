BUILD_DIR := .
OBJ_DIR := obj

LOCATION := .
ASSEMBLY := testbed
EXTENSION := 
COMPILER_FLAGS := -g -MD -Werror=vla -fdeclspec -fPIC
INCLUDE_FLAGS :=
LINKER_FLAGS := -L./$(BUILD_DIR)/ -Wl,-rpath,.
DEFINES := -D_DEBUG

# Uses wildcarding. Gotta be carefull with it but it works 99% of the time
SRC_FILES := $(shell find $(LOCATION) -name *.c)		# .c files
DIRECTORIES := $(shell find $(LOCATION) -type d)		# directories with .h files
OBJ_FILES := $(SRC_FILES:%=$(OBJ_DIR)/%.o)		# compiled .o objects

all: scaffold compile link

.PHONY: scaffold
scaffold: # create build directory
	@echo Scaffolding folder structure...
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(addprefix $(OBJ_DIR)/,$(DIRECTORIES))
	@echo Done.

.PHONY: link
link: scaffold $(OBJ_FILES) # link
	@echo Linking $(ASSEMBLY)...
	clang $(OBJ_FILES) -o $(BUILD_DIR)/$(ASSEMBLY)$(EXTENSION) $(LINKER_FLAGS)

.PHONY: compile
compile: #compile .c files
	@echo Compiling...

.PHONY: clean
clean: # clean build directory
	rm -rf $(BUILD_DIR)/$(ASSEMBLY)
	rm -rf $(OBJ_DIR)/$(ASSEMBLY)

$(OBJ_DIR)/%.c.o: %.c # compile .c to .o object
	@echo   $<...
	@clang $< $(COMPILER_FLAGS) -c -o $@ $(DEFINES) $(INCLUDE_FLAGS)

-include $(OBJ_FILES:.o=.d)

