/* exif-utils.c
 *
 * Copyright (c) 2001 Lutz Mueller <lutz@users.sourceforge.net>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful, 
 * but WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details. 
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA  02110-1301  USA.
 */

#include "exif-utils.h"
#include <config.h>

#include <libexif/exif-utils.h>

void
exif_array_set_byte_order (ExifFormat f, unsigned char *b, unsigned int n,
		ExifByteOrder o_orig, ExifByteOrder o_new)
{
	unsigned int j;
	unsigned int fs = exif_format_get_size (f);
	ExifShort s;
	ExifSShort ss;
	ExifLong l;
	ExifSLong sl;
	ExifFloat fl;
	ExifDouble d;
	ExifRational r;
	ExifSRational sr;

	if (!b || !n || !fs) return;

	switch (f) {
	case EXIF_FORMAT_SHORT:
		for (j = 0; j < n; j++) {
			s = exif_get_short (b + j * fs, o_orig);
			exif_set_short (b + j * fs, o_new, s);
		}
		break;
	case EXIF_FORMAT_SSHORT:
		for (j = 0; j < n; j++) {
			ss = exif_get_sshort (b + j * fs, o_orig);
			exif_set_sshort (b + j * fs, o_new, ss);
		}
		break;
	case EXIF_FORMAT_LONG:
		for (j = 0; j < n; j++) {
			l = exif_get_long (b + j * fs, o_orig);
			exif_set_long (b + j * fs, o_new, l);
		}
		break;
	case EXIF_FORMAT_RATIONAL:
		for (j = 0; j < n; j++) {
			r = exif_get_rational (b + j * fs, o_orig);
			exif_set_rational (b + j * fs, o_new, r);
		}
		break;
	case EXIF_FORMAT_SLONG:
		for (j = 0; j < n; j++) {
			sl = exif_get_slong (b + j * fs, o_orig);
			exif_set_slong (b + j * fs, o_new, sl);
		}
		break;
	case EXIF_FORMAT_SRATIONAL:
		for (j = 0; j < n; j++) {
			sr = exif_get_srational (b + j * fs, o_orig);
			exif_set_srational (b + j * fs, o_new, sr);
		}
		break;
	case EXIF_FORMAT_FLOAT:
		for (j = 0; j < n; j++) {
			fl = exif_get_float (b + j * fs, o_orig);
			exif_set_float (b + j * fs, o_new, fl);
		}
		break;
	case EXIF_FORMAT_DOUBLE:
		for (j = 0; j < n; j++) {
			d = exif_get_double (b + j * fs, o_orig);
			exif_set_double (b + j * fs, o_new, d);
		}
		break;
	case EXIF_FORMAT_UNDEFINED:
	case EXIF_FORMAT_BYTE:
	case EXIF_FORMAT_ASCII:
	default:
		/* Nothing here. */
		break;
	}
}

ExifSShort
exif_get_sshort (const unsigned char *buf, ExifByteOrder order)
{
	if (!buf) return 0;
        switch (order) {
        case EXIF_BYTE_ORDER_MOTOROLA:
                return (((unsigned int)buf[0] << 8) | buf[1]);
        case EXIF_BYTE_ORDER_INTEL:
                return (((unsigned int)buf[1] << 8) | buf[0]);
        }

	/* Won't be reached */
	return (0);
}

ExifShort
exif_get_short (const unsigned char *buf, ExifByteOrder order)
{
	return (exif_get_sshort (buf, order) & 0xffff);
}

void
exif_set_sshort (unsigned char *b, ExifByteOrder order, ExifSShort value)
{
	if (!b) return;
	switch (order) {
	case EXIF_BYTE_ORDER_MOTOROLA:
		b[0] = (unsigned char) (value >> 8);
		b[1] = (unsigned char) value;
		break;
	case EXIF_BYTE_ORDER_INTEL:
		b[0] = (unsigned char) value;
		b[1] = (unsigned char) (value >> 8);
		break;
	}
}

void
exif_set_short (unsigned char *b, ExifByteOrder order, ExifShort value)
{
	exif_set_sshort (b, order, value);
}

ExifSLong
exif_get_slong (const unsigned char *b, ExifByteOrder order)
{
	if (!b) return 0;
        switch (order) {
        case EXIF_BYTE_ORDER_MOTOROLA:
                return (((uint32_t)b[0] << 24) | ((uint32_t)b[1] << 16) | ((uint32_t)b[2] << 8) | (uint32_t)b[3]);
        case EXIF_BYTE_ORDER_INTEL:
                return (((uint32_t)b[3] << 24) | ((uint32_t)b[2] << 16) | ((uint32_t)b[1] << 8) | (uint32_t)b[0]);
        }

	/* Won't be reached */
	return (0);
}

void
exif_set_slong (unsigned char *b, ExifByteOrder order, ExifSLong value)
{
	if (!b) return;
	switch (order) {
	case EXIF_BYTE_ORDER_MOTOROLA:
		b[0] = (unsigned char) (value >> 24);
		b[1] = (unsigned char) (value >> 16);
		b[2] = (unsigned char) (value >> 8);
		b[3] = (unsigned char) value;
		break;
	case EXIF_BYTE_ORDER_INTEL:
		b[3] = (unsigned char) (value >> 24);
		b[2] = (unsigned char) (value >> 16);
		b[1] = (unsigned char) (value >> 8);
		b[0] = (unsigned char) value;
		break;
	}
}

