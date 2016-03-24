bin_PROGRAMS = dsl
dsl_SOURCES = main.c list.c list.h chess.c chess.h
#dsl_CFLAGS = -g -O1
#CFLAGS = -g -O1

check_SCRIPTS = greptest.sh
TESTS = $(check_SCRIPTS)

greptest.sh:
	echo './dsl | grep "Hello from .*dsl!"' > greptest.sh
	chmod +x greptest.sh
	
CLEANFILES = greptest.sh	 
