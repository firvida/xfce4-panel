/* $Id$ */
/*
 * Copyright (c) 2007 Nick Schermer <nick@xfce.org>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc., 59 Temple
 * Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef __CLOCK_ANALOG_H__
#define __CLOCK_ANALOG_H__

G_BEGIN_DECLS

typedef struct _XfceClockAnalogClass XfceClockAnalogClass;
typedef struct _XfceClockAnalog      XfceClockAnalog;

#define XFCE_TYPE_CLOCK_ANALOG            (xfce_clock_analog_get_type ())
#define XFCE_CLOCK_ANALOG(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), XFCE_TYPE_CLOCK_ANALOG, XfceClockAnalog))
#define XFCE_CLOCK_ANALOG_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), XFCE_TYPE_CLOCK_ANALOG, XfceClockAnalogClass))
#define XFCE_IS_CLOCK_ANALOG(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), XFCE_TYPE_CLOCK_ANALOG))
#define XFCE_IS_CLOCK_ANALOG_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), XFCE_TYPE_CLOCK_ANALOG))
#define XFCE_CLOCK_ANALOG_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), XFCE_TYPE_CLOCK_ANALOG, XfceClockAnalogClass))

GType      xfce_clock_analog_get_type      (void) G_GNUC_CONST  G_GNUC_INTERNAL;

void       xfce_clock_analog_register_type (XfcePanelModule *panel_module) G_GNUC_INTERNAL;

GtkWidget *xfce_clock_analog_new           (void) G_GNUC_MALLOC G_GNUC_INTERNAL;

gboolean   xfce_clock_analog_update        (gpointer user_data) G_GNUC_INTERNAL;

G_END_DECLS

#endif /* !__CLOCK_ANALOG_H__ */
