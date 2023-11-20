#include "appmain_historyaxi.hpp"
//
//
//
//

#include <sstream>
#include <iomanip>


// Implementation of: class AXIBusHistory::Transmission
/*
Type                            type;
Path                            path;

uint4_t                         id;
uint32_t                        data;
std::bitset<4>                  wstrb;
BullsEye::AXI4::attr_rresp_t    rresp;
BullsEye::AXI4::attr_bresp_t    bresp;
uint1_t                         last;
*/

AXIBusHistory::Transmission::Transmission() noexcept :
    type    (),
    path    (),
    id      (),
    data    (),
    wstrb   (),
    rresp   (),
    bresp   (),
    last    ()
{ }

AXIBusHistory::Transmission::Type AXIBusHistory::Transmission::GetType() const noexcept
{
    return type;
}

void AXIBusHistory::Transmission::SetType(Type type) noexcept
{
    this->type = type;
}

AXIBusHistory::Transmission::Path AXIBusHistory::Transmission::GetPath() const noexcept
{
    return path;
}

void AXIBusHistory::Transmission::SetPath(Path path) noexcept
{
    this->path = path;
}

uint4_t AXIBusHistory::Transmission::GetId() const noexcept
{
    return id;
}

uint32_t AXIBusHistory::Transmission::GetData() const noexcept
{
    return data;
}

std::bitset<4> AXIBusHistory::Transmission::GetWriteStrobe() const noexcept
{
    return wstrb;
}

BullsEye::AXI4::attr_rresp_t AXIBusHistory::Transmission::GetReadResponse() const noexcept
{
    return rresp;
}

BullsEye::AXI4::attr_bresp_t AXIBusHistory::Transmission::GetWriteResponse() const noexcept
{
    return bresp;
}

uint1_t AXIBusHistory::Transmission::GetLast() const noexcept
{
    return last;
}

void AXIBusHistory::Transmission::SetId(uint4_t id) noexcept
{
    this->id = id;
}

void AXIBusHistory::Transmission::SetData(uint32_t data) noexcept
{
    this->data = data;
}

void AXIBusHistory::Transmission::SetWriteStrobe(std::bitset<4> wstrb) noexcept
{
    this->wstrb = wstrb;
}

void AXIBusHistory::Transmission::SetReadResponse(BullsEye::AXI4::attr_rresp_t rresp) noexcept
{
    this->rresp = rresp;
}

void AXIBusHistory::Transmission::SetWriteResponse(BullsEye::AXI4::attr_bresp_t bresp) noexcept
{
    this->bresp = bresp;
}

void AXIBusHistory::Transmission::SetLast(uint1_t last) noexcept
{
    this->last = last;
}



// Implementation of: class AXIBusHistory::Transaction
/*
Type                            type;
Path                            path;

uint4_t                         id;
uint32_t                        address;
BullsEye::AXI4::attr_len_t      length;
BullsEye::AXI4::attr_size_t     size;
BullsEye::AXI4::attr_burst_t    burst;
uint1_t                         uncached;

std::vector<Transmission>       tranmissions;
*/

AXIBusHistory::Transaction::Transaction() noexcept :
    type            (),
    path            (),
    id              (),
    address         (),
    length          (),
    size            (),
    burst           (),
    uncached        (),
    tranmissions    ()
{ }

AXIBusHistory::Transaction::Type AXIBusHistory::Transaction::GetType() const noexcept
{
    return type;
}

void AXIBusHistory::Transaction::SetType(Type type) noexcept
{
    this->type = type;
}

AXIBusHistory::Transaction::Path AXIBusHistory::Transaction::GetPath() const noexcept
{
    return path;
}

void AXIBusHistory::Transaction::SetPath(Path path) noexcept
{
    this->path = path;
}

uint4_t AXIBusHistory::Transaction::GetId() const noexcept
{
    return id;
}

uint32_t AXIBusHistory::Transaction::GetAddress() const noexcept
{
    return address;
}

BullsEye::AXI4::attr_len_t AXIBusHistory::Transaction::GetLength() const noexcept
{
    return length;
}

BullsEye::AXI4::attr_size_t AXIBusHistory::Transaction::GetSize() const noexcept
{
    return size;
}

BullsEye::AXI4::attr_burst_t AXIBusHistory::Transaction::GetBurst() const noexcept
{
    return burst;
}

