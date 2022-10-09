GENERATES = prog prog-a prog-so test
TRASH = *.o *~ o.* *.so test *.a prog prog-a prog-so *-test.txt

# Can't compile liboutput.so without this flag (caused by const.o)
CFLAGS = -fPIC

# Test parameters
SINGLEPARAM = hello-world!
THREEPARAMS = first-param second-param third-param

all:	prog prog-a prog-so test

prog:	const.o fun.o prog.o
		cc $^ -o $@

prog-a:	prog.o liboutput_static.a
		cc -L. prog.o -loutput_static -o $@

# Don't forget about LD_LIBRARY_PATH=`pwd`
prog-so:	prog.o liboutput.so
			cc -L. prog.o -loutput -o $@

fun.o:	outlib.h

liboutput_static.a:	fun.o const.o
					ar -rcs $@ $^

liboutput.so:	fun.o const.o
				cc -shared $^ -o $@

test-basic-binary:	prog
					./$^ 1> out-basic-test.txt 2> err-basic-test.txt
					./$^ 1>> out-basic-test.txt 2>> err-basic-test.txt $(SINGLEPARAM)
					./$^ 1>> out-basic-test.txt 2>> err-basic-test.txt $(THREEPARAMS)

test-a:	prog-a
		./$^ 1> out-a-test.txt 2> err-a-test.txt
		./$^ 1>> out-a-test.txt 2>> err-a-test.txt $(SINGLEPARAM)
		./$^ 1>> out-a-test.txt 2>> err-a-test.txt $(THREEPARAMS)
		sed 's/prog-a/prog/g' err-a-test.txt > mod-err-a-test.txt

test-so:	prog-so
			LD_LIBRARY_PATH=`pwd` ./$^ 1> out-so-test.txt 2> err-so-test.txt
			LD_LIBRARY_PATH=`pwd` ./$^ 1>> out-so-test.txt 2>> err-so-test.txt $(SINGLEPARAM)
			LD_LIBRARY_PATH=`pwd` ./$^ 1>> out-so-test.txt 2>> err-so-test.txt $(THREEPARAMS)
			sed 's/prog-so/prog/g' err-so-test.txt > mod-err-so-test.txt



test-bruteforce:	test-basic-binary test-a test-so
					cmp out-basic-test.txt out-a-test.txt
					cmp out-basic-test.txt out-so-test.txt
					cmp out-a-test.txt out-so-test.txt
					cmp err-basic-test.txt err-a-test.txt
					cmp err-basic-test.txt err-so-test.txt
					cmp err-a-test.txt err-so-test.txt

# Compare modified error files with replaced binary names with 'prog'
test-smart:	test-basic-binary test-a test-so
					cmp out-basic-test.txt out-a-test.txt
					cmp out-basic-test.txt out-so-test.txt
					cmp out-a-test.txt out-so-test.txt
					cmp err-basic-test.txt mod-err-a-test.txt
					cmp err-basic-test.txt mod-err-so-test.txt
					cmp mod-err-a-test.txt mod-err-so-test.txt


test: test-smart

clean:
	rm -f $(TRASH)

distclean:	clean 
			rm -rf $(GENERATES)