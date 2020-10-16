//
// Created by aiden on 20-10-15.
//

#ifndef TOOL_ABSTRACT_FACTORY_PATTERN_H
#define TOOL_ABSTRACT_FACTORY_PATTERN_H

#include <iostream>
#include <memory>

namespace patterns {
    namespace abstract_factory {

        class ProductionBasicA{
        public:
            virtual void create_a() = 0;
        };

        class ProductionA_1 : public ProductionBasicA{
        public:
            void create_a() override;
        };

        class ProductionA_2 : public ProductionBasicA{
        public:
            void create_a() override;
        };



        class ProductionBasicB{
        public:
            virtual void create_b() = 0;
        };

        class ProductionB_1 : public ProductionBasicB{
        public:
            void create_b() override;
        };

        class ProductionB_2 : public ProductionBasicB{
        public:
            void create_b() override;
        };



        class FactoryBasic{
        public:
            virtual std::shared_ptr<ProductionBasicA> create_production_a() = 0;
            virtual std::shared_ptr<ProductionBasicB> create_production_b() = 0;
        };

        class Factory1: public FactoryBasic{
        public:
            std::shared_ptr<ProductionBasicA> create_production_a() override;
            std::shared_ptr<ProductionBasicB> create_production_b() override;
        };

        class Factory2: public FactoryBasic{
        public:
            std::shared_ptr<ProductionBasicA> create_production_a() override;
            std::shared_ptr<ProductionBasicB> create_production_b() override;
        };


    } // abstract_factory

} // patterns


#endif //TOOL_ABSTRACT_FACTORY_PATTERN_H
