#include "classes.h"
using namespace complex_namespace;

// Error handling
std::complex<double> complex_divide(std::complex<double> z1, std::complex<double> z2) 
{
    std::complex<double> zero = (0, 0);
    if(z2 == zero) throw divide_flag;
    return z1/z2;
}

// Overloading *
std::string operator * (std::string a, unsigned int n) 
{
    std::string output ("");
    while (n--){
        output += a; 
    }
    return output;
}

// Resistor // 

resistor::resistor(double r) : resistance{r} {};

// Setters and getters 
void resistor::set_frequency(double f)
{
    frequency = f;
}
double resistor::get_frequency(){return frequency;}
std::complex<double> resistor::get_impedance()
{
    impedance = std::complex<double>(resistance, 0.0);
    return impedance;
}
double resistor::get_impedance_modulus(){return resistance;} // impedence modulus for resistor is just its resistance 
double resistor::get_phase(){return 0.0;}

// Print info and circuit diagram
void resistor::info ()
{
    std::cout << "Resistor:" << std::endl; 
    std::cout << "Resistance = " << std::setprecision(3) << resistance << " Ω" << std::endl;
    std::cout << "Impedance modulus is " << std::setprecision(3) << get_impedance_modulus() << " Ω" << std::endl;
    std::cout << "Phase = " << std::setprecision(3) << get_phase() << " rad" << std::endl;
    std::cout << "Frequency = " << std::setprecision(3) << get_frequency() << " Hz" << std::endl;
}
std::string resistor::draw_component()
{
    std::string comp{"-R-"};
    return(comp);
}
std::string resistor::draw_circuit() // outputs component connected to power supply
{
    std::string circuit = "V--\n|  |\n" + draw_component(); // V represents power supply
    return circuit;
}

// Capacitor //

capacitor::capacitor(double c) : capacitance{c} {};

// Setters and getters 
void capacitor::set_frequency(double f)
{
    frequency = f;
}
double capacitor::get_frequency(){return frequency;}
std::complex<double> capacitor::get_impedance()
{
    capacitive_reactance = std::complex<double>(0.0, -1 / (2 * pi *get_frequency() * capacitance));
    return capacitive_reactance;
}
double capacitor::get_impedance_modulus(){return std::abs(get_impedance());} 
double capacitor::get_phase(){return (pi/2);}

// Print info and circuit diagram
void capacitor::info ()
{
    std::cout << "Capacitor:" << std::endl;
    std::cout << "Capacitance = " << std::setprecision(3) << capacitance << " F" << std::endl;
    std::cout << "Capacitive reactance = " << std::setprecision(3) << get_impedance() << " Ω" << std::endl;
    std::cout << "Impedance modulus is " << std::setprecision(3) << get_impedance_modulus() << " Ω" << std::endl;
    std::cout << "Phase = " << std::setprecision(3) << get_phase() << " rad" << std::endl;
    std::cout << "Frequency = " << std::setprecision(3) << get_frequency() << " Hz" << std::endl;
}
std::string capacitor::draw_component()
{
    std::string comp{"-C-"};
    return(comp);
}
std::string capacitor::draw_circuit()
{
    std::string circuit = "V--\n|  |\n" + draw_component();
    return circuit;
}

// Inductor //

inductor::inductor(double l) : inductance{l} {};

// Setters and getters 
void inductor::set_frequency(double f)
{
    frequency = f;
}
double inductor::get_frequency(){return frequency;}
std::complex<double> inductor::get_impedance()
{
    inductive_reactance = std::complex<double> (0.0, 2 * pi * get_frequency() * inductance); 
    return inductive_reactance;
}
double inductor::get_impedance_modulus(){return std::abs(get_impedance());} 
double inductor::get_phase(){return -(pi/2);}

// Print info and circuit diagram
void inductor::info ()
{
    std::cout << "Inductor:" << std::endl;
    std::cout << "Inductance = " << std::setprecision(3) << inductance << " H" << std::endl;
    std::cout << "Inductive reactance = " << std::setprecision(3) << get_impedance() << " Ω" << std::endl;
    std::cout << "Impedance modulus is " << std::setprecision(3) << get_impedance_modulus() << " Ω" << std::endl;
    std::cout << "Phase = " << std::setprecision(3) << get_phase() << " rad" << std::endl;
    std::cout << "Frequency = " << std::setprecision(3) << get_frequency() << " Hz" << std::endl;
}
std::string inductor::draw_component()
{
    std::string comp{"-L-"};
    return comp;
}
std::string inductor::draw_circuit()
{
    std::string circuit = "V--\n|  |\n" + draw_component();
    return circuit;
}

//  Circuit //

// Setters and getters
void circuit::set_frequency(double f)
{
    frequency = f;
}
double circuit::get_frequency(){return frequency;}
double circuit::get_impedance_modulus(){return std::abs(get_impedance());}
double circuit::get_phase()
{
    double real_part = real(get_impedance()); 
    double im_part = imag(get_impedance());
    phase = atan(im_part/real_part);
    return phase;
}

// Draw circuit
std::string circuit::draw_circuit()
{
    std::string wire("-");
    std::string space(" ");
    int length = draw_component().length() - 1; // finds length of component string so that wires in outputted circuit are correctly positioned
    std::string circuit = "V" + (wire * length) + "\n|" + (space * (length - 1)) + "|\n" + draw_component(); 
    return circuit;
}

// Series circuit //

std::complex<double> series_circuit::get_impedance()
{
    circuit_impedance = component1->get_impedance() + component2->get_impedance();
    return circuit_impedance;
}

// Print info and circuit diagram
void series_circuit::info()
{
    std::cout << "Series circuit:" << std::endl;
    std::cout << "Impedance of circuit is " << std::setprecision(3) << get_impedance() << " Ω" << std::endl;
    std::cout << "Impedance modulus is " << std::setprecision(3) << get_impedance_modulus() << " Ω" << std::endl;
    std::cout << "Phase is " << std::setprecision(3) << get_phase() << " rad" << std::endl;
}
std::string series_circuit::draw_component()
{
    std::string comp1 = component1->draw_component();
    std::string comp2 = component2->draw_component();
    std::string series_illustration{comp1 + "-" + comp2};
    return series_illustration;
}

// Parallel circuit //
std::complex<double> parallel_circuit::get_impedance()
{
    try // error handling used in case of the unlikely scenario that z1 + z2 = 0
    {
        circuit_impedance = complex_divide(component1->get_impedance() * component2->get_impedance(), component1->get_impedance() + component2->get_impedance());
    }
    catch(int error_flag)
    {
        if(error_flag == divide_flag){
        std::cerr << "Math error: cannot divide by 0" << std::endl;
        exit(error_flag);
        }
    }
    return circuit_impedance;
}

// Print info and circuit diagram
void parallel_circuit::info()
{
    std::cout << "Parallel circuit:" << std::endl;
    std::cout << "Impedance of circuit is " << std::setprecision(3) << get_impedance() << " Ω" << std::endl;
    std::cout << "Impedance modulus is " << std::setprecision(3) << get_impedance_modulus() << " Ω" << std::endl;
    std::cout << "Phase: " << std::setprecision(3) << get_phase() << " rad" << std::endl;
}
std::string parallel_circuit::draw_component()
{
    std::string comp1 = component1->draw_component();
    std::string comp2 = component2->draw_component();
    std::string parallel_illustration = "-P{" + comp1 + "," + comp2 + "}-";
    return parallel_illustration;
}