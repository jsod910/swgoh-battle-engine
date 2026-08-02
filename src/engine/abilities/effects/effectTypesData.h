#pragma once

#include "../../../entities/enums/resolverType.h"

namespace Effects::Data {

    struct DynamicValue {
        double base = 0.0;
        double step = 0.0;
        double cap = -1.0;
        ResolverType resolver = ResolverType::CONSTANT;

        DynamicValue(double b = 0.0) : base(b) {}
    };
    inline void from_json(const json& j, DynamicValue& d){
        if(j.contains("base")) { d.base = j.at("base").get<double>(); }
        if(j.contains("cap")) { d.cap = j.at("cap").get<double>(); }
        if(j.contains("step")) { d.step = j.at("step").get<double>(); }
        if(j.contains("resolver")){
            d.resolver = resolverTypeFromString(j.at("resolver").get<std::string>());
        }
    }
};