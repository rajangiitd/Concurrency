list:
	gcc -o obj/list_test test/list_test.c src/list.c
	./obj/list_test

hashmap:
	gcc -o obj/hashmap_test test/hashmap_test.c src/list.c src/hm.c
	./obj/hashmap_test

all:
	gcc -o obj/main test/main.c src/list.c src/hm.c src/mythread.c
	./obj/main data/in1.txt data/in2.txt data/in3.txt data/in4.txt
