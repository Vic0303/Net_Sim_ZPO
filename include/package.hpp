//
// Created by wikto on 28.11.2023.
//

#ifndef NET_SIM_ZPO_PACKAGE_HPP
#define NET_SIM_ZPO_PACKAGE_HPP

#include "types.hpp"
#include <set>

class Package {
public:
    Package();

    Package(ElementID);

    Package(Package &&);

    Package &operator=(Package &&);

    ElementID get_id()const;

    ~Package();

private:
    ElementID ID_;
    static std::set<ElementID> assigned_IDs;
    static std::set<ElementID> freed_IDs;
};

#endif //NET_SIM_ZPO_PACKAGE_HPP
