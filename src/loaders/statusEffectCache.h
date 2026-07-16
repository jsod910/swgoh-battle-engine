#pragma once

#include <array>
#include <memory>
#include <vector>
#include <cstdint>

#include "../entities/statusEffectDefinition.h"

enum class StatusEffectType : uint8_t;

class StatusEffectCache {
public:
    void loadAllStatus(const std::string& filePath);

    const StatusEffectDefinition* getStatusDefinition(StatusEffectType name) const;

private:
    std::array<
        std::unique_ptr<StatusEffectDefinition>, 
        static_cast<size_t>(StatusEffectType::COUNT)
    > statusEffectRegistry;
};