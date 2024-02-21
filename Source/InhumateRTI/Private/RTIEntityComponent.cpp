#include "RTIEntityComponent.h"
#include "Engine/World.h"
#include "RTIPositionComponent.h"

URTIEntityComponent::URTIEntityComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
    bAutoActivate = true;
    Owned = true;
    TitleFromActorName = true;
}

bool URTIEntityComponent::IsPublishing()
{
    return IsActive() && Owned && Created &&
           (GetSubsystem()->GetState() == ERuntimeState::RUNNING || GetSubsystem()->GetState() == ERuntimeState::UNKNOWN);
}

bool URTIEntityComponent::IsReceiving()
{
    return !IsPublishing() && (!Owned || (GetSubsystem()->GetState() != ERuntimeState::RUNNING &&
                                          GetSubsystem()->GetState() != ERuntimeState::UNKNOWN));
}

void URTIEntityComponent::BeginPlay()
{
    auto subsystem = GetSubsystem();
    if (subsystem && (subsystem->GetState() == ERuntimeState::LOADING || (subsystem->GetTime() < FLT_EPSILON && subsystem->GetState() != ERuntimeState::RUNNING))) {
        Persistent = true;        
    }
    if (Id.IsEmpty()) {
        if (Persistent) {
            Id = GetReadableName().Replace(TEXT(".RTIEntity"), TEXT(""));
            if (subsystem) Id = GetSubsystem()->Application + "." + Id;
        } else {
            Id = FGuid::NewGuid().ToString();
        }                
    }
    Super::BeginPlay();
}

void URTIEntityComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);
    auto subsystem = GetSubsystem();
    if (subsystem) {
        if (IsActive() && Created && Owned) {
            auto rti = subsystem->RTI();
            if (rti && rti->connected()) {
                UE_LOG(LogRTI, Log, TEXT("Publish destroy %s"), *Id);
                inhumate::rti::proto::EntityOperation message;
                message.set_id(TCHAR_TO_UTF8(*Id));
                message.set_client_id(rti->client_id());
                message.set_allocated_destroy(new google::protobuf::Empty());
                rti->Publish(inhumate::rti::ENTITY_CHANNEL, message);
            }
        }
        subsystem->UnregisterEntity(this);
    }
}

void URTIEntityComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (!IsActive()) return;

    TimeSinceLastUpdate += DeltaTime;
    auto subsystem = GetSubsystem();
    if (!subsystem) return;
    auto rti = subsystem->RTI();
    if (!rti || !rti->connected()) return;
    if (Owned && subsystem->HasPersistentEntityOwner() && (subsystem->GetState() == ERuntimeState::RUNNING || subsystem->GetState() == ERuntimeState::UNKNOWN)) {
        if (!Created) {
            Created = true;
            TimeSinceLastUpdate = 0;
            OwnerClientId = subsystem->ClientId();
            subsystem->RegisterEntity(this);
            if (Persistent && subsystem->HasPersistentEntityOwner() && !subsystem->IsPersistentEntityOwner()) {
                Owned = false;
                OwnerClientId = subsystem->GetPersistentEntityOwnerClientId();
            } else {
                inhumate::rti::proto::EntityOperation message;
                message.set_id(TCHAR_TO_UTF8(*Id));
                message.set_client_id(rti->client_id());
                auto data = new inhumate::rti::proto::EntityOperation_EntityData();
                FillEntityData(data);
                message.set_allocated_create(data);
                rti->Publish(inhumate::rti::ENTITY_CHANNEL, message);
                CreatedEvent.Broadcast();
                UE_LOG(LogRTI, Log, TEXT("Publish create %s %s"), *Type, *Id);
            }
        } else if (UpdateRequested || (UpdateInterval > 1e-5f && TimeSinceLastUpdate > UpdateInterval)) {
            UpdateRequested = false;
            TimeSinceLastUpdate = 0;
            inhumate::rti::proto::EntityOperation message;
            message.set_id(TCHAR_TO_UTF8(*Id));
            message.set_client_id(rti->client_id());
            auto data = new inhumate::rti::proto::EntityOperation_EntityData();
            FillEntityData(data);
            message.set_allocated_update(data);
            rti->Publish(inhumate::rti::ENTITY_CHANNEL, message);
            UpdatedEvent.Broadcast();
        }
    } else if (Owned && !Created && subsystem->GetState() == ERuntimeState::PLAYBACK) {
        UE_LOG(LogRTI, Log, TEXT("Destroy owned but non-created entity for playback %s"), *Id);
        GetOwner()->Destroy();
    }
}

void URTIEntityComponent::RequestUpdate()
{
    if (IsActive()) UpdateRequested = true;
}

void URTIEntityComponent::SetPropertiesFromEntityData(const inhumate::rti::proto::EntityOperation_EntityData &data)
{
    Type = FString(data.type().c_str());
    Category = EntityCategoryFromPb(data.category());
    Domain = EntityDomainFromPb(data.domain());
    LVC = LVCCategoryFromPb(data.lvc());
    if (data.has_dimensions()) {
        Size.X = data.dimensions().length() * 100;
        Size.Y = data.dimensions().width() * 100;
        Size.Z = data.dimensions().height() * 100;
        if (data.dimensions().has_center()) {
            Center.X = data.dimensions().center().z() * 100;
            Center.Y = data.dimensions().center().x() * 100;
            Center.Z = data.dimensions().center().y() * 100;
        }
    }
    if (data.has_color()) {
        Color.R = data.color().red();
        Color.G = data.color().green();
        Color.B = data.color().blue();
    }
}

void URTIEntityComponent::FillEntityData(inhumate::rti::proto::EntityOperation_EntityData *data)
{
    if (TitleFromActorName) {
        auto title = GetReadableName().Replace(TEXT(".RTIEntity"), TEXT(""));
        data->set_title(TCHAR_TO_UTF8(*title));
    } else {
        data->set_title(TCHAR_TO_UTF8(*Title));
    }
    data->set_type(TCHAR_TO_UTF8(*Type));
    data->set_category(PbCategoryFromEntityCategory(Category));
    data->set_domain(PbDomainFromEntityDomain(Domain));
    data->set_lvc(PbCategoryFromLVCCategory(LVC));
    if (Size.Size() < 1e-5 && Center.Size() < 1e-5) {
        FVector Origin, BoxExtent;
        GetOwner()->GetActorBounds(false, Origin, BoxExtent, true);
        Size = BoxExtent * 2;
        Center = Origin - GetOwner()->GetActorLocation();
    }
    if (Size.Size() > 1e-5 || Center.Size() > 1e-5) {
        auto dimensions = new inhumate::rti::proto::EntityOperation_Dimensions();
        dimensions->set_length(Size.X / 100);
        dimensions->set_width(Size.Y / 100);
        dimensions->set_height(Size.Z / 100);
        if (Center.Size() > 1e-5) {
            auto center = URTIPositionComponent::UE4ToRTILocalPosition(Center);
            dimensions->set_allocated_center(center);
        }
        data->set_allocated_dimensions(dimensions);
    }
    if (Color.R > 0 || Color.G > 0 || Color.B > 0 || Color.A > 0) {
        auto color = new inhumate::rti::proto::Color();
        color->set_red(Color.R);
        color->set_green(Color.G);
        color->set_blue(Color.B);
        data->set_allocated_color(color);
    }
    auto position = new inhumate::rti::proto::EntityPosition();
    URTIPositionComponent::SetPositionMessageFromActor(*position, GetOwner());
    data->set_allocated_position(position);
}
