#include "classic3_soc_prf32xn.hpp"


// Implementation of: class PRFReadAddressA
namespace Gravity::Classic3 {
    /*
    uint32_t    address;
    */

    PRFReadAddressA::PRFReadAddressA(Phase& source) noexcept
        : Wavefront<PRFReadAddressA>("Gravity::Classic3::PRFReadAddressA", source)
    { }

    PRFReadAddressA::PRFReadAddressA(Phase& source, uint32_t address) noexcept
        : Wavefront<PRFReadAddressA>("Gravity::Classic3::PRFReadAddressA", source)
        , address                   (address)
    { }
}


// Implementation of: class PRFReadDataA
namespace Gravity::Classic3 {
    /*
    uint32_t    data;
    */

    PRFReadDataA::PRFReadDataA(Phase& source) noexcept
        : Wavefront<PRFReadDataA>("Gravity::Classic3::PRFReadDataA", source)
    { }

    PRFReadDataA::PRFReadDataA(Phase& source, uint32_t data) noexcept
        : Wavefront<PRFReadDataA>("Gravity::Classic3::PRFReadDataA", source)
        , data                   (data)
    { }
}


// Implementation of: class PRFReadAddressB
namespace Gravity::Classic3 {
    /*
    uint32_t    address;
    */

    PRFReadAddressB::PRFReadAddressB(Phase& source) noexcept
        : Wavefront<PRFReadAddressB>("Gravity::Classic3::PRFReadAddressB", source)
    { }

    PRFReadAddressB::PRFReadAddressB(Phase& source, uint32_t address) noexcept
        : Wavefront<PRFReadAddressB>("Gravity::Classic3::PRFReadAddressB", source)
        , address                   (address)
    { }
}


// Implementation of: class PRFReadDataB
namespace Gravity::Classic3 {
    /*
    uint32_t    data;
    */

    PRFReadDataB::PRFReadDataB(Phase& source) noexcept
        : Wavefront<PRFReadDataB>("Gravity::Classic3::PRFReadDataB", source)
    { }

    PRFReadDataB::PRFReadDataB(Phase& source, uint32_t data) noexcept
        : Wavefront<PRFReadDataB>("Gravity::Classic3::PRFReadDataB", source)
        , data                   (data)
    { }
}


// Implementation of: class PRFWrite
namespace Gravity::Classic3 {
    /*
    uint32_t    address;
    bool        enable;
    uint32_t    data;
    uint32_t    bitEnable;
    */

    PRFWrite::PRFWrite(Phase& source) noexcept
        : Wavefront<PRFWrite>("Gravity::Classic3::PRFWrite", source)
    { }

    PRFWrite::PRFWrite(Phase& source, uint32_t address, bool enable, uint32_t data, uint32_t bitEnable) noexcept
        : Wavefront<PRFWrite>("Gravity::Classic3::PRFWrite", source)
        , address             (address)
        , enable              (enable)
        , data                (data)
        , bitEnable           (bitEnable)
    { }
}


// Implementation of: class PRF32Payload
namespace Gravity::Classic3 {
    /*
    uint32_t*   const array;
    size_t      const size;
    */

    PRF32Payload::PRF32Payload(size_t sizeInWord) noexcept
        : array (new uint32_t[sizeInWord])
        , size  (sizeInWord)
    { }

    PRF32Payload::~PRF32Payload() noexcept
    {
        delete[] array;
    }

    uint32_t& PRF32Payload::operator[](size_t index) noexcept
    {
        return array[index];
    }

    const uint32_t& PRF32Payload::operator[](size_t index) const noexcept
    {
        return array[index];
    }

    size_t PRF32Payload::GetSize() const noexcept
    {
        return size;
    }

    uint32_t* PRF32Payload::GetArray() noexcept
    {
        return array;
    }

    const uint32_t* PRF32Payload::GetArray() const noexcept
    {
        return array;
    }
}


// Implementation of: class PRF32XN1W2RCPBW
namespace Gravity::Classic3 {
    /*
    PRFReadDataA    readDataA;
    PRFReadDataB    readDataB;

    const PRFWrite* write;
    */

    void PRF32XN1W2RCPBW::OnClockPosedge(const ClockPosedge& in) noexcept
    {
        //
        if (write && write->enable)
        {
            this->array[write->address >> 2] 
                = (~write->bitEnable) & write->data
                | ( write->bitEnable) & this->array[write->address >> 2];
        }

        //
        this->write = nullptr;
    }

    void PRF32XN1W2RCPBW::OnWrite(const PRFWrite& in) noexcept
    {
        this->write = &in;
    }

    void PRF32XN1W2RCPBW::OnReadAddressA(const PRFReadAddressA& in) noexcept
    {
        readDataA.data = this->array[in.address >> 2];
        readDataA.Fire(GetOutDimension());
    }

    void PRF32XN1W2RCPBW::OnReadAddressB(const PRFReadAddressB& in) noexcept
    {
        readDataB.data = this->array[in.address >> 2];
        readDataB.Fire(GetOutDimension());
    }

    PRF32XN1W2RCPBW::PRF32XN1W2RCPBW(size_t             sizeInWord,
                                     DimensionId        inDimension,
                                     DimensionId        outDimension) noexcept
        : Phase         (inDimension, outDimension, "Gravity::Classic3::PRF32XN1W2RCPBW")
        , PRF32Payload  (sizeInWord)
        , readDataA     (*this)
        , readDataB     (*this)
        , write         (nullptr)
    { }

    PRF32XN1W2RCPBW::PRF32XN1W2RCPBW(size_t             sizeInWord,
                                     DimensionId        inDimension,
                                     DimensionId        outDimension,
                                     const std::string& name) noexcept
        : Phase         (inDimension, outDimension, name)
        , PRF32Payload  (sizeInWord)
        , readDataA     (*this)
        , readDataB     (*this)
        , write         (nullptr)
    { }

    PRF32XN1W2RCPBW::~PRF32XN1W2RCPBW() noexcept
    { }
}
