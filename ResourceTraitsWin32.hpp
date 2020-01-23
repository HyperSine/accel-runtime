#pragma once
#include <windows.h>
#include <type_traits>
#include <system_error>

namespace ARL::ResourceTraits {

    struct GenericHandle {
        using HandleType = HANDLE;

        static inline const HandleType InvalidValue = NULL;

        [[nodiscard]]
        static bool IsValid(const HandleType& Handle) noexcept {
            return Handle != InvalidValue;
        }

        static void Release(const HandleType& Handle) {
            if (CloseHandle(Handle) == FALSE) {
                auto err = GetLastError();
                throw std::system_error(err, std::system_category());
            }
        }
    };

    struct FileHandle {
        using HandleType = HANDLE;

        static inline const HandleType InvalidValue = INVALID_HANDLE_VALUE;

        [[nodiscard]]
        static bool IsValid(const HandleType& Handle) noexcept {
            return Handle != InvalidValue;
        }

        static void Release(const HandleType& Handle) {
            if (CloseHandle(Handle) == FALSE) {
                auto err = GetLastError();
                throw std::system_error(err, std::system_category());
            }
        }
    };

    struct ServiceHandle {
        using HandleType = SC_HANDLE;

        static inline const HandleType InvalidValue = NULL;

        [[nodiscard]]
        static bool IsValid(const HandleType& Handle) noexcept {
            return Handle != InvalidValue;
        }

        static void Release(const HandleType& Handle) {
            if (CloseServiceHandle(Handle) == FALSE) {
                auto err = GetLastError();
                throw std::system_error(err, std::system_category());
            }
        }
    };

    template<typename __PtrType = PVOID>
    struct VirtualAlloc {
        static_assert(
            std::is_pointer_v<__PtrType>,
            "[ARL::ResourceTraits::VirtualAlloc]: __PtrType must be a pointer type."
        );

        using HandleType = __PtrType;

        static inline const HandleType InvalidValue = nullptr;

        [[nodiscard]]
        static bool IsValid(const HandleType& Handle) noexcept {
            return Handle != InvalidValue;
        }

        static void Release(const HandleType& Handle) {
            if (VirtualFree(Handle, 0, MEM_RELEASE) == FALSE) {
                auto err = GetLastError();
                throw std::system_error(err, std::system_category());
            }
        }
    };

    template<typename __PtrType = PVOID>
    struct VirtualAllocEx {
        static_assert(
            std::is_pointer_v<__PtrType>,
            "[ARL::ResourceTraits::VirtualAllocEx]: __PtrType must be a pointer type."
        );

        using HandleType = __PtrType;

        static inline const HandleType InvalidValue = nullptr;

        [[nodiscard]]
        static bool IsValid(const HandleType& Handle) noexcept {
            return Handle != InvalidValue;
        }
    };

    template<typename __PtrType = PVOID>
    struct HeapAlloc {
        static_assert(
            std::is_pointer_v<__PtrType>,
            "[ARL::ResourceTraits::HeapAlloc]: __PtrType must be a pointer type."
        );

        using HandleType = __PtrType;

        static inline const HandleType InvalidValue = nullptr;

        [[nodiscard]]
        static bool IsValid(const HandleType& Handle) noexcept {
            return Handle != InvalidValue;
        }

        static void Release(const HandleType& Handle) {
            if (HeapFree(GetProcessHeap(), 0, Handle) == FALSE) {
                auto err = GetLastError();
                throw std::system_error(err, std::system_category());
            }
        }
    };

    template<typename __PtrType = PVOID>
    struct LocalAlloc {
        static_assert(
            std::is_pointer_v<__PtrType>,
            "[ARL::ResourceTraits::LocalAlloc]: __PtrType must be a pointer type."
        );

        using HandleType = __PtrType;

        static inline const HandleType InvalidValue = nullptr;

        [[nodiscard]]
        static bool IsValid(const HandleType& Handle) noexcept {
            return Handle != InvalidValue;
        }

        static void Release(const HandleType& Handle) {
            if (LocalFree(Handle) != NULL) {
                auto err = GetLastError();
                throw std::system_error(err, std::system_category());
            }
        }
    };

    struct RegistryKey {
        using HandleType = HKEY;

        static inline const HandleType InvalidValue = NULL;

        [[nodiscard]]
        static bool IsValid(const HandleType& Handle) noexcept {
            return Handle != InvalidValue;
        }

        static void Release(const HandleType& Handle) {
            if (RegCloseKey(Handle) != ERROR_SUCCESS) {
                auto err = GetLastError();
                throw std::system_error(err, std::system_category());
            }
        }
    };

}

