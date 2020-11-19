//
// Created by aiden on 20-10-15.
//

#include <iostream>
#include "../design_patterns/factory_pattern/sample_factory.h"
#include "../design_patterns/factory_pattern/factory_method_pattern.h"
#include "../design_patterns/factory_pattern/abstract_factory_pattern.h"
#include "../design_patterns/builder_pattern/builder_pattern.h"
#include "../design_patterns/prototype_pattern/prototype_pattern.h"
#include "../design_patterns/adapter_pattern/adapter_pattern.h"
#include "../design_patterns/bridge_pattern/bridge_pattern.h"
#include "../design_patterns/decorator_pattern/decorator_pattern.h"
#include "../design_patterns/composite_pattern/composite_pattern.h"

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

void adapter_pattern_test(){
    std::string name = "aiden";
    // 类适配器
    std::shared_ptr<AdapterClass> adapter_class =
            std::make_shared<AdapterClass>(name);
    std::string output = adapter_class->get_name();
    std::cout << "adapter class->" << output << std::endl;

    std::shared_ptr<Adaptee> adaptee = std::make_shared<Adaptee>();
    std::shared_ptr<AdapterObject> adapter_object =
            std::make_shared<AdapterObject>(adaptee, name);
    output = adapter_object->get_name();
    std::cout << "adapter object->" << output << std::endl;
}

void bridge_pattern_test(){
    std::shared_ptr<ImplementAbstract> impelment_a = std::make_shared<ConcreteImplementA>();
    std::shared_ptr<Abstract> abstract_a = std::make_shared<RefineAbstractA>(impelment_a);
    abstract_a->Operation();
    std::cout << "*******************************" << std::endl;

    std::shared_ptr<ImplementAbstract> impelment_b = std::make_shared<ConcreteImplementB>();
    abstract_a.reset(new RefineAbstractA(impelment_b));
    abstract_a->Operation();
    std::cout << "-------------------------------" << std::endl;

    std::shared_ptr<Abstract> abstract_b = std::make_shared<RefineAbstractB>(impelment_a);
    abstract_b->Operation();
    std::cout << "*******************************" << std::endl;

    abstract_b.reset(new RefineAbstractB(impelment_b));
    abstract_b->Operation();
}

void decorator_pattern_test(){
    std::shared_ptr<Component> component = std::make_shared<ConcreteComponent>();

    std::shared_ptr<ConcreteDecoratorA> decorator_a = std::make_shared<ConcreteDecoratorA>("aiden");
    decorator_a->setComponent(component);
    decorator_a->Operation();
    std::cout << decorator_a->get_name() << std::endl;

    std::cout << "--------------------------------------------------" << std::endl;

    std::shared_ptr<ConcreteDecoratorB> decorator = std::make_shared<ConcreteDecoratorB>();
    decorator->setComponent(component);
    decorator->Operation();
    decorator->add_behavior();
}

void composite_pattern_test(){
    std::shared_ptr<compposite_pattern::Component> root = std::make_shared<compposite_pattern::Composite>("root");
    std::shared_ptr<compposite_pattern::Component> leaf_1 = std::make_shared<compposite_pattern::Leaf>("Leaf1");
    std::shared_ptr<compposite_pattern::Component> leaf_2 = std::make_shared<compposite_pattern::Leaf>("Leaf2");
    std::shared_ptr<compposite_pattern::Component> composite_1 = std::make_shared<compposite_pattern::Composite>("Composite1");
    std::shared_ptr<compposite_pattern::Component> composite_2 = std::make_shared<compposite_pattern::Composite>("Composite2");

    composite_1->add(composite_2);
    composite_1->add(leaf_2);

    root->add(leaf_1);
    root->add(leaf_2);
    root->add(composite_1);
    root->add(composite_2);

    root->Operator();
    std::cout << "*****************************************" << std::endl;
    std::shared_ptr<compposite_pattern::Component> component_tmp =  root->get_current_component(2);
    component_tmp->Operator();
}

#include <time.h>
#include <stdio.h>
#include <math.h>

int main()
{
    int run_type;
    std::cout << "***********************************************************" << std::endl;
    std::cout << "1. sample factory pattern test" << std::endl;
    std::cout << "2. factory factory pattern test" << std::endl;
    std::cout << "3. abstract factory pattern test" << std::endl;
    std::cout << "4. builder pattern test" << std::endl;
    std::cout << "5. prototype pattern test" << std::endl;
    std::cout << "6. adapter pattern test" << std::endl;
    std::cout << "7. bridge pattern test" << std::endl;
    std::cout << "8. decorator pattern test" << std::endl;
    std::cout << "9. compsite pattern test" << std::endl;
    std::cout << "***********************************************************" << std::endl;
    std::cout << "Please input design patterns cmd(1 ~ 9): ";
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
        case 6:
            adapter_pattern_test();
            break;
        case 7:
            bridge_pattern_test();
            break;
        case 8:
            decorator_pattern_test();
            break;
        case 9:
            composite_pattern_test();
            break;
        default:
            std::cout << "Don't support this design pattern cmd " << run_type
                << ", please input the correct cmd" << std::endl;
            break;
    }
    return  0;
}
