//
// Created by aiden on 20-10-16.
//

#include "builder_pattern.h"

namespace patterns {
    void Production::set_part_a(int param) {
        this->part_a_ = param;
    }

    void Production::set_part_b(int param) {
        this->part_b_ = param;
    }

    void Production::set_part_c(int param) {
        this->part_c_ = param;
    }

    void Production::show() {
        std::cout << "Production, part_a: " << part_a_
                  << ", part_b: " << part_b_
                  << ", part_c: " << part_c_ << std::endl;
    }

    void ProductionBuilder::create_porduction() {
        this->production_ptr_ = std::make_shared<Production>();
    }

    void ProductionBuilder::set_part_a(int param) {
        this->production_ptr_->set_part_a(param);
    }

    void ProductionBuilder::set_part_b(int param) {
        this->production_ptr_->set_part_b(param);
    }

    void ProductionBuilder::set_part_c(int param) {
        this->production_ptr_->set_part_c(param);
    }

    std::shared_ptr<Production> ProductionBuilder::get_production() {
        return this->production_ptr_;
    }

    Director::Director(std::shared_ptr<AbstractBuilder>& builder) {
        this->builder_ = builder;
    }

    void Director::create() {
        this->builder_->create_porduction();
        this->builder_->set_part_a(1);
        this->builder_->set_part_b(2);
        this->builder_->set_part_c(3);
    }


} // patterns