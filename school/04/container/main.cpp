#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>


// Reads as many integers as the parameter count indicates
// and stores them into the parameter vector ints.
void read_integers(std::vector< int >& ints, int count)
{
    int new_integer = 0;
    for(int i = 0; i < count; ++i)
    {
        std::cin >> new_integer;
        // TODO: Implement your solution here
        ints.push_back(new_integer);
        std::cin.clear();
    }
}

// TODO: Implement your solution here
bool same_values(std::vector<int>&ints) {
    if (
        std::adjacent_find(
                ints.begin(),
                ints.end(),
                std::not_equal_to<>()
        ) == ints.end()
    ) {
      return true;

    } else {
        return false;
    }
}

bool is_ordered_non_strict_ascending(const std::vector<int>& ints) {
    std::vector<int> ordered = ints;
    sort(ordered.begin(),ordered.end());
    if (ints == ordered) {
        return true;
    } else {
        return false;
    }
}

bool is_arithmetic_series(std::vector<int>& ints) {
    int start_q = ints[1]-ints[0];
    auto size = ints.size();
    for (unsigned long i=0;i<size-1;++i) {
        int cur_val = ints[i];
        int next_val = ints[i+1];
        int q = next_val - cur_val;
        if (q != start_q) {
            return false;
        }
    }
    return true;
}

bool is_geometric_series(std::vector<int>& ints) {
    if ((same_values(ints)==true) and (ints[0]==0)){
        return false;
    }

    int start_q = ints[1]/ints[0];
    auto size = ints.size();
    for (unsigned long i=0;i<size-1;++i) {
        int cur_val = ints[i];
        int next_val = ints[i+1];
        int q = next_val / cur_val;
        if (q != start_q) {
            return false;
        }
    }
    return true;
}

int main()
{
    std::cout << "How many integers are there? ";
    int how_many = 0;
    std::cin >> how_many;

    std::cout << "Enter the integers: ";
    std::vector<int> integers;
    read_integers(integers, how_many);


    if(same_values(integers))
        std::cout << "All the integers are the same" << std::endl;
    else
        std::cout << "All the integers are not the same" << std::endl;

    if(is_ordered_non_strict_ascending(integers))
        std::cout << "The integers are in a non-strict ascending order" << std::endl;
    else
        std::cout << "The integers are not in a non-strict ascending order" << std::endl;

    if(is_arithmetic_series(integers))
        std::cout << "The integers form an arithmetic series" << std::endl;
    else
        std::cout << "The integers do not form an arithmetic series" << std::endl;

    if(is_geometric_series(integers))
        std::cout << "The integers form a geometric series" << std::endl;
    else
        std::cout << "The integers do not form a geometric series" << std::endl;

    return EXIT_SUCCESS;
}
