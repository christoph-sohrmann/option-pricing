CC=g++
LIB=-lexpat
INCLUDE=-I../include

xml: XMLTest.o
	${CC} -o XMLTest XMLTest.o ${LIB}

test:
	${CC} -o testrun ../src/testrun.c ${INCLUDE} ${LIB}
	
clean:
	rm -f *.o *.trace core *~ fort.* diag *.T *.lst

%.o: ../src/%.cpp
	${CC} ${INCLUDE} -c $<

#
#  Default command.
#
.DEFAULT:
	@$(ECHO) "Unknown target $@"
	@$(ECHO) "Available targets are: diag, clean"
#