uint1_t AXIBusHistory::Transaction::GetUncached() const noexcept
{
    return uncached;
}

void AXIBusHistory::Transaction::SetId(uint4_t id) noexcept
{
    this->id = id;
}

void AXIBusHistory::Transaction::SetAddress(uint32_t address) noexcept
{
    this->address = address;
}

void AXIBusHistory::Transaction::SetLength(BullsEye::AXI4::attr_len_t length) noexcept
{
    this->length = length;
}

void AXIBusHistory::Transaction::SetSize(BullsEye::AXI4::attr_size_t size) noexcept
{
    this->size = size;
}

void AXIBusHistory::Transaction::SetBurst(BullsEye::AXI4::attr_burst_t burst) noexcept
{
    this->burst = burst;
}

void AXIBusHistory::Transaction::SetUncached(uint1_t uncached) noexcept
{
    this->uncached = uncached;
}

std::vector<AXIBusHistory::Transmission>& AXIBusHistory::Transaction::GetTransmissions() noexcept
{
    return tranmissions;
}

const std::vector<AXIBusHistory::Transmission>& AXIBusHistory::Transaction::GetTransmissions() const noexcept
{
    return tranmissions;
}


// Implementation of: class AXIBusHistory::Builder
/*
unsigned int    eventBusId;
int             eventPriority;
*/

AXIBusHistory::Builder::Builder() noexcept :
    eventBusId      (0),
    eventPriority   (0)
{ }

AXIBusHistory::Builder& AXIBusHistory::Builder::EventBusId(unsigned int eventBusId) noexcept
{
    this->eventBusId = eventBusId;
    return *this;
}

AXIBusHistory::Builder& AXIBusHistory::Builder::EventPriority(int eventPriority) noexcept
{
    this->eventPriority = eventPriority;
    return *this;
}

unsigned int AXIBusHistory::Builder::GetEventBusId() const noexcept
{
    return eventBusId;
}

void AXIBusHistory::Builder::SetEventBusId(unsigned int eventBusId) noexcept
{
    this->eventBusId = eventBusId;
}

int AXIBusHistory::Builder::GetEventPriority() const noexcept
{
    return eventPriority;
}

void AXIBusHistory::Builder::SetEventPriority(int eventPriority) noexcept
{
    this->eventPriority = eventPriority;
}

AXIBusHistory* AXIBusHistory::Builder::Build() noexcept
{
    return new AXIBusHistory(eventBusId, eventPriority);
}


// Implementation of: class AXIBusHistory
/*
unsigned int            eventBusId;
int                     eventPriority;

std::deque<Transaction> history;
*/

AXIBusHistory::AXIBusHistory(unsigned int eventBusId, int eventPriority) noexcept :
    eventBusId      (eventBusId),
    eventPriority   (eventPriority),
    history         ()
{
    RegisterListeners();
}

AXIBusHistory::~AXIBusHistory() noexcept
{
    UnregisterListeners();
}

unsigned int AXIBusHistory::GetEventBusId() const noexcept
{
    return eventBusId;
}

int AXIBusHistory::GetEventPriority() const noexcept
{
    return eventPriority;
}

AXIBusHistory::Transaction& AXIBusHistory::Push() noexcept
{
    return history.emplace_back();
}

size_t AXIBusHistory::GetCount() const noexcept
{
    return history.size();
}

const AXIBusHistory::Transaction& AXIBusHistory::Get(unsigned int index) const noexcept
{
    return history[index];
}

void AXIBusHistory::Clear() noexcept
{
    history.clear();
}

AXIBusHistory::iterator AXIBusHistory::begin() noexcept
{
    return history.begin();
}

AXIBusHistory::const_iterator AXIBusHistory::begin() const noexcept
{
    return history.begin();
}

AXIBusHistory::iterator AXIBusHistory::end() noexcept
{
    return history.end();
}

AXIBusHistory::const_iterator AXIBusHistory::end() const noexcept
{
    return history.end();
}

std::string AXIBusHistory::GetListenerName(const char* listener_name) const noexcept
{
    std::ostringstream oss;
    oss << "AXIBusHistory[";
    oss << std::hex << std::setw(16) << std::setfill('0') << uintptr_t(this);
    oss << "]::" << listener_name;
    return oss.str();
}

