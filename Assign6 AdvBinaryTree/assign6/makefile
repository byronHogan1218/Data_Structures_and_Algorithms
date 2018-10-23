#
# PROGRAM:    Assignment6
# PROGRAMMER: Byron Hogan
# LOGON ID:   Z1825194
# DATE DUE:   3-23-18
#

# Compiler variables
CCFLAGS = -Wall
ASSIGNNAME = assignment6

# Rule to link object code files to create executable file
$(ASSIGNNAME).exe: $(ASSIGNNAME).o $(ASSIGNNAME)main.o assignment5.o
	g++ $(CCFLAGS) -o $(ASSIGNNAME).exe $(ASSIGNNAME).o $(ASSIGNNAME)main.o assignment5.o

# Rules to compile source code file to object code
$(ASSIGNNAME)main.o: $(ASSIGNNAME)main.cc $(ASSIGNNAME).h assignment5.h
	g++ $(CCFLAGS) -c $(ASSIGNNAME)main.cc

assignment5.o: assignment5.cc assignment5.h
	g++ $(CCFLAGS) -c assignment5.cc

$(ASSIGNNAME).o: $(ASSIGNNAME).cc $(ASSIGNNAME).h assignment5.h
	g++ $(CCFLAGS) -c $(ASSIGNNAME).cc

# Pseudo-target to remove object code and executable files
clean:
	-rm *.o $(ASSIGNNAME).exe
