# This Makefile is for phy242 final project: image restoration using ising model
#  Run 'make restore' will:
#		1. compile c file to binary executable file
#		2. generate data file from target image using python
#		3. run c program on data file
#		4. convert data file back to image file (either in matlab or python)
#	'make clean' will remove all intermediate results and keep the final result as well as the target image file

# set the default directory of source codes and images
SC = ./src/
IM = ./images/

# define compiler
COMPILER = gcc

# define flags for compiler
CFLAGS = -O3

# add necessary library
LIBRARY = -lm

# define image path
# 	default: target.png
ifndef $(IMAGE)
	IMAGE = $(IM)target.png
endif

# define the division value of black and white
ifdef gamma
	gamma = 1.6
endif

# set the number of iterations
ifndef nbeta
	nbeta = 1000
endif

BIN = spin.dat
OUTPUTDATA = restored.txt

# choose to use python or matlab to binarize and convert data file back to image
# Use python when P is set, otherwise use Matlab

# define dependencies
OBJECT = $(SC)ir_mcmc.c

default: restore

restore: $(OBJECT)
	$(COMPILER) $(OBJECT) $(CFLAGS) $(LIBRARY) -o ising.o
	./ising.o $(nbeta) $(gamma) $(BIN) > $(OUTPUTDATA)

clean:
	$(RM) *.o *.txt *.dat
