//
// Created by aiden on 20-10-15.
//

#include <iostream>
#include <memory>
#include "sample_factory.h"

using namespace std;

namespace patterns{
    namespace sample_factory {
        void Pro_0::product_fun() {
            std::cout << "Pro_0 production" << std::endl;
        }


        void Pro_1::product_fun() {
            std::cout << "Pro_1 production" << std::endl;
        }


        void Pro_2::product_fun() {
            std::cout << "Pro_2 production" << std::endl;
        }

        Production *SampleFactory::create_fun(Production_en pro_type) {
            std::shared_ptr<Production> pro = nullptr;
            switch (pro_type) {
                case Production_en::Production_0:
                    pro = std::make_shared<Pro_0>();
                    break;
                case Production_en::Production_1:
                    pro = std::make_shared<Pro_1>();
                    break;
                case Production_en::Production_2:
                    pro = std::make_shared<Pro_2>();
                    break;
                default:
                    std::cout << "Don't support this type " << pro_type << std::endl;
                    return nullptr;
            }
            return pro.get();
        }

    }

} // patterns
