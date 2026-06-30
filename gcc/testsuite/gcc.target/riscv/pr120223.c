/* { dg-do compile { target { ! riscv_abi_e } } } */
/* { dg-options "-mcpu=thead-c906" }  */
/* { dg-skip-if "This CPU doesn't support 128bits" { riscv128-*-* } } */
long foo(long x) { return x ^ 0x80000000; }

