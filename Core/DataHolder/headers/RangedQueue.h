#ifndef RANGEDQUEUE_H
#define RANGEDQUEUE_H

#include "IDataHolder.h"
#include <deque>

/**
 *  FIFO container. Deletes last new element if full
 */
namespace DH {
    template<typename T>
    class RangedQueue final : public IDataHolder<T> {
    public:
        explicit RangedQueue(std::size_t queueSize);

        /**
         * Add element to container
         */
        void Push(const T &item) override;

        /**
         * Add element to container
         */
        void Push(T &&item) override;

        /**
         * Get element from container.
         * @return first element in container
         */
        std::optional<T> Pop() override;

        /**
         *  Get current container size
         * @return size_t Current container size;
         */
        [[nodiscard]] size_t Size() const override;

        /**
         * Has items
         * @return True if empty
         */
        [[nodiscard]] bool Empty() const override;

        /**
         * Clear container
         */
        void Clear() override;

    protected:
        void EnsureContainer();

    private:
        std::size_t queueSize_;
        std::deque<T> container_;
    };

    template<typename T>
    RangedQueue<T>::RangedQueue(const std::size_t queueSize): queueSize_(queueSize) {
    }

    template<typename T>
    void RangedQueue<T>::Push(const T &item) {
        EnsureContainer();
        container_.push_back(item);
    }

    template<typename T>
    void RangedQueue<T>::Push(T &&item) {
        EnsureContainer();
        container_.push_back(std::move(item));
    }

    template<typename T>
    std::optional<T> RangedQueue<T>::Pop() {
        if (container_.empty()) return std::nullopt;
        T val = std::move(container_.front());
        container_.pop_front();
        return val;
    }

    template<typename T>
    size_t RangedQueue<T>::Size() const {
        return container_.size();
    }

    template<typename T>
    bool RangedQueue<T>::Empty() const {
        return container_.empty();
    }

    template<typename T>
    void RangedQueue<T>::Clear() {
        container_.clear();
    }

    template<typename T>
    void RangedQueue<T>::EnsureContainer() {
        if (container_.size() >= queueSize_) container_.pop_back();
    }
} // DH

#endif //RANGEDQUEUE_H
