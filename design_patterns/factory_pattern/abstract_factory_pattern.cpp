//
// Created by aiden on 20-10-15.
//

#include "abstract_factory_pattern.h"

using namespace std;

namespace patterns {
    namespace abstract_factory {

        void ProductionA_1::create_a() {
            std::cout << "ProductionA_1" << std::endl;
        }

        void ProductionA_2::create_a() {
            std::cout << "ProductionA_2" << std::endl;
        }

        void ProductionB_1::create_b() {
            std::cout << "ProductionB_1" << std::endl;
        }

        void ProductionB_2::create_b() {
            std::cout << "ProductionB_2" << std::endl;
        }

        std::shared_ptr<ProductionBasicA> Factory1::create_production_a() {
            std::cout << "Factory1 product ProductionA_1" << std::endl;
            return std::make_shared<ProductionA_1>();
        }

        std::shared_ptr<ProductionBasicB> Factory1::create_production_b() {
            std::cout << "Factory1 product ProductionB_1" << std::endl;
            return std::make_shared<ProductionB_1>();
        }

        std::shared_ptr<ProductionBasicA> Factory2::create_production_a() {
            std::cout << "Factory2 product ProductionA_2" << std::endl;
            return std::make_shared<ProductionA_2>();
        }

        std::shared_ptr<ProductionBasicB> Factory2::create_production_b() {
            std::cout << "Factory2 product ProductionB_2" << std::endl;
            return std::make_shared<ProductionB_2>();
        }
    }
}