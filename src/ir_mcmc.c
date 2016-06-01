#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Period parameters for Random Number Generator*/
#define N 624
#define M 397
#define MATRIX_A 0x9908b0df   /* constant vector a */
#define UPPER_MASK 0x80000000 /* most significant w-r bits */
#define LOWER_MASK 0x7fffffff /* least significant r bits */

/* Tempering parameters for PRNG*/
#define TEMPERING_MASK_B 0x9d2c5680
#define TEMPERING_MASK_C 0xefc60000
#define TEMPERING_SHIFT_U(y)  (y >> 11)
#define TEMPERING_SHIFT_S(y)  (y << 7)
#define TEMPERING_SHIFT_T(y)  (y << 15)
#define TEMPERING_SHIFT_L(y)  (y >> 18)

#define PI 3.14159
#define var 0.9216
#define beta_max 0.4 //0.5*log(4.0)
#define gamma 1.0
//#define warmups 10000
//#define measure 10000

static unsigned long mt[N]; /* the array for the state vector  */
static int mti=N+1; /* mti==N+1 means mt[N] is not initialized */
static double invvar = 1.0/2.0/var;

/* Mersene Twister PRNG */
/* initializing the array with a NONZERO seed */
void
sgenrand(seed)
    unsigned long seed;
{
    /* setting initial seeds to mt[N] using         */
    /* the generator Line 25 of Table 1 in          */
    /* [KNUTH 1981, The Art of Computer Programming */
    /*    Vol. 2 (2nd Ed.), pp102]                  */
    mt[0]= seed & 0xffffffff;
    for (mti=1; mti<N; mti++)
        mt[mti] = (69069 * mt[mti-1]) & 0xffffffff;
}

double /* generating reals */
/* unsigned long */ /* for integer generation */
genrand()
{
    unsigned long y;
    static unsigned long mag01[2]={0x0, MATRIX_A};
    /* mag01[x] = x * MATRIX_A  for x=0,1 */

    if (mti >= N) { /* generate N words at one time */
        int kk;

        if (mti == N+1)   /* if sgenrand() has not been called, */
            sgenrand(4357); /* a default initial seed is used   */

        for (kk=0;kk<N-M;kk++) {
            y = (mt[kk]&UPPER_MASK)|(mt[kk+1]&LOWER_MASK);
            mt[kk] = mt[kk+M] ^ (y >> 1) ^ mag01[y & 0x1];
        }
        for (;kk<N-1;kk++) {
            y = (mt[kk]&UPPER_MASK)|(mt[kk+1]&LOWER_MASK);
            mt[kk] = mt[kk+(M-N)] ^ (y >> 1) ^ mag01[y & 0x1];
        }
        y = (mt[N-1]&UPPER_MASK)|(mt[0]&LOWER_MASK);
        mt[N-1] = mt[M-1] ^ (y >> 1) ^ mag01[y & 0x1];

        mti = 0;
    }

    y = mt[mti++];
    y ^= TEMPERING_SHIFT_U(y);
    y ^= TEMPERING_SHIFT_S(y) & TEMPERING_MASK_B;
    y ^= TEMPERING_SHIFT_T(y) & TEMPERING_MASK_C;
    y ^= TEMPERING_SHIFT_L(y);

    return ( (double)y / (unsigned long)0xffffffff ); /* reals */
    /* return y; */ /* for integer generation */
}



//Ising potential with interpolated BCs. Might need to switch to periodic.
double ising(double **x, int i, int j, unsigned int height, unsigned int width){
  if(i == 0){
    if(j == 0){
      if(x[0][1] == x[1][0]){
        return x[i][j] * (4 * x[0][0] * x[0][1]);
      }
      else return 0;
    }
    else if(j == width - 1){
      if(x[0][width - 2] == x[1][width - 1]){
        return x[i][j] * (4 * x[0][width - 2] * x[0][width - 1]);
      }
      else return 0;
    }
    else{
      if(x[0][j - 1] + x[0][j + 1] + x[1][j] > 1.0){
        return x[i][j] * (x[0][j - 1] + x[0][j + 1] + x[1][j] + 1.0);
      }
      return x[i][j] * (x[0][j - 1] + x[0][j + 1] + x[1][j]  -  1.0);
    }
  }
  else if(i == height - 1){
    if(j == 0){
      if(x[height - 1][1] == x[height - 2][0]){
        return x[i][j] * (4 * x[height - 1][0] * x[height - 1][1]);
      }
      else return 0;
    }
    else if(j == width - 1){
      if(x[height - 1][width - 2] == x[height - 2][width - 1]){
        return x[i][j] * (4 * x[height - 1][width - 2] * x[height - 1][width - 1]);
      }
      else return 0;
    }
    else{
      if(x[height - 1][j - 1] + x[height - 1][j+1] + x[height - 2][j] > 1.0){
        return x[i][j] * (x[height - 1][j - 1] + x[height - 1][j + 1] + x[height - 2][j] + 1.0);
      }
      return x[i][j] * (x[0][j - 1] + x[0][j + 1] + x[1][j] - 1.0);
    }
  }
  else if(j == 0){
    if(x[i - 1][0] + x[i + 1][0] + x[i][1] > 1.0){
      return x[i][j] * (x[i - 1][0] + x[i + 1][0] + x[i][1] + 1.0);
    }
    return x[i][j] * (x[i - 1][0] + x[i + 1][0] + x[i][1] - 1.0);
  }
  else if(j == width - 1){
    if(x[i - 1][width - 1] + x[i + 1][width - 1] + x[i][width - 2] > 1.0){
      return x[i][j] * (x[i - 1][width - 1] + x[i + 1][width - 1] + x[i][width - 2] + 1.0);
    }
    return x[i][j] * (x[i - 1][width - 1] + x[i + 1][width - 1] + x[i][width - 2] - 1.0);
  }
  return x[i][j] * (x[i - 1][j] + x[i + 1][j] + x[i][j - 1] + x[i][j + 1]);
}

