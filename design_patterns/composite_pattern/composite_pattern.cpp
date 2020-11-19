//
// Created by aiden on 20-10-20.
//

#include "composite_pattern.h"

namespace patterns {
    namespace compposite_pattern {
        void Component::Operator() {

        }

        void Component::add(std::shared_ptr<Component> component) {

        }

        void Component::remove(int index) {

        }

        std::shared_ptr<Component> Component::get_current_component(int index) {
            return nullptr;
        }

        Leaf::Leaf(std::string name)
            /*: name_(name)*/{
            this->name_ = name;

        }

        void Leaf::Operator() {
            std::cout << this->name_ << ": " << __PRETTY_FUNCTION__ << std::endl;
        }

        Composite::Composite(std::string name)
            /*: name_(name)*/{
            this->name_ = name;
        }

        void Composite::Operator() {
            //todo
            std::cout << this->name_ << ": " << __PRETTY_FUNCTION__ << std::endl;
            for (auto it : this->com_v_)
                it->Operator();
        }

        void Composite::add(std::shared_ptr<Component> component) {
            this->com_v_.push_back(component);
        }

        void Composite::remove(int index) {
            this->com_v_.erase(this->com_v_.begin() + index);
        }

        std::shared_ptr<Component> Composite::get_current_component(int index) {
            return this->com_v_.at(index);
        }

    } // compposite_pattern

} // patterns
