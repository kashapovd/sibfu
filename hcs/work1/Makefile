INC=-I/opt/cuda/include
NVCC=/opt/cuda/bin/nvcc
NVCC_OPT=-std=c++11

all:
	$(NVCC) $(NVCC_OPT) array-add.cu -o array-add.out

clean:
	rm -f vector-add

run:
	./array-add.out