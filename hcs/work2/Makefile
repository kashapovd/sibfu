INC=-I/usr/local/cuda/include -I../Common
NVCC=/usr/local/cuda/bin/nvcc 
NVCC_OPT=-std=c++11 -ccbin g++ -m64

all:
	$(NVCC) $(NVCC_OPT) $(INC) matrix-mul.cu -o matrix-mul.out

clean:
	rm -f matrix-mul.out

run: all
	./matrix-mul.out
