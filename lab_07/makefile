CC := gcc 
CFLAGS := -std=c11 -Werror -Wall -pedantic -Wextra -lm -g3
CHECK_FLAGS := $(shell pkg-config --cflags --libs check)

OBJS :=  ./out/stack_array_t.o ./out/tree_t.o ./out/mytime.o ./out/tree.o ./out/tree_node.o ./out/avl_tree.o ./out/closed_hash.o ./out/open_hash.o ./out/list_t.o ./out/comparator.o

OBJS_CHECK :=  $(OBJS) ./unit_tests/out/check_process.o

app.exe : $(OBJS) ./out/main.o
	$(CC) $^ -o app.exe -lm

unit_tests.exe : $(OBJS_CHECK) 
	$(CC) $^ $(CHECK_FLAGS) -o unit_tests.exe

./unit_tests/out/%.o : ./unit_tests/%.c
	$(CC) $(CFLAGS) -c $< -o $@

./out/%.o : ./src/%.c ./inc/*.h
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean build run build_units run_units

build : app.exe

build_units : unit_tests.exe
	
run_units : build_units
	./unit_tests.exe

run : build
	./app.exe

clean :
	$(RM) *.o ./out/*.o *.exe *.out
