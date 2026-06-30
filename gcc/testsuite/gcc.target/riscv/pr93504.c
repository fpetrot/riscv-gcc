/* { dg-do compile } */
/* { dg-additional-options "-march=rv128gc_zicond -mabi=llp128d" { target { rv128 } } } */ 
/* { dg-additional-options "-march=rv64gc_zicond -mabi=lp64d" { target rv64 } } */
/* { dg-additional-options "-march=rv32gc_zicond -mabi=ilp32" { target rv32 } } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-O1" "-Og" } } */

#define N 0x202
#define OP ^

unsigned f(unsigned a, unsigned b)
{
  unsigned t = a OP b;
  unsigned t1 = t&N;
  unsigned t2 = a&~N;
  return t1 | t2;
}

/* { dg-final { scan-assembler-times "andi\t" 1 } } */
/* { dg-final { scan-assembler-times "xor\t" 1 } } */
/* { dg-final { scan-assembler-not "\tor\t" } } */
