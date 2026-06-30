/* { dg-do compile } */
/* { dg-options "-mcpu=xt-c920 -mrvv-vector-bits=zvl" } */
/* { dg-skip-if "This CPU doesn't support 128bits" { riscv128-*-* } } */

int i;
void *p;

void
foo ()
{
  __builtin_memset (p, i, 8);
}
