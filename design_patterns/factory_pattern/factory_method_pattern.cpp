//
// Created by aiden on 20-10-15.
//
#include <iostream>

#include "factory_method_pattern.h"

using namespace std;

namespace patterns{
    namespace factory_method {

        void Pro_0::product_fun() {
            std::cout << "Pro_0" << std::endl;
        }

        void Pro_1::product_fun() {
            std::cout << "Pro_1" << std::endl;
        }

        void Pro_2::product_fun() {
            std::cout << "Pro_2" << std::endl;
        }

        std::shared_ptr<ProBasic> Factory_0::create() {
            std::cout << "Factory_0 product Pro_0" << std::endl;
            return std::make_shared<Pro_0>();
        }

        std::shared_ptr<ProBasic> Factory_1::create() {
            std::cout << "Factory_1 product Pro_1" << std::endl;
            return std::make_shared<Pro_1>();
        }

        std::shared_ptr<ProBasic> Factory_2::create() {
            std::cout << "Factory_2 product Pro_2" << std::endl;
            return std::make_shared<Pro_2>();
        }
    } // factory method

} // patterns
