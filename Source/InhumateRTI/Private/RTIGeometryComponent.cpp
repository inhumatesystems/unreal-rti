#include "RTIGeometryComponent.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Components/SplineComponent.h"
#include "Components/StaticMeshComponent.h"
#include "RTICoordinateConversionInterface.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Engine/Classes/Engine/StaticMesh.h"

URTIGeometryComponent::URTIGeometryComponent()
{
    bAutoActivate = true;
    Persistent = true;
}

void URTIGeometryComponent::BeginPlay()
{
    Super::BeginPlay();

    if (!IsActive()) return;

    if (Id.IsEmpty()) Id = FGuid::NewGuid().ToString();
    auto subsystem = GetSubsystem();
    if (subsystem && !Registered) {
        Registered = subsystem->RegisterGeometry(this);
    }
    // To avoid tick we will try to create geometry component from timer instead.
    GetWorld()->GetTimerManager().SetTimer(RequestCreateTimer, this, &URTIGeometryComponent::On_TryPublishCreate, .1f, true);
}

void URTIGeometryComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);
    auto subsystem = GetSubsystem();
    if (subsystem) {
        if (IsActive() && Registered && Created && Owned && (!Persistent || subsystem->IsPersistentGeometryOwner())) {
            auto rti = subsystem->RTI();
            if (!rti || !rti->connected()) return;
            UE_LOG(LogRTI, Log, TEXT("Publish destroy geometry %s"), *Id);
            inhumate::rti::proto::GeometryOperation message;
            message.set_id(TCHAR_TO_UTF8(*Id));
            message.set_client_id(rti->client_id());
            message.set_allocated_destroy(new google::protobuf::Empty());
            rti->Publish(inhumate::rti::GEOMETRY_CHANNEL, message);
        }
        subsystem->UnregisterGeometry(this);
    }

    GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
}

void URTIGeometryComponent::On_TryPublishCreate()
{
    auto subsystem = GetSubsystem();
    if (!subsystem || !subsystem->RTI() || !subsystem->RTI()->connected()) return;
    if (subsystem && !Registered) {
        Registered = subsystem->RegisterGeometry(this);
    }
    if (Registered && !Created && Owned && (!Persistent || subsystem->IsPersistentGeometryOwner())) {
        PublishCreate();
        GetWorld()->GetTimerManager().ClearTimer(RequestCreateTimer);
    }
}

void URTIGeometryComponent::RequestUpdate()
{
    if (!IsActive()) return;

    // To avoid tick we will try update from timer instead.
    GetWorld()->GetTimerManager().SetTimer(RequestUpdateTimer, this, &URTIGeometryComponent::On_TryPublishUpdate, .1f, true);
}

void URTIGeometryComponent::On_TryPublishUpdate()
{
    auto subsystem = GetSubsystem();
    if (!subsystem || !subsystem->RTI() || !subsystem->RTI()->connected()) return;
    if (Registered && Owned && Created && (!Persistent || subsystem->IsPersistentGeometryOwner())) {
        PublishUpdate();
        GetWorld()->GetTimerManager().ClearTimer(RequestUpdateTimer);
    }
}

void URTIGeometryComponent::PublishCreate()
{
    auto subsystem = GetSubsystem();
    if (!subsystem || !subsystem->RTI() || !subsystem->RTI()->connected()) return;
    auto rti = subsystem->RTI();

    Created = true;

    inhumate::rti::proto::GeometryOperation message;
    message.set_id(TCHAR_TO_UTF8(*Id));
    message.set_client_id(rti->client_id());
    auto data = new inhumate::rti::proto::GeometryOperation_Geometry();
    FillGeometryData(data);
    message.set_allocated_create(data);
    switch (data->usage()) {
    case inhumate::rti::proto::GeometryOperation::Usage::GeometryOperation_Usage_SCENARIO:
        UE_LOG(LogRTI, Log, TEXT("Publish scenario geometry %s"), *Id);
        break;
    case inhumate::rti::proto::GeometryOperation::Usage::GeometryOperation_Usage_ENTITY:
        UE_LOG(LogRTI, Log, TEXT("Publish entity geometry %s"), *Id);
        break;
    default:
        UE_LOG(LogRTI, Log, TEXT("Publish UNKNOWN (%d) geometry %s"), data->usage(), *Id);
    }
    rti->Publish(inhumate::rti::GEOMETRY_CHANNEL, message);
    CreatedEvent.Broadcast();
}

