#pragma once

#include <filesystem>

namespace mcserver::server {

class WorldLock {
public:
    explicit WorldLock(std::filesystem::path const& worldDirectory);
    ~WorldLock();
    WorldLock(WorldLock const&) = delete;
    WorldLock& operator=(WorldLock const&) = delete;
    [[nodiscard]] std::filesystem::path const& directory() const noexcept { return directory_; }

private:
    std::filesystem::path directory_;
#ifdef _WIN32
    void* handle_ = nullptr;
#else
    int descriptor_ = -1;
#endif
};

} // namespace mcserver::server
