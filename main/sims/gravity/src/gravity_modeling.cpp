#include "gravity_modeling.hpp"


// Implementation of: class ClockPosedge
namespace Gravity {

    ClockPosedge::ClockPosedge(Phase& source) noexcept
        : Wavefront<ClockPosedge>   ("Gravity::ClockPosedge", source)
    { }

    ClockPosedge::ClockPosedge(const std::string& name, Phase& source) noexcept
        : Wavefront<ClockPosedge>   (name, source)
    { }

    ClockPosedge::~ClockPosedge() noexcept
    { }
}


// Implementation of: class ClockNegedge
namespace Gravity {

    ClockNegedge::ClockNegedge(Phase& source) noexcept
        : Wavefront<ClockNegedge>   ("Gravity::ClockNegedge", source)
    { }

    ClockNegedge::ClockNegedge(const std::string& name, Phase& source) noexcept
        : Wavefront<ClockNegedge>   (name, source)
    { }

    ClockNegedge::~ClockNegedge() noexcept
    { }
}


// Implementation of: class Phase
namespace Gravity {
    /*
    Dimension           inDimension;
    Dimension           outDimension;

    const std::string   name;
    */
    
    Phase::Phase(DimensionId          inDimension,
                 DimensionId          outDimension,
                 const std::string& name) noexcept
        : inDimension   (inDimension)
        , outDimension  (outDimension)
        , name          (name)
    { }

    Phase::~Phase() noexcept
    { }

    DimensionId Phase::GetInDimension() const noexcept
    {
        return this->inDimension;
    }

    void Phase::SetInDimension(DimensionId inDimension) noexcept
    {
        this->inDimension = inDimension;
    }

    DimensionId Phase::GetOutDimension() const noexcept
    {
        return this->outDimension;
    }

    void Phase::SetOutDimension(DimensionId outDimension) noexcept
    {
        this->outDimension = outDimension;
    }
}
