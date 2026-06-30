/* { dg-do compile } */
/* { dg-options "-mcpu=xt-c920 -mrvv-vector-bits=zvl -fzero-call-used-regs=all" */
/* { dg-skip-if "This CPU doesn't support 128bits" { riscv128-*-* } } */

void
foo ()
{}
