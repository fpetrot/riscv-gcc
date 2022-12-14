/* { dg-do assemble { target aarch64_asm_sve_ok } } */
/* { dg-options "-O2 -msve-vector-bits=2048 -save-temps" } */

#include <stdint.h>

#define TEST_OP(TYPE) \
  TYPE \
  test##_##TYPE##_reg (TYPE a, TYPE b, TYPE c, TYPE d) \
  { \
    return d == 0 ? a + b * c : c; \
  }

#define TEST_TYPE(TYPE, SIZE) \
  typedef TYPE TYPE##SIZE __attribute__((vector_size(SIZE))); \
  TEST_OP (TYPE##SIZE)

TEST_TYPE (uint8_t, 32)

TEST_TYPE (uint8_t, 64)
TEST_TYPE (uint16_t, 64)

TEST_TYPE (uint8_t, 128)
TEST_TYPE (uint16_t, 128)
TEST_TYPE (uint32_t, 128)

/* { dg-final { scan-assembler {\tld1b\t(z[0-9]+)\.h, p[0-7]/z, \[x2\][^L]*\tmad\t\1\.b,} } } */
/* { dg-final { scan-assembler {\tld1b\t(z[0-9]+)\.s, p[0-7]/z, \[x2\][^L]*\tmad\t\1\.b,} } } */
/* { dg-final { scan-assembler {\tld1b\t(z[0-9]+)\.d, p[0-7]/z, \[x2\][^L]*\tmad\t\1\.b,} } } */
/* { dg-final { scan-assembler {\tld1h\t(z[0-9]+)\.s, p[0-7]/z, \[x2\][^L]*\tmad\t\1\.h,} } } */
/* { dg-final { scan-assembler {\tld1h\t(z[0-9]+)\.d, p[0-7]/z, \[x2\][^L]*\tmad\t\1\.h,} } } */
/* { dg-final { scan-assembler {\tld1w\t(z[0-9]+)\.d, p[0-7]/z, \[x2\][^L]*\tmad\t\1\.s,} } } */

/* { dg-final { scan-assembler-not {\tsel\t} } } */
