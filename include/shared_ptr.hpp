// Copyright 2019 Fedorov james.sayfer2015@yandex.ru

#ifndef INCLUDE_SHARED_PTR_HPP_
#define INCLUDE_SHARED_PTR_HPP_

#include <cstdio>
#include <utility>

template<typename T>
class SharedPtr {
public:
    SharedPtr() {
        data = nullptr;
        count = nullptr;
    }

    explicit SharedPtr(T *ptr) {
        data = ptr;
        count = new int(1);
    }

    SharedPtr(const SharedPtr &r) noexcept {
        if (r.count == nullptr || r.data == nullptr) {
            return;
        }

        data = r.data;
        count = r.count;
        ++(*count);
    }

    SharedPtr(SharedPtr &&r) noexcept {
        if (r.count == nullptr || r.data == nullptr) {
            return;
        }

        data = r.data;
        count = r.count;

        r.data = nullptr;
        r.count = nullptr;
    }

    ~SharedPtr() {
        if (count == nullptr || data == nullptr) {
            return;
        }

        --(*count);

        if (*count == 0) {
            delete data;
            delete count;
        }
    }

    auto operator=(const SharedPtr &r) noexcept -> SharedPtr & {
        if (r == this) {
            return *this;
        }

        data = r.data;
        count = r.count;
        ++(*count);

        return *this;
    }

    auto operator=(SharedPtr &&r) noexcept -> SharedPtr & {
        if (r == this) {
            return *this;
        }

        data = r.data;
        count = r.count;

        r.data = nullptr;
        r.count = nullptr;

        return *this;
    }

    // проверяет, указывает ли указатель на объект
    explicit operator bool() const {
        if (count == nullptr || data == nullptr) {
            return false;
        }

        return *count > 0;
    }

    auto operator*() const -> T & {
        return *data;
    }

    auto operator->() const -> T * {
        return data;
    }

    auto get() -> T * {
        return data;
    }

    void reset(T *ptr) {
        if (count == nullptr || data == nullptr) {
            return;
        }

        --(*count);

        if (*count == 0) {
            delete data;
            delete count;
        }

        data = ptr;
        count = new int(1);
    }

    void swap(SharedPtr &r) {
        if (r.count == nullptr || r.data == nullptr) {
            return;
        }

        std::swap(data, r.data);
        std::swap(count, r.count);
    }

    // возвращает количество объектов SharedPtr,
    // которые ссылаются на тот же управляемый объект
    [[nodiscard]] auto use_count() const -> size_t {
        return *count;
    }

private:
    T *data;
    int *count;
};

#endif // INCLUDE_SHARED_PTR_HPP_
