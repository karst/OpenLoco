#pragma once

#include "../Core/Span.hpp"
#include "../Speed.hpp"
#include "../Types.hpp"
#include "Object.h"

namespace OpenLoco
{
    namespace Gfx
    {
        struct Context;
    }

    namespace Flags12
    {
        constexpr uint8_t unk_01 = 1 << 1;
        constexpr uint8_t unk_02 = 1 << 2;
        constexpr uint8_t unk_03 = 1 << 3; // Likely isTram
        constexpr uint8_t unk_04 = 1 << 4;
        constexpr uint8_t unk_05 = 1 << 5;
        constexpr uint8_t isRoad = 1 << 6; // If not set this is tram track
    }

    namespace RoadPieceFlags
    {
        constexpr uint16_t one_way = 1 << 0;
        constexpr uint16_t track = 1 << 1;
        constexpr uint16_t slope = 1 << 2;
        constexpr uint16_t steep_slope = 1 << 3;
        constexpr uint16_t intersection = 1 << 2;
        constexpr uint16_t one_sided = 1 << 5;
        constexpr uint16_t overtake = 1 << 6;
        constexpr uint16_t street_lights = 1 << 8;
    }
#pragma pack(push, 1)
    struct RoadObject
    {
        static constexpr auto kObjectType = ObjectType::road;

        string_id name;
        uint16_t road_pieces;       // 0x02
        int16_t build_cost_factor;  // 0x04
        int16_t sell_cost_factor;   // 0x06
        int16_t tunnel_cost_factor; // 0x08
        uint8_t cost_index;         // 0x0A
        uint8_t var_0B;
        Speed16 maxSpeed;       // 0x0C
        uint32_t image;         // 0x0E
        uint16_t flags;         // 0x12
        uint8_t num_bridges;    // 0x14
        uint8_t bridges[7];     // 0x15
        uint8_t num_stations;   // 0x1C
        uint8_t stations[7];    // 0x1D
        uint8_t paintStyle;     // 0x24
        uint8_t num_mods;       // 0x25
        uint8_t mods[2];        // 0x26
        uint8_t num_compatible; // 0x28
        uint8_t pad_29[0x30 - 0x29];

        void drawPreviewImage(Gfx::Context& context, const int16_t x, const int16_t y) const;
        bool validate() const;
        void load(const LoadedObjectHandle& handle, stdx::span<std::byte> data);
        void unload();
    };
#pragma pack(pop)

    static_assert(sizeof(RoadObject) == 0x30);
}
