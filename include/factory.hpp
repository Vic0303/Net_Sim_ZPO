//
// Created by wikto on 28.11.2023.
//

#include "nodes.hpp"
#include "storage_types.hpp"

#ifndef NET_SIM_ZPO_FACTORY_HPP
#define NET_SIM_ZPO_FACTORY_HPP

template <typename Node>
class NodeCollection {
public:

    //Dla własnej wygody zdefiniuj wewnątrz szablonu klasy
    // NodeCollection<Node> aliasy na typy iteratorów dla
    // wybranego kontenera z biblioteki standardowej
    // (tu oznaczonego roboczo jako std_container_t, Node oznacza
    // parametr szablonu kolekcji węzłów):

    // Umieszczenie słowa kluczowego `typename`
    // jest niezbędne aby poinformować
// kompilator, że `Node` to nazwa typu.
    using container_t = typename std::vector<Node>;
    using iterator = typename container_t::iterator;
    using const_iterator = typename container_t::const_iterator;

    // Dodawanie obiektu do kontenera
    void add(Node&& node) {
        node_vector_.push_back(std::move(node));
        //Metoda add() powinna “zawłaszczać” przekazany obiekt węzła
        //(gdyż wszelkie dalsze odwoływanie się do takiego obiektu węzła
        // powinno odbywać się poprzez obiekt klasy Factory) –
        //do realizacji metody add() użyj funkcji std::move().
    }

    // Wyszukiwanie obiektu po identyfikatorze
    iterator find_by_id(ElementID id) {
        auto it = std::find_if(node_vector_.begin(), node_vector_.end(),[id](auto& elem)
        {
            return (elem.get_id() == id);
        });
        return it;
    }
    //W przypadku nieznalezienia elementu o zadanym
    // ID obie wersje metody find_by_id() (jedna zwracającą
    // “zwykły” iterator, druga zwracająca const-iterator) powinny
    //zwrócić iterator na element tuż za końcem zakresu. Obie wersje
    // metody find_by_id() możesz zrealizować za pomocą jednej instrukcji
    // , używając algorytmu std::find_if i odpowiedniej lambdy
    // (zwracającej prawdę w przypadku, gdy ID węzła
    //w kolekcji pasuje do przekazanego ID).

    // Wyszukiwanie obiektu po identyfikatorze (wersja const)
    const_iterator find_by_id(ElementID id) const {
        auto it = std::find_if(node_vector_.cbegin(), node_vector_.cend(),[id](const auto& elem)
                               { return (elem.get_id() == id);
                               });
        return it;
    }

    // Usuwanie obiektu po identyfikatorze
    void remove_by_id(ElementID id) {
        //z wykorzystaniem metody find_by_id() – wystarczy usunąć
        // element wskazywany przez zwrócony iterator wywołując na
        // kontenerze metodę erase() (musisz się tylko wcześniej upewnić,
        // że element faktycznie został znaleziony! –
        auto it = std::find_if(node_vector_.begin(), node_vector_.end(),[id](auto& elem)
        {
            //This code is using the std::find_if algorithm from the C++
            // Standard Library to search for an element in the range defined
            // by node_vector_.begin() and node_vector_.end() that satisfies a
            // certain condition.
            //Here's a breakdown of each part of the code:
            return (elem.get_id() == id);
        });
        if (it != node_vector_.end())
        {
            node_vector_.erase(it);
        }
    }

    // Iterator na początek kontenera (wersja const)
    const_iterator cbegin() const { return node_vector_.cbegin(); }

    // Iterator na koniec kontenera (wersja const)
    const_iterator cend() const { return node_vector_.cend(); }

    // Iterator na początek kontenera (wersja niemodyfikowalna)
    const_iterator begin() const { return node_vector_.begin(); }

    // Iterator na koniec kontenera (wersja niemodyfikowalna)
    const_iterator end() const { return node_vector_.end(); }

    // Iterator na początek kontenera (wersja modyfikowalna)
    iterator begin() { return node_vector_.begin(); }

    // Iterator na koniec kontenera (wersja modyfikowalna)
    iterator end() { return node_vector_.end(); }

private:
    container_t node_vector_;  // Kontener przechowujący obiekty typu Node

};



class Factory {
private:
    NodeCollection<Worker> worker_;
    NodeCollection<Ramp> ramp_;
    NodeCollection<Storehouse> storehouse_;
    ElementID id_;

public:
    void add_ramp(Ramp&& ramp) {ramp_.add(std::move(ramp));}
    void remove_ramp(ElementID id) {}
    NodeCollection<Ramp>::iterator find_ramp_by_id(ElementID id) {return ramp_.find_by_id(id);}
    NodeCollection<Ramp>::const_iterator find_ramp_by_id(ElementID id) const {return ramp_.find_by_id(id);}
    NodeCollection<Ramp>::const_iterator ramp_cbegin() const {return ramp_.cbegin();}
    NodeCollection<Ramp>::const_iterator ramp_cend() const {return ramp_.cend();}

    void add_worker(Worker&& worker) {worker_.add(std::move(worker));}
    void remove_worker(ElementID id) {}
    NodeCollection<Worker>::iterator find_worker_by_id(ElementID id) {return worker_.find_by_id(id);}
    NodeCollection<Worker>::const_iterator find_worker_by_id(ElementID id) const {return worker_.find_by_id(id);}
    NodeCollection<Worker>::const_iterator worker_cbegin() const {return worker_.cbegin();}
    NodeCollection<Worker>::const_iterator worker_cend() const {return worker_.cend();}

    void add_storehouse(Storehouse&& storehouse) {storehouse_.add(std::move(storehouse));}
    void remove_storehouse(ElementID id) {}
    NodeCollection<Storehouse>::iterator find_storehouse_by_id(ElementID id) {return storehouse_.find_by_id(id);}
    NodeCollection<Storehouse>::const_iterator find_storehouse_by_id(ElementID id) const {return storehouse_.find_by_id(id);}
    NodeCollection<Storehouse>::const_iterator storehouse_cbegin() const {return storehouse_.cbegin();}
    NodeCollection<Storehouse>::const_iterator storehouse_cend() const {return storehouse_.cend();}

    bool is_consistent() const {
        return true;
    }

    void do_deliveries(Time time);

    void do_package_passing();

    void do_work(Time time);

};


#endif //NET_SIM_ZPO_FACTORY_HPP