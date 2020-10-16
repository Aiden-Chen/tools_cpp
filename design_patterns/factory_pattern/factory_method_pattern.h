//
// Created by aiden on 20-10-15.
//

#ifndef TOOL_FACTORY_METHOD_PATTERN_H
#define TOOL_FACTORY_METHOD_PATTERN_H

#include <memory>

namespace patterns {
    namespace factory_method {

        class ProBasic {
        public:
            virtual void product_fun() = 0;
        }; // ProBasic

        class Pro_0 : public ProBasic {
        public:
            void product_fun() override;
        }; //Pro_0

        class Pro_1 : public ProBasic {
        public:
            void product_fun() override;
        }; //Pro_1

        class Pro_2 : public ProBasic {
        public:
            void product_fun() override;
        }; //Pro_2


        class FactoryBasic {
        public:
            virtual std::shared_ptr<ProBasic> create() = 0;
        }; // FactoryBasic

        class Factory_0 : public FactoryBasic {
        public:
            std::shared_ptr<ProBasic> create() override;
        }; // Factory_0

        class Factory_1 : public FactoryBasic {
        public:
            std::shared_ptr<ProBasic> create() override;
        }; // Factory_1

        class Factory_2 : public FactoryBasic {
        public:
            std::shared_ptr<ProBasic> create() override;
        }; // Factory_2

    } //factory_method

} // pattern


#endif //TOOL_FACTORY_METHOD_PATTERN_H
