/* { dg-do compile } */

void foo (void);

#if __riscv_xlen == 128
__extension__ typedef unsigned long long size_t;
#else
typedef unsigned long size_t;
#endif

__attribute__((target("arch=+zbb")))
void*
memcpy (void *d, const void *s, size_t n)
{
  (void) s;
  (void) n;
  return d;
}
__attribute__((target("arch=+zbb"))) void fun0(void) {}
__attribute__((target("arch=+zbb"))) void fun1(void) {}
__attribute__((target("arch=+zbb"))) void fun2(void) {}
__attribute__((target("arch=+zbb"))) void fun3(void) {}
__attribute__((target("arch=+zbb"))) void fun4(void) {}
__attribute__((target("arch=+zbb"))) void fun5(void) {}
__attribute__((target("arch=+zbb"))) void fun6(void) {}
__attribute__((target("arch=+zbb"))) void fun7(void) {}
__attribute__((target("arch=+zbb"))) void fun8(void) {}
__attribute__((target("arch=+zbb"))) void fun9(void) {}
__attribute__((target("arch=+zbb"))) void fun10(void) {}
__attribute__((target("arch=+zbb"))) void fun11(void) {}
__attribute__((target("arch=+zbb"))) void fun12(void) {}
