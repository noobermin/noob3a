#ifndef NOOB3A_H_
#define NOOB3A_H_
/*------------------------------------------------------------------
noob3a.h, simple 3d array file reader

Copyright: Gregory K. Ngirmang, 2019


Permission is hereby granted, free of charge, to any person
obtaining a copy of this software and associated documentation files
(the “Software”), to deal in the Software without restriction,
including without limitation the rights to use, copy, modify, merge,
publish, distribute, sublicense, and/or sell copies of the Software,
and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Usage:
#include in a project. Define NOOB3A_IMPL to implement functions. Define
NOOB3A_STATIC if you want the implementation to be static. Otherwise,
just define the type. Please don't use NOOB3A_STATIC without IMPL
and then implement static. You know such will be the source of linker
errors.
---------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
typedef int   _nb3a_int;
typedef float _nb3a_float;

typedef struct nb3a_ {
  _nb3a_int nx,ny,nz,nd;
  _nb3a_float *x,*y,*z,*d;
}noob3a_t;

#if !defined(NOOB3A_IMPL) && !defined(NOOB3A_STATIC)
  void noob3a_clean(noob3a_t*);
  int noob3a_loadfile(FILE*, noob3a_t*);
#endif

#ifdef NOOB3A_IMPL

#ifdef NOOB3A_STATIC
 #undef NOOB3A_STATIC
 #define NOOB3A_STATIC static
#else 
 #define NOOB3A_STATIC
#endif /* NOOB3A_STATIC */


NOOB3A_STATIC void noob3a_clean(noob3a_t* out) {
  free(out->x); free(out->y); free(out->z); free(out->d);
  out->nx = out->ny = out->nz = out->nd = 0;
  out->x  = out->y  = out->z  = out->d  = NULL;
}

NOOB3A_STATIC int noob3a_loadfile(FILE* f, noob3a_t *out){
#define _fr(a,b,l) if(fread(a,b,l,f)!=l) goto _noob3a_loadfile_fail; 0
#define _read_coord(d)							\
  _fr(&out->n##d,sizeof(_nb3a_int),1);					\
  out->d =(_nb3a_float*)malloc(sizeof(_nb3a_float)*out->n##d);		\
  if (out->d == NULL) goto _noob3a_loadfile_fail;			\
  _fr(out->d,sizeof(_nb3a_float),out->n##d);0
  /*. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */
  
  out->nx = out->ny = out->nz = out->nd = 0;
  out->x  = out->y  = out->z  = out->d  = NULL;
  _read_coord(x);
  _read_coord(y);
  _read_coord(z);
  _read_coord(d);

  if (out->nd != out->nx*out->ny*out->nz) return 1;
  return 0;
  /*. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . */
#undef  _fr
#undef  _read_coord
 _noob3a_loadfile_fail:
  noob3a_clean(out);
  return -1;
}

#endif /*NOOB3A_IMPL*/

#endif /*NOOB3A_H_*/
