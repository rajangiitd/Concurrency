list:
	gcc -o obj/list_test test/list_test.c src/list.c
	./obj/list_test  -I include/
doc:
	doxygen Doxyfile
clean:
	rm -f obj/*
	rm -fr doc/*
hashmap:
	gcc -o obj/hashmap_test test/hashmap_test.c src/list.c src/hm.c src/mythread.c
	./obj/hashmap_test -I include/
test:
	gcc -g3 -o obj/main.o test/main_pthreads.c src/list.c src/hm.c src/mythread.c -I include/ -pthread
	./obj/main.o $(wildcard data/*.txt)
report:
	pdflatex texample.tex

.PHONY: all test clean
