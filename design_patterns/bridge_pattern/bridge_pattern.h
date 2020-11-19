//
// Created by aiden on 20-10-19.
//

#ifndef TOOL_BRIDGE_PATTERN_H
#define TOOL_BRIDGE_PATTERN_H

#include <iostream>
#include <memory>

namespace patterns {

    class Abstract {
    public:
        virtual void Operation() = 0;
    }; // Abstract

    class ImplementAbstract{
    public:
        virtual void Operation();
    }; // ImplementAbstract

    class ConcreteImplementA: public ImplementAbstract{
    public:
        void Operation() override;
    }; // ConcretImpelmentA

    class ConcreteImplementB: public ImplementAbstract{
    public:
        void Operation() override;
    }; // ConcretImpelmentB

    class RefineAbstractA: public Abstract{
    public:
        void Operation() override;
        RefineAbstractA(std::shared_ptr<ImplementAbstract>& impelment);
    private:
        std::shared_ptr<ImplementAbstract> impelment_;
    }; // RefineAbstractA

    class RefineAbstractB: public Abstract{
    public:
        void Operation() override;
        RefineAbstractB(std::shared_ptr<ImplementAbstract>& impelment);
    private:
        std::shared_ptr<ImplementAbstract> impelment_;
    }; // RefineAbstractB

} // patterns


#endif //TOOL_BRIDGE_PATTERN_H
