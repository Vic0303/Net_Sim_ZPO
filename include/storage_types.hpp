//
// Created by wikto on 28.11.2023.
//

#ifndef NET_SIM_ZPO_STORAGE_TYPES_HPP
#define NET_SIM_ZPO_STORAGE_TYPES_HPP

#include "list"
#include "package.hpp"

enum class PackageQueueType{
    FIFO,LIFO
};


class IPackageStockpile{
public:
    virtual void push(Package&& package);
    virtual bool empty() = 0;
    virtual std::size_t size() = 0;
};


class IPackageQueue : public IPackageStockpile{
public:
    virtual Package pop() = 0;
    virtual PackageQueueType get_queue_type() = 0;
};

class PackageQueue : IPackageQueue{
public:
    PackageQueue(PackageQueueType) = int;
private:
    std::list<Package> queue_;
    PackageQueueType queue_type;
};

#endif //NET_SIM_ZPO_STORAGE_TYPES_HPP
