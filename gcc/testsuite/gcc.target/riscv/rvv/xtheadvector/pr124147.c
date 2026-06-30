/* { dg-do compile } */
/* { dg-options "-O3 -mcpu=xt-c920 -mrvv-vector-bits=zvl" } */
/* { dg-skip-if "This CPU doesn't support 128bits" { riscv128-*-* } } */

typedef __attribute__((__vector_size__(2 * sizeof(int)))) int V;

V
foo(V v)
{
  return v > 0;
}

