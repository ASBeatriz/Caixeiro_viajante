all: caixeiro

item.o: item.c
	gcc -c item.c -o item.o

Lista_seq.o: Lista_seq.c
	gcc -c Lista_seq.c -o Lista_seq.o

# caixeiroviajante2.o: caixeiroviajante2.c
# 	gcc -c caixeiroviajante2.c -o caixeiroviajante2.o

# caixeiro: item.o Lista_seq.o caixeiroviajante2.o
# 	gcc item.o Lista_seq.o caixeiroviajante2.o -o caixeiro

caixeiroviajanteotimo.o: caixeiroviajanteotimo.c
	gcc -c caixeiroviajanteotimo.c -o caixeiroviajanteotimo.o

caixeiro: item.o Lista_seq.o caixeiroviajanteotimo.o
	gcc item.o Lista_seq.o caixeiroviajanteotimo.o -o caixeiro

run: caixeiro
	./caixeiro

clean:
	rm -f *.o caixeiro