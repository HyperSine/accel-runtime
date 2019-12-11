#pragma once
#include <stddef.h>
#include <stdint.h>
#include <type_traits>

namespace ARL {

    template<typename __PtrType1, typename __PtrType2>
    [[nodiscard]]
    inline ptrdiff_t AddressDelta(__PtrType1 p1, __PtrType2 p2) noexcept {
        static_assert(std::is_pointer_v<__PtrType1>);
        static_assert(std::is_pointer_v<__PtrType2>);
        return reinterpret_cast<const volatile char*>(p1) - reinterpret_cast<const volatile char*>(p2);
    }

    template<typename __PtrType>
    [[nodiscard]]
    inline __PtrType AddressOffset(__PtrType p, ptrdiff_t offset) noexcept {
        static_assert(std::is_pointer_v<__PtrType>);
        return reinterpret_cast<__PtrType>(
            const_cast<char*>(
                reinterpret_cast<const volatile char*>(p) + offset
            )
        );
    }

    template<typename __ReturnType, typename __PtrType>
    [[nodiscard]]
    inline __ReturnType AddressOffsetWithCast(__PtrType p, ptrdiff_t offset) noexcept {
        static_assert(std::is_pointer_v<__ReturnType>);
        static_assert(std::is_pointer_v<__PtrType>);
        return reinterpret_cast<__ReturnType>(
            const_cast<char*>(
                reinterpret_cast<const volatile char*>(p) + offset
            )
        );
    }

    template<typename __ReadType, typename __PtrType>
    [[nodiscard]]
    inline __ReadType AddressRead(__PtrType p) noexcept {
        static_assert(std::is_trivial_v<__ReadType> && std::is_standard_layout_v<__ReadType>);
        static_assert(std::is_pointer_v<__PtrType>);
        return *reinterpret_cast<const volatile __ReadType*>(p);
    }

    template<typename __ReadType, typename __PtrType>
    [[nodiscard]]
    inline __ReadType AddressRead(__PtrType p, ptrdiff_t offset) noexcept {
        static_assert(std::is_trivial_v<__ReadType> && std::is_standard_layout_v<__ReadType>);
        static_assert(std::is_pointer_v<__PtrType>);
        return *reinterpret_cast<const volatile __ReadType*>(
            reinterpret_cast<const volatile char*>(p) + offset
        );
    }

    template<typename __ReadType, typename __PtrType>
    [[nodiscard]]
    inline __ReadType AddressRead(__PtrType p, size_t scale, ptrdiff_t index) noexcept {
        static_assert(std::is_trivial_v<__ReadType> && std::is_standard_layout_v<__ReadType>);
        static_assert(std::is_pointer_v<__PtrType>);
        return *reinterpret_cast<const volatile __ReadType*>(
            reinterpret_cast<const volatile char*>(p) + scale * index
        );
    }

    template<typename __WriteType, typename __PtrType>
    inline void AddressWrite(__PtrType p, const __WriteType& value) noexcept {
        static_assert(std::is_trivial_v<__WriteType> && std::is_standard_layout_v<__WriteType>);
        static_assert(std::is_pointer_v<__PtrType>);
        *reinterpret_cast<volatile __WriteType*>(p) = value;
    }

    template<typename __WriteType, typename __PtrType>
    inline void AddressWrite(__PtrType p, ptrdiff_t offset, const __WriteType& value) noexcept {
        static_assert(std::is_trivial_v<__WriteType> && std::is_standard_layout_v<__WriteType>);
        static_assert(std::is_pointer_v<__PtrType>);
        *reinterpret_cast<volatile __WriteType*>(
            reinterpret_cast<volatile char*>(p) + offset
        ) = value;
    }

    template<typename __WriteType, typename __PtrType>
    inline void AddressWrite(__PtrType p, size_t scale, ptrdiff_t index, const __WriteType& value) noexcept {
        static_assert(std::is_trivial_v<__WriteType> && std::is_standard_layout_v<__WriteType>);
        static_assert(std::is_pointer_v<__PtrType>);
        *reinterpret_cast<volatile __WriteType*>(
            reinterpret_cast<volatile char*>(p) + scale * index
        ) = value;
    }

}

