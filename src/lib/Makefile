
CC     =  cc -Wall
LIBS   =  -lgc -lm
LEX    =  flex

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

#FLAGS  =  -DTRACE -DDEBUG -D_GNU_SOURCE
#FLAGS  =  -DTRACE -DDEBUG -DUSE_GARBAGE_COLLECTOR -D_GNU_SOURCE
FLAGS  =  -ggdb -DDEBUG -DUSE_GARBAGE_COLLECTOR -D_GNU_SOURCE
#FLAGS =  -O3 -DUSE_GARBAGE_COLLECTOR -D_GNU_SOURCE
#FLAGS =  -O3 -D_GNU_SOURCE
#FLAGS =  -O3 -DDEBUG -D_GNU_SOURCE
#FLAGS =  -D_GNU_SOURCE


# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 


objects     =   objects/cast.o objects/list.o objects/empty.o \
		objects/string.o objects/integer.o objects/real.o \
                objects/lazy.o objects/nvp.o objects/minihash.o \
		objects/trie.o

debug_code  =  objects/barf.o objects/trace.o 


# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 


lib:   libbaz

all:	libbaz tests test

check:  test

clean:
	@echo -- Cleaning:
	@-rm -rf objects
	@-rm -rf test/bin
	@echo -- Done.


# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 


start:
	@echo -- Checking libbaz:

libbaz:	start objects_dir $(debug_code) $(objects)
	@echo -- Done.


# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 


objects_dir: objects/

objects/:
	@echo .. making objects dir
	@-mkdir -p objects


# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 


objects/barf.o: src/barf.c src/barf.h Makefile
	@echo .. compiling barf
	@$(CC) -c -o objects/barf.o src/barf.c $(FLAGS)

objects/trace.o: src/trace.c src/trace.h Makefile
	@echo .. compiling trace
	@$(CC) -o objects/trace.o -c src/trace.c $(FLAGS)


# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

all_objects: objects_dir $(debug_code) $(objects)

objects/cache.o: src/cache.c

objects/cast.o: src/cast.c src/debug.h src/barf.h src/cast.h src/list.h \
	src/class.h src/size.h src/integer.h src/string.h src/empty.h \
	src/real.h
	@echo .. compiling cast
	@$(CC) -o objects/cast.o -c src/cast.c $(FLAGS)

objects/empty.o: src/empty.c src/class.h src/barf.h src/empty.h src/list.h \
	src/size.h src/cast.h src/integer.h src/string.h src/real.h
	@echo .. compiling empty
	@$(CC) -o objects/empty.o -c src/empty.c $(FLAGS)

objects/file.o: src/file.c

objects/hash.o: src/hash.c

objects/integer.o: src/integer.c src/class.h src/barf.h src/debug.h src/integer.h \
	src/size.h src/list.h src/string.h src/cast.h src/empty.h src/real.h
	@echo .. compiling integer
	@$(CC) -o objects/integer.o -c src/integer.c $(FLAGS)

objects/lazy.o: src/lazy.c src/debug.h src/barf.h src/empty.h src/class.h \
	src/list.h src/size.h src/lazy.h src/integer.h src/string.h
	@echo .. compiling lazy
	@$(CC) -o objects/lazy.o -c src/lazy.c $(FLAGS)

objects/lazy_dir.o: src/lazy_dir.c

objects/lazy_file.o: src/lazy_file.c

objects/list.o: src/list.c src/debug.h src/barf.h src/empty.h src/class.h \
	src/list.h src/size.h src/integer.h src/string.h
	@echo .. compiling list
	@$(CC) -o objects/list.o -c src/list.c $(FLAGS)

objects/minihash.o: src/minihash.c src/debug.h src/barf.h src/empty.h src/class.h \
	src/list.h src/size.h src/minihash.h src/string.h
	@echo .. compiling minihash
	@$(CC) -o objects/minihash.o -c src/minihash.c $(FLAGS)

objects/nvp.o: src/nvp.c src/debug.h src/barf.h src/nvp.h src/class.h src/size.h \
	src/string.h src/list.h
	@echo .. compiling nvp
	@$(CC) -o objects/nvp.o -c src/nvp.c $(FLAGS)

objects/pool.o: src/pool.c

objects/real.o: src/real.c src/class.h src/barf.h src/debug.h src/real.h \
	src/size.h src/list.h src/string.h src/cast.h src/integer.h src/empty.h
	@echo .. compiling real
	@$(CC) -o objects/real.o -c src/real.c $(FLAGS)

objects/string.o: src/string.c src/gc.h src/debug.h src/barf.h src/string.h \
	src/class.h src/list.h src/size.h src/cast.h src/integer.h src/empty.h \
	src/real.h
	@echo .. compiling string
	@$(CC) -o objects/string.o -c src/string.c $(FLAGS)

