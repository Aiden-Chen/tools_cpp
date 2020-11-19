//
// Created by aiden on 20-10-19.
//

#include "bridge_pattern.h"

namespace patterns {

    void ImplementAbstract::Operation() {

    }

    void ConcreteImplementA::Operation() {
        std::cout << "ConcretImpelmentA::Operation()" << std::endl;
    }

    void ConcreteImplementB::Operation() {
        std::cout << "ConcretImpelmentB::Operation()" << std::endl;
    }

    RefineAbstractA::RefineAbstractA(std::shared_ptr<patterns::ImplementAbstract>& impelment) {
        this->impelment_ = impelment;
    }

    void RefineAbstractA::Operation() {
        std::cout << "RefineAbstractA::Operation()" << std::endl;
        this->impelment_->Operation();
    }

    RefineAbstractB::RefineAbstractB(std::shared_ptr<patterns::ImplementAbstract>& impelment)
        : impelment_(impelment){

    }

    void RefineAbstractB::Operation() {
        std::cout << "RefineAbstractB::Operation()" << std::endl;
        this->impelment_->Operation();
    }
} // patterns
