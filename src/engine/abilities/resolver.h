#pragma once

#include "effects/effectContext.h"
#include "effects/effectTypesData.h"
#include "../../entities/enums/resolverType.h"

namespace Resolver {
    inline double resolveDynamicValue(const Effects::Data::DynamicValue& d, const EffectContext& c){
        double resolvedAmount = d.base;

        switch(d.resolver){
            case ResolverType::CONSTANT:
            {
                return resolvedAmount;
            }
            case ResolverType::PER_BUFF_DISPELLED:
            {
                resolvedAmount += d.step*c.rtValues.buffsDispelledCount;
                break;
            }
            case ResolverType::PER_DEBUFF_DISPELLED:
            {
                resolvedAmount += d.step*c.rtValues.debuffsDispelledCount;
                break;
            }

            default: return d.base;
        }

        if(d.cap >= 0.0){
            resolvedAmount = std::min(resolvedAmount, d.cap);
        }
        return resolvedAmount;
    };
}