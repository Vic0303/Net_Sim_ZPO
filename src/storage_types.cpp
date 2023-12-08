#include "storage_types.hpp"
//
// Created by artur on 08.12.2023.
//

Package PackageQueue::pop() {
    Package package;
    if (queue_type == PackageQueueType::FIFO) {
        package = std::move(queue.front());
        queue.pop_front();
    } else if (queue_type == PackageQueueType::LIFO) {
        package = std::move(queue.back());
        queue.pop_back();
    }
    return package;
}
