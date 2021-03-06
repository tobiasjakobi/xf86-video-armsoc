/*
 * Copyright © 2013 ARM Limited.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#ifndef DRMMODE_DRIVER_H
#define DRMMODE_DRIVER_H

#include <stdint.h>

#include "xorg-server.h"
#include "xf86Crtc.h"
#include "armsoc_dumb.h"

enum hwcursor_api {
	HWCURSOR_API_PLANE = 0,
	HWCURSOR_API_STANDARD = 1,
	HWCURSOR_API_NONE = 2
};

struct drmmode_interface {
	/* Boolean value indicating whether DRM page flip events should
	 * be requested and waited for during DRM_IOCTL_MODE_PAGE_FLIP.
	 */
	int use_page_flip_events;

	/* Boolean value indicating whether to support early display
	 * feature. This allows the next back buffer to be obtained while
	 * the previous is being flipped.
	 */
	int use_early_display;

	/* The cursor width */
	int cursor_width;

	/* The cursor height */
	int cursor_height;

	/* A padding column of pixels of this width is added to either
	 * side of the image
	 */
	int cursor_padding;

	/* Specifies the hardware cursor api used by the DRM :
	 *   HWCURSOR_API_PLANE    - Use planes.
	 *   HWCURSOR_API_STANDARD - Use the standard API : drmModeSetCursor() & drmModeMoveCursor().
	 *   HWCURSOR_API_NONE     - No hardware cursor - use a software cursor.
	 */
	enum hwcursor_api cursor_api;

	/* Boolean value indicating whether the DRM supports
	 * vblank timestamp query
	 */
	int vblank_query_supported;

	/* (Mandatory) Create new gem object
	 *
	 * A driver specific ioctl() is usually needed to create GEM objects
	 * with particular features such as contiguous memory, uncached, etc...
	 *
	 * @param       fd             DRM device file descriptor
	 * @param       create_gem     generic GEM description
	 * @return 0 on success, non-zero on failure
	 */
	int (*create_custom_gem)(int fd, struct armsoc_create_gem *create_gem);
};

struct drmmode_interface *drmmode_interface_get_implementation(int drm_fd);

#endif
