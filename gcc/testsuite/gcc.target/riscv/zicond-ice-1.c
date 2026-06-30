/* { dg-do compile } */
/* { dg-options "-march=rv128gc_zicond -mabi=llp128d" { target { rv128 } } } */ 
/* { dg-options "-march=rv64gc_zicond -mabi=lp64d" { target { rv64 } } } */
/* { dg-options "-march=rv32gc_zicond -mabi=ilp32f" { target { rv32 } } } */

int a, c;
long b;

void
d() {
  for (;;)
    if (a & (b < 8 ?: 1 << b))
      c = 1;
} 
