//
// Created by wikto on 28.11.2023.
//


#ifndef NET_SIM_ZPO_TYPES_HPP
#define NET_SIM_ZPO_TYPES_HPP

#include <functional>

using ElementID = unsigned long long;
using TimeOffset = unsigned long long;
using Time = unsigned long long;
using ProbabilityGenerator = std::function<double()>;

#endif //NET_SIM_ZPO_TYPES_HPP
