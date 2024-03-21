#include "classic3_soc.hpp"


// Implementation of: class SRAMReadAddressA
namespace Gravity::Classic3 {
    /*
    uint32_t    address;
    bool        enable;
    */

    SRAMReadAddressA::SRAMReadAddressA(Phase& source) noexcept
        : Wavefront<SRAMReadAddressA>   ("Gravity::Classic3::SRAMReadAddressA", source)
        , address                       ()
        , enable                        (false)
    { }
}


// Implementation of: class SRAMReadDataA
namespace Gravity::Classic3 {
    /*
    uint32_t    data;
    */

    SRAMReadDataA::SRAMReadDataA(Phase& source) noexcept
        : Wavefront<SRAMReadDataA>      ("Gravity::Classic3::SRAMReadDataA", source)
        , data                          ()
    { }
}


// Implementation of: class SRAMReadAddressB
namespace Gravity::Classic3 {
    /*
    uint32_t    address;
    bool        enable;
    */

    SRAMReadAddressB::SRAMReadAddressB(Phase& source) noexcept
        : Wavefront<SRAMReadAddressB>   ("Gravity::Classic3::SRAMReadAddressB", source)
        , address                       ()
        , enable                        (false)
    { }
}


// Implementation of: class SRAMReadDataB
namespace Gravity::Classic3 {
    /*
    uint32_t    data;
    */

    SRAMReadDataB::SRAMReadDataB(Phase& source) noexcept
        : Wavefront<SRAMReadDataB>      ("Gravity::Classic3::SRAMReadDataB", source)
        , data                          ()
    { }
}


// Implementation of: class SRAMWrite
namespace Gravity::Classic3 {
    /*
    uint32_t    address;
    bool        enable;
    uint32_t    data;
    */

    SRAMWrite::SRAMWrite(Phase& source) noexcept
        : Wavefront<SRAMWrite>          ("Gravity::Classic3::SRAMWrite", source)
        , address                       ()
        , enable                        (false)
        , data                          ()
    { }
}


// Implementation of: class SRAM32Payload
namespace Gravity::Classic3 {
    /*
    uint32_t* const array;
    size_t    const size;
    */

    SRAM32Payload::SRAM32Payload(size_t sizeInWord) noexcept
        : array (new uint32_t[sizeInWord])
        , size  (sizeInWord)
    { }

    SRAM32Payload::~SRAM32Payload() noexcept
    {
        delete[] array;
    }

    uint32_t& SRAM32Payload::operator[](size_t index) noexcept
    {
        return array[index];
    }

    const uint32_t& SRAM32Payload::operator[](size_t index) const noexcept
    {
        return array[index];
    }

    size_t SRAM32Payload::GetSize() const noexcept
    {
        return size;
    }

    uint32_t* SRAM32Payload::GetArray() noexcept
    {
        return array;
    }

    const uint32_t* SRAM32Payload::GetArray() const noexcept
    {
        return array;
    }
}


// Implementation of: class SRAM32XN1W2RCPBW
namespace Gravity::Classic3 {
    /*
    SRAMReadDataA   readDataA;
    SRAMReadDataB   readDataB;
    */

    void SRAM32XN1W2RCPBW::OnClockPosedge(const ClockPosedge& in) noexcept
    {
        //
        if (readAddressA && readAddressA->enable)
        {
            readDataA.data = this->array[readAddressA->address >> 2];
        }

        if (readAddressB && readAddressB->enable)
        {
            readDataB.data = this->array[readAddressB->address >> 2];
        }

        //
        if (write && write->enable)
        {
            this->array[write->address >> 2] 
                = (~write->bitEnable) & write->data
                | ( write->bitEnable) & this->array[write->address >> 2];
        }

        //
        this->readAddressA  = nullptr;
        this->readAddressB  = nullptr;
        this->write         = nullptr;

        //
        readDataA.Fire(GetOutDimension());
        readDataB.Fire(GetOutDimension());
    }

    void SRAM32XN1W2RCPBW::OnSRAMWrite(const SRAMWrite& in) noexcept
    {
        this->write = &in;
    }

    void SRAM32XN1W2RCPBW::OnSRAMReadAddressA(const SRAMReadAddressA& in) noexcept
    {
        this->readAddressA = &in;
    }

    void SRAM32XN1W2RCPBW::OnSRAMReadAddressB(const SRAMReadAddressB& in) noexcept
    {
        this->readAddressB = &in;
    }

    SRAM32XN1W2RCPBW::SRAM32XN1W2RCPBW(size_t               sizeInWord,
                                       DimensionId            inDimension,
                                       DimensionId            outDimension) noexcept
        : Phase         (inDimension, outDimension, "Gravity::Classic3::SRAM32XN1W2RCPBW")
        , SRAM32Payload (sizeInWord)
        , readDataA     (*this)
        , readDataB     (*this)
        , write         (nullptr)
        , readAddressA  (nullptr)
        , readAddressB  (nullptr)
    { }

    SRAM32XN1W2RCPBW::SRAM32XN1W2RCPBW(size_t               sizeInWord,
                                       DimensionId            inDimension,
                                       DimensionId            outDimension,
                                       const std::string&   name) noexcept
        : Phase         (inDimension, outDimension, name)
        , SRAM32Payload (sizeInWord)
        , readDataA     (*this)
        , readDataB     (*this)
        , write         (nullptr)
        , readAddressA  (nullptr)
        , readAddressB  (nullptr)
    { }

    SRAM32XN1W2RCPBW::~SRAM32XN1W2RCPBW() noexcept
    { }
}
