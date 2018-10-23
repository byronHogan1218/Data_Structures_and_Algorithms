#
# PROGRAM:    Assignment2
# PROGRAMMER: Byron Hogan
# LOGON ID:   Z1825194
# DATE DUE:   2-09-18
#

# Compiler variables
CCFLAGS = -Wall
ASSIGNNAME = assignment3

# Rule to link object code files to create executable file
$(ASSIGNNAME).exe: $(ASSIGNNAME).o
	g++ $(CCFLAGS) -o $(ASSIGNNAME).exe $(ASSIGNNAME).o

# Rules to compile source code file to object code
$(ASSIGNNAME).o: $(ASSIGNNAME).cc
	g++ $(CCFLAGS) -c $(ASSIGNNAME).cc

# Pseudo-target to remove object code and executable files
clean:
	-rm *.o $(ASSIGNNAME).exe
