/* { dg-do compile } */
/* { dg-options "-march=rv128gc_zicond -mabi=llp128d" { target { rv128 } } } */ 
/* { dg-options "-march=rv64gc_zicond -mabi=lp64d" { target { rv64 } } } */
/* { dg-options "-march=rv32gc_zicond -mabi=ilp32d" { target { rv32 } } } */

long a, b;
int c, d;
void e(long *f) {
  (b = *f) && --b;
  for (; c;)
    ;
}
void g() {
  for (; d; d--)
    e(&a);
}
