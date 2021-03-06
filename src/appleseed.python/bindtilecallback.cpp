
//
// This source file is part of appleseed.
// Visit http://appleseedhq.net/ for additional information and resources.
//
// This software is released under the MIT license.
//
// Copyright (c) 2012-2013 Esteban Tovagliari, Jupiter Jazz Limited
// Copyright (c) 2014-2017 Esteban Tovagliari, The appleseedhq Organization
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

// appleseed.python headers.
#include "gillocks.h"

// appleseed.renderer headers.
#include "renderer/api/frame.h"
#include "renderer/kernel/rendering/itilecallback.h"

// appleseed.foundation headers.
#include "foundation/platform/compiler.h"
#include "foundation/platform/python.h"

namespace bpy = boost::python;
using namespace foundation;
using namespace renderer;

namespace
{
    class ITileCallbackWrapper
      : public ITileCallback
      , public bpy::wrapper<ITileCallback>
    {
      public:
        virtual void release() override
        {
            delete this;
        }

        virtual void on_tiled_frame_begin(const Frame* frame) override
        {
            // Lock Python's global interpreter lock (it was released in MasterRenderer.render).
            ScopedGILLock lock;

            if (bpy::override f = this->get_override("on_tiled_frame_begin"))
                f(bpy::ptr(frame));
        }

        void default_on_tiled_frame_begin(const Frame* frame)
        {
        }

        virtual void on_tiled_frame_end(const Frame* frame) override
        {
            // Lock Python's global interpreter lock (it was released in MasterRenderer.render).
            ScopedGILLock lock;

            if (bpy::override f = this->get_override("on_tiled_frame_end"))
                f(bpy::ptr(frame));
        }

        void default_on_tiled_frame_end(const Frame* frame)
        {
        }

        virtual void on_tile_begin(
            const Frame*    frame,
            const size_t    tile_x,
            const size_t    tile_y) override
        {
            // Lock Python's global interpreter lock (it was released in MasterRenderer.render).
            ScopedGILLock lock;

            if (bpy::override f = this->get_override("on_tile_begin"))
                f(bpy::ptr(frame), tile_x, tile_y);
        }

        void default_on_tile_begin(
            const Frame*    frame,
            const size_t    tile_x,
            const size_t    tile_y)
        {
        }

        virtual void on_tile_end(
            const Frame*    frame,
            const size_t    tile_x,
            const size_t    tile_y) override
        {
            // Lock Python's global interpreter lock (it was released in MasterRenderer.render).
            ScopedGILLock lock;

            if (bpy::override f = this->get_override("on_tile_end"))
                f(bpy::ptr(frame), tile_x, tile_y);
        }

        void default_on_tile_end(
            const Frame*    frame,
            const size_t    tile_x,
            const size_t    tile_y)
        {
        }

        virtual void on_progressive_frame_begin(const Frame* frame) override
        {
            // Lock Python's global interpreter lock (it was released in MasterRenderer.render).
            ScopedGILLock lock;

            if (bpy::override f = this->get_override("on_progressive_frame_begin"))
                f(bpy::ptr(frame));
        }

        void default_on_progressive_frame_begin(const Frame* frame)
        {
        }

        virtual void on_progressive_frame_end(const Frame* frame) override
        {
            // Lock Python's global interpreter lock (it was released in MasterRenderer.render).
            ScopedGILLock lock;

            if (bpy::override f = this->get_override("on_progressive_frame_end"))
                f(bpy::ptr(frame));
        }

        void default_on_progressive_frame_end(const Frame* frame)
        {
        }
    };
}

void bind_tile_callback()
{
    bpy::class_<ITileCallbackWrapper, boost::noncopyable>("ITileCallback")
        .def("on_tiled_frame_begin", &ITileCallback::on_tiled_frame_begin, &ITileCallbackWrapper::default_on_tiled_frame_begin)
        .def("on_tiled_frame_end", &ITileCallback::on_tiled_frame_end, &ITileCallbackWrapper::default_on_tiled_frame_end)
        .def("on_tile_begin", &ITileCallback::on_tile_begin, &ITileCallbackWrapper::default_on_tile_begin)
        .def("on_tile_end", &ITileCallback::on_tile_end, &ITileCallbackWrapper::default_on_tile_end)
        .def("on_progressive_frame_begin", &ITileCallback::on_progressive_frame_begin, &ITileCallbackWrapper::default_on_progressive_frame_begin)
        .def("on_progressive_frame_end", &ITileCallback::on_progressive_frame_end, &ITileCallbackWrapper::default_on_progressive_frame_end)
        ;
}
