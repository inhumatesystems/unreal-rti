// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: Parameter.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_Parameter_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_Parameter_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3011000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3011002 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/inlined_string_field.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_Parameter_2eproto INHUMATE_RTI_PROTOS_EXPORT
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct INHUMATE_RTI_PROTOS_EXPORT TableStruct_Parameter_2eproto {
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::AuxillaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTable schema[1]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::FieldMetadata field_metadata[];
  static const ::PROTOBUF_NAMESPACE_ID::internal::SerializationTable serialization_table[];
  static const ::PROTOBUF_NAMESPACE_ID::uint32 offsets[];
};
extern INHUMATE_RTI_PROTOS_EXPORT const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_Parameter_2eproto;
namespace inhumate {
namespace rti {
namespace proto {
class Parameter;
class ParameterDefaultTypeInternal;
INHUMATE_RTI_PROTOS_EXPORT extern ParameterDefaultTypeInternal _Parameter_default_instance_;
}  // namespace proto
}  // namespace rti
}  // namespace inhumate
PROTOBUF_NAMESPACE_OPEN
template<> INHUMATE_RTI_PROTOS_EXPORT ::inhumate::rti::proto::Parameter* Arena::CreateMaybeMessage<::inhumate::rti::proto::Parameter>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace inhumate {
namespace rti {
namespace proto {

// ===================================================================

class INHUMATE_RTI_PROTOS_EXPORT Parameter :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:inhumate.rti.proto.Parameter) */ {
 public:
  Parameter();
  virtual ~Parameter();

  Parameter(const Parameter& from);
  Parameter(Parameter&& from) noexcept
    : Parameter() {
    *this = ::std::move(from);
  }

  inline Parameter& operator=(const Parameter& from) {
    CopyFrom(from);
    return *this;
  }
  inline Parameter& operator=(Parameter&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return GetMetadataStatic().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return GetMetadataStatic().reflection;
  }
  static const Parameter& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const Parameter* internal_default_instance() {
    return reinterpret_cast<const Parameter*>(
               &_Parameter_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(Parameter& a, Parameter& b) {
    a.Swap(&b);
  }
  inline void Swap(Parameter* other) {
    if (other == this) return;
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline Parameter* New() const final {
    return CreateMaybeMessage<Parameter>(nullptr);
  }

  Parameter* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<Parameter>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const Parameter& from);
  void MergeFrom(const Parameter& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::PROTOBUF_NAMESPACE_ID::uint8* _InternalSerialize(
      ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(Parameter* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "inhumate.rti.proto.Parameter";
  }
  private:
  inline ::PROTOBUF_NAMESPACE_ID::Arena* GetArenaNoVirtual() const {
    return nullptr;
  }
  inline void* MaybeArenaPtr() const {
    return nullptr;
  }
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;
  private:
  static ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadataStatic() {
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_Parameter_2eproto);
    return ::descriptor_table_Parameter_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kNameFieldNumber = 1,
    kLabelFieldNumber = 2,
    kDescriptionFieldNumber = 3,
    kDefaultValueFieldNumber = 4,
    kTypeFieldNumber = 5,
    kRequiredFieldNumber = 6,
  };
  // string name = 1;
  void clear_name();
  const std::string& name() const;
  void set_name(const std::string& value);
  void set_name(std::string&& value);
  void set_name(const char* value);
  void set_name(const char* value, size_t size);
  std::string* mutable_name();
  std::string* release_name();
  void set_allocated_name(std::string* name);
  private:
  const std::string& _internal_name() const;
  void _internal_set_name(const std::string& value);
  std::string* _internal_mutable_name();
  public:

  // string label = 2;
  void clear_label();
  const std::string& label() const;
  void set_label(const std::string& value);
  void set_label(std::string&& value);
  void set_label(const char* value);
  void set_label(const char* value, size_t size);
  std::string* mutable_label();
  std::string* release_label();
  void set_allocated_label(std::string* label);
  private:
  const std::string& _internal_label() const;
  void _internal_set_label(const std::string& value);
  std::string* _internal_mutable_label();
  public:

  // string description = 3;
  void clear_description();
  const std::string& description() const;
  void set_description(const std::string& value);
  void set_description(std::string&& value);
  void set_description(const char* value);
  void set_description(const char* value, size_t size);
  std::string* mutable_description();
  std::string* release_description();
  void set_allocated_description(std::string* description);
  private:
  const std::string& _internal_description() const;
  void _internal_set_description(const std::string& value);
  std::string* _internal_mutable_description();
  public:

  // string default_value = 4;
  void clear_default_value();
  const std::string& default_value() const;
  void set_default_value(const std::string& value);
  void set_default_value(std::string&& value);
  void set_default_value(const char* value);
  void set_default_value(const char* value, size_t size);
  std::string* mutable_default_value();
  std::string* release_default_value();
  void set_allocated_default_value(std::string* default_value);
  private:
  const std::string& _internal_default_value() const;
  void _internal_set_default_value(const std::string& value);
  std::string* _internal_mutable_default_value();
  public:

  // string type = 5;
  void clear_type();
  const std::string& type() const;
  void set_type(const std::string& value);
  void set_type(std::string&& value);
  void set_type(const char* value);
  void set_type(const char* value, size_t size);
  std::string* mutable_type();
  std::string* release_type();
  void set_allocated_type(std::string* type);
  private:
  const std::string& _internal_type() const;
  void _internal_set_type(const std::string& value);
  std::string* _internal_mutable_type();
  public:

  // bool required = 6;
  void clear_required();
  bool required() const;
  void set_required(bool value);
  private:
  bool _internal_required() const;
  void _internal_set_required(bool value);
  public:

  // @@protoc_insertion_point(class_scope:inhumate.rti.proto.Parameter)
 private:
  class _Internal;

  ::PROTOBUF_NAMESPACE_ID::internal::InternalMetadataWithArena _internal_metadata_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr name_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr label_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr description_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr default_value_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr type_;
  bool required_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_Parameter_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// Parameter

// string name = 1;
inline void Parameter::clear_name() {
  name_.ClearToEmptyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline const std::string& Parameter::name() const {
  // @@protoc_insertion_point(field_get:inhumate.rti.proto.Parameter.name)
  return _internal_name();
}
inline void Parameter::set_name(const std::string& value) {
  _internal_set_name(value);
  // @@protoc_insertion_point(field_set:inhumate.rti.proto.Parameter.name)
}
inline std::string* Parameter::mutable_name() {
  // @@protoc_insertion_point(field_mutable:inhumate.rti.proto.Parameter.name)
  return _internal_mutable_name();
}
inline const std::string& Parameter::_internal_name() const {
  return name_.GetNoArena();
}
inline void Parameter::_internal_set_name(const std::string& value) {
  
  name_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), value);
}
inline void Parameter::set_name(std::string&& value) {
  
  name_.SetNoArena(
    &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:inhumate.rti.proto.Parameter.name)
}
inline void Parameter::set_name(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  
  name_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:inhumate.rti.proto.Parameter.name)
}
inline void Parameter::set_name(const char* value, size_t size) {
  
  name_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:inhumate.rti.proto.Parameter.name)
}
inline std::string* Parameter::_internal_mutable_name() {
  
  return name_.MutableNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline std::string* Parameter::release_name() {
  // @@protoc_insertion_point(field_release:inhumate.rti.proto.Parameter.name)
  
  return name_.ReleaseNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline void Parameter::set_allocated_name(std::string* name) {
  if (name != nullptr) {
    
  } else {
    
  }
  name_.SetAllocatedNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), name);
  // @@protoc_insertion_point(field_set_allocated:inhumate.rti.proto.Parameter.name)
}

// string label = 2;
inline void Parameter::clear_label() {
  label_.ClearToEmptyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline const std::string& Parameter::label() const {
  // @@protoc_insertion_point(field_get:inhumate.rti.proto.Parameter.label)
  return _internal_label();
}
inline void Parameter::set_label(const std::string& value) {
  _internal_set_label(value);
  // @@protoc_insertion_point(field_set:inhumate.rti.proto.Parameter.label)
}
inline std::string* Parameter::mutable_label() {
  // @@protoc_insertion_point(field_mutable:inhumate.rti.proto.Parameter.label)
  return _internal_mutable_label();
}
inline const std::string& Parameter::_internal_label() const {
  return label_.GetNoArena();
}
inline void Parameter::_internal_set_label(const std::string& value) {
  
  label_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), value);
}
inline void Parameter::set_label(std::string&& value) {
  
  label_.SetNoArena(
    &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:inhumate.rti.proto.Parameter.label)
}
inline void Parameter::set_label(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  
  label_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:inhumate.rti.proto.Parameter.label)
}
inline void Parameter::set_label(const char* value, size_t size) {
  
  label_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:inhumate.rti.proto.Parameter.label)
}
inline std::string* Parameter::_internal_mutable_label() {
  
  return label_.MutableNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline std::string* Parameter::release_label() {
  // @@protoc_insertion_point(field_release:inhumate.rti.proto.Parameter.label)
  
  return label_.ReleaseNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline void Parameter::set_allocated_label(std::string* label) {
  if (label != nullptr) {
    
  } else {
    
  }
  label_.SetAllocatedNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), label);
  // @@protoc_insertion_point(field_set_allocated:inhumate.rti.proto.Parameter.label)
}

