//
// Created by aiden on 20-10-19.
//

#ifndef TOOL_DECORATOR_PATTERN_H
#define TOOL_DECORATOR_PATTERN_H

#include <iostream>
#include <memory>

namespace patterns {

    class Component {
    public:
        virtual void Operation() = 0;
    }; // Component

    class ConcreteComponent: public Component{
    public:
        void Operation() override;
    }; // ConcreateComponent

    class Decorator: public Component{
    public:
        virtual ~Decorator() = default;
        void Operation() override;
        void setComponent(std::shared_ptr<Component>& component);

    protected:
        std::shared_ptr<Component> component_;
    }; // Decorator

    class ConcreteDecoratorA: public Decorator{
    public:
        ConcreteDecoratorA(std::string name);
        std::string get_name();

    private:
        std::string name_;

    }; // ConcreateDecorator

    class ConcreteDecoratorB: public Decorator{
    public:
        void add_behavior();

    }; // ConcreateDecorator

} // patterns


#endif //TOOL_DECORATOR_PATTERN_H
