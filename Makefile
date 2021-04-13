build:
	gcc -Wall -g editor.c -o editor
run:
	./editor
valgrind:
	valgrind --tool=memcheck --leak-check=full ./editor
clean:
	rm -rf ./editor
