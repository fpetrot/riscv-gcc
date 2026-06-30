/* { dg-do compile } */
/* { dg-options "-march=rv128gcbv_zicond -mabi=llp128d" { target { rv128 } } } */ 
/* { dg-options "-march=rv64gcbv_zicond -mabi=lp64d" { target rv64 } } */
/* { dg-options "-march=rv32gcbv_zicond -mabi=ilp32" { target rv32 } } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-Og" } } */

long
frob (unsigned short *y, long z)
{
  long ret = (*y << 2) + z;
  if (ret != z)
    return 0;
  return ret;
}

/* { dg-final { scan-assembler-not "sh2add" } } */
/* { dg-final { scan-assembler-not "sub" } } */

