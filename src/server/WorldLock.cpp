#include "mcserver/server/WorldLock.hpp"

#include <stdexcept>

#ifdef _WIN32
#include <windows.h>
#else
#include <fcntl.h>
#include <unistd.h>
#endif

namespace mcserver::server {

WorldLock::WorldLock(std::filesystem::path const& worldDirectory) {
    if (!std::filesystem::is_directory(worldDirectory)) { throw std::runtime_error("world directory does not exist"); }
    directory_ = std::filesystem::canonical(worldDirectory);
    auto path = directory_ / "session.lock";
    constexpr char marker[] = "\xe2\x98\x83";
#ifdef _WIN32
    HANDLE handle = CreateFileW(path.c_str(), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE,
                                nullptr, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
    if (handle == INVALID_HANDLE_VALUE) { throw std::runtime_error("cannot open world session lock"); }
    DWORD written = 0;
    if (SetFilePointer(handle, 0, nullptr, FILE_BEGIN) == INVALID_SET_FILE_POINTER ||
        !SetEndOfFile(handle) ||
        !WriteFile(handle, marker, 3, &written, nullptr) ||
        written != 3 ||
        !SetEndOfFile(handle)) {
        CloseHandle(handle);
        throw std::runtime_error("cannot write world session lock");
    }
    if (!FlushFileBuffers(handle)) {
        CloseHandle(handle);
        throw std::runtime_error("cannot flush world session lock");
    }
    CloseHandle(handle);

    auto lockPath = directory_ / "session.lock.lock";
    handle = CreateFileW(lockPath.c_str(), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE,
                         nullptr, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
    if (handle == INVALID_HANDLE_VALUE) {
        throw std::runtime_error("cannot open world session lock");
    }
    OVERLAPPED overlap{};
    if (!LockFileEx(handle, LOCKFILE_EXCLUSIVE_LOCK | LOCKFILE_FAIL_IMMEDIATELY, 0, 1, 0, &overlap)) {
        CloseHandle(handle);
        throw std::runtime_error("world is locked by another process");
    }
    handle_ = handle;
#else
    descriptor_ = open(path.c_str(), O_RDWR | O_CREAT, 0666);
    if (descriptor_ < 0) { throw std::runtime_error("cannot open world session lock"); }
    struct flock lock{};
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    if (fcntl(descriptor_, F_SETLK, &lock) == -1) {
        close(descriptor_);
        descriptor_ = -1;
        throw std::runtime_error("world is locked by another process");
    }
    if (ftruncate(descriptor_, 0) == -1 || write(descriptor_, marker, 3) != 3) {
        close(descriptor_);
        descriptor_ = -1;
        throw std::runtime_error("cannot write world session lock");
    }
#endif
}

WorldLock::~WorldLock() {
#ifdef _WIN32
    if (handle_) { CloseHandle(handle_); }
#else
    if (descriptor_ >= 0) { close(descriptor_); }
#endif
}

} // namespace mcserver::server
