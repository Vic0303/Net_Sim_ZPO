//
// Created by wikto on 28.11.2023.
//

#ifndef NET_SIM_ZPO_REPORTS_HPP
#define NET_SIM_ZPO_REPORTS_HPP

#include "factory.hpp"
#include "storage_types.hpp"
#include <ostream>

void generate_structure_report(const Factory& factory, std::ostream& os);

void generate_simulation_turn_report(const Factory& factory, std::ostream& os, Time t);

#endif //NET_SIM_ZPO_REPORTS_HPP
