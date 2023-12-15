//
// Created by wikto on 28.11.2023.
//

#ifndef NET_SIM_ZPO_NODES_HPP
#define NET_SIM_ZPO_NODES_HPP

#include <optional>
#include "config.hpp"
#include "storage_types.hpp"
#include "types.hpp"
#include "memory"

class IPackageReceiver{
public:
    virtual void receive_package(Package &&p) = 0;
    virtual ElementID get_id() = 0;

    virtual IPackageStockpile::const_iterator begin() const = 0;
    virtual IPackageStockpile::const_iterator end() const = 0;
    virtual IPackageStockpile::const_iterator cbegin() const = 0;
    virtual IPackageStockpile::const_iterator cend() const = 0;

    #if (defined EXERCISE_ID && EXERCISE_ID != EXERCISE_ID_NODES)
    virtual ReceiverType get_receiver_type() const = 0;
    #endif

    virtual ~IPackageReceiver() = default;
};

class Storehouse: public IPackageReceiver {
public:
    Storehouse(ElementID id, std::unique_ptr<IPackageStockpile>
            d = std::make_unique<PackageQueue>(PackageQueueType::FIFO)) : id_(id), d_(std::move(d)) {}

    ElementID get_id() override { return id_; }
    void receive_package(Package &&p) override { d_->push(std::move(p)); }

    IPackageStockpile::const_iterator cbegin() const override { return d_->cbegin(); }
    IPackageStockpile::const_iterator cend() const override { return d_->cend(); }
    IPackageStockpile::const_iterator begin() const override { return d_->begin(); }
    IPackageStockpile::const_iterator end() const override { return d_->end(); }


private:
    ElementID id_;
    std::unique_ptr<IPackageStockpile> d_;
};

class PackageSender {
public:
    // konstruktor i konstruktor przenoszący
    PackageSender() = default;
    PackageSender(PackageSender &&packageSender) = default;

    void send_package();
    const std::optional<Package> &get_sending_buffer() const { return bufor_; }

protected:
    void push_package(Package &&package) { bufor_.emplace(package.get_id()); };

private:
    // Język C++ nie udostępnia specjalnych obiektów i literałów w stylu None w języku Python albo null w
    // języku Java, umożliwiających każdej zmiennej pełnienie roli bufora, natomiast
    // począwszy od standardu C++17 funkcjonalność taka jest dostępna z użyciem kontenera
    // standardowego std::optional.
    std::optional<Package> bufor_ = std::nullopt;
};

class Worker : public IPackageReceiver, public PackageSender {
public:
    Worker(ElementID id, TimeOffset pd, std::unique_ptr<IPackageQueue> q)
            : PackageSender(), id_(id), pd_(pd), q_(std::move(q)) {}

    void do_work(Time t);
    TimeOffset get_processing_duration() const { return pd_; }
    Time get_package_processing_start_time() const { return t_; }

    // Funkcja pomocnicza
    void process_buffer();

    void receive_package(Package &&p) override {q_->push(std::move(p)); }
    ElementID get_id() override { return id_; }

    IPackageStockpile::const_iterator cbegin() const override { return q_->cbegin(); }
    IPackageStockpile::const_iterator cend() const override { return q_->cend(); }
    IPackageStockpile::const_iterator begin() const override { return q_->begin(); }
    IPackageStockpile::const_iterator end() const override { return q_->end(); }


private:
    ElementID id_;
    TimeOffset pd_;
    std::unique_ptr<IPackageQueue> q_;
    Time t_{};
    // Język C++ nie udostępnia specjalnych obiektów i literałów w stylu None w języku Python albo null w
    // języku Java, umożliwiających każdej zmiennej pełnienie roli bufora, natomiast
    // począwszy od standardu C++17 funkcjonalność taka jest dostępna z użyciem kontenera
    // standardowego std::optional.
    std::optional<Package> bufor_ = std::nullopt;

};



#endif //NET_SIM_ZPO_NODES_HPP
