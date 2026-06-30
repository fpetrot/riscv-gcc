/* { dg-do compile } */
/* { dg-additional-options "-march=rv128gcb_zicond -mabi=llp128d" { target { rv128 } } } */ 
/* { dg-additional-options "-march=rv64gcb_zicond -mabi=lp64d" { target rv64 } } */
/* { dg-additional-options "-march=rv32gcb_zicond -mabi=ilp32" { target rv32 } } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-Og" } } */

int f(int a, int b, int c)
{
    return (a ^ b) ^ (a | c);
}

/* { dg-final { scan-assembler-times "xor\t" 1 } } */
/* { dg-final { scan-assembler-times "andn\t" 1 } } */
