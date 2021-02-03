// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: NetPackDefine.proto
#define PROTOBUF_USE_DLLS
#ifndef PROTOBUF_NetPackDefine_2eproto__INCLUDED
#define PROTOBUF_NetPackDefine_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3005000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3005001 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)

namespace protobuf_NetPackDefine_2eproto {
// Internal implementation detail -- do not use these members.
struct TableStruct {
  static const ::google::protobuf::internal::ParseTableField entries[];
  static const ::google::protobuf::internal::AuxillaryParseTableField aux[];
  static const ::google::protobuf::internal::ParseTable schema[1];
  static const ::google::protobuf::internal::FieldMetadata field_metadata[];
  static const ::google::protobuf::internal::SerializationTable serialization_table[];
  static const ::google::protobuf::uint32 offsets[];
};
void AddDescriptors();
void InitDefaultsPhoneImpl();
void InitDefaultsPhone();
inline void InitDefaults() {
  InitDefaultsPhone();
}
}  // namespace protobuf_NetPackDefine_2eproto
class Phone;
class PhoneDefaultTypeInternal;
extern PhoneDefaultTypeInternal _Phone_default_instance_;

// ===================================================================

class Phone : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:Phone) */ {
 public:
  Phone();
  virtual ~Phone();

  Phone(const Phone& from);

  inline Phone& operator=(const Phone& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  Phone(Phone&& from) noexcept
    : Phone() {
    *this = ::std::move(from);
  }

  inline Phone& operator=(Phone&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const Phone& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const Phone* internal_default_instance() {
    return reinterpret_cast<const Phone*>(
               &_Phone_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    0;

  void Swap(Phone* other);
  friend void swap(Phone& a, Phone& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline Phone* New() const PROTOBUF_FINAL { return New(NULL); }

  Phone* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const Phone& from);
  void MergeFrom(const Phone& from);
  void Clear() PROTOBUF_FINAL;
  bool IsInitialized() const PROTOBUF_FINAL;

  size_t ByteSizeLong() const PROTOBUF_FINAL;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) PROTOBUF_FINAL;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const PROTOBUF_FINAL;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const PROTOBUF_FINAL;
  int GetCachedSize() const PROTOBUF_FINAL { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const PROTOBUF_FINAL;
  void InternalSwap(Phone* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const PROTOBUF_FINAL;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // string name = 1;
  void clear_name();
  static const int kNameFieldNumber = 1;
  const ::std::string& name() const;
  void set_name(const ::std::string& value);
  #if LANG_CXX11
  void set_name(::std::string&& value);
  #endif
  void set_name(const char* value);
  void set_name(const char* value, size_t size);
  ::std::string* mutable_name();
  ::std::string* release_name();
  void set_allocated_name(::std::string* name);

  // int64 phonenumber = 2;
  void clear_phonenumber();
  static const int kPhonenumberFieldNumber = 2;
  ::google::protobuf::int64 phonenumber() const;
  void set_phonenumber(::google::protobuf::int64 value);

  // @@protoc_insertion_point(class_scope:Phone)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::ArenaStringPtr name_;
  ::google::protobuf::int64 phonenumber_;
  mutable int _cached_size_;
  friend struct ::protobuf_NetPackDefine_2eproto::TableStruct;
  friend void ::protobuf_NetPackDefine_2eproto::InitDefaultsPhoneImpl();
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// Phone

// string name = 1;
inline void Phone::clear_name() {
  name_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& Phone::name() const {
  // @@protoc_insertion_point(field_get:Phone.name)
  return name_.GetNoArena();
}
inline void Phone::set_name(const ::std::string& value) {
  
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:Phone.name)
}
#if LANG_CXX11
inline void Phone::set_name(::std::string&& value) {
  
  name_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:Phone.name)
}
#endif
inline void Phone::set_name(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:Phone.name)
}
inline void Phone::set_name(const char* value, size_t size) {
  
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:Phone.name)
}
inline ::std::string* Phone::mutable_name() {
  
  // @@protoc_insertion_point(field_mutable:Phone.name)
  return name_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* Phone::release_name() {
  // @@protoc_insertion_point(field_release:Phone.name)
  
  return name_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void Phone::set_allocated_name(::std::string* name) {
  if (name != NULL) {
    
  } else {
    
  }
  name_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), name);
  // @@protoc_insertion_point(field_set_allocated:Phone.name)
}

// int64 phonenumber = 2;
inline void Phone::clear_phonenumber() {
  phonenumber_ = GOOGLE_LONGLONG(0);
}
inline ::google::protobuf::int64 Phone::phonenumber() const {
  // @@protoc_insertion_point(field_get:Phone.phonenumber)
  return phonenumber_;
}
inline void Phone::set_phonenumber(::google::protobuf::int64 value) {
  
  phonenumber_ = value;
  // @@protoc_insertion_point(field_set:Phone.phonenumber)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)


// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_NetPackDefine_2eproto__INCLUDED
