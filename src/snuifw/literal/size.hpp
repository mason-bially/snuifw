#pragma once
#include "snuifw/common.h"
#include "snuifw/literal/literal.h"

namespace snuifw::literal
{
    struct StyleSize2d
    {
        // TODO: split flags into two byte sized types and pack independently for better switch usage?
        enum class Flags
            : uint16_t
        {
            Mask_Kind = 0x00FF,
            // absolutes
            Pixel = 0x00,

            // relatives
            Percent = 0x80,
            ElementFontSize = 0x90,

            Mask_Type = 0xF000,
            TypeInt = 0x0000,
            TypeFloat = 0x8000,
        };

    private:
        union Value
        {
            int32_t i;
            float f;
        };

        uint32_t _flags;
        Value _x;
        Value _y;

    // TODO: rewrite with static casts instead?
    private:
        static inline Flags _extractXFlags(uint32_t f)
        {
            return (Flags)((uint16_t)f);
        }

        static inline Flags _extractYFlags(uint32_t f)
        {
            return (Flags)((uint16_t)(f >> 16));
        }

        static inline Flags _setType(Flags f, Flags t)
        {
            return static_cast<Flags>(
                (static_cast<uint16_t>(f) & ~static_cast<uint16_t>(Flags::Mask_Type))
                | (static_cast<uint16_t>(t) & static_cast<uint16_t>(Flags::Mask_Type))
            );
        }

        static inline uint32_t _packFlags(Flags x, Flags y)
        {
            return ((uint32_t)x) | (((uint32_t)y) << 16);
        }

    public:
        static inline bool isInt(Flags f)
        {
            return ((uint16_t)f & (uint16_t)Flags::Mask_Type) == (uint16_t)Flags::TypeInt;
        }
        static inline bool isFloat(Flags f)
        {
            return ((uint16_t)f & (uint16_t)Flags::Mask_Type) == (uint16_t)Flags::TypeFloat;
        }

    public:
        inline StyleSize2d()
            : _flags(0), _x(), _y()
        { }

        inline StyleSize2d(Flags xf, int32_t xv, Flags yf, int32_t yv)
            : _flags(_packFlags(_setType(xf, Flags::TypeInt), _setType(yf, Flags::TypeInt)))
            , _x { .i = xv }, _y { .i = yv }
        { }

        inline StyleSize2d(Flags xf, float xv, Flags yf, float yv)
            : _flags(_packFlags(_setType(xf, Flags::TypeFloat), _setType(yf, Flags::TypeFloat)))
            , _x { .f = xv }, _y { .f = yv }
        { }

        inline StyleSize2d(Flags xf, int32_t xv, Flags yf, float yv)
            : _flags(_packFlags(_setType(xf, Flags::TypeInt), _setType(yf, Flags::TypeFloat)))
            , _x { .i = xv }, _y { .f = yv }
        { }

        inline StyleSize2d(Flags xf, float xv, Flags yf, int32_t yv)
            : _flags(_packFlags(_setType(xf, Flags::TypeFloat), _setType(yf, Flags::TypeInt)))
            , _x { .f = xv }, _y { .i = yv }
        { }

    public:
        inline Flags getXFlags() const
        {
            return _extractXFlags(_flags);
        }
        inline Flags getYFlags() const
        {
            return _extractYFlags(_flags);
        }

        inline float getXf() const
        {
            auto f = getXFlags();
            if (isInt(f))
                return (float)_x.i;
            else
                return _x.f;
            // exception?
        }

        inline int32_t getXi() const
        {
            auto f = getXFlags();
            if (isFloat(f))
                return (int32_t)_x.f;
            else
                return _x.i;
            // exception?
        }

        inline float getYf() const
        {
            auto f = getYFlags();
            if (isInt(f))
                return (float)_y.i;
            else
                return _y.f;
            // exception?
        }

        inline int32_t getYi() const
        {
            auto f = getYFlags();
            if (isFloat(f))
                return (int32_t)_y.f;
            else
                return _y.i;
            // exception?
        }

        inline float getHeightf() const { return getYf(); }
        inline int32_t getHeighti() const { return getYi(); }
        inline float getWidthf() const { return getXf(); }
        inline int32_t getWidthi() const { return getXi(); }
    };

    inline StyleSize2d px(int x, int y) { return StyleSize2d(StyleSize2d::Flags::Pixel, x, StyleSize2d::Flags::Pixel, y); }
    inline StyleSize2d px(float x, float y) { return StyleSize2d(StyleSize2d::Flags::Pixel, x, StyleSize2d::Flags::Pixel, y); }
    inline StyleSize2d px(int x, float y) { return StyleSize2d(StyleSize2d::Flags::Pixel, x, StyleSize2d::Flags::Pixel, y); }
    inline StyleSize2d px(float x, int y) { return StyleSize2d(StyleSize2d::Flags::Pixel, x, StyleSize2d::Flags::Pixel, y); }

    inline StyleSize2d pct(float x, float y) { return StyleSize2d(StyleSize2d::Flags::Percent, x, StyleSize2d::Flags::Percent, y); }
}
