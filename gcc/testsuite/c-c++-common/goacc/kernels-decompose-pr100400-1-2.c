/* { dg-additional-options "--param openacc-kernels=decompose" } */

/* { dg-additional-options "-fchecking" }
   { dg-ice TODO { c++ } }
   { dg-prune-output "during GIMPLE pass: omp_oacc_kernels_decompose" } */

/* { dg-additional-options "-g" } */
/* { dg-additional-options "-O1" } so that we may get some 'GIMPLE_DEBUG's.  */

/* { dg-additional-options "-fopt-info-all-omp" } */

/* { dg-additional-options "--param=openacc-privatization=noisy" } */

int *p;

void
foo (void)
{
  /* { dg-bogus {sorry, unimplemented: 'gimple_debug' not yet supported} TODO { xfail *-*-* } .+1 } */
#pragma acc kernels /* { dg-line l_compute1 } */
  /* { dg-note {variable 'c' declared in block is candidate for adjusting OpenACC privatization level} {} { xfail *-*-* } l_compute1 } */
  /* { dg-note {variable 'c\.0' declared in block isn't candidate for adjusting OpenACC privatization level: not addressable} {} { xfail *-*-* } l_compute1 } */
  {
    /* { dg-bogus {note: beginning 'gang-single' part in OpenACC 'kernels' region} {w/ debug} { xfail c++ } .-1 }
       { dg-bogus {note: beginning 'gang-single' part in OpenACC 'kernels' region} {w/ debug} { xfail c } .+1 } */
    int c;

    /* { dg-note {beginning 'gang-single' part in OpenACC 'kernels' region} {} { xfail *-*-* } .+1 } */
    p = &c;

    /* { dg-note {parallelized loop nest in OpenACC 'kernels' region} {} { xfail c++ } .+1 } */
#pragma acc loop independent /* { dg-line l_loop_c1 } */
    /* { dg-note {variable 'c\.0' in 'private' clause isn't candidate for adjusting OpenACC privatization level: not addressable} {} { xfail *-*-* } l_loop_c1 } */
    /* { dg-note {variable 'c' in 'private' clause is candidate for adjusting OpenACC privatization level} {} { xfail *-*-* } l_loop_c1 }
       { dg-note {variable 'c' ought to be adjusted for OpenACC privatization level: 'vector'} {} { xfail *-*-* } l_loop_c1 } */
    /* { dg-optimized {assigned OpenACC gang vector loop parallelism} {} { xfail *-*-* } l_loop_c1 } */
    for (c = 0; c < 1; ++c)
      ;
  }
}
