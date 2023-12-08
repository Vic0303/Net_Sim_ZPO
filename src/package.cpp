//Do realizacji mechanizmu przydzielania unikalnego ID możesz użyć dwóch pól
// statycznych typu set<ElementID> – jeden zbiór (assigned_IDs) przechowywać
// będzie przydzielone obecnie ID, a drugi (freed_IDs) ID kiedyś użyte, ale obecnie zwolnione:
#include "package.hpp"
std::set<ElementID> Package::assigned_IDs = {};
std::set<ElementID> Package::freed_IDs = {};

Package::Package() {
    //metodę empty() zwracającą wartość logiczną prawda,
    // jeśli kontener nie zawiera żadnych elementów (w przeciwnym razie zwraca fałsz)

    //Gdy zachodzi konieczność przydzielenia ID dla nowo tworzonego półproduktu,
    // w pierwszej kolejności rozpatrywane są identyfikatory ze zbioru freed_IDs;
    // jeśli brak takich – wówczas przydzielany jest nowy identyfikator, o
    //1
    // większy od największego identyfikatora w zbiorze assigned_IDs (każdorazowo zbiór
    // assigned_IDs jest odpowiednio aktua
    ElementID new_id;
    if (!freed_IDs.empty())
    {
        new_id = *freed_IDs.begin();
        freed_IDs.erase(new_id);
    }
    else if (assigned_IDs.empty() && freed_IDs.empty()) {
        new_id = 1;
    }

    else
    {
        new_id = *assigned_IDs.end() + 1;
    }
    assigned_IDs.insert(id_);
    id_=new_id;
}



Package::Package(Package &&p)
{
    id_ = p.id_;
    p.id_ = -1;
}

Package &Package::operator=(Package &&p)    {
    if(id_ != -1){
        freed_IDs.insert(id_);
        assigned_IDs.erase(id_);
    }
    id_ = p.id_;
    p.id_ = -1;
    return *this;
}

//Podczas usuwania obiektu klasy Package należy przenieść jego
// identyfikator ze zbioru assigned_IDs do zbioru freed_IDs.

Package::~Package() {
    if(id_ != -1) {
        freed_IDs.insert(id_);
        assigned_IDs.erase(id_);
    }
}