objects/trie.o: src/trie.c src/gc.h src/debug.h src/barf.h src/trie.h \
	src/class.h src/size.h src/cast.h src/empty.h
	@echo .. compiling trie
	@$(CC) -o objects/trie.o -c src/trie.c $(FLAGS)



# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 


test_dir: test/bin

test/bin: test/
	@echo .. making test/bin
	@-mkdir -p test/bin

start_tests:
	@echo -- Making tests:

tests:	start_tests \
	test/bin/barf  \
	test/bin/trace \
	test/bin/debug  \
	test/bin/integer \
	test/bin/lazy \
	test/bin/list \
	test/bin/minihash \
	test/bin/nvp \
	test/bin/real \
	test/bin/string \
	test/bin/trie


# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 


test: tests
	@echo -- Testing:
	@-test/test.pl


# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 


test/bin/barf: test/src/barf.c src/barf.h Makefile test_dir
	@echo .. compiling barf test
	@$(CC) -o test/bin/barf test/src/barf.c src/barf.c $(FLAGS) -DTEST -DDEBUG $(LIBS)

test/bin/trace: test/src/trace.c src/trace.h Makefile test_dir
	@echo .. compiling trace test
	@$(CC) -o test/bin/trace test/src/trace.c src/trace.c $(FLAGS) -DTEST -DDEBUG -DTRACE $(LIBS)


# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

# It is important that each test file is rebuilt after each modification

test/bin/debug: test/src/debug.c src/debug.h src/barf.h \
	src/trace.c src/barf.c  # unit .c files too \
	test_dir
	@echo .. compiling debug test
	@$(CC) -o test/bin/debug test/src/debug.c src/trace.c src/barf.c $(FLAGS) -DTRACE -DDEBUG $(LIBS)

test/bin/integer: test/src/integer.c src/debug.h src/barf.h src/integer.h \
	src/size.h src/class.h src/list.h src/string.h src/cast.h src/empty.h \
	src/real.h \
	test_dir all_objects
	@echo .. compiling integer test
	@$(CC) -o test/bin/integer test/src/integer.c $(objects) $(debug_code) $(FLAGS) -DTEST $(LIBS)

test/bin/lazy: test/src/lazy.c src/lazy.h src/class.h src/barf.h src/size.h \
	src/debug.h src/cast.h src/list.h src/integer.h src/string.h \
	src/empty.h src/real.h \
	test_dir all_objects
	@echo .. compiling lazy test
	@$(CC) -o test/bin/lazy test/src/lazy.c $(objects) $(debug_code) $(FLAGS) -DTEST $(LIBS)

test/bin/list: test/src/list.c src/empty.h src/class.h src/barf.h src/list.h \
	src/size.h src/debug.h src/integer.h src/string.h \
	test_dir all_objects
	@echo .. compiling list test
	@$(CC) -o test/bin/list test/src/list.c $(objects) $(debug_code) $(FLAGS) -DTEST $(LIBS)

test/bin/minihash: test/src/minihash.c src/minihash.h src/size.h src/class.h \
	src/barf.h src/string.h src/list.h src/debug.h src/cast.h src/integer.h \
	src/empty.h src/real.h \
	test_dir all_objects
	@echo .. compiling minihash test
	@$(CC) -o test/bin/minihash test/src/minihash.c $(objects) $(debug_code) $(FLAGS) -DTEST $(LIBS)

test/bin/nvp: test/src/nvp.c src/nvp.h src/class.h src/barf.h src/size.h \
	src/string.h src/list.h src/debug.h src/cast.h src/integer.h \
	src/empty.h src/real.h \
	test_dir all_objects
	@echo .. compiling nvp test
	@$(CC) -o test/bin/nvp test/src/nvp.c $(objects) $(debug_code) $(FLAGS) -DTEST $(LIBS)

test/bin/real: test/src/real.c src/debug.h src/barf.h src/real.h src/size.h \
	src/class.h src/list.h src/string.h src/cast.h src/integer.h \
	src/empty.h \
	test_dir all_objects
	@echo .. compiling real test
	@$(CC) -o test/bin/real test/src/real.c $(objects) $(debug_code) $(FLAGS) -DTEST $(LIBS)

test/bin/string: test/src/string.c src/string.h src/class.h src/barf.h \
	src/list.h src/size.h src/debug.h src/cast.h src/integer.h src/empty.h \
	src/real.h \
	test_dir all_objects
	@echo .. compiling string test
	@$(CC) -o test/bin/string test/src/string.c $(objects) $(debug_code) $(FLAGS) -DTEST $(LIBS)

test/bin/trie: test/src/trie.c src/debug.h src/barf.h src/trie.h src/class.h \
	src/string.h src/list.h src/size.h \
	test_dir all_objects
	@echo .. compiling trie test
	@$(CC) -o test/bin/trie test/src/trie.c $(objects) $(debug_code) $(FLAGS) -DTEST $(LIBS)
