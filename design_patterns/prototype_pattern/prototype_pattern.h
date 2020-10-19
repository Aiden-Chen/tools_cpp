//
// Created by aiden on 20-10-18.
//

#ifndef TOOL_PROTOTYPE_PATTERN_H
#define TOOL_PROTOTYPE_PATTERN_H

#include <iostream>
#include <memory>

namespace patterns {

    class PrototypePattern {
    public:
        PrototypePattern();
        explicit PrototypePattern(std::string& type);
        explicit PrototypePattern(const PrototypePattern& prototypePattern);
        ~PrototypePattern() = default;

        void show();
        PrototypePattern* clone();

    private:
        std::string type_;
    }; // PrototypePattern

} // patterns


#endif //TOOL_PROTOTYPE_PATTERN_H