void URTIGeometryComponent::PublishUpdate()
{
    auto subsystem = GetSubsystem();
    if (!subsystem || !subsystem->RTI() || !subsystem->RTI()->connected()) return;
    auto rti = subsystem->RTI();

    UpdateRequested = false;

    inhumate::rti::proto::GeometryOperation message;
    message.set_id(TCHAR_TO_UTF8(*Id));
    message.set_client_id(rti->client_id());
    auto data = new inhumate::rti::proto::GeometryOperation_Geometry();
    FillGeometryData(data);
    message.set_allocated_update(data);
    rti->Publish(inhumate::rti::GEOMETRY_CHANNEL, message);
    UpdatedEvent.Broadcast();
}

void URTIGeometryComponent::FillGeometryData(inhumate::rti::proto::GeometryOperation_Geometry *data)
{
}

inhumate::rti::proto::GeometryOperation_Point2D *URTIGeometryComponent::CreatePoint2D(const FVector &location)
{
    auto point = new inhumate::rti::proto::GeometryOperation_Point2D();
    SetPoint2D(location, point);
    return point;
}

inhumate::rti::proto::GeometryOperation_Point3D *URTIGeometryComponent::CreatePoint3D(const FVector &location)
{
    auto point = new inhumate::rti::proto::GeometryOperation_Point3D();
    SetPoint3D(location, point);
    return point;
}

inhumate::rti::proto::GeometryOperation_Polygon *URTIGeometryComponent::CreatePolygon(const UStaticMeshComponent *component)
{
    auto polygon = new inhumate::rti::proto::GeometryOperation_Polygon();
    FVector Min;
    FVector Max;
    component->GetLocalBounds(Min, Max);
    auto transform = component->GetOwner()->GetActorTransform();
    auto corner1 = transform.TransformPosition(FVector(Min.X, Min.Y, 0));
    auto corner2 = transform.TransformPosition(FVector(Min.X, Max.Y, 0));
    auto corner3 = transform.TransformPosition(FVector(Max.X, Max.Y, 0));
    auto corner4 = transform.TransformPosition(FVector(Max.X, Min.Y, 0));
    SetPoint2D(corner1, polygon->add_points());
    SetPoint2D(corner2, polygon->add_points());
    SetPoint2D(corner3, polygon->add_points());
    SetPoint2D(corner4, polygon->add_points());
    polygon->set_base(transform.TransformPosition(Min).Z / 100);
    polygon->set_height(transform.TransformPosition(Max).Z / 100 - polygon->base());
    return polygon;
}

inhumate::rti::proto::GeometryOperation_Mesh *URTIGeometryComponent::CreateMesh(const UStaticMesh *Mesh)
{
    auto mesh = new inhumate::rti::proto::GeometryOperation_Mesh();
    AddMesh(mesh, Mesh, 0, nullptr, nullptr);
    return mesh;
}

