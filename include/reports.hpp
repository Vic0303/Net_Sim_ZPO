//
// Created by wikto on 28.11.2023.
//

#ifndef NET_SIM_ZPO_REPORTS_HPP
#define NET_SIM_ZPO_REPORTS_HPP


#include "factory.hpp"
#include "nodes.hpp"
#include <iostream>
#include <fstream>


void generate_structure_report(f: const Factory&, os: std::ostream&) {

//LOADING_RAMP id=<ramp-id> delivery-interval=<delivery-interval>
//WORKER id=<worker.get_id()> processing-time=<processing-time> queue-type=<queue-type>
//STOREHOUSE id=<storehouse-id>
//LINK src=<node-type>-<node-id> dest=<node-type>-<node-id>

    os << "== LOADING RAMPS ==\n" << std::endl;

    os << "LOADING RAMP #" << ramp1.id << std::endl;
    os << "  Delivery interval: "<< ramp1.delivery_interval << std::endl;
    os << "  Receivers: " << std::endl;
    for (const auto& receiver : ramp1.receivers) {
        os << "    worker #" << receiver.id << std::endl;
    }

    os << "\nLOADING RAMP #" << ramp2.id << std::endl;
    os << "  Delivery interval: "<< ramp2.delivery_interval << std::endl;
    os << "  Receivers: " << std::endl;
    for (const auto& receiver : ramp2.receivers) {
        os << "    worker #" << receiver.id << std::endl;
    }

    os << "\n== WORKERS ==\n" << std::endl;

    os << "WORKER #" << worker1.id << std::endl;
    os << "  Processing time: " << worker1.processing_time << std::endl;
    os << "  Queue type: "<< worker1.queue_type << std::endl;
    os << "  Receivers: "<< std::endl;
    for (const auto& receiver : worker1.receivers) {
        os << "    worker #" << receiver.id << std::endl;
    }

    os << "\nWORKER #" << worker2.id << std::endl;
    os << "  Processing time: " << worker2.processing_time << std::endl;
    os << "  Queue type: " << worker2.queue_type << std::endl;
    os << "  Receivers: " << std::endl;
    os << "    storehouse #" << worker2.receiver << std::endl;

    os << "\n== STOREHOUSES ==\n" << std::endl;
    os << "STOREHOUSE #" << storehouse1.id << std::endl;
}

void generate_simulation_turn_report(f: const Factory&, os: std::ostream&, t: Time) {
//LOADING_RAMP id=<ramp-id> delivery-interval=<delivery-interval>
//WORKER id=<worker.get_id()> processing-time=<processing-time> queue-type=<queue-type>
//STOREHOUSE id=<storehouse-id>
//LINK src=<node-type>-<node-id> dest=<node-type>-<node-id>
//TURN turn=<turn-no>
os << "=== [ Turn : {} ] ===\n".format(turn-no) << std::endl;
os << "== WORKERS ==\n" << std::endl;
os << "WORKER #" << worker1.id << std::endl;
os << "  PBuffer: #" << pbelement-id << "(pt = {})".format(processing-time) << std::endl;

bool is_empty = (queue.begin() == queue.end());
os << "  Queue: " << std::endl;
if (!is_empty){
    int queue = [];
    for (auto it = queue.begin(); it != queue.end(); ++it){
        queue.append(*it);
    }
    return queue
} else {
    return "(empty)";
}

os << "  SBuffer: #" << <sbelement-id> << std::endl;


os << "WORKER #" << worker2.id << std::endl;
os << "  PBuffer: #" << <pbelement-id> << "(pt = {})".format(<processing-time>) << std::endl;

bool is_empty = (queue.begin() == queue.end());
os << "  Queue: " << std::endl;
if (!is_empty){
int queue = [];
for (auto it = queue.begin(); it != queue.end(); ++it){
queue.append(*it);
}
return queue
} else {
return "(empty)";
}

os << "  SBuffer: #" << <sbelement-id>

os << "\n== STOREHOUSES ==\n" << std::endl;
os << "STOREHOUSE #" << storehouse1.id << std::endl;

bool is_empty = (queue.begin() == queue.end());
os << "  Stock: " << std::endl;
if (!is_empty){
int queue = [];
for (auto it = queue.begin(); it != queue.end(); ++it){
queue.append(*it);
}
return queue
} else {
return "(empty)";
}

}




#endif //NET_SIM_ZPO_REPORTS_HPP
