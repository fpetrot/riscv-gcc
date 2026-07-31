/* Implement the 128bit modifiers in printf format functions.
   Copyright (C) 2003-2026 Free Software Foundation, Inc.
   Written by Julien THILLARD <julien.thillard38@gmail.com>.

This file is part of the libiberty library.  This library is free
software; you can redistribute it and/or modify it under the
terms of the GNU General Public License as published by the
Free Software Foundation; either version 2, or (at your option)
any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with GNU CC; see the file COPYING.  If not, write to
the Free Software Foundation, 51 Franklin Street - Fifth Floor, Boston, MA 02110-1301, USA.

As a special exception, if you link this library with files
compiled with a GNU compiler to produce an executable, this does not cause
the resulting executable to be covered by the GNU General Public License.
This exception does not however invalidate any other reasons why
the executable file might be covered by the GNU General Public License. */

#include <printf.h>
#include <stdio.h>

static int pa_int128;
static int pa_uint128;

static int
printf_uint128_hex (FILE *stream, const struct printf_info *info,
		    const void *const *args)
{
  unsigned __int128 val = **(const unsigned __int128 *const *) args[0];
  char buf[33];
  int i = 32;
  buf[32] = '\0';

  const char *prefix = "";
  int prefix_len = 0;

  if (val == 0)
    {
      buf[--i] = '0';
    }
  else
    {
      while (val > 0 && i > 0)
	{
	  buf[--i] = "0123456789abcdef"[val & 0xf];
	  val >>= 4;
	}
      if (info->alt)
	prefix = "0x", prefix_len = 2;
    }

  int len = 32 - i + prefix_len;
  int written = 0;

  /* Left padding */
  if (!info->left && info->width > len)
    {
      if (info->pad == '0')
	{
	  written += fputs (prefix, stream);
	  prefix = "";
	  prefix_len = 0;
	  for (int p = len; p < info->width; p++)
	    written += fputc ('0', stream);
	}
      else
	{
	  for (int p = len; p < info->width; p++)
	    written += fputc (' ', stream);
	}
    }

  written += fputs (prefix, stream);
  written += fputs (buf + i, stream);

  /* Right padding */
  if (info->left && info->width > len)
    for (int p = len; p < info->width; p++)
      written += fputc (' ', stream);

  return written;
}

static int
printf_uint128_octal (FILE *stream, const struct printf_info *info,
		      const void *const *args)
{
  unsigned __int128 val = **(const unsigned __int128 *const *) args[0];
  char buf[43];
  int i = 42;
  buf[42] = '\0';

  const char *prefix = "";
  int prefix_len = 0;

  if (val == 0)
    {
      if (info->alt)
	prefix = "0o", prefix_len = 2;
      buf[--i] = '0';
    }
  else
    {
      while (val > 0 && i > 0)
	{
	  buf[--i] = "01234567"[val & 0x7];
	  val >>= 3;
	}
      if (info->alt)
	prefix = "0o", prefix_len = 2;
    }

  int len = 42 - i + prefix_len;
  int written = 0;

  /* Left padding */
  if (!info->left && info->width > len)
    {
      if (info->pad == '0')
	{
	  written += fputs (prefix, stream);
	  prefix = "";
	  prefix_len = 0;
	  for (int p = len; p < info->width; p++)
	    written += fputc ('0', stream);
	}
      else
	{
	  for (int p = len; p < info->width; p++)
	    written += fputc (' ', stream);
	}
    }

  written += fputs (prefix, stream);
  written += fputs (buf + i, stream);

  /* Right padding */
  if (info->left && info->width > len)
    for (int p = len; p < info->width; p++)
      written += fputc (' ', stream);

  return written;
}

static int
printf_uint128_decimal (FILE *stream, const struct printf_info *info,
			const void *const *args)
{
  unsigned __int128 val = **(const unsigned __int128 *const *) args[0];
  char buf[40];
  int i = 39;
  buf[39] = '\0';

  if (val == 0)
    buf[--i] = '0';
  else
    while (val > 0 && i > 0)
      {
	buf[--i] = '0' + val % 10;
	val /= 10;
      }

  int len = 39 - i;
  int written = 0;

  /* Left padding */
  if (!info->left && info->width > len)
    for (int p = len; p < info->width; p++)
      written += fputc (info->pad, stream);

  written += fputs (buf + i, stream);

  /* Right padding */
  if (info->left && info->width > len)
    for (int p = len; p < info->width; p++)
      written += fputc (' ', stream);

  return written;
}

static int
printf_int128_decimal (FILE *stream, const struct printf_info *info,
		       const void *const *args)
{
  __int128 val = **(const __int128 *const *) args[0];
  int len = 39;

  if (val < 0)
    {
      fputc ('-', stream);
      val = -val;
      len--;
    }

  char buf[41];
  int i = 40;
  buf[40] = '\0';

  if (val == 0)
    buf[--i] = '0';
  else
    while (val > 0 && i > 0)
      {
	buf[--i] = '0' + val % 10;
	val /= 10;
      }

  len -= i;
  int written = 0;

  /* Left padding */
  if (!info->left && info->width > len)
    for (int p = len; p < info->width; p++)
      written += fputc (info->pad, stream);

  written += fputs (buf + i, stream);

  /* Right padding */
  if (info->left && info->width > len)
    for (int p = len; p < info->width; p++)
      written += fputc (' ', stream);

  return written;
}

static void
printf_int128_va (void *mem, va_list *ap)
{
  *(__int128 *) mem = va_arg (*ap, __int128);
}

static void
printf_uint128_va (void *mem, va_list *ap)
{
  *(unsigned __int128 *) mem = va_arg (*ap, unsigned __int128);
}

static int
printf_int128_arginfo (const struct printf_info *info, size_t n, int *argtypes,
		       int *size)
{
  if (n > 0)
    {
      argtypes[0] = pa_int128;
      size[0] = sizeof (__int128);
    }
  return 1;
}

static int
printf_uint128_arginfo (const struct printf_info *info, size_t n,
			int *argtypes, int *size)
{
  if (n > 0)
    {
      argtypes[0] = pa_uint128;
      size[0] = sizeof (unsigned __int128);
    }
  return 1;
}

__attribute__ ((constructor)) void
init_printf_uint128 (void)
{
  pa_int128 = register_printf_type (printf_int128_va);
  pa_uint128 = register_printf_type (printf_uint128_va);

  register_printf_specifier ('Y', printf_int128_decimal,
			     printf_int128_arginfo);
  register_printf_specifier ('y', printf_uint128_octal,
			     printf_uint128_arginfo);
  register_printf_specifier ('Q', printf_uint128_decimal,
			     printf_uint128_arginfo);
  register_printf_specifier ('W', printf_uint128_hex, printf_uint128_arginfo);
}
