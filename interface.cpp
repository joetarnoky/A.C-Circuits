#include "classes.h"
using namespace complex_namespace;

//-------------------interface functions---------------------//

std::vector<component*> component_list; // vector of base class pointers to store different components

int get_index(std::vector<component*> list) // used to find the index of the most recently added component
{
    int i = list.size() - 1; 
    return i;
}

void print_list(std::vector<component*> list) // function to print out component list
{
    for (int i = 0; i < list.size(); ++i){
        std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
        std::cout << "Component " << i + 1 << std::endl;
        list[i] -> info();
        std::cout << list[i]->draw_component() << std::endl; 
    }
}

void set_circuit_frequency(std::vector<component*> list, double f) // function to set every circuit component to the same frequency
{
    for (int i = 0; i < list.size(); ++i){
        list[i]->set_frequency(f);
    }
}

void clear_list(std::vector<component*> list) 
{
    for (auto it = list.begin(); it < list.end(); ++it){ delete * it; } 
}

void print_menu()
{
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~ Menu ~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl; 
    std::cout << "Would you like to:" << std::endl;
    std::cout << "1) Print out the list of stored components" << std::endl;
    std::cout << "2) Create your own component" << std::endl;
    std::cout << "3) Create a series circuit using two stored components" << std::endl; 
    std::cout << "4) Create a Parallel circuit using two stored components" << std::endl;
    std::cout << "5) Clear all circuits and components" << std::endl;
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
}

int validate_option_input(std::string question, int n) // ensures input corresponds to an option listed, n is number of options listed
{
    int input;
    std::cout << question << std::endl;
    std::cin >> input;
    while(std::cin.fail() || input < 1 || input > n || std::cin.peek() != '\n'){  // cin.peek() ensures no wrong input follows correct int, e.g. 3r
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Ignores all characters in input stream up to new line character
        std::cout << "Please enter an option listed" << std::endl;
        std::cin >> input;        
    }   
    return input;
}

double validate_value_input(std::string question) // ensures value inputted is a positive double
{
    double value;
    std::cout << question << std::endl;
    std::cin >> value;
    while(std::cin.fail() || std::cin.peek() != '\n' || value <= 0 ){ 
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Please enter a positive number" << std::endl;
        std::cout << question << std::endl;
        std::cin >> value;
    }
    return value;
}

void input_component()
{
    std::cout << "Which component would you like to make?" << std::endl;
    std::cout << "1) Resistor" << std::endl;
    std::cout << "2) Capacitor" << std::endl;
    std::cout << "3) Inductor" << std::endl;
    int input;
    input = validate_option_input("Please choose your option", 3);
    if(input == 1){
        double resistance;
        double frequency;
        resistance = validate_value_input("Input the resistance of the resistor in Ω"); 
        frequency = validate_value_input("Input the frequency of the resistor in Hz");
        component_list.push_back(new resistor{resistance}); // stores created component in component list
        component_list[get_index(component_list)]->set_frequency(frequency);
        std::cout << "Here is your new resistor" << std::endl;
        component_list[get_index(component_list)]->info(); // prints info
        std::cout << component_list[get_index(component_list)]->draw_component() << std::endl; // prints component illustration
    }
    else if(input == 2){
        double capacitance;
        double frequency;
        capacitance = validate_value_input("Input the capacitance of the capacitor in Farads"); 
        frequency = validate_value_input("Input the frequency of the capacitor in Hz");
        component_list.push_back(new capacitor{capacitance});
        component_list[get_index(component_list)]->set_frequency(frequency);
        std::cout << "Here is your new capacitor" << std::endl;
        component_list[get_index(component_list)]->info();
        std::cout << component_list[get_index(component_list)]->draw_component() << std::endl;
    }
    else if(input == 3){
        double inductance;
        double frequency;
        inductance = validate_value_input("Input the inductance of the inductor in Henrys"); 
        frequency = validate_value_input("Input the frequency of the inductor in Hz");
        component_list.push_back(new inductor{inductance});
        component_list[get_index(component_list)]->set_frequency(frequency);
        std::cout << "Here is your new inductor" << std::endl;
        component_list[get_index(component_list)]->info();
        std::cout << component_list[get_index(component_list)]->draw_component() << std::endl;
    }
}

