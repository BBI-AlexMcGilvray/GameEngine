#pragma once

#include <array>
#include <mutex>

#include "Core/Debugging/Headers/Declarations.h"
#include "Core/Headers/TimeDefs.h"
#include "Core/Logging/Logger.h"

namespace Core
{
namespace Threading
{
template <typename T>
struct TripleBuffer
{
    TripleBuffer()
    : _buffers({ BufferData(_clock), BufferData(_clock), BufferData(_clock) })
    {}
    TripleBuffer(TripleBuffer&&) = default;
    TripleBuffer& operator=(TripleBuffer&&) = default;

    // don't have copy constructors, triple buffers are heavy so should be minimized
    TripleBuffer(const TripleBuffer&) = delete;
    TripleBuffer& operator=(const TripleBuffer&) = delete;

    void WriteBuffer(T&& data)
    {
        T& buffer = _LockAndGetOldestNonLockedBuffer();

        buffer = std::move(data);
        ReturnBuffer(buffer);
    }

    // any 'read' buffers must be returned when done
    const T& ReadBuffer() const
    {
        return _LockAndGetNewestNonLockedBuffer();
    }

    void ReturnBuffer(const T& buffer)
    {
        auto lock = _GetLock();

        for (auto& _buffer : _buffers)
        {
            if (_buffer.HoldsBuffer(buffer))
            {
                _buffer.ReturnData(buffer);
                return;
            }
        }

        CORE_THROW("TripleBuffer", "returned buffer is not held");
    }

private:
    struct BufferData
    {
        BufferData(Core::SteadyClock& clock)
        : _clock(clock)
        , _locked(false)
        {}

        bool IsLocked() const { return _locked; }

        Core::Second TimeSinceLastUpdate(const Core::TimePoint& now) const
        {
            return now - _lastUpdateTime;
        }

        T& GetData()
        {
            _Lock();

            return _buffer;
        }

        bool HoldsBuffer(const T& buffer) const
        {
            return &buffer == &_buffer;
        }

        void SetData(T&& data)
        {
            _Lock();

            std::swap(data, _buffer);
            _lastUdateTime = _clock.now();
        }

        void ReturnData(const T& data)
        {
            _LockMustBe(true);
            if (!HoldsBuffer(data))
            {
                CORE_THROW("TripleBuffer", "Returned data is not the held buffer");
            }

            _locked = false;
        }

    private:
        Core::SteadyClock& _clock;

        // no internal mutex as it is always handled by TripleBuffer
        bool _locked;
        T _buffer;
        Core::TimePoint _lastUpdateTime;

        void _Lock()
        {
            _LockMustBe(false);
            _locked = true;
        }

        void _LockMustBe(bool value) const
        {
        #if DEBUG
            if (_locked != value)
            {
                CORE_THROW("TripleBuffer", "returned buffer is not held");
            }
        #endif
        }
    };

    Core::SteadyClock _clock;
    mutable std::mutex _mutex;
    mutable std::array<BufferData, 3> _buffers;

    std::unique_lock<std::mutex> _GetLock() const
    {
        return std::unique_lock(_mutex);
    }

    T& _LockAndGetOldestNonLockedBuffer() const
    {
        auto lock = _GetLock();
        Core::TimePoint now = _clock.now();

        bool found = false;
        size_t oldestNonLocked = 0;
        Core::Second longestTimeSinceUpdate;

        size_t index = 0;
        for (auto& buffer : _buffers)
        {
            if (!buffer.IsLocked())
            {
                auto timeSince = buffer.TimeSinceLastUpdate(now);
                if (!found || timeSince < longestTimeSinceUpdate)
                {
                    found = true;
                    oldestNonLocked = index;
                    longestTimeSinceUpdate = timeSince;
                }
            }
            ++index;
        }

        if (!found)
        {
            CORE_THROW("TripleBuffer", "Some buffer must be available");
        }

        return _buffers[oldestNonLocked].GetData();
    }

    const T& _LockAndGetNewestNonLockedBuffer() const
    {
        auto lock = _GetLock();
        Core::TimePoint now = _clock.now();

        bool found = false;
        size_t newestNonLocked = 0;
        Core::Second longestTimeSinceUpdate;

        size_t index = 0;
        for (auto& buffer : _buffers)
        {
            if (!buffer.IsLocked())
            {
                auto timeSince = buffer.TimeSinceLastUpdate(now);
                if (!found || timeSince > longestTimeSinceUpdate)
                {
                    found = true;
                    newestNonLocked = index;
                    longestTimeSinceUpdate = timeSince;
                }
            }
            ++index;
        }

        if (!found)
        {
            CORE_THROW("TripleBuffer", "Some buffer must be available");
        }

        return _buffers[newestNonLocked].GetData();
    }
};
} // namespace Threading
} // namespace Core