void AXIBusHistory::RegisterListeners() noexcept
{
    //
    BullsEye::RegisterListener(
        BullsEye::MakeListener(
            GetListenerName("OnFetchReadAddressAccepted"),
            eventPriority,
            &AXIBusHistory::OnFetchReadAddressAccepted,
            this
        ),
        eventBusId
    );

    BullsEye::RegisterListener(
        BullsEye::MakeListener(
            GetListenerName("OnFetchReadDataAccepted"),
            eventPriority,
            &AXIBusHistory::OnFetchReadDataAccepted,
            this
        ),
        eventBusId
    );

    //
    BullsEye::RegisterListener(
        BullsEye::MakeListener(
            GetListenerName("OnDataReadAddressAccepted"),
            eventPriority,
            &AXIBusHistory::OnDataReadAddressAccepted,
            this
        ),
        eventBusId
    );

    BullsEye::RegisterListener(
        BullsEye::MakeListener(
            GetListenerName("OnDataReadDataAccepted"),
            eventPriority,
            &AXIBusHistory::OnDataReadDataAccepted,
            this
        ),
        eventBusId
    );

    //
    BullsEye::RegisterListener(
        BullsEye::MakeListener(
            GetListenerName("OnDataWriteAddressAccepted"),
            eventPriority,
            &AXIBusHistory::OnDataWriteAddressAccepted,
            this
        ),
        eventBusId
    );

    BullsEye::RegisterListener(
        BullsEye::MakeListener(
            GetListenerName("OnDataWriteDataAccepted"),
            eventPriority,
            &AXIBusHistory::OnDataWriteDataAccepted,
            this
        ),
        eventBusId
    );

    BullsEye::RegisterListener(
        BullsEye::MakeListener(
            GetListenerName("OnDataWriteResponseAccepted"),
            eventPriority,
            &AXIBusHistory::OnDataWriteResponseAccepted,
            this
        ),
        eventBusId
    );
}

void AXIBusHistory::UnregisterListeners() noexcept
{
    //
    BullsEye::UnregisterListener(
        GetListenerName("OnFetchReadAddressAccepted"),
        &AXIBusHistory::OnFetchReadAddressAccepted,
        eventBusId
    );

    BullsEye::UnregisterListener(
        GetListenerName("OnFetchReadDataAccepted"),
        &AXIBusHistory::OnFetchReadDataAccepted,
        eventBusId
    );

    //
    BullsEye::UnregisterListener(
        GetListenerName("OnDataReadAddressAccepted"),
        &AXIBusHistory::OnDataReadAddressAccepted,
        eventBusId
    );

    BullsEye::UnregisterListener(
        GetListenerName("OnDataReadDataAccepted"),
        &AXIBusHistory::OnDataReadDataAccepted,
        eventBusId
    );

    //
    BullsEye::UnregisterListener(
        GetListenerName("OnDataWriteAddressAccepted"),
        &AXIBusHistory::OnDataWriteAddressAccepted,
        eventBusId
    );

    BullsEye::UnregisterListener(
        GetListenerName("OnDataWriteDataAccepted"),
        &AXIBusHistory::OnDataWriteDataAccepted,
        eventBusId
    );

    BullsEye::UnregisterListener(
        GetListenerName("OnDataWriteResponseAccepted"),
        &AXIBusHistory::OnDataWriteResponseAccepted,
        eventBusId
    );
}

void AXIBusHistory::OnFetchReadAddressAccepted(BullsEye::Draconids3014::SoCAXIBridgeFetchReadAddressAcceptedPostEvent& event) noexcept
{
    //
    auto& bundle = event.GetBundle();

    //
    Transaction& transaction = Push();

    transaction.SetType(Transaction::Type::READ);
    transaction.SetPath(Transaction::Path::INSN);

    transaction.SetId       (bundle.arid);
    transaction.SetAddress  (bundle.araddr);
    transaction.SetLength   (bundle.arlen);
    transaction.SetSize     (bundle.arsize);
    transaction.SetBurst    (bundle.arburst);
    transaction.SetUncached (bundle.aruser);
}

void AXIBusHistory::OnFetchReadDataAccepted(BullsEye::Draconids3014::SoCAXIBridgeFetchReadDataAcceptedPostEvent& event) noexcept
{
    //
    auto& bundle = event.GetBundle();

    //
    for (Transaction& transaction : *this)
    {
        if (transaction.GetType() == Transaction::Type::READ 
        &&  transaction.GetPath() == Transaction::Path::INSN
        &&  transaction.GetId()   == bundle.rid)
        {
            //
            Transmission& transmission = transaction.GetTransmissions().emplace_back();

            transmission.SetType(Transmission::Type::DATA_READ);
            transmission.SetPath(Transmission::Path::INSN);

            transmission.SetId          (bundle.rid);
            transmission.SetData        (bundle.rdata);
            transmission.SetReadResponse(bundle.rresp);
            transmission.SetLast        (bundle.rlast);

            break;
        }
    }
}

