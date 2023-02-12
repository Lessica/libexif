/* mnote-apple-tag.c:
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

#include <config.h>
#include "mnote-apple-tag.h"

#include <libexif/i18n.h>
#include <libexif/exif-utils.h>

#include <stdlib.h>

static const struct {
    MnoteAppleTag tag;
    const char *name;
    const char *title;
    const char *description;
} table[] = {
#ifndef NO_VERBOSE_TAG_STRINGS
    {MNOTE_APPLE_TAG_VERSION, "MakerNoteVersion", N_("MakerNote Version"), ""},
    {MNOTE_APPLE_TAG_AE_MATRIX, "AEMatrix", N_("AE Matrix"), ""},
    {MNOTE_APPLE_TAG_RUNTIME, "RunTime", N_("Runtime"), ""},
    {MNOTE_APPLE_TAG_AE_STABLE, "AEStable", N_("AE Stable"), ""},
    {MNOTE_APPLE_TAG_AE_TARGET, "AETarget", N_("AE Target"), ""},
    {MNOTE_APPLE_TAG_AE_AVERAGE, "AEAverage", N_("AE Average"), ""},
    {MNOTE_APPLE_TAG_AF_STABLE, "AFStable", N_("AF Stable"), ""},
    {MNOTE_APPLE_TAG_ACCELERATION_VECTOR, "AccelerationVector", N_("Acceleration Vector"), N_("XYZ coordinates of the acceleration vector in units of g. As viewed from the front of the phone, positive X is toward the left side, positive Y is toward the bottom, and positive Z points into the face of the phone")},
    {MNOTE_APPLE_TAG_HDR, "HDRImageType", N_("HDR Image Type"), N_("3 = HDR, 4 = Original")},
    {MNOTE_APPLE_TAG_BURST_UUID, "BurstUUID", N_("Burst UUID"), N_("unique ID for all images in a burst")},
    {MNOTE_APPLE_TAG_FOCUS_DISTANCE_RANGE, "FocusDistanceRange", N_("Focus Distance Range"), ""},
    {MNOTE_APPLE_TAG_OIS_MODE, "OISMode", N_("OIS Mode"), ""},
    {MNOTE_APPLE_TAG_MEDIA_GROUP_UUID, "MediaGroupUUID", N_("Media Group UUID"), ""},
    {MNOTE_APPLE_TAG_IMAGE_CAPTURE_TYPE, "ImageCaptureType", N_("Image Capture Type"), ""},
    {MNOTE_APPLE_TAG_IMAGE_UNIQUE_ID, "ImageUniqueID", N_("Image Unique ID"), ""},
    {MNOTE_APPLE_TAG_LIVE_PHOTO_VIDEO_INDEX, "LivePhotoVideoIndex", N_("Live Photo Video Index"), N_("divide by RunTimeScale to get time in seconds")},
    {MNOTE_APPLE_TAG_IMAGE_PROCESSING_FLAGS, "ImageProcessingFlags", N_("Image Processing Flags"), ""},
    {MNOTE_APPLE_TAG_QUALITY_HINT, "QualityHint", N_("Quality Hint"), ""},
    {MNOTE_APPLE_TAG_LUMINANCE_NOISE_AMPLITUDE, "LuminanceNoiseAmplitude", N_("Luminance Noise Amplitude"), ""},
    {MNOTE_APPLE_TAG_IMAGE_CAPTURE_REQUEST_ID, "ImageCaptureRequestID", N_("Image Capture Request ID"), ""},
    {MNOTE_APPLE_TAG_HDR_HEADROOM, "HDRHeadroom", N_("HDR Headroom"), ""},
    {MNOTE_APPLE_TAG_SCENE_FLAGS, "SceneFlags", N_("Scene Flags"), ""},
    {MNOTE_APPLE_TAG_SIGNAL_TO_NOISE_RATIO_TYPE, "SignalToNoiseRatioType", N_("Signal To Noise Ratio Type"), ""},
    {MNOTE_APPLE_TAG_SIGNAL_TO_NOISE_RATIO, "SignalToNoiseRatio", N_("Signal To Noise Ratio"), ""},
    {MNOTE_APPLE_TAG_FOCUS_POSITION, "FocusPosition", N_("Focus Position"), ""},
    {MNOTE_APPLE_TAG_HDR_GAIN, "HDRGain", N_("HDR Gain"), ""},
    {MNOTE_APPLE_TAG_AF_MEASURED_DEPTH, "AFMeasuredDepth", N_("AF Measured Depth"), N_("from the time-of-flight-assisted auto-focus estimator")},
    {MNOTE_APPLE_TAG_AF_CONFIDENCE, "AFConfidence", N_("AF Confidence"), ""},
    {MNOTE_APPLE_TAG_COLOR_CORRECTION_MATRIX, "ColorCorrectionMatrix", N_("Color Correction Matrix"), ""},
    {MNOTE_APPLE_TAG_GREEN_GHOST_MITIGATION_STATUS, "GreenGhostMitigationStatus", N_("Green Ghost Mitigation Status"), ""},
    {MNOTE_APPLE_TAG_SEMANTIC_STYLE, "SemanticStyle", N_("Semantic Style"), ""},
    {MNOTE_APPLE_TAG_SEMANTIC_STYLE_RENDERING_VERSION, "SemanticStyleRenderingVersion", N_("Semantic Style Rendering Version"), ""},
    {MNOTE_APPLE_TAG_SEMANTIC_STYLE_PRESET, "SemanticStylePreset", N_("Semantic Style Preset"), ""},
    {MNOTE_APPLE_TAG_FRONT_FACING_CAMERA, "FrontFacingCamera", N_("Front Facing Camera"), N_("0 = No, 1 = Yes")},
#endif
    {0, NULL, NULL, NULL}
};

const char *
mnote_apple_tag_get_name(MnoteAppleTag t) {
    unsigned int i;

    for (i = 0; i < sizeof (table) / sizeof (table[0]); i++) {
        if (table[i].tag == t) {
            return table[i].name;
        }
    }

    return NULL;
}

const char *
mnote_apple_tag_get_title(MnoteAppleTag t) {
    unsigned int i;

    (void) bindtextdomain(GETTEXT_PACKAGE, LOCALEDIR);
    for (i = 0; i < sizeof (table) / sizeof (table[0]); i++) {
        if (table[i].tag == t) {
            return _(table[i].title);
        }
    }

    return NULL;
}

const char *
mnote_apple_tag_get_description(MnoteAppleTag t) {
    unsigned int i;

    for (i = 0; i < sizeof (table) / sizeof (table[0]); i++) {
        if (table[i].tag == t) {
            if (!table[i].description || !*table[i].description) {
                return "";
            }
            (void) bindtextdomain(GETTEXT_PACKAGE, LOCALEDIR);
            return _(table[i].description);
        }
    }

    return NULL;
}
