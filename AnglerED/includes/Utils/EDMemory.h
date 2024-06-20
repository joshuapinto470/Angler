//
// Created by joshua on 6/20/24.
//

#ifndef ANGLER_EDMEMORY_H
#define ANGLER_EDMEMORY_H

#endif //ANGLER_EDMEMORY_H

#include <cstddef>
#include <cstdint>

// Implementation details : https://indiegamedev.net/2022/03/27/custom-c20-memory-allocators-for-stl-containers/

// Alignment functions
inline std::size_t align_forward_adjustment
        (const void* const ptr, const std::size_t & alignment) noexcept
{
    const auto iptr = reinterpret_cast<std::uintptr_t>(ptr);
    const auto aligned = (iptr - 1u + alignment) & -alignment;
    return aligned - iptr;
}

inline void* ptr_add(const void* const p, const std::uintptr_t& amount) noexcept
{
    return reinterpret_cast<void*>
    (reinterpret_cast<std::uintptr_t>(p) + amount);
}

// Allocator Interface
class IMemoryAllocator
{
    public:
        IMemoryAllocator(std::size_t, void *) noexcept;
        IMemoryAllocator(const IMemoryAllocator&) = delete;
        IMemoryAllocator& operator= (IMemoryAllocator&) = delete;
        IMemoryAllocator(IMemoryAllocator&&) noexcept;
        IMemoryAllocator& operator=(IMemoryAllocator&&) noexcept;

        virtual ~IMemoryAllocator() noexcept;

        virtual void* Allocate(const std::size_t& size,
                           const std::uintptr_t& alignment) = 0;

        virtual void Free(void* ) = 0;

        [[nodiscard]] const std::size_t& GetSize() const noexcept;
        [[nodiscard]] const std::size_t& GetUsed() const noexcept;
        [[nodiscard]] const std::size_t& GetNumAllocation() const noexcept;
        [[nodiscard]] const void* GetStart() const noexcept;

protected:
    std::size_t m_size;
    std::size_t m_usedBytes;
    std::size_t m_numAllocations;

    void* m_start;
};

// Linear Allocator

class LinearAllocator : public IMemoryAllocator
{
public:
    LinearAllocator(std::size_t, void* ) noexcept;
    LinearAllocator(const LinearAllocator&) = delete;
    LinearAllocator& operator=(LinearAllocator&) = delete;
    LinearAllocator(LinearAllocator&&) noexcept;
    LinearAllocator& operator=(LinearAllocator&&) noexcept;

    void* Allocate(const std::size_t & size, const std::uintptr_t& alignment) override;
    void Free(void* ) noexcept override;

    [[nodiscard]] void* GetCurrent() const noexcept;
    [[maybe_unused]] void Rewind(void*) noexcept;
    void Clear() noexcept;

protected:
    void* m_current;
};
