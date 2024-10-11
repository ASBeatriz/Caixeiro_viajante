all: pcv pcv_otimo

Lista.o: Lista.c
	gcc -c -Wall -Wextra -g Lista.c -o Lista.o

pcv.o: pcv.c
	gcc -c -Wall -Wextra -g pcv.c -o pcv.o

pcv: Lista.o pcv.o
	gcc -Wall -Wextra -g Lista.o pcv.o -o pcv

pcv_otimo.o: pcv_otimo.c
	gcc -c -Wall -Wextra -g pcv_otimo.c -o pcv_otimo.o

pcv_otimo: Lista.o pcv_otimo.o
	gcc -Wall -Wextra -g Lista.o pcv_otimo.o -o pcv_otimo

run_pcv: pcv
	./pcv

run_pcv_otimo: pcv_otimo
	./pcv_otimo

clean:
	rm -f *.o pcv pcv_otimo