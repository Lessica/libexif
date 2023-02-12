/* mnote-apple-entry.c
 *
 * Copyright (c) 2018 zhanwang-sky <zhanwang_sky@163.com>
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

#include "mnote-apple-entry.h"
#include "mnote-apple-tag.h"
#include <config.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libexif/exif-entry.h>
#include <libexif/exif-format.h>
#include <libexif/exif-utils.h>
#include <libexif/i18n.h>

char *mnote_apple_entry_get_value(MnoteAppleEntry *entry, char *v,
                                  unsigned int maxlen) {
  ExifLong vl;
  ExifSLong vsl;
  ExifShort vs;
  ExifSShort vss;
  ExifRational vr;
  ExifSRational vsr;
  size_t size;
  unsigned char *data;

  if (!entry || entry->components < 1)
    return NULL;

  memset(v, 0, maxlen);
  maxlen--;

  size = entry->size;
  data = entry->data;
  switch (entry->tag) {
  case MNOTE_APPLE_TAG_VERSION:
  case MNOTE_APPLE_TAG_AE_STABLE:
  case MNOTE_APPLE_TAG_AE_TARGET:
  case MNOTE_APPLE_TAG_AE_AVERAGE:
  case MNOTE_APPLE_TAG_AF_STABLE:
  case MNOTE_APPLE_TAG_HDR:
  case MNOTE_APPLE_TAG_OIS_MODE:
  case MNOTE_APPLE_TAG_IMAGE_CAPTURE_TYPE:
  case MNOTE_APPLE_TAG_IMAGE_PROCESSING_FLAGS:
  case MNOTE_APPLE_TAG_SCENE_FLAGS:
  case MNOTE_APPLE_TAG_SIGNAL_TO_NOISE_RATIO_TYPE:
  case MNOTE_APPLE_TAG_FOCUS_POSITION:
  case MNOTE_APPLE_TAG_AF_MEASURED_DEPTH:
  case MNOTE_APPLE_TAG_AF_CONFIDENCE:
  case MNOTE_APPLE_TAG_GREEN_GHOST_MITIGATION_STATUS:
  case MNOTE_APPLE_TAG_FRONT_FACING_CAMERA:
    if (entry->format != EXIF_FORMAT_SLONG)
      return NULL;
    if (size < sizeof(ExifSLong))
      return NULL;
    if (entry->components != 1)
      return NULL;
    vsl = exif_get_slong(data, entry->order);
    snprintf(v, maxlen, "%d", vsl);
    break;
  case MNOTE_APPLE_TAG_IMAGE_CAPTURE_REQUEST_ID:
  case MNOTE_APPLE_TAG_QUALITY_HINT:
  case MNOTE_APPLE_TAG_IMAGE_UNIQUE_ID:
  case MNOTE_APPLE_TAG_BURST_UUID:
  case MNOTE_APPLE_TAG_MEDIA_GROUP_UUID:
    if (entry->format != EXIF_FORMAT_ASCII)
      return NULL;
    strncpy(v, (char *)data, MIN(maxlen - 1, size));
    v[MIN(maxlen - 1, size)] = 0;
    break;
  default:
    switch (entry->format) {
    case EXIF_FORMAT_ASCII:
      strncpy(v, (char *)data, MIN(maxlen, size));
      break;
    case EXIF_FORMAT_SHORT: {
      size_t i, len = 0;
      for (i = 0; i < entry->components; i++) {
        if (size < sizeof(ExifShort))
          break;
        if (len > maxlen)
          break;
        vs = exif_get_short(data, entry->order);
        if (i == entry->components - 1)
          snprintf(v + len, maxlen - len, "%hu", vs);
        else
          snprintf(v + len, maxlen - len, "%hu ", vs);
        len = strlen(v);
        data += sizeof(ExifShort);
        size -= sizeof(ExifShort);
      }
    } break;
    case EXIF_FORMAT_SSHORT: {
      size_t i, len = 0;
      for (i = 0; i < entry->components; i++) {
        if (size < sizeof(ExifSShort))
          break;
        if (len > maxlen)
          break;
        vss = exif_get_sshort(data, entry->order);
        if (i == entry->components - 1)
          snprintf(v + len, maxlen - len, "%hi", vss);
        else
          snprintf(v + len, maxlen - len, "%hi ", vss);
        len = strlen(v);
        data += sizeof(ExifSShort);
        size -= sizeof(ExifSShort);
      }
    } break;
    case EXIF_FORMAT_LONG: {
      size_t i, len = 0;
      for (i = 0; i < entry->components; i++) {
        if (size < sizeof(ExifLong))
          break;
        if (len > maxlen)
          break;
        vl = exif_get_long(data, entry->order);
        if (i == entry->components - 1)
          snprintf(v + len, maxlen - len, "%lu", (long unsigned)vl);
        else
          snprintf(v + len, maxlen - len, "%lu ", (long unsigned)vl);
        len = strlen(v);
        data += sizeof(ExifLong);
        size -= sizeof(ExifLong);
      }
    } break;
    case EXIF_FORMAT_SLONG: {
      size_t i, len = 0;
      for (i = 0; i < entry->components; i++) {
        if (size < sizeof(ExifSLong))
          break;
        if (len > maxlen)
          break;
        vsl = exif_get_slong(data, entry->order);
        if (i == entry->components - 1)
          snprintf(v + len, maxlen - len, "%li", (long int)vsl);
        else
          snprintf(v + len, maxlen - len, "%li ", (long int)vsl);
        len = strlen(v);
        data += sizeof(ExifSLong);
        size -= sizeof(ExifSLong);
      }
    } break;
    case EXIF_FORMAT_FLOAT: {
      size_t i, len = 0;
      for (i = 0; i < entry->components; i++) {
        if (size < sizeof(float))
          break;
        if (len > maxlen)
          break;
        if (i == entry->components - 1)
          snprintf(v + len, maxlen - len, "%f", exif_get_float(data, entry->order));
        else
          snprintf(v + len, maxlen - len, "%f ", exif_get_float(data, entry->order));
        len = strlen(v);
        data += sizeof(float);
        size -= sizeof(float);
      }
    } break;
    case EXIF_FORMAT_DOUBLE: {
      size_t i, len = 0;
      for (i = 0; i < entry->components; i++) {
        if (size < sizeof(double))
          break;
        if (len > maxlen)
          break;
        if (i == entry->components - 1)
          snprintf(v + len, maxlen - len, "%f", exif_get_double(data, entry->order));
        else
          snprintf(v + len, maxlen - len, "%f ", exif_get_double(data, entry->order));
        len = strlen(v);
        data += sizeof(double);
        size -= sizeof(double);
      }
    } break;
    case EXIF_FORMAT_RATIONAL: {
      size_t i, len = 0;
      for (i = 0; i < entry->components; i++) {
        size_t tsize = exif_format_get_size(EXIF_FORMAT_RATIONAL);
        if (size < tsize)
          break;
        if (len > maxlen)
          break;
        vr = exif_get_rational(data, entry->order);
        if (!vr.denominator)
          break;
        if (i == entry->components - 1)
          snprintf(v + len, maxlen - len, "%f", (double)vr.numerator / vr.denominator);
        else
          snprintf(v + len, maxlen - len, "%f ", (double)vr.numerator / vr.denominator);
        len = strlen(v);
        data += tsize;
        size -= tsize;
      }
    } break;
    case EXIF_FORMAT_SRATIONAL: {
      size_t i, len = 0;
      for (i = 0; i < entry->components; i++) {
        size_t tsize = exif_format_get_size(EXIF_FORMAT_SRATIONAL);
        if (size < tsize)
          break;
        if (len > maxlen)
          break;
        vsr = exif_get_srational(data, entry->order);
        if (!vsr.denominator)
          break;
        if (i == entry->components - 1)
          snprintf(v + len, maxlen - len, "%f", (double)vsr.numerator / vsr.denominator);
        else
          snprintf(v + len, maxlen - len, "%f ", (double)vsr.numerator / vsr.denominator);
        len = strlen(v);
        data += tsize;
        size -= tsize;
      }
    } break;
    case EXIF_FORMAT_UNDEFINED:
    default:
      snprintf(v, maxlen, _("%i bytes unknown data"), entry->size);
      break;
    }
    break;
  }

  return v;
}