// string description = 3;
inline void Parameter::clear_description() {
  description_.ClearToEmptyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline const std::string& Parameter::description() const {
  // @@protoc_insertion_point(field_get:inhumate.rti.proto.Parameter.description)
  return _internal_description();
}
inline void Parameter::set_description(const std::string& value) {
  _internal_set_description(value);
  // @@protoc_insertion_point(field_set:inhumate.rti.proto.Parameter.description)
}
inline std::string* Parameter::mutable_description() {
  // @@protoc_insertion_point(field_mutable:inhumate.rti.proto.Parameter.description)
  return _internal_mutable_description();
}
inline const std::string& Parameter::_internal_description() const {
  return description_.GetNoArena();
}
inline void Parameter::_internal_set_description(const std::string& value) {
  
  description_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), value);
}
inline void Parameter::set_description(std::string&& value) {
  
  description_.SetNoArena(
    &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:inhumate.rti.proto.Parameter.description)
}
inline void Parameter::set_description(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  
  description_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:inhumate.rti.proto.Parameter.description)
}
inline void Parameter::set_description(const char* value, size_t size) {
  
  description_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:inhumate.rti.proto.Parameter.description)
}
inline std::string* Parameter::_internal_mutable_description() {
  
  return description_.MutableNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline std::string* Parameter::release_description() {
  // @@protoc_insertion_point(field_release:inhumate.rti.proto.Parameter.description)
  
  return description_.ReleaseNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline void Parameter::set_allocated_description(std::string* description) {
  if (description != nullptr) {
    
  } else {
    
  }
  description_.SetAllocatedNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), description);
  // @@protoc_insertion_point(field_set_allocated:inhumate.rti.proto.Parameter.description)
}

