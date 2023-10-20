#ifndef ArrayDeque_h
#define ArrayDeque_h

#include <stdexcept>
#include <ostream>

template<typename T>
class ArrayDeque {
public:
    using value_type = T;
    using reference = T &;
    using const_reference = const T &;
    using pointer = T *;
    using size_type = std::size_t;

private:
    pointer pBuffer;
    size_type mCapacity;
    size_type mStart;
    size_type mSize;

public:
    /* ------------------------------------------------------------
     * Constructors
     * ------------------------------------------------------------ */
    explicit ArrayDeque(size_type capacity = 0) : pBuffer(nullptr), mCapacity(capacity), mStart(0), mSize(0) {
        if (capacity) {
            pBuffer = (pointer) ::operator new(capacity * sizeof(value_type));
        }
    }

    ArrayDeque(const ArrayDeque<value_type> &other)
            : pBuffer(nullptr),
              mCapacity(other.mCapacity),
              mStart(other.mStart),
              mSize(0) {
        if (other.mCapacity) {
            auto buf = (pointer) ::operator new(other.mCapacity * sizeof(value_type));
            try {
                for (size_type i = 0; i < other.mSize; ++i) {
                    size_type offset = (other.mStart + i) % other.mCapacity;
                    new(&buf[offset]) value_type{other.pBuffer[offset]};
                    ++mSize;
                }
            } catch (...) {
                for (size_type j = 0; j < mSize; ++j) {
                    buf[(other.mStart + j) % other.mCapacity].~value_type();
                }

                ::operator delete(buf);
                throw;
            }

            pBuffer = buf;
        }
    }

    ArrayDeque(ArrayDeque<value_type> &&other) noexcept
            : pBuffer(other.pBuffer),
              mCapacity(other.mCapacity),
              mStart(other.mStart),
              mSize(other.mSize) {
        other.pBuffer = nullptr;
        other.mCapacity = 0;
        other.mStart = 0;
        other.mSize = 0;
    }

    /* ------------------------------------------------------------
     * Destructor
     * ------------------------------------------------------------ */

    ~ArrayDeque() {
        if (pBuffer) {
            for (size_type i = 0; i < mSize; ++i) {
                pBuffer[(mStart + i) % mCapacity].~value_type();
            }
            ::operator delete(pBuffer);
        }
    }

    /* ------------------------------------------------------------
     * Operators
     * ------------------------------------------------------------ */

    // assignment from other ArrayDeque, strong exception safety
    ArrayDeque<value_type> &operator=(const ArrayDeque<value_type> &rhs) {
        if (this == &rhs) {
            return *this;
        }

        ArrayDeque<value_type> tmp{rhs};
        swap(tmp);
        return *this;
    }

    ArrayDeque<value_type> &operator=(ArrayDeque<value_type> &&rhs) noexcept {
        if (this == &rhs) {
            return *this;
        }

        ArrayDeque<value_type> tmp = std::move(rhs);
        swap(tmp);
        return *this;
    }

    /* ------------------------------------------------------------
     * Capacity getters
     * ------------------------------------------------------------ */

    /**
     * @return The number of elements in the deque.
     */
    [[nodiscard]] size_type size() const noexcept {
        return mSize;
    }

    /**
     * @return The number of elements that the deque can hold without resizing.
     */
    [[nodiscard]] size_type capacity() const noexcept {
        return mCapacity;
    }

    /**
     * @return Whether the deque is empty.
     */
    [[nodiscard]] bool empty() const noexcept {
        return mSize == 0;
    }

    /* ------------------------------------------------------------
     * Positional data getters
     * ------------------------------------------------------------ */

    /**
     * @param index The index of the element to return
     * @return A reference to the element at the specified position,
     *         no checks are made for boundaries.
     */
    reference operator[](size_type index) {
        return pBuffer[(mStart + index) % mCapacity];
    }

    /**
     * @param index The index of the element to return
     * @return A reference to the element at the specified position,
     *         no checks are made for boundaries.
     */
    const_reference operator[](size_type index) const {
        return pBuffer[(mStart + index) % mCapacity];
    }

    /**
     * @return The first element in the deque.
     */
    reference front() {
        if (empty()) {
            throw std::out_of_range("ArrayDeque::front()");
        }

        return pBuffer[mStart];
    }

    /**
     * @return The first element in the deque.
     */
    const_reference front() const {
        if (empty()) {
            throw std::out_of_range("ArrayDeque::front()");
        }

        return pBuffer[mStart];
    }

