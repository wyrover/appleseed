
//
// This source file is part of appleseed.
// Visit http://appleseedhq.net/ for additional information and resources.
//
// This software is released under the MIT license.
//
// Copyright (c) 2015-2017 Francois Beaune, The appleseedhq Organization
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#ifndef APPLESEED_STUDIO_MAINWINDOW_RENDERING_PIXELCOLORTRACKER_H
#define APPLESEED_STUDIO_MAINWINDOW_RENDERING_PIXELCOLORTRACKER_H

// appleseed.foundation headers.
#include "foundation/platform/compiler.h"

// Qt headers.
#include <QObject>

// Forward declarations.
namespace appleseed { namespace studio { class MouseCoordinatesTracker; } }
namespace renderer  { class Project; }
class QEvent;
class QLabel;
class QPoint;
class QWidget;

namespace appleseed {
namespace studio {

class PixelColorTracker
  : public QObject
{
    Q_OBJECT

  public:
    PixelColorTracker(
        QWidget*                            widget,
        QLabel*                             r_label,
        QLabel*                             g_label,
        QLabel*                             b_label,
        QLabel*                             a_label,
        const MouseCoordinatesTracker&      mouse_tracker,
        const renderer::Project&            project);

    ~PixelColorTracker();

    void set_enabled(const bool enabled);

  private:
    QWidget*                                m_widget;
    QLabel*                                 m_r_label;
    QLabel*                                 m_g_label;
    QLabel*                                 m_b_label;
    QLabel*                                 m_a_label;
    const MouseCoordinatesTracker&          m_mouse_tracker;
    const renderer::Project&                m_project;
    bool                                    m_enabled;

    virtual bool eventFilter(QObject* object, QEvent* event) override;

    void clear_rgba_labels() const;
    void set_rgba_labels(const QPoint& point) const;
};

}       // namespace studio
}       // namespace appleseed

#endif  // !APPLESEED_STUDIO_MAINWINDOW_RENDERING_PIXELCOLORTRACKER_H
