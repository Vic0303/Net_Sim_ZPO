#ifndef NET_SIM_ZPO_PACKAGE_HPP
#define NET_SIM_ZPO_PACKAGE_HPP

#include "types.hpp"
#include <set>

class Package {
public:
    Package();

    Package(ElementID id): id_(id) {assigned_IDs.insert(id_);}

    Package(Package&& package) : id_(package.id_) {};

    Package &operator=(Package &&) noexcept;

    ElementID get_id() const {return id_; }

    ~Package();

private:
    ElementID id_;
    static std::set<ElementID> assigned_IDs;
    static std::set<ElementID> freed_IDs;
};

#endif //NET_SIM_ZPO_PACKAGE_HPP