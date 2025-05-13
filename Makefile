####################################### BEG_3 ####

# The name of the final program (the executable)
NAME        := text-analyse

#------------------------------------------------#
#   INGREDIENTS                                  #
#------------------------------------------------#

# Source directory — folder where .cpp files are stored
SRC_DIR     := src

# Object directory — folder where compiled .o files will be placed
OBJ_DIR     := obj

# List of source files (just the filenames initially)
SRCS        := \
    main.cpp          \
    file_loader.cpp	  \
	text_analyser.cpp \
	csv_analyser.cpp

# Prepend 'src/' to each filename so we get full paths like 'src/main.cpp'
# This transforms 'main.cpp' into 'src/main.cpp' (i.e., prepends the SRC_DIR)
SRCS        := $(SRCS:%=$(SRC_DIR)/%)

# Replace .cpp extensions with .o and 'src/' with 'obj/' to get object file paths
# Example: 'src/main.cpp' → 'obj/main.o'
OBJS        := $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

#------------------------------------------------#
#   COMPILER CONFIGURATION                       #
#------------------------------------------------#

# The compiler to use (G++)
CXX         := g++

# Compiler flags:
# -Wall: enable all basic warnings
# -Wextra: enable extra warnings (useful for debugging)
# -Werror: treat warnings as errors (forces code quality)
CXXFLAGS    := -Wall -Wextra -Werror

# Preprocessor flags:
# -I include: tells compiler to look in 'include/' for header files
CPPFLAGS    := -I include

#------------------------------------------------#
#   UTILITY COMMANDS                             #
#------------------------------------------------#

# Command to remove files (used in clean targets)
RM          := rm -f

# Make output is cleaner — doesn’t print unnecessary directory info
MAKEFLAGS   += --no-print-directory

# Helper to create parent directories as needed
# $(@D) = the directory part of the target file
DIR_DUP     = mkdir -p $(@D)

#------------------------------------------------#
#   BUILD TARGETS                                #
#------------------------------------------------#

# Default target — what gets built when you just run `make`
# In this case, it will create the final program $(NAME)
all: $(NAME)

# How to build the final program (the executable)
# Link all the .o object files into one executable
$(NAME): $(OBJS)
	# Compile and link object files into the final executable
	$(CXX) $(OBJS) -o $(NAME)
	@echo "CREATED $(NAME)"  # Print message once compiled

# How to build each object file from its corresponding .cpp file
# This ensures the obj/ directory exists, then compiles .cpp into .o
# Example: 'src/main.cpp' → 'obj/main.o'
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(DIR_DUP)  # Create necessary directories for the object file
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c -o $@ $<  # Compile .cpp to .o
	@echo "CREATED $@"  # Print message once object file is created

#------------------------------------------------#
#   CLEANUP TARGETS                              #
#------------------------------------------------#

# Removes only the object files (.o)
# It will delete the object files that were compiled
clean:
	$(RM) $(OBJS)

# Removes both object files and the final executable
fclean: clean
	$(RM) $(NAME)  # Delete the executable file

# Shortcut to fully clean and then rebuild everything from scratch
# This will run 'fclean' first and then build everything
re:
	$(MAKE) fclean
	$(MAKE) all

#------------------------------------------------#
#   SPECIAL FLAGS                                #
#------------------------------------------------#

# Marks targets that are not actual files (helps with special targets like 'all', 'clean')
.PHONY: all clean fclean re

# Suppresses command output in terminal (e.g. doesn't echo every `g++` command)
.SILENT:
