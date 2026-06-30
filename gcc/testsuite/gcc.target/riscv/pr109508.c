/* { dg-do compile { target { ! riscv_abi_e } } } */
/* { dg-options "-mcpu=sifive-s76" } */
/* { dg-skip-if "This CPU doesn't support 128bits" { riscv128-*-* } } */

typedef char __attribute__((__vector_size__ (1))) V;

V v;

void
foo (void)
{
  (char) __builtin_shuffle (0 % v, (V){6}, v);
}
