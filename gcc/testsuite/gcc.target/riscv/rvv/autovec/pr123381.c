/* { dg-do compile } */
/* { dg-options "-Ofast -mcpu=xiangshan-kunminghu -mrvv-vector-bits=zvl -fno-tree-ccp -fno-vect-cost-model" } */
/* { dg-skip-if "This CPU doesn't support 128bits" { riscv128-*-* } } */

char c;

void
foo(short, short, short, short, int, int, int, int, long x)
{
  x /= *(_Complex short *)&x;
  c = x;
}
