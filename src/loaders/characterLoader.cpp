// #include "characterLoader.h"

// #include <fstream>
// #include <vector>
// #include <utility>

// #include "../../external/json/json_loader.hpp"
// using json = nlohmann::json;

// CharacterDefinition CharacterLoader::loadCharacter(const std::string& filePath) {
//     std::ifstream file(filePath);

//     json data = json::parse(file);
//     // file >> data;

//     CharacterDefinition character;
    
//     character.id = data["id"];
//     character.name = data["name"];

//     character.baseStats.health = data["stats"]["health"];
//     character.baseStats.offense = data["stats"]["offense"];
//     character.baseStats.speed = data["stats"]["speed"];

//     for(const auto& abilityData : data["abilities"]){
//         AbilityDefinition ability;

//         ability.id = abilityData["id"];
//         ability.name = abilityData["name"];
//         ability.damageMultiplier = abilityData["damageMultiplier"];
//         ability.baseCooldown = abilityData["cooldown"];

//         character.abilityIds.push_back(std::move(ability));
//     }

//     return character;
// }