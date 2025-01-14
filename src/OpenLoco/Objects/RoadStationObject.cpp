#include "RoadStationObject.h"
#include "../Graphics/Colour.h"
#include "../Graphics/Gfx.h"
#include "../Interop/Interop.hpp"
#include "ObjectManager.h"

namespace OpenLoco
{
    // 0x00490C17
    void RoadStationObject::drawPreviewImage(Gfx::Context& context, const int16_t x, const int16_t y) const
    {
        auto colourImage = Gfx::recolour(image, Colour::mutedDarkRed);

        Gfx::drawImage(&context, x - 34, y - 34, colourImage);

        auto colour = ExtColour::translucentMutedDarkRed1;
        if (!(flags & RoadStationFlags::recolourable))
        {
            colour = ExtColour::unk2E;
        }

        auto translucentImage = Gfx::recolourTranslucent(image + 1, colour);

        Gfx::drawImage(&context, x - 34, y - 34, translucentImage);
    }

    // 0x00490C59
    void RoadStationObject::drawDescription(Gfx::Context& context, const int16_t x, const int16_t y, [[maybe_unused]] const int16_t width) const
    {
        Ui::Point rowPosition = { x, y };
        ObjectManager::drawGenericDescription(context, rowPosition, designed_year, obsolete_year);
    }

    // 0x00490BD8
    bool RoadStationObject::validate() const
    {
        if (cost_index >= 32)
        {
            return false;
        }
        if (-sell_cost_factor > build_cost_factor)
        {
            return false;
        }
        if (build_cost_factor <= 0)
        {
            return false;
        }
        if (paintStyle >= 1)
        {
            return false;
        }
        if (num_compatible > 7)
        {
            return false;
        }
        if ((flags & RoadStationFlags::passenger) && (flags & RoadStationFlags::freight))
        {
            return false;
        }
        return true;
    }

    // 0x00490ABE
    void RoadStationObject::load(const LoadedObjectHandle& handle, stdx::span<std::byte> data)
    {
        Interop::registers regs;
        regs.esi = Interop::X86Pointer(this);
        regs.ebx = handle.id;
        regs.ecx = enumValue(handle.type);
        Interop::call(0x00490ABE, regs);
    }

    // 0x00490B8E
    void RoadStationObject::unload()
    {
        name = 0;
        image = 0;
        var_10 = 0;
        var_14 = 0;
        var_18 = 0;
        var_1C = 0;
        std::fill(std::begin(mods), std::end(mods), 0);
        var_2C = 0;
        std::fill(std::begin(var_2E), std::end(var_2E), 0);
    }
}
