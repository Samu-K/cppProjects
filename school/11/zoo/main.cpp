#include <iostream>

#include "owl.hh"
#include "giraffe.hh"
#include "cockatoo.hh"

using namespace std;

int main()
{

    std::cout << "Owl" << std::endl;

    Owl owl;
    owl.move(3, 5, std::cout);
    owl.fly(56, 23, 6, std::cout);
    owl.print_location(std::cout);
    owl.print_altitude(std::cout);
    owl.hoot(std::cout);



    std::cout << std::endl << "Giraffe" << std::endl;

    Giraffe Giraffe;
    Giraffe.move(1, 2, std::cout);
    Giraffe.print_location(std::cout);
    Giraffe.suckle(std::cout);

    std::cout << std::endl << "Cockatoo" << std::endl;

    Cockatoo cockatoo;
    cockatoo.move(23, 57, std::cout);
    cockatoo.fly(63, 1, 10, std::cout);
    cockatoo.print_location(std::cout);
    cockatoo.print_altitude(std::cout);
    cockatoo.sing(std::cout);

}
