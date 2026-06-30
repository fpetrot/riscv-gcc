/* { dg-do compile } */
/* { dg-additional-options "-std=c23 -mcpu=xiangshan-kunminghu" } */
/* { dg-skip-if "This CPU doesn't support 128bits" { riscv128-*-* } } */

_Float16 f, g;
void foo() { f /= g; }
