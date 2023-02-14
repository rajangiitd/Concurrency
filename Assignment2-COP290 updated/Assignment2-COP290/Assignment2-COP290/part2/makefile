list:
	gcc -o obj/list_test test/list_test.c src/list.c
	./obj/list_test

hashmap:
	gcc -o obj/hashmap_test test/hashmap_test.c src/list.c src/hashmap.c
	./obj/hashmap_test

all:
	gcc -o obj/main test/main.c src/list.c src/hashmap.c src/mythread.c
	./obj/main
