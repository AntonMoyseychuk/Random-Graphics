#include "pch.h"
#include "event_dispatcher.h"

#include "utils/debug/assertion.h"
#include "utils/data_structures/hash.h"


EventListenerID::EventListenerID(std::type_index eventTypeIndex)
    : BaseID(), m_eventTypeIndexHash(eventTypeIndex.hash_code())
{}


EventListenerID::EventListenerID(uint64_t ID, std::type_index eventTypeIndex)
    : BaseID(ID), m_eventTypeIndexHash(eventTypeIndex.hash_code())
{
}


EventListenerID::EventListenerID(uint64_t ID, uint64_t eventTypeIndexHash)
    : BaseID(ID), m_eventTypeIndexHash(eventTypeIndexHash)
{
}


void EventListenerID::Invalidate() noexcept
{
    BaseID::Invalidate(); 
    m_eventTypeIndexHash = UINT64_MAX;
}


uint64_t EventListenerID::Hash() const noexcept
{
    ds::HashBuilder builder;

    builder.AddValue(BaseID::Hash());
    builder.AddValue(m_eventTypeIndexHash);

    return builder.Value();
}


void EventListener::Invalidate() noexcept
{
#if defined(ENG_DEBUG)
    m_dbgName = "";
#endif
    m_ID.Invalidate();
    m_callback = {};
}


EventListener::EventListener(EventListenerID ID, const CallbackType& callback)
    : m_ID(ID), m_callback(callback)
{
    ENG_ASSERT(ID.IsValid(), "Passed invalid event listener ID");
    ENG_ASSERT(static_cast<bool>(callback), "Passed invalid event listener callback");
}


void EventListener::SetDebugName(ds::StrID name) noexcept
{
#if defined(ENG_DEBUG)
    m_dbgName = name;
#endif
}


ds::StrID EventListener::GetDebugName(ds::StrID name) const noexcept
{
#if defined(ENG_DEBUG)
    return m_dbgName;
#else
    return "";
#endif
}


void EventListener::Excecute(const void* pEvent) const noexcept
{
    if (!IsValid()) {
        return;
    }

    ENG_ASSERT(pEvent != nullptr, "pEvent is nullptr");

    m_callback(pEvent);
}


EventDispatcher& EventDispatcher::GetInstance()
{
    static EventDispatcher dispatcher;
    return dispatcher;
}


void EventDispatcher::SetListenerDebugName(const EventListenerID& listenerID, ds::StrID name) noexcept
{
#if defined(ENG_DEBUG)
    auto listenersCollectionIt = m_listenersMap.find(listenerID.TypeIndexHash());
    if (listenersCollectionIt == m_listenersMap.cend()) {
        return;
    }

    std::vector<EventListener>& listenersCollection = listenersCollectionIt->second;
    ENG_ASSERT(listenerID.Value() < listenersCollection.size(), "listenerID value is out of range");
    
    listenersCollection[listenerID.Value()].SetDebugName(name);
#endif
}


void EventDispatcher::Unsubscribe(EventListenerID listenerID) noexcept
{
    auto listenersCollectionIt = m_listenersMap.find(listenerID.TypeIndexHash());
    if (listenersCollectionIt == m_listenersMap.cend()) {
        return;
    }

    std::vector<EventListener>& listenersCollection = listenersCollectionIt->second;
    ENG_ASSERT(listenerID.Value() < listenersCollection.size(), "listenerID value is out of range");
    
    listenersCollection[listenerID.Value()].Invalidate();
}


EventDispatcher::EventDispatcher()
{
    static constexpr size_t EVENTS_TYPES_RESERVE_SIZE = 128ull;
    
    m_listenersMap.reserve(EVENTS_TYPES_RESERVE_SIZE);
}