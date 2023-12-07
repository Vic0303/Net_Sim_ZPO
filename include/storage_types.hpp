//
// Created by wikto on 28.11.2023.
//

#ifndef NET_SIM_ZPO_STORAGE_TYPES_HPP
#define NET_SIM_ZPO_STORAGE_TYPES_HPP


class IPackageStockpile{
public:
};

class IPackageQueue : public IPackageStockpile{
public:
    virtual Package pop() = 0;
};

class PackageQueue : IPackageQueue{
public:
    PackageQueue(PackageQueueType) = int;
private:
    PackageQueueuType
};

enum class PackageQueueType{
    FIFO,LIFO
};

PackageQueueType t = PackageQueueType::FIFO;

switch(t){
    case PackageQueueType::FIFO:
        std::cout << "FIFO" << std::endl;
        break;
    case PackageQueueType::LIFO:
        std::cout << "LIFO" << std::endl;
        break;
}

#endif //NET_SIM_ZPO_STORAGE_TYPES_HPP
