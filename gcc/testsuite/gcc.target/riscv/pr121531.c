/* { dg-do compile } */
/* { dg-additional-options "-mcpu=sifive-p670" } */
/* { dg-skip-if "This CPU doesn't support 128bits" { riscv128-*-* } } */

__attribute__((__vector_size__(sizeof(int)))) int v;
void foo() { v &= 1; }
