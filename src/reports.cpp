//
// Created by wikto on 02.01.2024.
//
#include "reports.hpp"
#include <algorithm>


std::ostream& operator<<(std::ostream& os, ReceiverType receiverType) {
    switch(receiverType) {
        case ReceiverType::WORKER:
            os << "worker";
            break;
        case ReceiverType::STOREHOUSE:
            os << "storehouse";
            break;
    }
    return os;
}

bool compareReceivers(const std::pair<IPackageReceiver*, double>& receiver1,
                      const std::pair<IPackageReceiver*, double>& receiver2) {
    if (receiver1.first->get_receiver_type() != receiver2.first->get_receiver_type()) {
        return receiver1.first->get_receiver_type() < receiver2.first->get_receiver_type();
    }
    return receiver1.first->get_id() < receiver2.first->get_id();
}

void generate_structure_report(const Factory& factory, std::ostream& os) {
    os << "" << std::endl;
    os << "== LOADING RAMPS ==" << std::endl;
    for (const auto& ramp : factory.getRamps()) {
        os << std::endl << "LOADING RAMP #" << ramp.get_id() << std::endl;
        os << "  Delivery interval: " << ramp.get_delivery_interval() << std::endl;
        os << "  Receivers:" << std::endl;

        auto receivers = ramp.receiver_preferences_.get_preferences();

        std::vector<std::pair<IPackageReceiver*, double>> receiverVector(receivers.begin(), receivers.end());

        std::sort(receiverVector.begin(), receiverVector.end(), compareReceivers);

        for (const auto& receiver : receiverVector) {
            os << "    " << receiver.first->get_receiver_type() << " #" << receiver.first->get_id() << std::endl;
        }
    }
    os << "" << std::endl;
    os << std::endl << "== WORKERS ==" << std::endl;
    for (const auto& worker : factory.getWorkers()) {
        os << std::endl << "WORKER #" << worker.get_id() << std::endl;
        os << "  Processing time: " << worker.get_processing_duration() << std::endl;
        os << "  Queue type: " << (worker.get_queue()->get_queue_type() == PackageQueueType::FIFO ? "FIFO" : "LIFO") << std::endl;
        os << "  Receivers:" << std::endl;

        auto receivers = worker.receiver_preferences_.get_preferences();

        std::vector<std::pair<IPackageReceiver*, double>> receiverVector(receivers.begin(), receivers.end());

        std::sort(receiverVector.begin(), receiverVector.end(), compareReceivers);

        for (const auto& receiver : receiverVector) {
            os << "    " << receiver.first->get_receiver_type() << " #" << receiver.first->get_id() << std::endl;
        }
    }
    os << "" << std::endl;
    os << std::endl << "== STOREHOUSES ==" << std::endl;

    for (const auto& storehouse : factory.getStorehouses()) {
        os << std::endl << "STOREHOUSE #" << storehouse.get_id() << std::endl;
    }
    os << "" << std::endl;
}

// ... (other includes and definitions)

void generate_simulation_turn_report(const Factory& factory, std::ostream& os, Time t) {
    os << "=== [ Turn: " << t << " ] ===" << std::endl << std::endl;

    os << "== WORKERS ==" << std::endl;
    for (const auto& worker : factory.getWorkers()) {
        os << std::endl << "WORKER #" << worker.get_id() << std::endl;
        os << "  PBuffer: " << (worker.get_processing_buffer().has_value() ? "#" + std::to_string(worker.get_processing_buffer()->get_id()) + " (pt = " + std::to_string(worker.get_package_processing_start_time()) + ")" : "(empty)") << std::endl;
        os << "  Queue:";
        if (worker.get_queue()->cbegin() == worker.get_queue()->cend()) {
            os << " (empty)";
        } else {
            for (const auto& package : *worker.get_queue()) {
                os << " #" << package.get_id();
            }
        }
        os << "" << std::endl;
        os << "  SBuffer: " << (worker.get_sending_buffer().has_value() ? "#" + std::to_string(worker.get_sending_buffer()->get_id()) : "(empty)") << std::endl;
    }
    os << std::endl;
    os << std::endl << "== STOREHOUSES ==" << std::endl;
    for (const auto& storehouse : factory.getStorehouses()) {
        os << std::endl << "STOREHOUSE #" << storehouse.get_id() << std::endl;
        os << "  Stock:";
        if (storehouse.cbegin() == storehouse.cend()) {
            os << " (empty)";
        } else {
            for (const auto& package : storehouse) {
                os << " #" << package.get_id();
            }
        }
        os << std::endl;
    }
    os << "" << std::endl;
}



