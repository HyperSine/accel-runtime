#pragma once
#include <errno.h>
#include <unistd.h>
#include <sys/mman.h>
#include <system_error>

namespace ARL::ResourceTraits {

    struct FileDescriptor {
        using HandleType = int;

        static inline const HandleType InvalidValue = -1;

        [[nodiscard]]
        static bool IsValid(const HandleType& Handle) noexcept {
            return Handle != InvalidValue;
        }

        static void Release(const HandleType& Handle) {
            if (close(Handle) != 0) {
                throw std::system_error(errno, std::generic_category());
            }
        }
    };

    template<typename __PtrType>
    struct MapView {
        static_assert(
            std::is_pointer_v<__PtrType>,
            "[ARL::ResourceTraits::MapView]: __PtrType must be a pointer type."
        );

        using HandleType = __PtrType;

        static inline const HandleType InvalidValue = reinterpret_cast<HandleType>(MAP_FAILED);

        [[nodiscard]]
        static bool IsValid(const HandleType& Handle) noexcept {
            return Handle != InvalidValue;
        }
    };

}

