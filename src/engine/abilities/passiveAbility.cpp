#include "passiveAbility.h"
#include "effectContext.h"

#include <string>
#include <vector>

PassiveAbility::PassiveAbility(std::string name) : name(name)
{
}

void PassiveAbility::cast(EffectContext& context) const {
    for(auto& effect : effects){
        effect->execute(context);
    }
}