
T=2
B=1
R=1
L=2
I=1000
N=8

all: compare_jacobi.py 

run: 
	python jacobi.py $(T) $(B) $(R) $(L) $(I) $(N)

check: compare_jacobi.py 
	python compare_jacobi.py -t=$(T) -b=$(B) -r=$(R) -l=$(L) -i=$(I) -n=$(N)

clean:

