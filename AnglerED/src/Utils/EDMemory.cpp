#include "EDMemory.h"

#include <cassert>
#include <utility>
#include <new>

IMemoryAllocator::IMemoryAllocator(IMemoryAllocator &&other) noexcept
    : m_size(other.m_size), m_usedBytes(other.m_usedBytes), m_numAllocations(other.m_numAllocations),
      m_start(other.m_start)
{
    other.m_start = nullptr;
    other.m_numAllocations = 0;
    other.m_usedBytes = 0;
    other.m_size = 0;
}

IMemoryAllocator::IMemoryAllocator(const std::size_t sizeBytes, void *const start) noexcept
    : m_size(sizeBytes), m_usedBytes(0), m_numAllocations(0), m_start(start)
{
    assert(sizeBytes > 0);
}

IMemoryAllocator &IMemoryAllocator::operator=(IMemoryAllocator &&rhs) noexcept
{
    m_size = rhs.m_size;
    m_usedBytes = rhs.m_usedBytes;
    m_numAllocations = rhs.m_numAllocations;
    m_start = rhs.m_start;

    rhs.m_start = nullptr;
    rhs.m_numAllocations = 0;
    rhs.m_usedBytes = 0;
    rhs.m_size = 0;

    return *this;
}

IMemoryAllocator::~IMemoryAllocator() noexcept
{
    assert(m_numAllocations == 0 && m_usedBytes == 0);
}

const std::size_t &IMemoryAllocator::GetUsed() const noexcept
{
    return m_usedBytes;
}

const void *IMemoryAllocator::GetStart() const noexcept
{
    return m_start;
}

const std::size_t &IMemoryAllocator::GetNumAllocation() const noexcept
{
    return m_numAllocations;
}

const std::size_t &IMemoryAllocator::GetSize() const noexcept
{
    return m_size;
}

// Linear Allocator

LinearAllocator::LinearAllocator(const std::size_t size, void *const ptr) noexcept
    : IMemoryAllocator(size, ptr), m_current(static_cast<void *>(ptr))
{
}

LinearAllocator::LinearAllocator(LinearAllocator &&other) noexcept
    : IMemoryAllocator(std::move(other)), m_current(other.m_current)
{
}

LinearAllocator &LinearAllocator::operator=(LinearAllocator &&rhs) noexcept
{
    IMemoryAllocator::operator=(std::move(rhs));
    m_current = rhs.m_current;
    rhs.m_current = nullptr;
    return *this;
}

void *LinearAllocator::Allocate(const size_t &size, const uintptr_t &alignment)
{
    assert(size > 0 && alignment > 0);
    std::size_t adjustment = align_forward_adjustment(m_current, alignment);

    if (m_usedBytes + adjustment + size > m_size)
        throw std::bad_alloc();

    void *alignedAddr = ptr_add(m_current, adjustment);
    m_current = ptr_add(alignedAddr, size);
    m_usedBytes = reinterpret_cast<std::uintptr_t>(m_current) - reinterpret_cast<std::uintptr_t>(m_start);
    ++m_numAllocations;
    return alignedAddr;
}

void LinearAllocator::Free([[maybe_unused]] void *const ptr) noexcept
{
    // No free operation on linear allocator.
}

void *LinearAllocator::GetCurrent() const noexcept
{
    return m_current;
}

void LinearAllocator::Clear() noexcept
{
    m_numAllocations = 0;
    m_usedBytes = 0;
    m_current = const_cast<void *>(m_start);
}

[[maybe_unused]] void LinearAllocator::Rewind(void *const mark) noexcept
{
    assert(m_current >= mark && m_start <= mark);
    m_current = mark;
    m_usedBytes = reinterpret_cast<std::uintptr_t>(m_current) - reinterpret_cast<std::uintptr_t>(m_start);
}
