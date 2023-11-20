#pragma once
//
//
//
//

#include <bitset>
#include <vector>
#include <deque>


#include "../csrc/soc/soc_axi_event.hpp"


#include "autoinclude.h"

#include AUTOINC_BE_COMMON(nonstdint.hpp)
#include AUTOINC_BE_COMMON(amba/axi4.hpp)


class AXIBusHistory {
public:
    static constexpr size_t     DEFAULT_DEPTH   = 32;

public:
    class Builder;

    class Transmission {
    public:
        enum class Type {
            DATA_READ = 0,
            DATA_WRITE,
            RESPONSE_WRITE
        };

        enum class Path {
            INSN = 0,
            DATA
        };

    private:
        Type                            type;
        Path                            path;

        uint4_t                         id;
        uint32_t                        data;
        std::bitset<4>                  wstrb;
        BullsEye::AXI4::attr_rresp_t    rresp;
        BullsEye::AXI4::attr_bresp_t    bresp;
        uint1_t                         last;

    public:
        Transmission() noexcept;

        Type                            GetType() const noexcept;
        void                            SetType(Type type) noexcept;

        Path                            GetPath() const noexcept;
        void                            SetPath(Path path) noexcept;

        uint4_t                         GetId() const noexcept;
        uint32_t                        GetData() const noexcept;
        std::bitset<4>                  GetWriteStrobe() const noexcept;
        BullsEye::AXI4::attr_rresp_t    GetReadResponse() const noexcept;
        BullsEye::AXI4::attr_bresp_t    GetWriteResponse() const noexcept;
        uint1_t                         GetLast() const noexcept;

        void                            SetId(uint4_t id) noexcept;
        void                            SetData(uint32_t data) noexcept;
        void                            SetWriteStrobe(std::bitset<4> wstrb) noexcept;
        void                            SetReadResponse(BullsEye::AXI4::attr_rresp_t rresp) noexcept;
        void                            SetWriteResponse(BullsEye::AXI4::attr_bresp_t bresp) noexcept;
        void                            SetLast(uint1_t last) noexcept;
    };

    class Transaction {
    public:
        enum class Type {
            READ = 0,
            WRITE
        };

        enum class Path {
            INSN = 0,
            DATA
        };

    private:
        Type                            type;
        Path                            path;

        uint4_t                         id;
        uint32_t                        address;
        BullsEye::AXI4::attr_len_t      length;
        BullsEye::AXI4::attr_size_t     size;
        BullsEye::AXI4::attr_burst_t    burst;
        uint1_t                         uncached;

        std::vector<Transmission>       tranmissions;

    public:
        Transaction() noexcept;

        Type                            GetType() const noexcept;
        void                            SetType(Type type) noexcept;

        Path                            GetPath() const noexcept;
        void                            SetPath(Path path) noexcept;

        uint4_t                         GetId() const noexcept;
        uint32_t                        GetAddress() const noexcept;
        BullsEye::AXI4::attr_len_t      GetLength() const noexcept;
        BullsEye::AXI4::attr_size_t     GetSize() const noexcept;
        BullsEye::AXI4::attr_burst_t    GetBurst() const noexcept;
        uint1_t                         GetUncached() const noexcept;

        void                            SetId(uint4_t id) noexcept;
        void                            SetAddress(uint32_t address) noexcept;
        void                            SetLength(BullsEye::AXI4::attr_len_t length) noexcept;
        void                            SetSize(BullsEye::AXI4::attr_size_t size) noexcept;
        void                            SetBurst(BullsEye::AXI4::attr_burst_t burst) noexcept;
        void                            SetUncached(uint1_t uncached) noexcept;

        std::vector<Transmission>&      GetTransmissions() noexcept;
        const std::vector<Transmission>&GetTransmissions() const noexcept;
    };

private:
    unsigned int            eventBusId;
    int                     eventPriority;

    size_t                  depth;
    std::deque<Transaction> history;

public:
    using iterator          = std::deque<Transaction>::iterator;
    using const_iterator    = std::deque<Transaction>::const_iterator;

protected:
    std::string     GetListenerName(const char* name) const noexcept;
    void            RegisterListeners() noexcept;
    void            UnregisterListeners() noexcept;

protected:
    void            OnFetchReadAddressAccepted(BullsEye::Draconids3014::SoCAXIBridgeFetchReadAddressAcceptedPostEvent& event) noexcept;
    void            OnFetchReadDataAccepted(BullsEye::Draconids3014::SoCAXIBridgeFetchReadDataAcceptedPostEvent& event) noexcept;

    void            OnDataReadAddressAccepted(BullsEye::Draconids3014::SoCAXIBridgeDataReadAddressAcceptedPostEvent& event) noexcept;
    void            OnDataReadDataAccepted(BullsEye::Draconids3014::SoCAXIBridgeDataReadDataAcceptedPostEvent& event) noexcept;

    void            OnDataWriteAddressAccepted(BullsEye::Draconids3014::SoCAXIBridgeDataWriteAddressAcceptedPostEvent& event) noexcept;
    void            OnDataWriteDataAccepted(BullsEye::Draconids3014::SoCAXIBridgeDataWriteDataAcceptedPostEvent& event) noexcept;
    void            OnDataWriteResponseAccepted(BullsEye::Draconids3014::SoCAXIBridgeDataWriteResponseAcceptedPostEvent& event) noexcept;

protected:
    AXIBusHistory(size_t depth, unsigned int eventBusId, int eventPriority) noexcept;

public:
    ~AXIBusHistory() noexcept;

    //
    size_t              GetDepth() const noexcept;
    void                SetDepth(size_t depth) noexcept;

    //
    unsigned int        GetEventBusId() const noexcept;
    int                 GetEventPriority() const noexcept;

    Transaction&        Push() noexcept;

    size_t              GetCount() const noexcept;
    const Transaction&  Get(unsigned int index) const noexcept;

    void                Clear() noexcept;

    //
    iterator            begin() noexcept;
    const_iterator      begin() const noexcept;

    iterator            end() noexcept;
    const_iterator      end() const noexcept;

    //
    AXIBusHistory(const AXIBusHistory&) = delete;
    AXIBusHistory& operator=(const AXIBusHistory&) = delete;

    AXIBusHistory(AXIBusHistory&&) = delete;
    AXIBusHistory& operator=(AXIBusHistory&&) = delete;
};


class AXIBusHistory::Builder {
private:
    size_t          depth;
    unsigned int    eventBusId;
    int             eventPriority;

public:
    Builder() noexcept;

    //
    Builder&        Depth(size_t depth) noexcept;
    Builder&        EventBusId(unsigned int eventBusId) noexcept;
    Builder&        EventPriority(int eventPriority) noexcept;

    //
    size_t          GetDepth() const noexcept;
    void            SetDepth(size_t depth) noexcept;

    unsigned int    GetEventBusId() const noexcept;
    void            SetEventBusId(unsigned int eventBusId) noexcept;

    int             GetEventPriority() const noexcept;
    void            SetEventPriority(int eventPriority) noexcept;

    //
    AXIBusHistory*  Build() noexcept;
};
