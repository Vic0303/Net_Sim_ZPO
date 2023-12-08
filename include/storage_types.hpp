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
    using const_iterator = std::list<Package>::const_iterator;
    virtual void push(Package&& package) = 0;
    virtual bool empty() = 0;
    virtual std::size_t size() = 0;
    virtual const_iterator cbegin() const = 0;
    virtual const_iterator cend() const = 0;
    virtual const_iterator begin() const = 0;
    virtual const_iterator end() const = 0;
    virtual ~IPackageStockpile() = default;
};


class IPackageQueue : public IPackageStockpile{
public:
    virtual Package pop() = 0;
    virtual PackageQueueType get_queue_type() = 0;
    ~IPackageQueue() override = default;
};

class PackageQueue : IPackageQueue{
public:
    explicit PackageQueue(PackageQueueType queue_type) : queue(), queue_type(queue_type) {}
    void push(Package&& package) override { queue.emplace_back(std::move(package)); }
    std::size_t size() const { return queue.size(); }
    bool empty() const { return queue.empty(); }
    const_iterator cbegin() const override { return queue.cbegin(); }
    const_iterator cend() const override { return queue.cend(); }
    const_iterator begin() const override { return queue.begin(); }
    const_iterator end() const { return queue.end(); }
    Package pop() override;
    PackageQueueType get_queue_type() const { return queue_type; }
    ~PackageQueue() override = default;
private:
    std::list<Package> queue;
    PackageQueueType queue_type;
};

#endif //NET_SIM_ZPO_STORAGE_TYPES_HPP
