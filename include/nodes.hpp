//
// Created by wikto on 28.11.2023.
//

#ifndef NET_SIM_ZPO_NODES_HPP
#define NET_SIM_ZPO_NODES_HPP

#include "config.hpp"
#include "package.hpp"
#include "storage_types.hpp"
#include "types.hpp"
#include "memory"

class IPackageReceiver{
public:
    virtual void push(Package&& p) = 0;
    virtual ElementID get_id() = 0;


    virtual IPackageStockpile::const_iterator begin() const = 0;
    virtual IPackageStockpile::const_iterator end() const = 0;
    virtual IPackageStockpile::const_iterator cbegin() const = 0;
    virtual IPackageStockpile::const_iterator cend() const = 0;

    #if (defined EXERCISE_ID && EXERCISE_ID != EXERCISE_ID_NODES)
    virtual ReceiverType get_receiver_type() const = 0;
    #endif

    virtual ~IPackageReceiver() = default;
};

class Storehouse: public IPackageReceiver {
public:

};

class Worker: public IPackageReceiver {
public:

};

#endif //NET_SIM_ZPO_NODES_HPP
