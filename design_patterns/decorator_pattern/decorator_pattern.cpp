//
// Created by aiden on 20-10-19.
//

#include "decorator_pattern.h"

namespace patterns{

    void ConcreteComponent::Operation() {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }

    void Decorator::Operation() {
        this->component_->Operation();
    }

    void Decorator::setComponent(std::shared_ptr<patterns::Component> &component) {
        this->component_ = component;
    }

    ConcreteDecoratorA::ConcreteDecoratorA(std::string name) {
        this->name_ = name;
    }

    std::string ConcreteDecoratorA::get_name() {
        return this->name_;
    }

    void ConcreteDecoratorB::add_behavior() {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
} // patterns