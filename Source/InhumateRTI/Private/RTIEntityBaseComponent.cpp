#include "RTIEntityBaseComponent.h"
#include "GameFramework/Actor.h"
#include "inhumaterti.hpp"
#include "IdMessage.pb.h"
#include "EntityPosition.pb.h"

URTIEntityBaseComponent::URTIEntityBaseComponent(const FObjectInitializer& init)
{
    // uh.. this is required by Unreal. dunno what to do.
}

URTIEntityBaseComponent::URTIEntityBaseComponent(const FString& channelName, const bool stateless, const bool ephemeral)
{
    ChannelName = channelName;
    Stateless = stateless;
    Ephemeral = ephemeral;
    PrimaryComponentTick.bCanEverTick = true;
}

bool URTIEntityBaseComponent::IsPublishing()
{
    return Entity && Entity->IsPublishing();
}

bool URTIEntityBaseComponent::IsReceiving()
{
    return Entity && Entity->IsReceiving();
}

void URTIEntityBaseComponent::BeginPlay()
{
	Super::BeginPlay();
}

void URTIEntityBaseComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);
    Unsubscribe();
}

void URTIEntityBaseComponent::Publish(const google::protobuf::Message& message)
{
    auto *idmessage_p = (inhumate::rti::proto::IdMessage*) &message;
    if (idmessage_p->id().empty()) {
        UE_LOG(LogRTI, Warning, TEXT("Missing entity ID in published message on channel %s"), *ChannelName);
    }
    auto rti = RTI();
    if (!registeredChannel.Contains(ChannelName)) registeredChannel.Add(ChannelName, false);
    if (!registeredChannel[ChannelName] && rti) RegisterChannel();
    if (rti->connected()) rti->Publish(TCHAR_TO_UTF8(*ChannelName), message);
}

void URTIEntityBaseComponent::Initialize()
{
    // Q: Why not in BeginPlay() or InitializeComponent() 
    // A: Because it gets called right after spawn... and RTISpawnerActor needs to have a chance to set id.
    if (!instances.Contains(ChannelName)) {
        TMap<FString, TArray<URTIEntityBaseComponent*>> newInstanceMap;
        instances.Add(ChannelName, newInstanceMap);
        subscribed.Add(ChannelName, false);
    }
    Entity = Cast<URTIEntityComponent>(GetOwner()->GetComponentByClass(URTIEntityComponent::StaticClass()));
    if (Entity && !Entity->Id.IsEmpty()) {
        if (!instances[ChannelName].Contains(Entity->Id)) instances[ChannelName].Add(Entity->Id);
        instances[ChannelName][Entity->Id].Add(this);
        SubscribedEntityId = Entity->Id;
        initialized = true;
    } else if (!Entity && !warnedNoEntity) {
        UE_LOG(LogRTI, Warning, TEXT("Missing RTIEntity component on actor %s"), *GetOwner()->GetName());
    }
}

void URTIEntityBaseComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (!SubscribedEntityId.IsEmpty() && (!Entity || Entity->Id.IsEmpty() || Entity->Id != SubscribedEntityId)) {
        Unsubscribe();
        initialized = false;
    }

    if (!initialized) Initialize();

    auto rti = RTI();
    if (!registeredChannel.Contains(ChannelName)) registeredChannel.Add(ChannelName, false);
    if (!registeredChannel[ChannelName] && rti) RegisterChannel();
    if (!subscribed.Contains(ChannelName)) subscribed.Add(ChannelName, false);
    if (!subscribed[ChannelName] && rti && rti->connected()) {
        // Note that subscribed and instances are static. 
        // We lazily subscribe once for each derived class and keep track of class instances for each entity id,
        // then deliver messages by calling the OnMessage() method in the appropriate instance.
        subscribed[ChannelName] = true;
        subscription.Add(ChannelName, rti->Subscribe(TCHAR_TO_UTF8(*ChannelName), [](const std::string& channel, const std::string& content) {
            auto message = inhumate::rti::RTIClient::Parse<inhumate::rti::proto::IdMessage>(content);
            FString Channel(channel.c_str());
            if (!instances[Channel].Contains(message.id().c_str())) {
                if (!warnedUnknown.Contains(Channel + message.id().c_str())) {
                    if (!message.id().empty()) UE_LOG(LogRTI, Warning, TEXT("Unknown entity id %s, channel %s"), *FString(message.id().c_str()), *FString(channel.c_str()));
                    warnedUnknown.Add(Channel + message.id().c_str(), true);
                }
            } else {
                for (auto instance : instances[Channel][message.id().c_str()]) {
                    if (instance != nullptr) instance->OnMessage(content.c_str());
                }
            }
        }));
    }
}

void URTIEntityBaseComponent::ResetSubscriptions()
{
    subscribed.Empty();
    subscription.Empty();
    instances.Empty();
    warnedUnknown.Empty();
}

void URTIEntityBaseComponent::Unsubscribe()
{
    if (SubscribedEntityId.IsEmpty() || ChannelName.IsEmpty() || !instances.Contains(ChannelName)) return;
    if (instances[ChannelName].Contains(SubscribedEntityId)) {
        if (instances[ChannelName][SubscribedEntityId].Contains(this)) instances[ChannelName][SubscribedEntityId].Remove(this);
        if (instances[ChannelName][SubscribedEntityId].Num() == 0) instances[ChannelName].Remove(SubscribedEntityId);
    }
    if (instances[ChannelName].Num() == 0 && subscribed[ChannelName]) {
        auto rti = RTI();
        if (rti && rti->connected() && subscription[ChannelName]) {
            rti->Unsubscribe(subscription[ChannelName]);
        }
        subscribed[ChannelName] = false;
    }
    SubscribedEntityId = "";
}

void URTIEntityBaseComponent::RegisterChannel()
{
    inhumate::rti::proto::Channel channel;
    channel.set_name(TCHAR_TO_UTF8(*ChannelName));
    channel.set_data_type(TCHAR_TO_UTF8(*GetClass()->GetName()));
    channel.set_stateless(Stateless);
    channel.set_ephemeral(Ephemeral);
    channel.set_first_field_id(true);
    RTI()->RegisterChannel(channel);
    if (!registeredChannel.Contains(ChannelName)) registeredChannel.Add(ChannelName, true);
    registeredChannel[ChannelName] = true;
}

TMap< FString, bool> URTIEntityBaseComponent::subscribed;
TMap< FString, TMap< FString, TArray<URTIEntityBaseComponent*> > > URTIEntityBaseComponent::instances;
TMap< FString, inhumate::rti::messagecallback_p > URTIEntityBaseComponent::subscription;
TMap< FString, bool> URTIEntityBaseComponent::warnedUnknown;
TMap< FString, bool> URTIEntityBaseComponent::registeredChannel;
