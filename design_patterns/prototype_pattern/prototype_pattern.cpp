//
// Created by aiden on 20-10-18.
//

#include "prototype_pattern.h"

namespace patterns {
    PrototypePattern::PrototypePattern() {
        this->type_ = "None";
    }

    PrototypePattern::PrototypePattern(std::string &type) {
        this->type_ = type;
    }

    PrototypePattern::PrototypePattern(const patterns::PrototypePattern &prototypePattern) {
        this->type_ = prototypePattern.type_;
    }

    void PrototypePattern::show() {
        std::cout << this->type_ << std::endl;
    }

    PrototypePattern* PrototypePattern::clone() {
        return new PrototypePattern(*this);
    }
}