inhumate::rti::proto::GeometryOperation_Mesh *
URTIGeometryComponent::CreateMesh(const TArray<UStaticMeshComponent *> &components, const bool local, const bool bFlippedNormals)
{
    auto mesh = new inhumate::rti::proto::GeometryOperation_Mesh();
    uint32 offset = 0; // offset indices when adding multiple meshes
    for (auto component : components) {
        if (!component->GetStaticMesh()) continue;
        offset += AddMesh(mesh, component->GetStaticMesh(), offset, &component->GetComponentTransform(),
                          local ? &component->GetOwner()->GetActorTransform() : nullptr, bFlippedNormals);
    }
    if (offset > 0 && (mesh->vertices_size() > WARN_MESH_SIZE || mesh->indices_size() > WARN_MESH_SIZE ||
                       mesh->ByteSizeLong() > WARN_MESSAGE_BYTES)) {
        UE_LOG(LogRTI, Warning, TEXT("Large combined mesh geometry - %d vertices and %d indices, %d kbytes"),
               mesh->vertices_size(), mesh->indices_size(), mesh->ByteSizeLong() / 1024);
    }
    return mesh;
}

uint32 URTIGeometryComponent::AddMesh(inhumate::rti::proto::GeometryOperation_Mesh *mesh,
                                      const UStaticMesh *Mesh,
                                      uint32 Offset = 0,
                                      const FTransform *ComponentTransform = nullptr,
                                      const FTransform *ActorTransform = nullptr,
                                      const bool bFlippedNormals)
{
    FString MeshName = Mesh->GetPathName(NULL);
    if (!Mesh->bAllowCPUAccess) {
#if WITH_EDITOR
        UE_LOG(LogRTI, Warning,
               TEXT("Packaged build won't create mesh geometry - static mesh %s needs 'Allow CPU Access' flag"), *MeshName);
#else
        return 0;
#endif
    }
    auto RenderData = Mesh->GetRenderData();
    if (!RenderData) return 0;
    auto NumLODs = RenderData->LODResources.Num();
    if (NumLODs == 0) return 0;
    auto LOD = NumLODs - 1;
    auto &LODResource = RenderData->LODResources[LOD];
    auto VertexBuffer = &LODResource.VertexBuffers.PositionVertexBuffer;
    if (!VertexBuffer) return 0;
    auto IndexBuffer = &LODResource.IndexBuffer;
    if (!IndexBuffer) return 0;
    if (VertexBuffer->GetNumVertices() > WARN_MESH_SIZE || IndexBuffer->GetNumIndices() > WARN_MESH_SIZE) {
        UE_LOG(LogRTI, Warning, TEXT("Creating mesh geometry from large static mesh %s - LOD %d has %d vertices and %d indices"),
               *MeshName, LOD, VertexBuffer->GetNumVertices(), IndexBuffer->GetNumIndices());
    }
    for (uint32 i = 0; i < VertexBuffer->GetNumVertices(); i++) {
        FVector Point = VertexBuffer->VertexPosition(i);
        if (ComponentTransform) Point = ComponentTransform->TransformPosition(Point);
        if (ActorTransform) Point = ActorTransform->InverseTransformPosition(Point);
        auto point = mesh->add_vertices();
        point->set_x(Point.Y / 100);
        point->set_y(Point.Z / 100);
        point->set_z(Point.X / 100);
    }
    if (LODResource.bHasReversedIndices && bFlippedNormals == false) {
        for (int32 i = 0; i + 2 < IndexBuffer->GetNumIndices(); i += 3) {
            mesh->add_indices(Offset + IndexBuffer->GetIndex(i + 2));
            mesh->add_indices(Offset + IndexBuffer->GetIndex(i + 1));
            mesh->add_indices(Offset + IndexBuffer->GetIndex(i));
        }
    } else {
        for (int32 i = 0; i < IndexBuffer->GetNumIndices(); i++) {
            mesh->add_indices(Offset + IndexBuffer->GetIndex(i));
        }
    }
    return VertexBuffer->GetNumVertices();
}

FVector BOX_CORNERS[] = {
    FVector(0, 0, 0), FVector(1, 0, 0), FVector(1, 1, 0), FVector(0, 1, 0),
    FVector(0, 1, 1), FVector(1, 1, 1), FVector(1, 0, 1), FVector(0, 0, 1),
};

