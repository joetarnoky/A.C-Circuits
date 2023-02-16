#include<iostream>
#include<cstdlib>
#include<limits>
#include<string>
#include<vector>
#include<cmath>
#include<iomanip>
#include<complex>
#include<algorithm>
#ifndef classes_h
#define classes_h
const double pi  = 3.141592653589;
const int divide_flag(1); // error handling
namespace complex_namespace
{
    template <class T> class complex; 
}
using namespace complex_namespace;

std::complex<double> complex_divide(std::complex<double> z1, std::complex<double> z2); // check for divide by 0 when dividing complex numbers

std::string operator * (std::string a, unsigned int n); // overloading * operator to output a character n times

class component
{
protected:
    std::complex<double> impedance;
    double frequency;
public:
    component(){};
    virtual ~component(){};
    
    // Pure virtual functions
    virtual void info() = 0;
    virtual std::string draw_component() = 0; 
    virtual std::string draw_circuit() = 0; 
    virtual void set_frequency(double) = 0;
    virtual double get_frequency() = 0;
    virtual std::complex<double> get_impedance() = 0;
    virtual double get_impedance_modulus() = 0;
    virtual double get_phase() = 0;
};

class resistor : public component
{
private:
    double resistance;
public:
    resistor(double r);
    ~resistor(){};
    void set_frequency(double f);
    double get_frequency();
    std::complex<double> get_impedance();
    double get_impedance_modulus();
    double get_phase();
    void info();
    std::string draw_component();
    std::string draw_circuit();
};

class capacitor : public component
{
private:
    double capacitance;
    std::complex<double> capacitive_reactance;
public:
    capacitor(double c);
    ~capacitor(){};
    void set_frequency(double f);
    double get_frequency();
    std::complex<double> get_impedance();
    double get_impedance_modulus();
    double get_phase();
    void info();
    std::string draw_component();
    std::string draw_circuit();
};

class inductor : public component
{
private:
    double inductance;
    std::complex<double> inductive_reactance;
public:
    inductor(double l);
    ~inductor(){};
    void set_frequency(double f);
    double get_frequency();
    std::complex<double> get_impedance();
    double get_impedance_modulus();
    double get_phase();
    void info();
    std::string draw_component();
    std::string draw_circuit();
};

class circuit : public component
{
protected:
    double phase;
    std::complex<double> circuit_impedance;
public:
    circuit(){};
    ~circuit(){};
    void set_frequency(double f);
    double get_frequency();
    double get_impedance_modulus();
    double get_phase();
    std::string draw_circuit();
};

class series_circuit : public circuit
{
private:
    component* component1; // base class pointer to general circuit class to access member functions of compenent classes 
    component* component2; // components 1/2 could be individual components or circuits that have been built by the user
public:
    series_circuit(component* c1, component* c2) : component1{c1}, component2{c2} {};
    ~series_circuit(){};
    std::complex<double> get_impedance();
    void info();
    std::string draw_component();
};

class parallel_circuit : public circuit
{
private:
    component* component1; 
    component* component2; 
public:
    parallel_circuit(component* c1, component* c2) : component1{c1}, component2{c2}{};
    ~parallel_circuit(){};
    std::complex<double> get_impedance();
    void info();
    std::string draw_component();
};
#endif