// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: rpc_header.proto

#include "rpc_header.pb.h"

#include <algorithm>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
namespace rpc {
class RpcHeaderDefaultTypeInternal {
 public:
  ::PROTOBUF_NAMESPACE_ID::internal::ExplicitlyConstructed<RpcHeader> _instance;
} _RpcHeader_default_instance_;
}  // namespace rpc
static void InitDefaultsscc_info_RpcHeader_rpc_5fheader_2eproto() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::rpc::_RpcHeader_default_instance_;
    new (ptr) ::rpc::RpcHeader();
    ::PROTOBUF_NAMESPACE_ID::internal::OnShutdownDestroyMessage(ptr);
  }
  ::rpc::RpcHeader::InitAsDefaultInstance();
}

::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<0> scc_info_RpcHeader_rpc_5fheader_2eproto =
    {{ATOMIC_VAR_INIT(::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase::kUninitialized), 0, 0, InitDefaultsscc_info_RpcHeader_rpc_5fheader_2eproto}, {}};

static ::PROTOBUF_NAMESPACE_ID::Metadata file_level_metadata_rpc_5fheader_2eproto[1];
static constexpr ::PROTOBUF_NAMESPACE_ID::EnumDescriptor const** file_level_enum_descriptors_rpc_5fheader_2eproto = nullptr;
static constexpr ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor const** file_level_service_descriptors_rpc_5fheader_2eproto = nullptr;

const ::PROTOBUF_NAMESPACE_ID::uint32 TableStruct_rpc_5fheader_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::rpc::RpcHeader, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::rpc::RpcHeader, service_name_),
  PROTOBUF_FIELD_OFFSET(::rpc::RpcHeader, method_name_),
  PROTOBUF_FIELD_OFFSET(::rpc::RpcHeader, args_size_),
};
static const ::PROTOBUF_NAMESPACE_ID::internal::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, sizeof(::rpc::RpcHeader)},
};

static ::PROTOBUF_NAMESPACE_ID::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::rpc::_RpcHeader_default_instance_),
};

const char descriptor_table_protodef_rpc_5fheader_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\020rpc_header.proto\022\003rpc\"I\n\tRpcHeader\022\024\n\014"
  "service_name\030\001 \001(\014\022\023\n\013method_name\030\002 \001(\014\022"
  "\021\n\targs_size\030\003 \001(\rb\006proto3"
  ;
static const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable*const descriptor_table_rpc_5fheader_2eproto_deps[1] = {
};
static ::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase*const descriptor_table_rpc_5fheader_2eproto_sccs[1] = {
  &scc_info_RpcHeader_rpc_5fheader_2eproto.base,
};
static ::PROTOBUF_NAMESPACE_ID::internal::once_flag descriptor_table_rpc_5fheader_2eproto_once;
static bool descriptor_table_rpc_5fheader_2eproto_initialized = false;
const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_rpc_5fheader_2eproto = {
  &descriptor_table_rpc_5fheader_2eproto_initialized, descriptor_table_protodef_rpc_5fheader_2eproto, "rpc_header.proto", 106,
  &descriptor_table_rpc_5fheader_2eproto_once, descriptor_table_rpc_5fheader_2eproto_sccs, descriptor_table_rpc_5fheader_2eproto_deps, 1, 0,
  schemas, file_default_instances, TableStruct_rpc_5fheader_2eproto::offsets,
  file_level_metadata_rpc_5fheader_2eproto, 1, file_level_enum_descriptors_rpc_5fheader_2eproto, file_level_service_descriptors_rpc_5fheader_2eproto,
};

// Force running AddDescriptors() at dynamic initialization time.
static bool dynamic_init_dummy_rpc_5fheader_2eproto = (  ::PROTOBUF_NAMESPACE_ID::internal::AddDescriptors(&descriptor_table_rpc_5fheader_2eproto), true);
namespace rpc {

// ===================================================================

void RpcHeader::InitAsDefaultInstance() {
}
class RpcHeader::_Internal {
 public:
};

RpcHeader::RpcHeader()
  : ::PROTOBUF_NAMESPACE_ID::Message(), _internal_metadata_(nullptr) {
  SharedCtor();
  // @@protoc_insertion_point(constructor:rpc.RpcHeader)
}
RpcHeader::RpcHeader(const RpcHeader& from)
  : ::PROTOBUF_NAMESPACE_ID::Message(),
      _internal_metadata_(nullptr) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  service_name_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  if (!from._internal_service_name().empty()) {
    service_name_.AssignWithDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), from.service_name_);
  }
  method_name_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  if (!from._internal_method_name().empty()) {
    method_name_.AssignWithDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), from.method_name_);
  }
  args_size_ = from.args_size_;
  // @@protoc_insertion_point(copy_constructor:rpc.RpcHeader)
}

