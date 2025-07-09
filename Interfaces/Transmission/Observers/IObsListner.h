#ifndef IOBSLISTNER_H
#define IOBSLISTNER_H


template<typename T>
class IObsListner {
public:
    virtual void OnNotification(const T &ntfData) =0;

    virtual ~IObsListner() = default;
};
#endif //IOBSLISTNER_H
