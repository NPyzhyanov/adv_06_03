#include <iostream>
#include <stdexcept>
#include <string>
#include <typeindex>
#include <cmath>
#include <cstdlib>
#include <time.h>
#include <windows.h>

#include "vector.h"

int main()
{
    Vector<double> data(5, 0.0);
    
    const int total_number_of_actions = 25;
    const std::string actions_variants[] = {"push back", "pop back", "replace an element", "shrink to fit"};
    const double actions_weights[] = {0.4, 0.3, 0.2, 0.1};
    const int max_module = 100;
    
    int actions_limits[4];
    int limit = -1;
    for (unsigned int a = 0; a < (sizeof(actions_limits) / sizeof(actions_limits[0])); a++)
    {
        limit += static_cast<int>(actions_weights[a] * 10.0);
        actions_limits[a] = limit;
    }
    
    for (int action = 0; action < total_number_of_actions; action++)
    {
        Sleep(701 + action * 10 + (action % 2) * 184 - !(action % 3) * 72 + !(action % 4) * (action / 4) * 98 + !(action % 5) * (action / 5) * 56);
        
        std::srand(time(nullptr));
        int random_action = std::rand() % 10;
        
        std::cout << "[" << action << "] I'm going to ";
        int variant;
        if (random_action <= actions_limits[0]) // "push back"
        {
            variant = 0;
        }
        else if (random_action <= actions_limits[1]) // "pop back"
        {
            variant = 1;
        }
        else if (random_action <= actions_limits[2]) // "replace an element"
        {
            variant = 2;
        }
        else // "shrink to fit"
        {
            variant = 3;
        }
        std::cout << actions_variants[variant];
        
        double random_value_to_add = 0.0;
        int random_position = 0;
        double random_value_to_replace = 0.0;
        
        switch (variant)
        {
        case 0: // "push back"
            std::srand(time(nullptr));
            random_value_to_add = static_cast<double>(std::rand() % (2 * max_module * 10) - max_module * 10) / 10.0;
            std::cout << " \"" << random_value_to_add << "\"" << std::endl;
            data.push_back(random_value_to_add);
            break;
            
        case 1: // "pop back"
            std::cout << std::endl;
            data.pop_back();
            break;
            
        case 2: // "replace an element"
            if (data.get_size() != 0)
            {
                std::srand(time(nullptr));
                random_position = std::rand() % data.get_size();
                std::srand(time(nullptr));
                random_value_to_replace = static_cast<double>(std::rand() % (2 * max_module * 10) - max_module * 10) / 10.0;
                std::cout << " #" << random_position << " with a value " << random_value_to_replace;
            }
            std::cout << std::endl;
            try
            {
                data.at(random_position) = random_value_to_replace;
            }
            catch (const std::exception& ex)
            {
                std::cout << ex.what() << std::endl;
                if (data.get_size() == 0)
                {
                    std::cout << "\t(This exception thrown because of zero size of the vector)\n";
                }
            }
            break;
            
        case 3: // "shrink to fit"
            std::cout << std::endl;
            data.shrink_to_fit();
            break;
        }
        
        std::cout << "Vector:\n";
        data.print();
        std::cout << std::endl;
    }
    
    return 0;
}
