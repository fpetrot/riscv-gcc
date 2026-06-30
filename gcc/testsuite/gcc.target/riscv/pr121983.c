/* { dg-do compile } */
/* { dg-options "-mcpu=xiangshan-nanhu" } */
/* { dg-skip-if "This CPU doesn't support 128bits" { riscv128-*-* } } */

struct {
  int a;
  short s;
  unsigned x : 18;
  unsigned y : 14;
} bf;

void
foo()
{
  bf.s ^= bf.y / __builtin_stdc_rotate_left(bf.x, 5);
}
