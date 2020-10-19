//
// Created by aiden on 20-10-16.
//

#ifndef TOOL_BUILDER_PATTERN_H
#define TOOL_BUILDER_PATTERN_H

#include <iostream>
#include <memory>

namespace patterns {

    class Production{
    public:
        void set_part_a(int param);
        void set_part_b(int param);
        void set_part_c(int param);
        void show();
    private:
        int part_a_;
        int part_b_;
        int part_c_;
    }; // Production

    class AbstractBuilder{
    public:
        AbstractBuilder() = default;
        virtual ~AbstractBuilder() = default;
        virtual void create_porduction() = 0;
        virtual void set_part_a(int param) = 0;
        virtual void set_part_b(int param) = 0;
        virtual void set_part_c(int param) = 0;
        virtual std::shared_ptr<Production> get_production() = 0;
    }; // AbstractBuilder

    class ProductionBuilder: public AbstractBuilder{
    public:
        void create_porduction() override;
        void set_part_a(int param) override;
        void set_part_b(int param) override;
        void set_part_c(int param) override;
        std::shared_ptr<Production> get_production() override;

    private:
        std::shared_ptr<Production> production_ptr_;

    }; // ProductionBuilder

    class Director{
    public:
        Director(std::shared_ptr<AbstractBuilder>& builder);
        ~Director() = default;
        void create();
    private:
        std::shared_ptr<AbstractBuilder> builder_;
    }; // Director

} // patterns


#endif //TOOL_BUILDER_PATTERN_H
