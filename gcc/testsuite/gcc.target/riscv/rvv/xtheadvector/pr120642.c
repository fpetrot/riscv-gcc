/* { dg-do compile } */
/* { dg-options "-O -mcpu=xt-c920 -mrvv-vector-bits=zvl" } */
/* { dg-skip-if "This CPU doesn't support 128bits" { riscv128-*-* } } */
int __attribute__((__vector_size__(4 * sizeof(int)))) v;
void foo() { v /= 3; }
