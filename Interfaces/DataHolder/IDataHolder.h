#ifndef IDATAHOLDER_H
#define IDATAHOLDER_H

#include <optional>

namespace DH{
    template<typename T>
    class IDataHolder {
    public:
        virtual ~IDataHolder() = default;

        virtual void Push(const T& item) = 0;
        virtual void Push(T&& item) = 0;

        virtual std::optional<T> Pop() = 0;

        [[nodiscard]] virtual size_t Size() const = 0;
        [[nodiscard]] virtual bool Empty() const = 0;

        virtual void Clear() = 0;
    };

}

#endif //IDATAHOLDER_H
