/* mnote-apple-tag.h
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

#ifndef LIBEXIF_MNOTE_APPLE_TAG_H
#define LIBEXIF_MNOTE_APPLE_TAG_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

enum _MnoteAppleTag {
  MNOTE_APPLE_TAG_VERSION = 0x1,
  MNOTE_APPLE_TAG_AE_MATRIX = 0x2,
  MNOTE_APPLE_TAG_RUNTIME = 0x3,
  MNOTE_APPLE_TAG_AE_STABLE = 0x4,
  MNOTE_APPLE_TAG_AE_TARGET = 0x5,
  MNOTE_APPLE_TAG_AE_AVERAGE = 0x6,
  MNOTE_APPLE_TAG_AF_STABLE = 0x7,
  MNOTE_APPLE_TAG_ACCELERATION_VECTOR = 0x8,
  MNOTE_APPLE_TAG_HDR = 0xA,
  MNOTE_APPLE_TAG_BURST_UUID = 0xB,
  MNOTE_APPLE_TAG_FOCUS_DISTANCE_RANGE = 0xC,
  MNOTE_APPLE_TAG_OIS_MODE = 0xF,
  MNOTE_APPLE_TAG_MEDIA_GROUP_UUID = 0x11,
  MNOTE_APPLE_TAG_IMAGE_CAPTURE_TYPE = 0x14,
  MNOTE_APPLE_TAG_IMAGE_UNIQUE_ID = 0x15,
  MNOTE_APPLE_TAG_LIVE_PHOTO_VIDEO_INDEX = 0x17,
  MNOTE_APPLE_TAG_IMAGE_PROCESSING_FLAGS = 0x19,
  MNOTE_APPLE_TAG_QUALITY_HINT = 0x1A,
  MNOTE_APPLE_TAG_LUMINANCE_NOISE_AMPLITUDE = 0x1D,
  MNOTE_APPLE_TAG_IMAGE_CAPTURE_REQUEST_ID = 0x20,
  MNOTE_APPLE_TAG_HDR_HEADROOM = 0x21,
  MNOTE_APPLE_TAG_SCENE_FLAGS = 0x25,
  MNOTE_APPLE_TAG_SIGNAL_TO_NOISE_RATIO_TYPE = 0x26,
  MNOTE_APPLE_TAG_SIGNAL_TO_NOISE_RATIO = 0x27,
  MNOTE_APPLE_TAG_FOCUS_POSITION = 0x2F,
  MNOTE_APPLE_TAG_HDR_GAIN = 0x30,
  MNOTE_APPLE_TAG_AF_MEASURED_DEPTH = 0x38,
  MNOTE_APPLE_TAG_AF_CONFIDENCE = 0x3D,
  MNOTE_APPLE_TAG_COLOR_CORRECTION_MATRIX = 0x3E,
  MNOTE_APPLE_TAG_GREEN_GHOST_MITIGATION_STATUS = 0x3F,
  MNOTE_APPLE_TAG_SEMANTIC_STYLE = 0x40,
  MNOTE_APPLE_TAG_SEMANTIC_STYLE_RENDERING_VERSION = 0x41,
  MNOTE_APPLE_TAG_SEMANTIC_STYLE_PRESET = 0x42,
  MNOTE_APPLE_TAG_FRONT_FACING_CAMERA = 0x45,
};
typedef enum _MnoteAppleTag MnoteAppleTag;

const char *mnote_apple_tag_get_name(MnoteAppleTag);
const char *mnote_apple_tag_get_title(MnoteAppleTag);
const char *mnote_apple_tag_get_description(MnoteAppleTag);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !defined(LIBEXIF_MNOTE_APPLE_TAG_H) */
