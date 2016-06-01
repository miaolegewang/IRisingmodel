#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){
  FILE *f = fopen("noise.dat", "r");
  unsigned int height, width;
  fscanf(f, "%u,%u\n", &height, &width);
  double tmp;
  printf("Height: %u, Width: %u\n", height, width);
  for(unsigned int i = 0; i < height; i++){
    for(unsigned int j = 0; j < width; j++){
      fscanf(f, "%lf", &tmp);
      printf("%lf ", tmp);
    }
    printf("\n");
  }
  fclose(f);
}
