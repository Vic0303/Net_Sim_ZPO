//
// Created by wikto on 28.11.2023.
//
#include "package.hpp"


#include "package.hpp"
//Do realizacji mechanizmu przydzielania unikalnego ID możesz użyć dwóch pól statycznych typu set<ElementID> – jeden zbiór (assigned_IDs)
// przechowywać będzie przydzielone obecnie ID, a drugi (freed_IDs) ID kiedyś użyte, ale obecnie zwolnione
std::set<ElementID> Package::assigned_IDs = {};
std::set<ElementID> Package::freed_IDs = {};

Package::Package() {
    //Gdy zachodzi konieczność przydzielenia ID dla nowo tworzonego półproduktu, w pierwszej kolejności
    // rozpatrywane są identyfikatory ze zbioru freed_IDs; jeśli brak takich – wówczas przydzielany jest nowy
    // identyfikator, o
    //1
    // większy od największego identyfikatora w zbiorze assigned_IDs
    if (assigned_IDs.empty() && freed_IDs.empty()) {
        ID_ = 1;
    }
    else if (!freed_IDs.empty()) {
        ID_ = *freed_IDs.begin();
        freed_IDs.erase(*freed_IDs.begin());
    } else if(!assigned_IDs.empty())
    {
        ID_ = *assigned_IDs.end() + 1;
    }
    assigned_IDs.insert(ID_);
}



Package::~Package() {
    //Podczas usuwania obiektu klasy Package należy przenieść jego
    // identyfikator ze zbioru assigned_IDs do zbioru freed_IDs.
    freed_IDs.insert(ID_);
    assigned_IDs.erase(ID_);
}