int BOX_INDICES[] = { 0, 2, 1, // face front
                      0, 3, 2, 2, 3, 4, // face top
                      2, 4, 5, 1, 2, 5, // face right
                      1, 5, 6, 0, 7, 4, // face left
                      0, 4, 3, 5, 4, 7, // face back
                      5, 7, 6, 0, 6, 7, // face bottom
                      0, 1, 6 };

inhumate::rti::proto::GeometryOperation_Mesh *URTIGeometryComponent::CreateMeshFromCollision(const TArray<UShapeComponent *> &components)
{
    auto mesh = new inhumate::rti::proto::GeometryOperation_Mesh();
    uint32 offset = 0; // offset indices when adding multiple meshes
    for (auto component : components) {
        FVector Size;
        UBoxComponent *Box = Cast<UBoxComponent>(component);
        if (Box) {
            Size = Box->GetUnscaledBoxExtent();
        }
        USphereComponent *Sphere = Cast<USphereComponent>(component);
        if (Sphere) {
            auto Radius = Sphere->GetUnscaledSphereRadius();
            Size = FVector(Radius, Radius, Radius);
        }
        UCapsuleComponent *Capsule = Cast<UCapsuleComponent>(component);
        if (Capsule) {
            auto Radius = Capsule->GetUnscaledCapsuleRadius();
            auto HalfHeight = Capsule->GetUnscaledCapsuleHalfHeight();
            Size = FVector(Radius, Radius, HalfHeight + Radius);
        }

        if (Size.SizeSquared() > 0.1) {
            for (auto corner : BOX_CORNERS) {
                auto Point = component->GetComponentTransform().TransformPosition(corner * (Size * 2) - Size);
                auto point = mesh->add_vertices();
                point->set_x(Point.Y / 100);
                point->set_y(Point.Z / 100);
                point->set_z(Point.X / 100);
            }
            for (auto index : BOX_INDICES) {
                mesh->add_indices(offset + index);
            }
            offset += 8;
        }
    }
    return mesh;
}

inhumate::rti::proto::GeometryOperation_Line2D *URTIGeometryComponent::CreateLine2DFromSpline(const TArray<USplineComponent *> &components)
{
    auto line = new inhumate::rti::proto::GeometryOperation_Line2D();
    for (auto component : components) {
        for (int32 i = 0; i < component->GetNumberOfSplinePoints(); i++) {
            auto location = component->GetLocationAtSplinePoint(i, ESplineCoordinateSpace::World);
            auto point = line->add_points();
            SetPoint2D(location, point);
        }
    }
    return line;
}

inhumate::rti::proto::GeometryOperation_Line3D *URTIGeometryComponent::CreateLine3DFromSpline(const TArray<USplineComponent *> &components)
{
    auto line = new inhumate::rti::proto::GeometryOperation_Line3D();
    for (auto component : components) {
        for (int32 i = 0; i < component->GetNumberOfSplinePoints(); i++) {
            auto location = component->GetLocationAtSplinePoint(i, ESplineCoordinateSpace::World);
            auto point = line->add_points();
            SetPoint3D(location, point);
        }
    }
    return line;
}

inhumate::rti::proto::GeometryOperation_Spline2D *URTIGeometryComponent::CreateSpline2D(const TArray<USplineComponent *> &components)
{
    auto spline = new inhumate::rti::proto::GeometryOperation_Spline2D();
    for (auto component : components) {
        for (int32 i = 0; i < component->GetNumberOfSplinePoints(); i++) {
            FVector Location, Tangent;
            component->GetLocationAndTangentAtSplinePoint(i, Location, Tangent, ESplineCoordinateSpace::World);
            auto point = spline->add_points();
            SetPoint2D(Location, point);
            auto controlpoint = spline->add_control_points();
            // Recalculate tangent to control point involves a scale by 3.
            // See https://answers.unrealengine.com/questions/330317/which-algorithm-is-used-for-spline-components-in-u.html
            SetPoint2D(Location + Tangent / 3.0f, controlpoint);
        }
    }
    return spline;
}