// string default_value = 4;
inline void Parameter::clear_default_value() {
  default_value_.ClearToEmptyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline const std::string& Parameter::default_value() const {
  // @@protoc_insertion_point(field_get:inhumate.rti.proto.Parameter.default_value)
  return _internal_default_value();
}
inline void Parameter::set_default_value(const std::string& value) {
  _internal_set_default_value(value);
  // @@protoc_insertion_point(field_set:inhumate.rti.proto.Parameter.default_value)
}
inline std::string* Parameter::mutable_default_value() {
  // @@protoc_insertion_point(field_mutable:inhumate.rti.proto.Parameter.default_value)
  return _internal_mutable_default_value();
}
inline const std::string& Parameter::_internal_default_value() const {
  return default_value_.GetNoArena();
}
inline void Parameter::_internal_set_default_value(const std::string& value) {
  
  default_value_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), value);
}
inline void Parameter::set_default_value(std::string&& value) {
  
  default_value_.SetNoArena(
    &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:inhumate.rti.proto.Parameter.default_value)
}
inline void Parameter::set_default_value(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  
  default_value_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:inhumate.rti.proto.Parameter.default_value)
}
inline void Parameter::set_default_value(const char* value, size_t size) {
  
  default_value_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:inhumate.rti.proto.Parameter.default_value)
}
inline std::string* Parameter::_internal_mutable_default_value() {
  
  return default_value_.MutableNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline std::string* Parameter::release_default_value() {
  // @@protoc_insertion_point(field_release:inhumate.rti.proto.Parameter.default_value)
  
  return default_value_.ReleaseNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline void Parameter::set_allocated_default_value(std::string* default_value) {
  if (default_value != nullptr) {
    
  } else {
    
  }
  default_value_.SetAllocatedNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), default_value);
  // @@protoc_insertion_point(field_set_allocated:inhumate.rti.proto.Parameter.default_value)
}

// string type = 5;
inline void Parameter::clear_type() {
  type_.ClearToEmptyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline const std::string& Parameter::type() const {
  // @@protoc_insertion_point(field_get:inhumate.rti.proto.Parameter.type)
  return _internal_type();
}
inline void Parameter::set_type(const std::string& value) {
  _internal_set_type(value);
  // @@protoc_insertion_point(field_set:inhumate.rti.proto.Parameter.type)
}
inline std::string* Parameter::mutable_type() {
  // @@protoc_insertion_point(field_mutable:inhumate.rti.proto.Parameter.type)
  return _internal_mutable_type();
}
inline const std::string& Parameter::_internal_type() const {
  return type_.GetNoArena();
}
inline void Parameter::_internal_set_type(const std::string& value) {
  
  type_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), value);
}
inline void Parameter::set_type(std::string&& value) {
  
  type_.SetNoArena(
    &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:inhumate.rti.proto.Parameter.type)
}
inline void Parameter::set_type(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  
  type_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:inhumate.rti.proto.Parameter.type)
}
inline void Parameter::set_type(const char* value, size_t size) {
  
  type_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:inhumate.rti.proto.Parameter.type)
}
inline std::string* Parameter::_internal_mutable_type() {
  
  return type_.MutableNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline std::string* Parameter::release_type() {
  // @@protoc_insertion_point(field_release:inhumate.rti.proto.Parameter.type)
  
  return type_.ReleaseNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline void Parameter::set_allocated_type(std::string* type) {
  if (type != nullptr) {
    
  } else {
    
  }
  type_.SetAllocatedNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), type);
  // @@protoc_insertion_point(field_set_allocated:inhumate.rti.proto.Parameter.type)
}

// bool required = 6;
inline void Parameter::clear_required() {
  required_ = false;
}
inline bool Parameter::_internal_required() const {
  return required_;
}
inline bool Parameter::required() const {
  // @@protoc_insertion_point(field_get:inhumate.rti.proto.Parameter.required)
  return _internal_required();
}
inline void Parameter::_internal_set_required(bool value) {
  
  required_ = value;
}
inline void Parameter::set_required(bool value) {
  _internal_set_required(value);
  // @@protoc_insertion_point(field_set:inhumate.rti.proto.Parameter.required)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace proto
}  // namespace rti
}  // namespace inhumate

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_Parameter_2eproto
