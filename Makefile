collatz: main.c lrucache.h collatz.h
	gcc -o main collatz lrucache main.c collatz.h lrucache.h
	
clean:
	rm main lrucache collatz