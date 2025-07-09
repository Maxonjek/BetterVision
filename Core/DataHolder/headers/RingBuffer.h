#ifndef RINGBUFFER_H
#define RINGBUFFER_H
#include <stdexcept>

#include "IDataHolder.h"
#include <vector>

namespace DH {
    template<typename T>
    /**
     *FIFO ringbuffer
     */
    class RingBuffer final : public IDataHolder<T> {
    public:
        explicit RingBuffer(std::size_t bufferSize);

        void Push(const T &item) override;

        void Push(T &&item) override;

        std::optional<T> Pop() override;

        [[nodiscard]] size_t Size() const override;

        [[nodiscard]] bool Empty() const override;

        void Clear() override;

    protected:
        void Advance();

    private:
        std::vector<T> buffer_;
        size_t bufferSize_;
        size_t head_; // точка записи
        size_t tail_; // точка чтения
        bool full_;
    };

    template<typename T>
    RingBuffer<T>::RingBuffer(std::size_t bufferSize): buffer_(bufferSize), bufferSize_(bufferSize),
                                                       head_(0), tail_(0), full_(false) {
        if (bufferSize == 0)
            throw std::invalid_argument("bufferSize must be greater than 0.");
    }

    template<typename T>
    void RingBuffer<T>::Push(const T &item) {
        buffer_[head_] = item;
        Advance();
    }

    template<typename T>
    void RingBuffer<T>::Push(T &&item) {
        buffer_[head_] = std::move(item);
        Advance();
    }

    template<typename T>
    std::optional<T> RingBuffer<T>::Pop() {
        if (Empty()) {
            return std::nullopt;
        };
        T item = std::move(buffer_[tail_]);
        tail_ = (tail_ + 1) % bufferSize_;
        full_ = false;
        return item;
    }

    template<typename T>
    size_t RingBuffer<T>::Size() const {
        if (full_) return bufferSize_;
        if (head_ >= tail_) return head_ - tail_;
        return bufferSize_ - tail_ + head_;
    }

    template<typename T>
    bool RingBuffer<T>::Empty() const {
        return (!full_ && head_ == tail_);
    }

    template<typename T>
    void RingBuffer<T>::Clear() {
        head_ = tail_ = 0;
        full_ = false;
    }

    template<typename T>
    void RingBuffer<T>::Advance() {
        head_ = (head_ + 1) % bufferSize_;
        if (full_) {
            tail_ = (tail_ + 1) % bufferSize_; // перезапись — сдвигаем хвост
        }
        full_ = head_ == tail_;
    }
} // DH

#endif //RINGBUFFER_H
