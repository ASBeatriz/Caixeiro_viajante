all: caixeiro

Lista.o: Lista.c
	gcc -c Lista.c -o Lista.o

# caixeiroviajante2.o: caixeiroviajante2.c
# 	gcc -c caixeiroviajante2.c -o caixeiroviajante2.o

# caixeiro: Lista.o caixeiroviajante2.o
# 	gcc Lista.o caixeiroviajante2.o -o caixeiro

caixeiroviajanteotimo.o: caixeiroviajanteotimo.c
	gcc -c caixeiroviajanteotimo.c -o caixeiroviajanteotimo.o

caixeiro: Lista.o caixeiroviajanteotimo.o
	gcc Lista.o caixeiroviajanteotimo.o -o caixeiro

run: caixeiro
	./caixeiro

clean:
	rm -f *.o caixeiro