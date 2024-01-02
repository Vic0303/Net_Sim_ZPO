//
// Created by wikto on 28.11.2023.
//


#ifndef NET_SIM_ZPO_FACTORY_HPP
#define NET_SIM_ZPO_FACTORY_HPP

#include "types.hpp"
#include "package.hpp"
#include "nodes.hpp"
#include "storage_types.hpp"
#include <vector>
#include <stdexcept>
#include <algorithm>

template <class Node>
class NodeCollection {
public:
    using container_t = typename std::list<Node>;
    using iterator = typename container_t::iterator;
    using const_iterator = typename container_t::const_iterator;

    void add(Node&& node) { node_vector_.push_back(std::move(node));}
    void remove_by_id(ElementID id);

    NodeCollection<Node>::iterator find_by_id(ElementID id) {return std::find_if(node_vector_.begin(), node_vector_.end(), [id](Node& elem) {return elem.get_id()==id;});}
    NodeCollection<Node>::const_iterator find_by_id(ElementID id) const {return std::find_if(node_vector_.cbegin(), node_vector_.cend(), [id] (const Node& elem) {return elem.get_id()==id;});}


    iterator begin() { return node_vector_.begin() ;}
    iterator end() {return node_vector_.end();}

    const_iterator cbegin() const {return node_vector_.cbegin();}
    const_iterator cend() const {return node_vector_.cend();}
    const_iterator begin() const {return node_vector_.begin();}
    const_iterator end() const {return node_vector_.end();}
private:
    container_t node_vector_;

};

class Factory {
public:

    void add_ramp(Ramp&& ramp) { ramp_.add(std::move(ramp)); };
    void remove_ramp(ElementID id) { ramp_.remove_by_id(id); };
    NodeCollection<Ramp>::iterator find_ramp_by_id(ElementID id) { return ramp_.find_by_id(id); };
    NodeCollection<Ramp>::const_iterator find_ramp_by_id(ElementID id) const { return ramp_.find_by_id(id); };
    NodeCollection<Ramp>::const_iterator ramp_cbegin() { return ramp_.cbegin(); };
    NodeCollection<Ramp>::const_iterator ramp_cend() { return ramp_.cend(); };


    void add_worker(Worker&& worker) { worker_.add(std::move(worker)); }
    void remove_worker(ElementID id);
    NodeCollection<Worker>::iterator find_worker_by_id(ElementID id) { return worker_.find_by_id(id); };
    NodeCollection<Worker>::const_iterator find_worker_by_id(ElementID id) const { return worker_.find_by_id(id); }
    NodeCollection<Worker>::const_iterator worker_cbegin() { return worker_.cbegin(); };
    NodeCollection<Worker>::const_iterator worker_cend() { return worker_.cend(); };


    void add_storehouse(Storehouse&& storehouse) { storehouse_.add(std::move(storehouse)); }
    void remove_storehouse(ElementID id);
    NodeCollection<Storehouse>::iterator find_storehouse_by_id(ElementID id) { return storehouse_.find_by_id(id); };
    NodeCollection<Storehouse>::const_iterator find_storehouse_by_id(ElementID id) const { return storehouse_.find_by_id(id); }
    NodeCollection<Storehouse>::const_iterator storehouse_cbegin() { return storehouse_.cbegin(); };
    NodeCollection<Storehouse>::const_iterator storehouse_cend() { return storehouse_.cend(); };

    bool is_consistent();

    void do_deliveries(Time t);

    void do_work(Time t);

    void do_package_passing();

private:
    NodeCollection<Ramp> ramp_;
    NodeCollection<Worker> worker_;
    NodeCollection<Storehouse> storehouse_;

    template<class Node>
    void remove_receiver(NodeCollection<Node>& collection, ElementID id);
};

enum ElementType {
    RAMP, WORKER, STOREHOUSE, LINK,
};

struct ParsedLineData{
    ElementType element_type;
    std::map<std::string, std::string> mapped;
};

ParsedLineData parse_line(std::string line);

Factory load_factory_structure(std::istream& input_stream);

void save_factory_structure(Factory& factory, std::ostream& output_stream);



#endif //NET_SIM_ZPO_FACTORY_HPP