ExifLong
exif_get_long (const unsigned char *buf, ExifByteOrder order)
{
        return (exif_get_slong (buf, order) & 0xffffffff);
}

void
exif_set_long (unsigned char *b, ExifByteOrder order, ExifLong value)
{
	exif_set_slong (b, order, value);
}

ExifFloat
exif_get_float (const unsigned char *buf, ExifByteOrder order)
{
	ExifFloat f;
	unsigned char *b = (unsigned char *) &f;

	if (!buf) return 0;
	switch (order) {
	case EXIF_BYTE_ORDER_MOTOROLA:
		b[0] = buf[0];
		b[1] = buf[1];
		b[2] = buf[2];
		b[3] = buf[3];
		break;
	case EXIF_BYTE_ORDER_INTEL:
		b[0] = buf[3];
		b[1] = buf[2];
		b[2] = buf[1];
		b[3] = buf[0];
		break;
	}

	return (f);
}

void
exif_set_float (unsigned char *buf, ExifByteOrder order, ExifFloat value)
{
	unsigned char *b = (unsigned char *) &value;

	if (!buf) return;
	switch (order) {
	case EXIF_BYTE_ORDER_MOTOROLA:
		buf[0] = b[0];
		buf[1] = b[1];
		buf[2] = b[2];
		buf[3] = b[3];
		break;
	case EXIF_BYTE_ORDER_INTEL:
		buf[0] = b[3];
		buf[1] = b[2];
		buf[2] = b[1];
		buf[3] = b[0];
		break;
	}
}

ExifDouble
exif_get_double (const unsigned char *buf, ExifByteOrder order)
{
	ExifDouble d;
	unsigned char *b = (unsigned char *) &d;

	if (!buf) return 0;
	switch (order) {
	case EXIF_BYTE_ORDER_MOTOROLA:
		b[0] = buf[0];
		b[1] = buf[1];
		b[2] = buf[2];
		b[3] = buf[3];
		b[4] = buf[4];
		b[5] = buf[5];
		b[6] = buf[6];
		b[7] = buf[7];
		break;
	case EXIF_BYTE_ORDER_INTEL:
		b[0] = buf[7];
		b[1] = buf[6];
		b[2] = buf[5];
		b[3] = buf[4];
		b[4] = buf[3];
		b[5] = buf[2];
		b[6] = buf[1];
		b[7] = buf[0];
		break;
	}

	return (d);
}

void
exif_set_double (unsigned char *buf, ExifByteOrder order, ExifDouble value)
{
	unsigned char *b = (unsigned char *) &value;

	if (!buf) return;
	switch (order) {
	case EXIF_BYTE_ORDER_MOTOROLA:
		buf[0] = b[0];
		buf[1] = b[1];
		buf[2] = b[2];
		buf[3] = b[3];
		buf[4] = b[4];
		buf[5] = b[5];
		buf[6] = b[6];
		buf[7] = b[7];
		break;
	case EXIF_BYTE_ORDER_INTEL:
		buf[0] = b[7];
		buf[1] = b[6];
		buf[2] = b[5];
		buf[3] = b[4];
		buf[4] = b[3];
		buf[5] = b[2];
		buf[6] = b[1];
		buf[7] = b[0];
		break;
	}
}

ExifSRational
exif_get_srational (const unsigned char *buf, ExifByteOrder order)
{
	ExifSRational r;

	r.numerator   = buf ? exif_get_slong (buf, order) : 0;
	r.denominator = buf ? exif_get_slong (buf + 4, order) : 0;

	return (r);
}

ExifRational
exif_get_rational (const unsigned char *buf, ExifByteOrder order)
{
	ExifRational r;

	r.numerator   = buf ? exif_get_long (buf, order) : 0;
	r.denominator = buf ? exif_get_long (buf + 4, order) : 0;

	return (r);
}

void
exif_set_rational (unsigned char *buf, ExifByteOrder order,
		   ExifRational value)
{
	if (!buf) return;
	exif_set_long (buf, order, value.numerator);
	exif_set_long (buf + 4, order, value.denominator);
}

void
exif_set_srational (unsigned char *buf, ExifByteOrder order,
		    ExifSRational value)
{
	if (!buf) return;
	exif_set_slong (buf, order, value.numerator);
	exif_set_slong (buf + 4, order, value.denominator);
}

/*! This function converts rather UCS-2LE than UTF-16 to UTF-8.
 * It should really be replaced by iconv().
 */
void
exif_convert_utf16_to_utf8 (char *out, const unsigned char *in, int maxlen)
{
	if (maxlen <= 0) {
		return;
	}
	for (;;) {
		ExifShort v = exif_get_short(in, EXIF_BYTE_ORDER_INTEL);
		if (!v)
			break;
		if (v < 0x80) {
			if (maxlen > 1) {
				*out++ = (char)v;
				maxlen--;
			} else {
				break;
			}
		} else if (v < 0x800) {
			if (maxlen > 2) {
				*out++ = ((v >> 6) & 0x1F) | 0xC0;
				*out++ = (v & 0x3F) | 0x80;
				maxlen -= 2;
			} else {
				break;
			}
		} else {
			if (maxlen > 3) {
				*out++ = ((v >> 12) & 0x0F) | 0xE0;
				*out++ = ((v >> 6) & 0x3F) | 0x80;
				*out++ = (v & 0x3F) | 0x80;
				maxlen -= 3;
			} else {
				break;
			}
		}
		in += 2;
	}
	*out = 0;
}
