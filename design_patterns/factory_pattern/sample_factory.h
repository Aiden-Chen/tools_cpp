//
// Created by aiden on 20-10-15.
//

#ifndef TOOL_SAMPLE_FACTORY_H
#define TOOL_SAMPLE_FACTORY_H

namespace patterns {
    namespace sample_factory {
        /* *
         * @brief sample factory pattern: it has only one factory to product many kinds of production,
         *        and has two interface: production and factory. The production need a basic class, and
         *        this class must be an abstract class, and it has an virtual function to product the
         *        production. Then creates a factory to production different productions.
         * */

        enum Production_en {
            Production_0 = 0,
            Production_1,
            Production_2
        }; // Production_en

        class Production {
        public:
            virtual void product_fun() = 0;
        }; // production


        class Pro_0 : public Production {
        public:
            void product_fun();
        }; // Pro_0

        class Pro_1 : public Production {
        public:
            void product_fun();
        }; // Pro_1


        class Pro_2 : public Production {
        public:
            void product_fun() override;
        }; // Pro_2


        class SampleFactory {
        public:
            Production *create_fun(Production_en pro_type);
        }; // sample_factory

    }

}


#endif //TOOL_SAMPLE_FACTORY_H
