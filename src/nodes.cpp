//
// Created by wikto on 15.12.2023.
//
#include <nodes.hpp>

void Worker::process_buffer() {
    push_package(Package(bufor_.value().get_id()));
    bufor_.reset();
}

void Worker::do_work(Time t) {
    // Sprawdzenie czy bufor jest pusty i czy kolejka nie jest pusta
    if (!bufor_ && !q_->empty()) {
        bufor_.emplace(q_->pop());
        t_ = t;
    } else {
        // Sprawdzenie czy warunek czasowy jest spełniony
        if (t - t_ + 1 == pd_) {
            process_buffer();
            // Jeżeli kolejka nie jest pusta nowy element umieszczany w buforze
            if (!q_->empty()) {
                bufor_.emplace(q_->pop());
            }
        }
    }
}