inhumate::rti::proto::GeometryOperation_Spline3D *URTIGeometryComponent::CreateSpline3D(const TArray<USplineComponent *> &components)
{
    auto spline = new inhumate::rti::proto::GeometryOperation_Spline3D();
    for (auto component : components) {
        for (int32 i = 0; i < component->GetNumberOfSplinePoints(); i++) {
            FVector Location, Tangent;
            component->GetLocationAndTangentAtSplinePoint(i, Location, Tangent, ESplineCoordinateSpace::World);
            auto point = spline->add_points();
            SetPoint3D(Location, point);
            auto controlpoint = spline->add_control_points();
            SetPoint3D(Location + Tangent / 3.0f, controlpoint);
        }
    }
    return spline;
}


// Conversion methods similar to those in RTIPositionComponent

void URTIGeometryComponent::SetPoint2D(const FVector &location, inhumate::rti::proto::GeometryOperation_Point2D *point)
{
    point->set_allocated_local(UEToRTILocalPoint2D(location));

    AActor *LevelBP = (AActor *)GetOwner()->GetWorld()->GetLevelScriptActor();
    if (LevelBP && LevelBP->Implements<URTIGeodeticCoordinateConversionInterface>()) {
        IRTIGeodeticCoordinateConversionInterface *Conversion = Cast<IRTIGeodeticCoordinateConversionInterface>(LevelBP);
        auto GeoLocation = Conversion->Execute_LocalToGeodetic(LevelBP, location);
        auto geo = new inhumate::rti::proto::GeometryOperation_GeodeticPoint2D();
        geo->set_longitude(GeoLocation.Longitude);
        geo->set_latitude(GeoLocation.Latitude);
        point->set_allocated_geodetic(geo);
    }
}

void URTIGeometryComponent::SetPoint3D(const FVector &location, inhumate::rti::proto::GeometryOperation_Point3D *point)
{
    point->set_allocated_local(UEToRTILocalPoint3D(location));

    AActor *LevelBP = (AActor *)GetOwner()->GetWorld()->GetLevelScriptActor();
    if (LevelBP && LevelBP->Implements<URTIGeodeticCoordinateConversionInterface>()) {
        IRTIGeodeticCoordinateConversionInterface *Conversion = Cast<IRTIGeodeticCoordinateConversionInterface>(LevelBP);
        auto GeoLocation = Conversion->Execute_LocalToGeodetic(LevelBP, location);
        auto geo = new inhumate::rti::proto::GeometryOperation_GeodeticPoint3D();
        geo->set_longitude(GeoLocation.Longitude);
        geo->set_latitude(GeoLocation.Latitude);
        geo->set_altitude(GeoLocation.Altitude);
        point->set_allocated_geodetic(geo);
    }
}

inhumate::rti::proto::GeometryOperation_LocalPoint2D *URTIGeometryComponent::UEToRTILocalPoint2D(const FVector &location)
{
    auto local = new inhumate::rti::proto::GeometryOperation_LocalPoint2D();
    local->set_x(location.Y / 100);
    local->set_y(location.X / 100);
    return local;
}

inhumate::rti::proto::GeometryOperation_LocalPoint3D *URTIGeometryComponent::UEToRTILocalPoint3D(const FVector &location)
{
    auto local = new inhumate::rti::proto::GeometryOperation_LocalPoint3D();
    local->set_x(location.Y / 100);
    local->set_y(location.Z / 100);
    local->set_z(location.X / 100);
    return local;
}

inhumate::rti::proto::Color *URTIGeometryComponent::UEToRTIColor(const FColor &Color)
{
    if (Color.R > 0 || Color.G > 0 || Color.B > 0 || Color.A > 0) {
        auto color = new inhumate::rti::proto::Color();
        color->set_red(Color.R);
        color->set_green(Color.G);
        color->set_blue(Color.B);
        return color;
    }
    return nullptr;
}