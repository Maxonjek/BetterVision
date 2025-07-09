#ifndef IOBSSENDER_H
#define IOBSSENDER_H

#include <memory>
#include "IObsListner.h"


template<typename T>
class IObsSender {
public:
    virtual void Attach(std::shared_ptr<IObsListner<T> > listner) = 0;

    virtual void Detouch(std::shared_ptr<IObsListner<T> > listner) = 0;

    virtual ~IObsSender() = default;

protected:
    virtual void Notify(const T &ntfData) = 0;
};


#endif //IOBSSENDER_H
