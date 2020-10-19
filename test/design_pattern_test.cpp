//
// Created by aiden on 20-10-15.
//

#include <iostream>
#include "../design_patterns/factory_pattern/sample_factory.h"
#include "../design_patterns/factory_pattern/factory_method_pattern.h"
#include "../design_patterns/factory_pattern/abstract_factory_pattern.h"
#include "../design_patterns/builder_pattern/builder_pattern.h"
#include "../design_patterns/prototype_pattern/prototype_pattern.h"

using namespace patterns;

void sample_factory_test(){
    std::shared_ptr<sample_factory::SampleFactory> factory = std::make_shared<sample_factory::SampleFactory>();
    factory->create_fun(sample_factory::Production_en::Production_0)->product_fun();
    factory->create_fun(sample_factory::Production_en::Production_1)->product_fun();
    factory->create_fun(sample_factory::Production_en::Production_2)->product_fun();
}

void factory_method_test(){
    std::shared_ptr<factory_method::Factory_0> factory_0 = std::make_shared<factory_method::Factory_0>();
    factory_0->create();
    std::shared_ptr<factory_method::Factory_1> factory_1 = std::make_shared<factory_method::Factory_1>();
    factory_1->create();
    std::shared_ptr<factory_method::Factory_2> factory_3 = std::make_shared<factory_method::Factory_2>();
    factory_1->create();
}

void abstract_factory_test(){
    std::shared_ptr<abstract_factory::Factory1> factory_1 = std::make_shared<abstract_factory::Factory1>();
    factory_1->create_production_a();
    factory_1->create_production_b();
    std::shared_ptr<abstract_factory::Factory2> factory_2 = std::make_shared<abstract_factory::Factory2>();
    factory_2->create_production_a();
    factory_2->create_production_b();
}

void builder_pattern_test(){
    std::shared_ptr<AbstractBuilder> builder = std::make_shared<ProductionBuilder>();
    std::shared_ptr<Director> director = std::make_shared<Director>(builder);
    director->create();
    std::shared_ptr<Production> production = builder->get_production();
    production->show();
}

void prototype_pattern_test(){
    std::string type = "test";
    PrototypePattern* prototype = new patterns::PrototypePattern(type);
    PrototypePattern* prototype_b = prototype->clone();
    prototype_b->show();
    prototype->show();
    delete prototype;
    delete prototype_b;
}

int main()
{
    int run_type;
    std::cout << "***********************************************************" << std::endl;
    std::cout << "1. sample factory pattern test" << std::endl;
    std::cout << "2. factory factory pattern test" << std::endl;
    std::cout << "3. abstract factory pattern test" << std::endl;
    std::cout << "4. builder pattern test" << std::endl;
    std::cout << "5. prototype pattern test" << std::endl;
    std::cout << "***********************************************************" << std::endl;
    std::cout << "Please input design patterns cmd(1 ~ 5): ";
    std::cin >> run_type;

    switch(run_type){
        case 1:
            sample_factory_test();
            break;
        case 2:
            factory_method_test();
            break;
        case 3:
            abstract_factory_test();
            break;
        case 4:
            builder_pattern_test();
            break;
        case 5:
            prototype_pattern_test();
            break;
        default:
            std::cout << "Don't support this design pattern cmd " << run_type
                << ", please input the correct cmd" << std::endl;
            break;
    }
    return  0;
}
