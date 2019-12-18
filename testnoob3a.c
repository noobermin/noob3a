//#include <stdio.h>
#define NOOB3A_IMPL
#define NOOB3A_STATIC
#include "noob3a.h"

void
pnoob3a (const noob3a_t*);

int
main(int argc, char*argv[]) {
  FILE *fp;
  noob3a_t in;
  if (argc != 2) {
    printf("usage: testnoob3a <file>\n");
    return 0;
  }
  if ((fp=fopen(argv[1],"r"))==NULL) {
    perror("failed to open file\n");
    return 1;
  } else {
    int ret = noob3a_loadfile(fp, &in);
    if (ret == 1) {
      perror("invalid file: sizes don't match\n");
      return 3;
    } else if (ret == -1) {
      perror("i/o error with file\n");
      return 2;
    }
    fclose(fp);
  }
  pnoob3a(&in);
  noob3a_clean(&in);
}    
void
pnoob3a(const noob3a_t* in) {
  printf("nx: %d, ny: %d, nz: %d\n",
	 in->nx, in->ny, in->nz);
#define _prcoord(d)				\
  printf("##d##: \n ");				\
  for(int i=0; i < in->n##d ; ++i) {		\
    printf("%f ", in->d[i]);			\
  } putchar('\n');				\
  0
  _prcoord(x);
  _prcoord(y);
  _prcoord(z);
  _prcoord(d);
}
