//
// Created by aiden on 20-10-19.
//

#include "adapter_pattern.h"

namespace patterns{
    std::string Target::get_name() {
        return "None";
    }

    std::string Adaptee::get_person_name() {
        return "person: ";
    }

    AdapterClass::AdapterClass(std::string name)
        : name_(std::move(name)){
    }

    std::string AdapterClass::get_name() {
        return this->get_person_name() + this->name_;
    }

    AdapterObject::AdapterObject(std::shared_ptr<patterns::Adaptee> adaptee,
            std::string &name)
        : adaptee_(std::move(adaptee)), name_(name){

    }

    std::string AdapterObject::get_name() {
        return adaptee_->get_person_name() + this->name_;
    }
} // patterns
