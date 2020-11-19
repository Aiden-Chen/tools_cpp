//
// Created by aiden on 20-10-20.
//

#ifndef TOOL_COMPOSITE_PATTERN_H
#define TOOL_COMPOSITE_PATTERN_H

#include <iostream>
#include <memory>
#include <vector>

namespace patterns {

    namespace compposite_pattern {

        class Component {
        public:
            virtual ~Component() = default;

            virtual void Operator();

            virtual void add(std::shared_ptr<Component> component);

            virtual void remove(int index);

            virtual std::shared_ptr<Component> get_current_component(int index);
        }; // component

        class Leaf : public Component {
        public:
            Leaf(std::string name);
            virtual void Operator();

        private:
            std::string name_;
        }; // Leaf

        class Composite : public Component {
        public:
            Composite(std::string name);
            virtual void Operator();

            void add(std::shared_ptr<Component> component);

            void remove(int index);

            std::shared_ptr<Component> get_current_component(int index);

        private:
            std::vector<std::shared_ptr<Component> > com_v_;

            std::string name_;
        }; // Composite

    } // composite patterns

} // patterns


#endif //TOOL_COMPOSITE_PATTERN_H
