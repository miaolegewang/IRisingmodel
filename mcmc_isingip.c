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
#define NT 256 // 512
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
double ising(double x[NT][NT], int i, int j){
  if(i == 0){
    if(j == 0){
      if(x[0][1] == x[1][0]){
        return x[i][j]*(4*x[0][0]*x[0][1]);
      }
      else return 0;
    }
    else if(j == NT-1){
      if(x[0][NT-2] == x[1][NT-1]){
        return x[i][j]*(4*x[0][NT-2]*x[0][NT-1]);
      }
      else return 0;
    }
    else{
      if(x[0][j-1] + x[0][j+1] + x[1][j] > 1.0){
        return x[i][j]*(x[0][j-1] + x[0][j+1] + x[1][j] + 1.0);
      }
      return x[i][j]*(x[0][j-1] + x[0][j+1] + x[1][j] - 1.0);
    }
  }
  else if(i == NT-1){
    if(j == 0){
      if(x[NT-1][1] == x[NT-2][0]){
        return x[i][j]*(4*x[NT-1][0]*x[NT-1][1]);
      }
      else return 0;
    }
    else if(j == NT-1){
      if(x[NT-1][NT-2] == x[NT-2][NT-1]){
        return x[i][j]*(4*x[NT-1][NT-2]*x[NT-1][NT-1]);
      }
      else return 0;
    }
    else{
      if(x[NT-1][j-1] + x[NT-1][j+1] + x[NT-2][j] > 1.0){
        return x[i][j]*(x[NT-1][j-1] + x[NT-1][j+1] + x[NT-2][j] + 1.0);
      }
      return x[i][j]*(x[0][j-1] + x[0][j+1] + x[1][j] - 1.0);
    }
  }
  else if(j == 0){
    if(x[i-1][0] + x[i+1][0] + x[i][1] > 1.0){
      return x[i][j]*(x[i-1][0] + x[i+1][0] + x[i][1] + 1.0);
    }
    return x[i][j]*(x[i-1][0] + x[i+1][0] + x[i][1] - 1.0);
  }
  else if(j == NT-1){
    if(x[i-1][NT-1] + x[i+1][NT-1] + x[i][NT-2] > 1.0){
      return x[i][j]*(x[i-1][NT-1] + x[i+1][NT-1] + x[i][NT-2] + 1.0);
    }
    return x[i][j]*(x[i-1][NT-1] + x[i+1][NT-1] + x[i][NT-2] - 1.0);
  }
  return x[i][j]*(x[i-1][j] + x[i+1][j] + x[i][j-1] + x[i][j+1]);
}

double gaussian(double x[NT][NT], double y[NT][NT], int i, int j){
  //return -0.42*(y[i][j] - x[i][j])*(y[i][j] - x[i][j]);
  return beta_max*y[i][j]*x[i][j];
}

double energy(double x[NT][NT], double y[NT][NT], int i, int j, double beta){
  return gaussian(x, y, i, j) + beta*gamma*ising(x, i, j);
  //return (-gaussian(x, y, i, j) - beta*gamma*ising(x, i, j));
}

int main(int argc, char* argv[]){
  //Initialize vectors and important values
  double x[NT][NT];
  double y[NT][NT];
  double avg[NT][NT];
  double d_action;
  double temp;
  double naccept;
  double nreject;

  ////////*******NEED TO WRITE I/O CODE HERE********////////
  if( argc != 3 ) {
    printf("Invalid number of arguments! Please try running again.\n");
    return 0;
  }

  int nbeta = atoi(argv[1]);

  FILE *f = fopen(argv[2], "r");
  for(unsigned int i = 0; i < NT; ++i) {
    for(unsigned int j = 0; j < NT; ++j) {
      fscanf(f, "%lf,\r\n", &y[i][j]);
    }
  }
  fclose(f);

  //Start X in noisy configuration Y
  for(int i = 0; i < NT; i++){
    for(int j = 0; j < NT; j++){
      x[i][j] = y[i][j];
      avg[i][j] = 0.0;
    }
  }

  //Monte Carlo Measurement Sweeps
  double beta = beta_max/nbeta;
  for(int count = 0; count < nbeta; count++){
    naccept = 0.0;
    nreject = 0.0;
    //Flip pixel spins and accept/reject based on relative actions.
    for(int i = 0; i < NT; i++){
      for(int j = 0; j < NT; j++){
        x[i][j] *= -1.0;
        d_action = energy(x,y,i,j,beta);
        x[i][j] *= -1.0;
        d_action -= energy(x,y,i,j,beta);
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
    for(int i = 0; i < NT; i++){
      for(int j = 0; j < NT; j++){
        //avg[i][j] += x[i][j]; //exp(-weight)*x[i][j];
        avg[i][j] += beta*x[i][j];
      }
    }
    printf("%12.6f", naccept/(naccept + nreject));
    beta += beta_max/nbeta;
  }
  printf("\n");

  //Print most likely image
  for(int i = 0; i < NT; i++){
    for(int j = 0; j < NT; j++){
      //if(avg[i][j]/(measure/100.0) > 0.0){
      if(avg[i][j] > 0.0){
        printf("%12.6f", 1.0);
      }
      else if(avg[i][j] < 0.0){
        printf("%12.6f", -1.0);
      }
      else printf("%12.6f", y[i][j]);
    }
    printf("\n");
  }

  return 1;
}
