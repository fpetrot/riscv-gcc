/* { dg-do compile } */
/* { dg-additional-options "-march=rv128gcb_zicond -mabi=llp128d" { target { rv128 } } } */ 
/* { dg-additional-options "-march=rv64gcb_zicond -mabi=lp64d" { target rv64 } } */
/* { dg-additional-options "-march=rv32gcb_zicond -mabi=ilp32" { target rv32 } } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-Og" } } */

unsigned
foo (unsigned int a)
{
  unsigned int b = a & 0x00FFFFFF;
  unsigned int c = ((b & 0x000000FF) << 8
            | (b & 0x0000FF00) << 8
            | (b & 0x00FF0000) << 8
            | (b & 0xFF000000) >> 24);
  return c;
}

/* These don't have the trailing "w" so that they work for
   both rv32 and rv64.  */
/* { dg-final { scan-assembler-not "srli" } } */
/* { dg-final { scan-assembler-not "rori" } } */
/* { dg-final { scan-assembler-times "sll" 1 } } */
