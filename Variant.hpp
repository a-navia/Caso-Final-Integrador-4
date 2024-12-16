#ifndef VARIANT_HPP
#define VARIANT_HPP

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include "json11/json11.hpp"

//alias para la libreria json11
namespace jsonlib = json11;

//declaracion de entorno
struct Entorno;

class Variant {
public:
    enum variant_type { Symbol, Number, List, Proc, Lambda, Cadena };
    typedef Variant(*proc_type)(const std::vector<Variant>&);
    typedef std::vector<Variant>::const_iterator iter;
    typedef std::map<std::string, Variant> map;

    // Atributos
    variant_type type;
    // Union para almacenar los diferentes tipos de datos
    union {
        double num;
        std::string* str;
        std::vector<Variant>* list;
        proc_type proc;
        Entorno* env;
    };

    // Constructors
    Variant(variant_type t = Symbol);
    Variant(variant_type t, const std::string& val);
    Variant(double n);
    Variant(proc_type p);
    Variant(const std::vector<Variant>& lst);
    ~Variant();

    // Metodos
    std::string to_string() const;
    std::string to_json_string() const;
    static Variant from_json_string(const std::string& json);
    static Variant parse_json(const jsonlib::Json& json_job);
};
//definicion de entorno para almacenar variables
struct Entorno {
    std::map<std::string, Variant> vars;
    Entorno* padre;

    Entorno(Entorno* padre = nullptr);

    Variant& operator[] (const std::string& key);
};

#endif // VARIANT_HPP
