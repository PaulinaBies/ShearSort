all: shearsort

sample: shearsort.c
	gcc shearsort.c -lpthread -o shearsort

clean:
	rm shearsort