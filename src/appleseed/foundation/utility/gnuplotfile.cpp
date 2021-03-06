
//
// This source file is part of appleseed.
// Visit http://appleseedhq.net/ for additional information and resources.
//
// This software is released under the MIT license.
//
// Copyright (c) 2014-2017 Francois Beaune, The appleseedhq Organization
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

// Interface header.
#include "gnuplotfile.h"

// appleseed.foundation headers.
#include "foundation/utility/foreach.h"

// Standard headers.
#include <cstddef>
#include <iostream>

using namespace std;

namespace foundation
{

//
// GnuplotFile class implementation.
//

GnuplotFile::GnuplotFile()
  : m_has_xrange(false)
  , m_has_yrange(false)
  , m_xrange(0.0, 0.0)
  , m_yrange(0.0, 0.0)
  , m_logscale_x(false)
  , m_logscale_y(false)
{
}

GnuplotFile& GnuplotFile::set_title(const string& title)
{
    m_title = title;
    return *this;
}

GnuplotFile& GnuplotFile::set_xlabel(const string& label)
{
    m_xlabel = label;
    return *this;
}

GnuplotFile& GnuplotFile::set_ylabel(const string& label)
{
    m_ylabel = label;
    return *this;
}

GnuplotFile& GnuplotFile::set_xrange(const double low, const double high)
{
    m_has_xrange = true;
    m_xrange = Vector2d(low, high);
    return *this;
}

GnuplotFile& GnuplotFile::set_yrange(const double low, const double high)
{
    m_has_yrange = true;
    m_yrange = Vector2d(low, high);
    return *this;
}

GnuplotFile& GnuplotFile::set_logscale_x()
{
    m_logscale_x = true;
    return *this;
}

GnuplotFile& GnuplotFile::set_logscale_y()
{
    m_logscale_y = true;
    return *this;
}

GnuplotFile::Plot& GnuplotFile::new_plot()
{
    m_plots.push_back(Plot());
    return m_plots.back();
}

bool GnuplotFile::write(const string& filepath) const
{
    ofstream file(filepath.c_str());

    if (!file.is_open())
        return false;

    if (!m_title.empty())
        file << "set title \"" << m_title << "\" noenhanced" << endl;
    else file << "unset title" << endl;

    if (!m_xlabel.empty())
        file << "set xlabel \"" << m_xlabel << "\" noenhanced" << endl;
    else file << "unset xlabel" << endl;

    if (!m_ylabel.empty())
        file << "set ylabel \"" << m_ylabel << "\" noenhanced" << endl;
    else file << "unset ylabel" << endl;

    if (m_has_xrange)
        file << "set xrange [" << m_xrange[0] << ":" << m_xrange[1] << "]" << endl;
    else file << "set autoscale x" << endl;

    if (m_has_yrange)
        file << "set yrange [" << m_yrange[0] << ":" << m_yrange[1] << "]" << endl;
    else file << "set autoscale y" << endl;

    if (m_logscale_x)
        file << "set logscale x" << endl;
    else file << "unset logscale x" << endl;

    if (m_logscale_y)
        file << "set logscale y" << endl;
    else file << "unset logscale y" << endl;

    if (!m_plots.empty())
    {
        file << "plot ";

        for (size_t i = 0; i < m_plots.size(); ++i)
        {
            if (i > 0)
                file << ", ";
            m_plots[i].write_decl(file);
        }

        file << endl;

        for (size_t i = 0; i < m_plots.size(); ++i)
            m_plots[i].write_points(file);
    }

    return file.good();
}


//
// GnuplotFile::Plot class implementation.
//

GnuplotFile::Plot& GnuplotFile::Plot::set_points(const vector<Vector2d>& points)
{
    m_points = points;
    return *this;
}

GnuplotFile::Plot& GnuplotFile::Plot::set_points(const vector<Vector2f>& points)
{
    const size_t n = points.size();

    m_points.resize(n);

    for (size_t i = 0; i < n; ++i)
        m_points[i] = Vector2d(points[i]);

    return *this;
}

GnuplotFile::Plot& GnuplotFile::Plot::set_title(const string& title)
{
    m_title = title;
    return *this;
}

GnuplotFile::Plot& GnuplotFile::Plot::set_color(const string& color)
{
    m_color = color;
    return *this;
}

GnuplotFile::Plot& GnuplotFile::Plot::set_style(const string& style)
{
    m_style = style;
    return *this;
}

GnuplotFile::Plot& GnuplotFile::Plot::set_smoothing(const string& smoothing)
{
    m_smoothing = smoothing;
    return *this;
}

void GnuplotFile::Plot::write_decl(ofstream& file) const
{
    file << "\"-\" with ";

    file << (m_style.empty() ? "lines" : m_style);

    if (!m_color.empty())
        file << " linecolor rgbcolor \"" << m_color << "\"";

    if (!m_smoothing.empty())
        file << " smooth " << m_smoothing;

    if (!m_title.empty())
        file << " title \"" << m_title << "\" noenhanced";
    else file << " notitle";
}

void GnuplotFile::Plot::write_points(ofstream& file) const
{
    for (const_each<vector<Vector2d>> i = m_points; i; ++i)
    {
        const Vector2d& p = *i;
        file << "    " << p[0] << " " << p[1] << endl;
    }

    file << "    e" << endl;
}

}   // namespace foundation
