#pragma once
#include "snuifw/common.h"
#include "snuifw/literal/literal.h"

namespace snuifw::literal
{
    struct StyleColor4b
    {
        // TODO: Color space corrections
        // TODO: Gamma space corrections
        // TODO: Transfer function annotations
        // TODO: sRGB curve
        enum class Flags
            : uint32_t
        {
            Mask_Layout = 0x000000FF,
            ARGB = 0x00,
            ABGR = 0x01,
            RGBA = 0x08,
            BGRA = 0x09
        };

    private:
        Flags _flags;
        uint8_t _value[4];

    public:
        static inline Flags _extractLayout(Flags f)
        {
            return static_cast<Flags>((uint32_t)f & (uint32_t)Flags::Mask_Layout);
        }
        static inline Flags _extractNotLayout(Flags f)
        {
            return static_cast<Flags>((uint32_t)f & ~(uint32_t)Flags::Mask_Layout);
        }
        static inline Flags _merge(Flags a, Flags b)
        {
            return static_cast<Flags>((uint32_t)a | (uint32_t)b);
        }

        static inline bool _isARGB(Flags f)
        {
            return _extractLayout(f) == Flags::ARGB;
        }
        static inline bool _isABGR(Flags f)
        {
            return _extractLayout(f) == Flags::ABGR;
        }
        static inline bool _isRGBA(Flags f)
        {
            return _extractLayout(f) == Flags::RGBA;
        }
        static inline bool _isBGRA(Flags f)
        {
            return _extractLayout(f) == Flags::BGRA;
        }
        
        static inline uint8_t _indexR(Flags f)
        {
            switch (_extractLayout(f))
            {
                case Flags::RGBA: return 0;
                case Flags::BGRA: return 2;

                case Flags::ARGB: return 1;
                case Flags::ABGR: return 3;
            }
            assert(false); // impossible
            return 0xFF;
        }
        static inline uint8_t _indexG(Flags f)
        {
            switch (_extractLayout(f))
            {
                case Flags::RGBA: return 1;
                case Flags::BGRA: return 1;
                
                case Flags::ARGB: return 2;
                case Flags::ABGR: return 2;
            }
            assert(false); // impossible
            return 0xFF;
        }
        static inline uint8_t _indexB(Flags f)
        {
            switch (_extractLayout(f))
            {
                case Flags::RGBA: return 2;
                case Flags::BGRA: return 0;
                
                case Flags::ARGB: return 3;
                case Flags::ABGR: return 1;
            }
            assert(false); // impossible
            return 0xFF;
        }
        static inline uint8_t _indexA(Flags f)
        {
            switch (_extractLayout(f))
            {
                case Flags::RGBA: return 3;
                case Flags::BGRA: return 3;
                
                case Flags::ARGB: return 0;
                case Flags::ABGR: return 0;
            }
            assert(false); // impossible
            return 0xFF;
        }

    public:
        inline StyleColor4b()
            : _flags(static_cast<Flags>(0)), _value { 0, 0, 0, 0 }
        { }

        inline StyleColor4b(Flags f, uint8_t _0, uint8_t _1, uint8_t _2, uint8_t _3)
            : _flags(f), _value { _0, _1, _2, _3 }
        { }


    public:
        inline uint8_t getR() const
        {
            return _value[_indexR(_flags)];
        }
        inline uint8_t getB() const
        {
            return _value[_indexB(_flags)];
        }
        inline uint8_t getG() const
        {
            return _value[_indexG(_flags)];
        }
        inline uint8_t getA() const
        {
            return _value[_indexA(_flags)];
        }

        inline StyleColor4b asLayout(Flags f)
        {
            uint8_t v[4];
            v[_indexR(f)] = _value[_indexR(_flags)];
            v[_indexB(f)] = _value[_indexB(_flags)];
            v[_indexG(f)] = _value[_indexG(_flags)];
            v[_indexA(f)] = _value[_indexA(_flags)];

            return StyleColor4b(_merge(_extractLayout(f), _extractNotLayout(_flags)), v[0], v[1], v[2], v[3]);
        }

        inline uint32_t asUint(Flags f)
        {
            auto layout = asLayout(f);

            return *reinterpret_cast<uint32_t const*>(
                static_cast<uint8_t const*>(layout._value));
        }
    };

    inline StyleColor4b rgb(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 0xFF) { return StyleColor4b(StyleColor4b::Flags::RGBA, r, g, b, a); }
}