double gaussian(double **x, double **y, unsigned int i, unsigned int j){
  //return -0.42*(y[i][j] - x[i][j])*(y[i][j] - x[i][j]);
  return beta_max*y[i][j]*x[i][j];
}

double energy(double **x, double **y, int i, int j, double beta, int height, int width){
  return gaussian(x, y, i, j) + beta*gamma*ising(x, i, j, height, width);
  //return (-gaussian(x, y, i, j) - beta*gamma*ising(x, i, j));
}

int main(int argc, char* argv[]){
  ////////*******NEED TO WRITE I/O CODE HERE********////////
  if( argc != 3 ) {
    printf("Invalid number of arguments! Please try running again.\n");
    return 0;
  }

  // step size to reduce beta
  int nbeta = atoi(argv[1]);
  unsigned int height, width;

  // read data from file
  FILE *f = fopen(argv[2], "r");

  // first line is the dimension of the images
  int miao;  // just try to get rid of
  miao = fscanf(f, "%u,%u\n", &height, &width);


  // Initialize vectors and important values
  // Allocate memory for x, y and avg
  double **x = (double**)malloc(height * sizeof(double*));
  double **y = (double**)malloc(height * sizeof(double*));
  double **avg = (double**)malloc(height * sizeof(double*));
  double d_action;
  double temp;
  double naccept;
  double nreject;

  for(int i = 0; i < height; ++i) {
    x[i] = (double*)malloc(width * sizeof(double));
    y[i] = (double*)malloc(width * sizeof(double));
    avg[i] = (double*)malloc(width * sizeof(double));
    for(int j = 0; j < width; ++j) {
      miao = fscanf(f, "%lf ", &y[i][j]);
    }
  }
  fclose(f);

  //Start X in noisy configuration Y
  for(int i = 0; i < height; i++){
    for(int j = 0; j < width; j++){
      x[i][j] = y[i][j];
      avg[i][j] = 0.0;
    }
  }

  //Monte Carlo Measurement Sweeps
  double beta = beta_max / nbeta;
  for(int count = 0; count < nbeta; count++){
    naccept = 0.0;
    nreject = 0.0;
    //Flip pixel spins and accept/reject based on relative actions.
    for(int i = 0; i < height; i++){
      for(int j = 0; j < width; j++){
        x[i][j] *= -1.0;
        d_action = energy(x, y, i, j, beta, height, width);
        x[i][j] *= -1.0;
        d_action -= energy(x, y, i, j, beta, height, width);
        if(d_action > 0 || exp(d_action) > genrand()){
        //if(d_action < 0 || exp(-d_action) > genrand()){
          x[i][j] *= -1.0;
          naccept += 1.0;
        }
        else nreject += 1.0;
      }
    }
    /*
    double weight = 0;
    for(int i = 1; i < NT-1; i++){
      for(int j = 1; j < NT-1; j++){
        weight += energy(x,y,i,j,1.0);
      }
    }
    */
    for(int i = 0; i < height; i++){
      for(int j = 0; j < width; j++){
        //avg[i][j] += x[i][j]; //exp(-weight)*x[i][j];
        avg[i][j] += beta * x[i][j];
      }
    }
    printf("%12.6f", naccept / (naccept + nreject));
    beta += beta_max / nbeta;
  }
  printf("\n");

  //Print most likely image
  for(int i = 0; i < height; i++){
    for(int j = 0; j < width; j++){
      //if(avg[i][j]/(measure/100.0) > 0.0){
      if(avg[i][j] > 0.0){
        printf("%12.6f", 1.0);
      }
      else if(avg[i][j] < 0.0){
        printf("%12.6f", -1.0);
      }
      //else printf("%12.6f", y[i][j]);
    }
    printf("\n");
  }


  //  free the memory allocated
  for(int i = 0; i < height; i++){
    free(x[i]);
    free(y[i]);
    free(avg[i]);
  }
  free(x);
  free(y);
  free(avg);
  return 1;
}
