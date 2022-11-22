INC=-I/usr/local/cuda/include -I../Common
NVCC=/usr/local/cuda/bin/nvcc 
NVCC_OPT=-std=c++11 -ccbin g++ -m64

all:
	$(NVCC) $(NVCC_OPT) $(INC) array-add.cu -o array-add.out

clean:
	rm -f array-add.out

run: all
	./array-add.out
