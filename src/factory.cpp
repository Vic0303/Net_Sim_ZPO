#include "factory.hpp"

void Factory::do_work(Time time) {

    for (auto worker_iter = worker_.begin(); worker_iter != worker_.end(); ++worker_iter) {
        worker_iter->do_work(time);
    }
}

void Factory::do_deliveries(Time time) {
    for (auto ramp_iter = ramp_.begin(); ramp_iter != ramp_.end(); ++ramp_iter) {
        ramp_iter->deliver_goods(time);
    }
}

void Factory::do_package_passing() {
    for (auto& worker : worker_) {
        worker.send_package();
    }
}