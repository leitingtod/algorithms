VPATH = @srcdir@

bin_PROGRAMS = dsl
dsl_SOURCES = main.c

check_SCRIPTS = greptest.sh
TESTS = $(check_SCRIPTS)
greptest.sh:
	echo './dsl | grep "Hello from .*dsl!"' > greptest.sh
	chmod +x greptest.sh
	
CLEANFILES = greptest.sh	 
