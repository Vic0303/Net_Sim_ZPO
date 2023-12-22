//
// Created by wikto on 28.11.2023.
//

#include <nodes.hpp>
#include <storage_types.hpp>
#include <nodes.hpp>

#ifndef NET_SIM_ZPO_FACTORY_HPP
#define NET_SIM_ZPO_FACTORY_HPP

template <typename Node>
class NodeCollection {
public:
    void add(Node&& node) {}
    void remove_by_id (ElementID id) {}

    using container_t = typename std::vector<Node>;
    using iterator = typename container_t::iterator;
    using const_iterator = typename container_t::const_iterator;

    NodeCollection<Node>::iterator find_by_id(ElementID id) {}
    NodeCollection<Node>::const_iterator find_by_id(ElementID id) const {}
private:
    Node node_;
    ElementID id_;
};


class Factory {
private:
    NodeCollection<Worker> worker_;
    NodeCollection<Ramp> ramp_;
    NodeCollection<Storehouse> storehouse_;
    ElementID id_;

public:
    void add_ramp(Ramp&& ramp) {}
    void remove_ramp(ElementID id) {}
    NodeCollection<Ramp>::iterator find_ramp_by_id(ElementID id) {}
    NodeCollection<Ramp>::const_iterator find_ramp_by_id(ElementID id) const {}
    NodeCollection<Ramp>::const_iterator ramp_cbegin() const {}
    NodeCollection<Ramp>::const_iterator ramp_cend() const {}

    void add_worker(Worker&& worker) {}
    void remove_worker(ElementID id) {}
    NodeCollection<Worker>::iterator find_worker_by_id(ElementID id) {}
    NodeCollection<Worker>::const_iterator find_worker_by_id(ElementID id) const {}
    NodeCollection<Worker>::const_iterator worker_cbegin() const {}
    NodeCollection<Worker>::const_iterator worker_cend() const {}

    void add_storehouse(Storehouse&& storehouse) {}
    void remove_storehouse(ElementID id) {}
    NodeCollection<Storehouse>::iterator find_storehouse_by_id(ElementID id) {}
    NodeCollection<Storehouse>::const_iterator find_storehouse_by_id(ElementID id) const {}
    NodeCollection<Storehouse>::const_iterator storehouse_cbegin() const {}
    NodeCollection<Storehouse>::const_iterator storehouse_cend() const {}

    bool is_consistent() const {}

    void do_deliveries(Time time) {}

    void do_package_passing() {}

    void do_work(Time time) {}

};




#endif //NET_SIM_ZPO_FACTORY_HPP
