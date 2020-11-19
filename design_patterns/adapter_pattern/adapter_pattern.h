//
// Created by aiden on 20-10-19.
//

#ifndef TOOL_ADAPTER_PATTERN_H
#define TOOL_ADAPTER_PATTERN_H

#include <iostream>
#include <memory>


namespace patterns {

    class Target {
    public:
        Target() = default;
        virtual ~Target() = default;

        virtual std::string get_name();
    }; // Target

    class Adaptee{
    public:
        std::string get_person_name();
    }; //Adaptee

    // 类适配器
    class AdapterClass: public Target, private Adaptee{
    public:
        AdapterClass(std::string name);
        std::string get_name();
    private:
        std::string name_;
    }; // AdapterClass

    // 对象适配器
    class AdapterObject: public Target{
    public:
        AdapterObject(std::shared_ptr<Adaptee> adaptee, std::string &name);
        std::string get_name();
    private:
        std::shared_ptr<Adaptee> adaptee_;
        std::string name_;
    }; // AdapterObject

} // patterns


#endif //TOOL_ADAPTER_PATTERN_H
