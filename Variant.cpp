#include "Variant.hpp"
#include <string>
#include <vector>
#include <iostream>
#include "json11/json11.hpp"

namespace jsonlib = json11;

Variant::Variant(variant_type t) : type(t) {
    //uso de switch para inicializar los tipos de datos de cada variable
    switch (t) {
        case Symbol:
        case Cadena:
            str = new std::string("");  // Inicializar con una cadena vacía
            break;
        case Number:
            num = 0.0;  // Inicializar con un número
            break;
        case List:
            list = new std::vector<Variant>();  // Inicializar con un vector vacío
            break;
        case Proc:
            proc = nullptr;  // Inicializar el procedimiento a nullptr
            break;
        case Lambda:
            env = nullptr;  // Inicializar el entorno a nullptr
            break;
        default:
            break;
    }
}

Variant::Variant(variant_type t, const std::string& val) : type(t) {
    if (t == Symbol || t == Cadena) {
        str = new std::string(val);  // Asignar una nueva cadena
    }
}

Variant::Variant(double n) : type(Number) {
    num = n;  // Inicializar con un número
}

Variant::Variant(proc_type p) : type(Proc) {
    proc = p;  // Inicializar el procedimiento
}

Variant::Variant(const std::vector<Variant>& lst) : type(List) {
    list = new std::vector<Variant>(lst);  // Inicializar con una lista
}

Variant::~Variant() {
    // Destructor para manejar la desasignación de tipos no triviales
    switch (type) {
        case Symbol:
        case Cadena:
            delete str;  // Eliminar la cadena asignada
            break;
        case List:
            delete list;  // Eliminar el vector asignado
            break;
        default:
            break;
    }
}

std::string Variant::to_string() const {
    switch (type) {
        case Symbol:
        case Cadena:
            return *str;
        case Number:
            return std::to_string(num);
        case List: {
            std::string slist = "(";
            for (const auto& item : *list) {
                slist += item.to_string() + " ";
            }
            if (!list->empty()) {
                slist.pop_back(); // Eliminar el último espacio
            }
            slist += ")";
            return slist;
        }
        case Proc:
            return "<proc>";
        case Lambda:
            return "<lambda>";
        default:
            return "Desconocido";
    }
}

std::string Variant::to_json_string() const {
    switch (type) {
        case Symbol:
        case Number:
        case Cadena:
            return "\"" + to_string() + "\"";
        case List: {
            std::string json = "[";
            for (const auto& item : *list) {
                json += item.to_json_string() + ", ";
            }
            if (!list->empty()) {
                json.pop_back(); // Eliminar la última coma
                json.pop_back(); // Eliminar el último espacio
            }
            json += "]";
            return json;
        }
        case Proc:
            return "\"Proc\"";
        case Lambda:
            return "\"Lambda\"";
        default:
            return "\"Desconocido\"";
    }
}

Variant Variant::from_json_string(const std::string& sjson) {
    std::string err;
    jsonlib::Json job = jsonlib::Json::parse(sjson, err);
    if (!err.empty()) {
        std::cerr << "Error al analizar JSON: " << err << std::endl;
        return Variant();
    }
    return parse_json(job);
}

Variant Variant::parse_json(const jsonlib::Json& job) {
    if (job.is_string()) {
        return Variant(Cadena, job.string_value());
    } else if (job.is_number()) {
        return Variant(job.number_value());
    } else if (job.is_array()) {
        std::vector<Variant> lst;
        for (const auto& item : job.array_items()) {
            lst.push_back(parse_json(item));
        }
        return Variant(lst);
    } else {
        return Variant();
    }
}