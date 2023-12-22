#include "factory.hpp"
#include <unordered_set>

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

enum class NodeColor { UNVISITED, VISITED, VERIFIED };

static bool hasReachableStorehouse(const Factory& factory, const PackageSender* sender,
                                   std::unordered_map<const PackageSender*, NodeColor>& nodeColors) {
    if (nodeColors[sender] == NodeColor::VERIFIED) {
        return true;
    }

    nodeColors[sender] = NodeColor::VISITED;

    if (!sender->receiver_preferences_.get_preferences().empty()) {
        bool hasOtherReceiver = false;

        for (const auto& [receiver, _] : sender->receiver_preferences_.get_preferences()) {
            if (auto worker = dynamic_cast<const Worker*>(receiver)) {
                if (worker != sender) {
                    hasOtherReceiver = true;
                    if (nodeColors[worker] == NodeColor::UNVISITED &&
                        hasReachableStorehouse(factory, worker, nodeColors)) {
                        return true;
                    }
                }
            } else if (auto ramp = dynamic_cast<const Ramp*>(receiver)) {
                if (nodeColors[ramp] == NodeColor::UNVISITED &&
                    hasReachableStorehouse(factory, ramp, nodeColors)) {
                    return true;
                }
            }
        }

        if (!hasOtherReceiver) {
            return true;
        }
    }

    nodeColors[sender] = NodeColor::VERIFIED;

    return false;
}

bool Factory::is_consistent() const {

    std::unordered_map<const PackageSender*, NodeColor> nodeColors;

    try {
        for (const auto& ramp : ramp_) {
            if (!hasReachableStorehouse(*this, &ramp, nodeColors)) {
                return false;
            }
        }

        for (const auto& worker : worker_) {
            if (!hasReachableStorehouse(*this, &worker, nodeColors)) {
                return false;
            }
        }
    } catch (...) {
        return false;
    }

    return true;
}

