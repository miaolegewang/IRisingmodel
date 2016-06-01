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
ifdef rate
	rate = 0.44
endif

# set the number of iterations
ifndef itr
	itr = 10000
endif

BIN = noise.dat
OUTPUTDATA = restore.dat

# choose to use python or matlab to binarize and convert data file back to image
# Use python when P is set, otherwise use Matlab

# define dependencies
OBJECT = $(SC)ir_mcmc.c

default: restore

restore: $(OBJECT)
	$(COMPILER) $(OBJECT) $(CFLAGS) $(LIBRARY) -o ising.o

pyrestore: $(OBJECT)
	$(COMPILER) $(OBJECT) $(CFLAGS) $(LIBRARY) -o ising.o
	python $(SC)binarize.py $(IMAGE) $(rate)
	./ising.o $(itr) $(BIN) > $(OUTPUTDATA)
	python $(SC)restore.py $(OUTPUTDATA)

test: $(SC)test.c
	$(COMPILER) $(SC)test.c $(CFLAGS) $(LIBRARY) -o test.o

clean:
	$(RM) *.o *.txt *.dat

cld:
	$(RM) *.txt *.dat

ri:
	$(RM) *.jpg *.png *.jpeg *.JPG *.JPEG *.bmp *.gif