void RpcHeader::SharedCtor() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&scc_info_RpcHeader_rpc_5fheader_2eproto.base);
  service_name_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  method_name_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  args_size_ = 0u;
}

RpcHeader::~RpcHeader() {
  // @@protoc_insertion_point(destructor:rpc.RpcHeader)
  SharedDtor();
}

void RpcHeader::SharedDtor() {
  service_name_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  method_name_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}

void RpcHeader::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const RpcHeader& RpcHeader::default_instance() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&::scc_info_RpcHeader_rpc_5fheader_2eproto.base);
  return *internal_default_instance();
}


void RpcHeader::Clear() {
// @@protoc_insertion_point(message_clear_start:rpc.RpcHeader)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  service_name_.ClearToEmptyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  method_name_.ClearToEmptyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  args_size_ = 0u;
  _internal_metadata_.Clear();
}

const char* RpcHeader::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    CHK_(ptr);
    switch (tag >> 3) {
      // bytes service_name = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 10)) {
          auto str = _internal_mutable_service_name();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // bytes method_name = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 18)) {
          auto str = _internal_mutable_method_name();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // uint32 args_size = 3;
      case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 24)) {
          args_size_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      default: {
      handle_unusual:
        if ((tag & 7) == 4 || tag == 0) {
          ctx->SetLastTag(tag);
          goto success;
        }
        ptr = UnknownFieldParse(tag, &_internal_metadata_, ptr, ctx);
        CHK_(ptr != nullptr);
        continue;
      }
    }  // switch
  }  // while
success:
  return ptr;
failure:
  ptr = nullptr;
  goto success;
#undef CHK_
}

::PROTOBUF_NAMESPACE_ID::uint8* RpcHeader::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:rpc.RpcHeader)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // bytes service_name = 1;
  if (this->service_name().size() > 0) {
    target = stream->WriteBytesMaybeAliased(
        1, this->_internal_service_name(), target);
  }

  // bytes method_name = 2;
  if (this->method_name().size() > 0) {
    target = stream->WriteBytesMaybeAliased(
        2, this->_internal_method_name(), target);
  }

  // uint32 args_size = 3;
  if (this->args_size() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteUInt32ToArray(3, this->_internal_args_size(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields(), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:rpc.RpcHeader)
  return target;
}

size_t RpcHeader::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:rpc.RpcHeader)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // bytes service_name = 1;
  if (this->service_name().size() > 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::BytesSize(
        this->_internal_service_name());
  }

  // bytes method_name = 2;
  if (this->method_name().size() > 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::BytesSize(
        this->_internal_method_name());
  }

  // uint32 args_size = 3;
  if (this->args_size() != 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::UInt32Size(
        this->_internal_args_size());
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
        _internal_metadata_, total_size, &_cached_size_);
  }
  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void RpcHeader::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:rpc.RpcHeader)
  GOOGLE_DCHECK_NE(&from, this);
  const RpcHeader* source =
      ::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<RpcHeader>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:rpc.RpcHeader)
    ::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:rpc.RpcHeader)
    MergeFrom(*source);
  }
}

void RpcHeader::MergeFrom(const RpcHeader& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:rpc.RpcHeader)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (from.service_name().size() > 0) {

    service_name_.AssignWithDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), from.service_name_);
  }
  if (from.method_name().size() > 0) {

    method_name_.AssignWithDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), from.method_name_);
  }
  if (from.args_size() != 0) {
    _internal_set_args_size(from._internal_args_size());
  }
}

void RpcHeader::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:rpc.RpcHeader)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void RpcHeader::CopyFrom(const RpcHeader& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:rpc.RpcHeader)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool RpcHeader::IsInitialized() const {
  return true;
}

void RpcHeader::InternalSwap(RpcHeader* other) {
  using std::swap;
  _internal_metadata_.Swap(&other->_internal_metadata_);
  service_name_.Swap(&other->service_name_, &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
    GetArenaNoVirtual());
  method_name_.Swap(&other->method_name_, &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
    GetArenaNoVirtual());
  swap(args_size_, other->args_size_);
}

::PROTOBUF_NAMESPACE_ID::Metadata RpcHeader::GetMetadata() const {
  return GetMetadataStatic();
}


// @@protoc_insertion_point(namespace_scope)
}  // namespace rpc
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::rpc::RpcHeader* Arena::CreateMaybeMessage< ::rpc::RpcHeader >(Arena* arena) {
  return Arena::CreateInternal< ::rpc::RpcHeader >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
