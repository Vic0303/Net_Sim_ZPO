//
// Created by wikto on 28.11.2023.
//

#ifndef NET_SIM_ZPO_SIMULATION_HPP
#define NET_SIM_ZPO_SIMULATION_HPP

#include "reports.hpp"
#include "types.hpp"
#include "factory.hpp"

void simulate(Factory& f, TimeOffset d, std::function<void (Factory&, Time)> rf);

#endif //NET_SIM_ZPO_SIMULATION_HPP
