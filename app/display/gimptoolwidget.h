/* GIMP - The GNU Image Manipulation Program
 * Copyright (C) 1995 Spencer Kimball and Peter Mattis
 *
 * gimptoolwidget.h
 * Copyright (C) 2017 Michael Natterer <mitch@gimp.org>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __GIMP_TOOL_WIDGET_H__
#define __GIMP_TOOL_WIDGET_H__


#include "core/gimpobject.h"


#define GIMP_TYPE_TOOL_WIDGET            (gimp_tool_widget_get_type ())
#define GIMP_TOOL_WIDGET(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_TOOL_WIDGET, GimpToolWidget))
#define GIMP_TOOL_WIDGET_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_TOOL_WIDGET, GimpToolWidgetClass))
#define GIMP_IS_TOOL_WIDGET(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_TOOL_WIDGET))
#define GIMP_IS_TOOL_WIDGET_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_TOOL_WIDGET))
#define GIMP_TOOL_WIDGET_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_TOOL_WIDGET, GimpToolWidgetClass))


typedef struct _GimpToolWidgetPrivate GimpToolWidgetPrivate;
typedef struct _GimpToolWidgetClass   GimpToolWidgetClass;

struct _GimpToolWidget
{
  GimpObject             parent_instance;

  GimpToolWidgetPrivate *private;
};

struct _GimpToolWidgetClass
{
  GimpObjectClass  parent_class;

  /*  signals  */
  void     (* changed)        (GimpToolWidget        *widget);

  /*  virtual functions  */
  gboolean (* button_press)    (GimpToolWidget        *widget,
                                const GimpCoords      *coords,
                                guint32                time,
                                GdkModifierType        state,
                                GimpButtonPressType    press_type);
  void     (* button_release)  (GimpToolWidget        *widget,
                                const GimpCoords      *coords,
                                guint32                time,
                                GdkModifierType        state,
                                GimpButtonReleaseType  release_type);
  void     (* motion)          (GimpToolWidget        *widget,
                                const GimpCoords      *coords,
                                guint32                time,
                                GdkModifierType        state);

  void     (* hover)           (GimpToolWidget        *widget,
                                const GimpCoords      *coords,
                                GdkModifierType        state,
                                gboolean               proximity);

  void     (* motion_modifier) (GimpToolWidget        *widget,
                                GdkModifierType        key,
                                gboolean               press,
                                GdkModifierType        state);
  void     (* hover_modifier)  (GimpToolWidget        *widget,
                                GdkModifierType        key,
                                gboolean               press,
                                GdkModifierType        state);

  gboolean (* get_cursor)      (GimpToolWidget        *widget,
                                const GimpCoords      *coords,
                                GdkModifierType        state,
                                GimpCursorType        *cursor,
                                GimpToolCursorType    *tool_cursor,
                                GimpCursorModifier    *cursor_modifier);
};


GType             gimp_tool_widget_get_type         (void) G_GNUC_CONST;

GimpCanvasItem  * gimp_tool_widget_get_item         (GimpToolWidget  *widget);

/*  for subclasses, to add and manage their items
 */
void              gimp_tool_widget_add_item         (GimpToolWidget  *widget,
                                                     GimpCanvasItem  *item);
void              gimp_tool_widget_remove_item      (GimpToolWidget  *widget,
                                                     GimpCanvasItem  *item);

GimpCanvasGroup * gimp_tool_widget_add_stroke_group (GimpToolWidget  *widget);
GimpCanvasGroup * gimp_tool_widget_add_fill_group   (GimpToolWidget  *widget);

void              gimp_tool_widget_push_group       (GimpToolWidget  *widget,
                                                     GimpCanvasGroup *group);
void              gimp_tool_widget_pop_group        (GimpToolWidget  *widget);

/*  convenience functions to add specific items
 */
GimpCanvasItem * gimp_tool_widget_add_line   (GimpToolWidget   *widget,
                                              gdouble           x1,
                                              gdouble           y1,
                                              gdouble           x2,
                                              gdouble           y2);
GimpCanvasItem * gimp_tool_widget_add_handle (GimpToolWidget   *widget,
                                              GimpHandleType    type,
                                              gdouble           x,
                                              gdouble           y,
                                              gint              width,
                                              gint              height,
                                              GimpHandleAnchor  anchor);

/*  for tools, to be called from the respective GimpTool method
 *  implementations
 */
gboolean   gimp_tool_widget_button_press    (GimpToolWidget        *widget,
                                             const GimpCoords      *coords,
                                             guint32                time,
                                             GdkModifierType        state,
                                             GimpButtonPressType    press_type);
void       gimp_tool_widget_button_release  (GimpToolWidget        *widget,
                                             const GimpCoords      *coords,
                                             guint32                time,
                                             GdkModifierType        state,
                                             GimpButtonReleaseType  release_type);
void       gimp_tool_widget_motion          (GimpToolWidget        *widget,
                                             const GimpCoords      *coords,
                                             guint32                time,
                                             GdkModifierType        state);

void       gimp_tool_widget_hover           (GimpToolWidget        *widget,
                                             const GimpCoords      *coords,
                                             GdkModifierType        state,
                                             gboolean               proximity);

void       gimp_tool_widget_motion_modifier (GimpToolWidget        *widget,
                                             GdkModifierType        key,
                                             gboolean               press,
                                             GdkModifierType        state);
void       gimp_tool_widget_hover_modifier  (GimpToolWidget        *widget,
                                             GdkModifierType        key,
                                             gboolean               press,
                                             GdkModifierType        state);

gboolean   gimp_tool_widget_get_cursor      (GimpToolWidget        *widget,
                                             const GimpCoords      *coords,
                                             GdkModifierType        state,
                                             GimpCursorType        *cursor,
                                             GimpToolCursorType    *tool_cursor,
                                             GimpCursorModifier    *cursor_modifier);


#endif /* __GIMP_TOOL_WIDGET_H__ */