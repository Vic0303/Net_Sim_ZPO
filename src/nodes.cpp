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
    if (!bufor_ && !q_->empty())
    {
        bufor_.emplace(q_->pop());
        t_ = t;
    } else {
        // Sprawdzenie czy warunek czasowy jest spełniony
        if (t - t_ + 1 == pd_)
        {
            process_buffer();
            // Jeżeli kolejka nie jest pusta nowy element umieszczany w buforze
            if (!q_->empty())
            {
                bufor_.emplace(q_->pop());
            }
        }
    }
}
void ReceiverPreferences::add_receiver(IPackageReceiver *r) {

    double numbersss = double(preferences_.size());
    if (numbersss == 0)
    {
        preferences_[r] = 1.0;
    } else
    {
        for (auto &rec: preferences_)
        {
            rec.second = 1 / (numbersss + 1);
        }
        preferences_[r] = 1 / (numbersss + 1);
    }
}



void ReceiverPreferences::remove_receiver(IPackageReceiver *r) {
    double numberss = double(preferences_.size());
    if (numberss > 1) {
        for (auto &rec: preferences_) {
            if (rec.first != r) {
                rec.second = 1 / (numberss - 1);
            }
        }
    }
    preferences_.erase(r);
}

IPackageReceiver *ReceiverPreferences::choose_receiver() {
    auto p = pg_();
    if (p >= 0 && p <= 1) {
        double distribution = 0.0;
        for (auto &rec: preferences_)
        {
            distribution = distribution + rec.second;
            if (distribution < 0 || distribution > 1)
            {
                return nullptr;
            }
            if (p <= distribution)
            {
                return rec.first;
            }
        }
        return nullptr;
    }
    return nullptr;
}

void PackageSender::send_package() {
    IPackageReceiver *receiver;
    if (bufor_)
    {
        receiver = receiver_preferences_.choose_receiver();
        receiver->receive_package(std::move(*bufor_));
        bufor_.reset();
    }
}

void Ramp::deliver_goods(Time t) {
    if (!bufor_)
    {
        push_package(Package());
        bufor_.emplace(id_);
        t_ = t;
    }
    else
    {
        if (t - di_ == t_)
        {
            push_package(Package());
        }
    }
}
