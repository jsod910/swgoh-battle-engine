#pragma once

#include <cmath>

#include "../../external/json/json_loader.hpp"
#include "statusEffect.h"
using json = nlohmann::json;

namespace statData {
    struct Stats {
        int mastery;

        int health;
        int protection;
        int speed;
        double critDamage;
        double potency;
        double tenacity;
        double healthSteal;
        int defensePen; 
        
        int physOffense;
        double physCritChance;
        int armorPen;
        double physAccuracy;

        int flatArmor;
        double dodge;
        double critAvoid;
        
        int specOffense;
        double specCritChance;
        int resistancePen;
        double specAccuracy;

        int flatResistance;
        double deflection;
    
        double getStatValue(ModifierStat type) const {
            switch(type) {
                case ModifierStat::MASTERY: return mastery;
                case ModifierStat::HEALTH:  return health;
                case ModifierStat::PROTECTION:  return protection;
                case ModifierStat::SPEED:   return speed;
                case ModifierStat::CRIT_DAMAGE: return critDamage;
                case ModifierStat::POTENCY: return potency;
                case ModifierStat::TENACITY: return tenacity;
                case ModifierStat::HEALTH_STEAL: return healthSteal;
                case ModifierStat::DEFENSE_PEN: return defensePen;
                case ModifierStat::PHYS_OFFENSE: return physOffense;
                case ModifierStat::PHYS_CRIT_CHANCE: return physCritChance;
                case ModifierStat::ARMOR_PEN:   return armorPen;
                case ModifierStat::PHYS_ACCURACY:   return physAccuracy;
                case ModifierStat::FLAT_ARMOR:   return flatArmor;
                case ModifierStat::DODGE:   return dodge;
                case ModifierStat::CRIT_AVOIDANCE:  return critAvoid;
                case ModifierStat::SPEC_OFFENSE: return specOffense;
                case ModifierStat::SPEC_CRIT_CHANCE: return specCritChance;
                case ModifierStat::RESISTANCE_PEN:  return resistancePen;
                case ModifierStat::SPEC_ACCURACY:   return specAccuracy;
                case ModifierStat::FLAT_RESISTANCE:  return flatResistance;
                case ModifierStat::DEFLECTION:  return deflection;
                default: return 0.0;
            }
            return 0.0;
        }
    };

    // static bool isFlatStat(ModifierStat type) {
    //     switch(type) {
    //         case ModifierStat::MASTERY:
    //         case ModifierStat::HEALTH:  
    //         case ModifierStat::PROTECTION:  
    //         case ModifierStat::SPEED:   
    //         case ModifierStat::DEFENSE_PEN:
    //         case ModifierStat::PHYS_OFFENSE:
    //         case ModifierStat::ARMOR_PEN:
    //         case ModifierStat::SPEC_OFFENSE: 
    //         case ModifierStat::RESISTANCE_PEN:   
    //         case ModifierStat::FLAT_ARMOR:
    //         case ModifierStat::FLAT_RESISTANCE:
    //             return true;
    //         case ModifierStat::CRIT_DAMAGE: 
    //         case ModifierStat::POTENCY: 
    //         case ModifierStat::TENACITY: 
    //         case ModifierStat::HEALTH_STEAL: 
    //         case ModifierStat::PHYS_CRIT_CHANCE: 
    //         case ModifierStat::PHYS_ACCURACY:
    //         case ModifierStat::DODGE:   
    //         case ModifierStat::CRIT_AVOIDANCE:   
    //         case ModifierStat::SPEC_CRIT_CHANCE:  
    //         case ModifierStat::SPEC_ACCURACY:    
    //         case ModifierStat::DEFLECTION:
    //             return false;
    //     }
    //     return false;
    // };

    inline void from_json(const json& j, Stats& s){
        j.at("mastery").get_to(s.mastery);
        j.at("health").get_to(s.health);
        j.at("protection").get_to(s.protection);
        j.at("speed").get_to(s.speed);
        j.at("critDamage").get_to(s.critDamage);
        j.at("potency").get_to(s.potency);
        j.at("tenacity").get_to(s.tenacity);
        j.at("healthSteal").get_to(s.healthSteal);
        j.at("defensePen").get_to(s.defensePen); 
        j.at("physOffense").get_to(s.physOffense);
        j.at("physCritChance").get_to(s.physCritChance);
        j.at("armorPen").get_to(s.armorPen);
        j.at("physAccuracy").get_to(s.physAccuracy);
        // j.at("armor").get_to(s.armor);   // convert armor from % to flat stat
        j.at("dodge").get_to(s.dodge);
        j.at("critAvoid").get_to(s.critAvoid);
        j.at("specOffense").get_to(s.specOffense);
        j.at("specCritChance").get_to(s.specCritChance);
        j.at("resistancePen").get_to(s.resistancePen);
        j.at("specAccuracy").get_to(s.specAccuracy);
        // j.at("resistance").get_to(s.resistance);    // convert resistance from % to flatStat
        j.at("deflection").get_to(s.deflection);

        double armorPercent, resistancePercent, flatDefense;
        j.at("armor").get_to(armorPercent);
        flatDefense = ( (637.5 * armorPercent) / (1 - armorPercent) );
        s.flatArmor = static_cast<int>(flatDefense);

        j.at("resistance").get_to(resistancePercent);
        flatDefense = ( (637.5 * resistancePercent) / (1 - resistancePercent) );
        s.flatResistance = static_cast<int>(flatDefense);
        
    };
}