void create_series_circuit()
{
    int index1;
    int index2;
    int list_length = get_index(component_list) + 1; // finds number of components user has to choose from
    double frequency; 
    std::cout << "Choose 2 components from the component list to combine in a series circuit" << std::endl;
    print_list(component_list);
    index1 = validate_option_input("Choose the index of your first component", list_length);
    index2 = validate_option_input("Choose the index of your second component", list_length);
    frequency = validate_value_input("What frequency (in Hz) would you like your circuit to operate at? \nThis will set the frequency of all stored components");
    set_circuit_frequency(component_list, frequency);
    component_list.push_back(new series_circuit{component_list[index1 - 1], component_list[index2 - 1]}); // stores created circuit in component list
    std::cout << "Here is your new series circuit" << std::endl;
    component_list[get_index(component_list)]->info();
    std::cout << component_list[get_index(component_list)]->draw_circuit() << std::endl; // prints circuit illustration
}

void create_parallel_circuit()
{
    int index1;
    int index2;
    int list_length = get_index(component_list) + 1; 
    double frequency;
    std::cout << "Choose 2 components from the component list to combine in a parallel circuit" << std::endl;
    print_list(component_list);
    index1 = validate_option_input("Choose the index of your first component", list_length);
    index2 = validate_option_input("Choose the index of your second component", list_length);
    frequency = validate_value_input("What frequency (in Hz) would you like your circuit to operate at? \nThis will set the frequency of all stored components");
    set_circuit_frequency(component_list, frequency);
    component_list.push_back(new parallel_circuit{component_list[index1 - 1], component_list[index2 - 1]});
    std::cout << "Here is your new parallel circuit" << std::endl;
    component_list[get_index(component_list)]->info();
    std::cout << component_list[get_index(component_list)]->draw_circuit() << std::endl;
}

void interface()
{
    char menu_return; // used to give option to run program again
    int order_choice; 
    int menu_choice; 

    // creating starting component list
    component_list.push_back(new resistor{330}); 
    component_list[0]->set_frequency(50);
    component_list.push_back(new capacitor{0.000001});
    component_list[1]->set_frequency(50);
    component_list.push_back(new inductor{0.5});
    component_list[2]->set_frequency(50);

    // main program
    do
    {
        print_menu();
        menu_choice = validate_option_input("Please choose your option", 5); 
        if(menu_choice == 1){
            if (component_list.size() != 0){ // checks if there are components in the list to display
            std::cout << "Would you like to order by:" << std::endl;
            std::cout << "1) Order of creation (least to most recent)" << std::endl;
            std::cout << "2) Order of impedance modulus (largest to smallest)" << std::endl;
            order_choice = validate_option_input("Please choose your option", 2);
            if(order_choice == 1){
            std::cout << "Here are your components:" << std::endl;
            print_list(component_list);
            }
            else if(order_choice == 2){
            std::cout << "Here are your components:" << std::endl;
            // lambda function used to sort components in order of impedance modulus
            std::sort(std::begin(component_list), std::end(component_list), [&](component* a, component* b) 
            {return a->get_impedance_modulus() > b->get_impedance_modulus();}); 
            print_list(component_list);
            }      
            }
            else{
                std::cout << "Component list is empty, create more components" << std::endl;
            }    
        }
        else if(menu_choice == 2){
            input_component();
        }
        else if(menu_choice == 3){
            if(component_list.size() > 1){ // ensures there are at least 2 components so a circuit can be formed
                create_series_circuit();
            }
            else{
                std::cout << "Not enough components, create at least 2 before circuit construction" << std::endl;
            }
        }
        else if(menu_choice == 4){
            if(component_list.size() > 1){
                create_parallel_circuit();
            }
            else{
                std::cout << "Not enough components, create at least 2 before circuit construction" << std::endl;
            }
        }
        else if(menu_choice == 5){
        clear_list(component_list); // deletes memory
        component_list.clear(); // clears vector
        std::cout << "All components deleted" << std::endl;
        }
        std::cout << "Type y to return to the main menu or any other key to quit the program" << std::endl;
        std::cin >> menu_return;
    }
    while(menu_return == 'y');
    clear_list(component_list); 
    component_list.clear(); 
}

int main()
{
    interface();
    return 0;
};