void AXIBusHistory::OnDataReadAddressAccepted(BullsEye::Draconids3014::SoCAXIBridgeDataReadAddressAcceptedPostEvent& event) noexcept
{
    //
    auto& bundle = event.GetBundle();

    //
    Transaction& transaction = Push();

    transaction.SetType(Transaction::Type::READ);
    transaction.SetPath(Transaction::Path::DATA);

    transaction.SetId       (bundle.arid);
    transaction.SetAddress  (bundle.araddr);
    transaction.SetLength   (bundle.arlen);
    transaction.SetSize     (bundle.arsize);
    transaction.SetBurst    (bundle.arburst);
    transaction.SetUncached (bundle.aruser);
}

void AXIBusHistory::OnDataReadDataAccepted(BullsEye::Draconids3014::SoCAXIBridgeDataReadDataAcceptedPostEvent& event) noexcept
{
    //
    auto& bundle = event.GetBundle();

    //
    for (Transaction& transaction : *this)
    {
        if (transaction.GetType() == Transaction::Type::READ
        &&  transaction.GetPath() == Transaction::Path::DATA 
        &&  transaction.GetId()   == bundle.rid)
        {
            //
            Transmission& transmission = transaction.GetTransmissions().emplace_back();

            transmission.SetType(Transmission::Type::DATA_READ);
            transmission.SetPath(Transmission::Path::DATA);

            transmission.SetId          (bundle.rid);
            transmission.SetData        (bundle.rdata);
            transmission.SetReadResponse(bundle.rresp);
            transmission.SetLast        (bundle.rlast);

            break;
        }
    }
}

void AXIBusHistory::OnDataWriteAddressAccepted(BullsEye::Draconids3014::SoCAXIBridgeDataWriteAddressAcceptedPostEvent& event) noexcept
{
    //
    auto& bundle = event.GetBundle();

    //
    Transaction& transaction = Push();

    transaction.SetType(Transaction::Type::WRITE);
    transaction.SetPath(Transaction::Path::DATA);

    transaction.SetId       (bundle.awid);
    transaction.SetAddress  (bundle.awaddr);
    transaction.SetLength   (bundle.awlen);
    transaction.SetSize     (bundle.awsize);
    transaction.SetBurst    (bundle.awburst);
    transaction.SetUncached (bundle.awuser);
}

void AXIBusHistory::OnDataWriteDataAccepted(BullsEye::Draconids3014::SoCAXIBridgeDataWriteDataAcceptedPostEvent& event) noexcept
{
    //
    auto& bundle = event.GetBundle();

    //
    for (Transaction& transaction : *this)
    {
        if (transaction.GetType() == Transaction::Type::WRITE
        &&  transaction.GetPath() == Transaction::Path::DATA)
        {
            //
            Transmission& transmission = transaction.GetTransmissions().emplace_back();

            transmission.SetType(Transmission::Type::DATA_WRITE);
            transmission.SetPath(Transmission::Path::DATA);

            transmission.SetData    (bundle.wdata);
            transmission.SetWriteStrobe(bundle.wstrb);
            transmission.SetLast    (bundle.wlast);

            break;
        }
    }
}

void AXIBusHistory::OnDataWriteResponseAccepted(BullsEye::Draconids3014::SoCAXIBridgeDataWriteResponseAcceptedPostEvent& event) noexcept
{
    //
    auto& bundle = event.GetBundle();

    //
    for (Transaction& transaction : *this)
    {
        if (transaction.GetType() == Transaction::Type::WRITE 
        &&  transaction.GetPath() == Transaction::Path::DATA
        &&  transaction.GetId()   == bundle.bid)
        {
            //
            Transmission& transmission = transaction.GetTransmissions().emplace_back();

            transmission.SetType(Transmission::Type::DATA_WRITE);
            transmission.SetPath(Transmission::Path::DATA);

            transmission.SetId              (bundle.bid);
            transmission.SetWriteResponse   (bundle.bresp);

            break;
        }
    }
}

