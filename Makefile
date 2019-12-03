all: asst2

asst2 : mergesort.c multiThreadSorter.c multiThreadSorter.h simpleCSVsorter.c simpleCSVsorter.h   
	gcc multiThreadSorter.c -pthread -o multiThreadSorter

clean:
	rm -rf multThreadSorter
