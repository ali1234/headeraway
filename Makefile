all: libheaderaway.so

GTK=`pkg-config --cflags gtk+-3.0`

%.o: %.c
	echo $(GTK)
	gcc $(GTK) -fPIC -c -Wall $*.c -o $*.o

libheaderaway.so: preload.o
	gcc -shared preload.o -ldl -o libheaderaway.so

clean:
	rm -f *.o *.so