    /**
     * @return The last element in the deque.
     */
    reference back() {
        if (empty()) {
            throw std::out_of_range("ArrayDeque::back()");
        }

        return pBuffer[(mStart + mSize - 1) % mCapacity];
    }

    /**
     * @return The last element in the deque.
     */
    const_reference back() const {
        if (empty()) {
            throw std::out_of_range("ArrayDeque::back()");
        }

        return pBuffer[(mStart + mSize - 1) % mCapacity];
    }

    /**
     * @param index The index of the element to return
     * @return A reference to the element at the specified position.
     */
    reference at(size_type index) {
        if (mSize - mStart <= index) {
            throw std::out_of_range("ArrayDeque::at()");
        }

        return pBuffer[(mStart + index) % mCapacity];
    }

    /**
     * @param index The index of the element to return
     * @return A reference to the element at the specified position.
     */
    const_reference at(size_type index) const {
        if (mSize - mStart <= index) {
            throw std::out_of_range("ArrayDeque::at()");
        }

        return pBuffer[(mStart + index) % mCapacity];
    }

    /* ------------------------------------------------------------
     * Positional data setters
     * ------------------------------------------------------------ */

    /**
     * Push an element at the start of the buffer.
     * @param value The value to push.
     */
    void push_back(const_reference value) {
        if (mSize >= mCapacity) {
            resize(getNewCapacity());
        }

        new(&pBuffer[(mStart + mSize) % mCapacity]) value_type{value};
        ++mSize;
    }

    /**
     * Push an element at the end of the buffer
     * @param value The value to push.
     */
    void push_front(const_reference value) {
        if (mSize >= mCapacity) {
            resize(getNewCapacity());
        }

        size_type offset = (mStart + mCapacity - 1) % mCapacity;
        new(&pBuffer[offset]) value_type{value};
        mStart = offset;
        ++mSize;
    }

    /**
     * Pop an element from the front of the queue.
     */
    void pop_front() {
        if (empty()) {
            throw std::out_of_range("ArrayDeque::pop_front()");
        }

        pBuffer[mStart].~value_type();
        mStart = (mStart + 1) % mCapacity;
        --mSize;
    }

    /**
     * Pop an element from the end of the buffer.
     */
    void pop_back() {
        if (empty()) {
            throw std::out_of_range("ArrayDeque::pop_back()");
        }

        pBuffer[(mStart + mSize - 1) % mCapacity].~value_type();
        --mSize;
    }

    /* ------------------------------------------------------------
     * Utility methods
     * ------------------------------------------------------------ */

    /**
     * Swap the contents of this deque with another.
     * @param other The deque to swap from.
     */
    void swap(ArrayDeque<value_type> &other) noexcept {
        using std::swap;
        swap(pBuffer, other.pBuffer);
        swap(mCapacity, other.mCapacity);
        swap(mStart, other.mStart);
        swap(mSize, other.mSize);
    }

    /**
     * Shrink the capacity of the buffer to the current size.
     */
    constexpr void shrink_to_fit() {
        if (mSize < mCapacity) {
            resize(mSize);
        }
    }

private:
    /**
     * @return A new value to use for the capacity of the deque.
     */
    size_type getNewCapacity() {
        if (!mCapacity) {
            return 1;
        }

        return 2 * mCapacity;
    }

    /**
     * Resizes the deque to the specified capacity.
     * @param newCapacity The new capacity of the deque.
     */
    void resize(size_type newCapacity) {
        if (newCapacity == mCapacity) {
            return;
        }

        ArrayDeque<value_type> tmp(newCapacity);
        for (size_type i = 0; i < mSize; ++i) {
            tmp.push_back(pBuffer[(mStart + i) % mCapacity]);
        }

        swap(tmp);
    }
};

template<typename T>
inline std::ostream &operator<<(std::ostream &s, const ArrayDeque<T> &v) {
    s << "(" << v.size() << "/" << v.capacity() << ") : ";
    if (not v.empty())
        s << v.front() << " -> " << v.back() << " : ";
    s << "[";
    for (size_t i = 0; i < v.size(); ++i) {
        s << v[i];
        if (i != v.size() - 1)
            s << ", ";
    }
    s << "]";
    return s;
}

template<typename T>
inline constexpr
void swap(ArrayDeque<T> &lhs, ArrayDeque<T> &rhs) noexcept {
    lhs.swap(rhs);
}

#endif /* ArrayDeque_h */
