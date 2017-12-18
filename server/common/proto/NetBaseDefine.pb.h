// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: NetBaseDefine.proto

#ifndef PROTOBUF_NetBaseDefine_2eproto__INCLUDED
#define PROTOBUF_NetBaseDefine_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3002000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3002000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
class C2LS_Login;
class C2LS_LoginDefaultTypeInternal;
extern C2LS_LoginDefaultTypeInternal _C2LS_Login_default_instance_;

namespace protobuf_NetBaseDefine_2eproto {
// Internal implementation detail -- do not call these.
struct TableStruct {
  static const ::google::protobuf::uint32 offsets[];
  static void InitDefaultsImpl();
  static void Shutdown();
};
void AddDescriptors();
void InitDefaults();
}  // namespace protobuf_NetBaseDefine_2eproto

// ===================================================================

class C2LS_Login : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:C2LS_Login) */ {
 public:
  C2LS_Login();
  virtual ~C2LS_Login();

  C2LS_Login(const C2LS_Login& from);

  inline C2LS_Login& operator=(const C2LS_Login& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields();
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields();
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const C2LS_Login& default_instance();

  static inline const C2LS_Login* internal_default_instance() {
    return reinterpret_cast<const C2LS_Login*>(
               &_C2LS_Login_default_instance_);
  }

  void Swap(C2LS_Login* other);

  // implements Message ----------------------------------------------

  inline C2LS_Login* New() const PROTOBUF_FINAL { return New(NULL); }

  C2LS_Login* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const C2LS_Login& from);
  void MergeFrom(const C2LS_Login& from);
  void Clear() PROTOBUF_FINAL;
  bool IsInitialized() const PROTOBUF_FINAL;

  size_t ByteSizeLong() const PROTOBUF_FINAL;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) PROTOBUF_FINAL;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const PROTOBUF_FINAL;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const PROTOBUF_FINAL;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output)
      const PROTOBUF_FINAL {
    return InternalSerializeWithCachedSizesToArray(
        ::google::protobuf::io::CodedOutputStream::IsDefaultSerializationDeterministic(), output);
  }
  int GetCachedSize() const PROTOBUF_FINAL { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const PROTOBUF_FINAL;
  void InternalSwap(C2LS_Login* other);
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

  // required string user_name = 1;
  bool has_user_name() const;
  void clear_user_name();
  static const int kUserNameFieldNumber = 1;
  const ::std::string& user_name() const;
  void set_user_name(const ::std::string& value);
  #if LANG_CXX11
  void set_user_name(::std::string&& value);
  #endif
  void set_user_name(const char* value);
  void set_user_name(const char* value, size_t size);
  ::std::string* mutable_user_name();
  ::std::string* release_user_name();
  void set_allocated_user_name(::std::string* user_name);

  // required string passwd = 2;
  bool has_passwd() const;
  void clear_passwd();
  static const int kPasswdFieldNumber = 2;
  const ::std::string& passwd() const;
  void set_passwd(const ::std::string& value);
  #if LANG_CXX11
  void set_passwd(::std::string&& value);
  #endif
  void set_passwd(const char* value);
  void set_passwd(const char* value, size_t size);
  ::std::string* mutable_passwd();
  ::std::string* release_passwd();
  void set_allocated_passwd(::std::string* passwd);

  // @@protoc_insertion_point(class_scope:C2LS_Login)
 private:
  void set_has_user_name();
  void clear_has_user_name();
  void set_has_passwd();
  void clear_has_passwd();

  // helper for ByteSizeLong()
  size_t RequiredFieldsByteSizeFallback() const;

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::HasBits<1> _has_bits_;
  mutable int _cached_size_;
  ::google::protobuf::internal::ArenaStringPtr user_name_;
  ::google::protobuf::internal::ArenaStringPtr passwd_;
  friend struct  protobuf_NetBaseDefine_2eproto::TableStruct;
};
// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
// C2LS_Login

// required string user_name = 1;
inline bool C2LS_Login::has_user_name() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void C2LS_Login::set_has_user_name() {
  _has_bits_[0] |= 0x00000001u;
}
inline void C2LS_Login::clear_has_user_name() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void C2LS_Login::clear_user_name() {
  user_name_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  clear_has_user_name();
}
inline const ::std::string& C2LS_Login::user_name() const {
  // @@protoc_insertion_point(field_get:C2LS_Login.user_name)
  return user_name_.GetNoArena();
}
inline void C2LS_Login::set_user_name(const ::std::string& value) {
  set_has_user_name();
  user_name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:C2LS_Login.user_name)
}
#if LANG_CXX11
inline void C2LS_Login::set_user_name(::std::string&& value) {
  set_has_user_name();
  user_name_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:C2LS_Login.user_name)
}
#endif
inline void C2LS_Login::set_user_name(const char* value) {
  set_has_user_name();
  user_name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:C2LS_Login.user_name)
}
inline void C2LS_Login::set_user_name(const char* value, size_t size) {
  set_has_user_name();
  user_name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:C2LS_Login.user_name)
}
inline ::std::string* C2LS_Login::mutable_user_name() {
  set_has_user_name();
  // @@protoc_insertion_point(field_mutable:C2LS_Login.user_name)
  return user_name_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* C2LS_Login::release_user_name() {
  // @@protoc_insertion_point(field_release:C2LS_Login.user_name)
  clear_has_user_name();
  return user_name_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void C2LS_Login::set_allocated_user_name(::std::string* user_name) {
  if (user_name != NULL) {
    set_has_user_name();
  } else {
    clear_has_user_name();
  }
  user_name_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), user_name);
  // @@protoc_insertion_point(field_set_allocated:C2LS_Login.user_name)
}

// required string passwd = 2;
inline bool C2LS_Login::has_passwd() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void C2LS_Login::set_has_passwd() {
  _has_bits_[0] |= 0x00000002u;
}
inline void C2LS_Login::clear_has_passwd() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void C2LS_Login::clear_passwd() {
  passwd_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  clear_has_passwd();
}
inline const ::std::string& C2LS_Login::passwd() const {
  // @@protoc_insertion_point(field_get:C2LS_Login.passwd)
  return passwd_.GetNoArena();
}
inline void C2LS_Login::set_passwd(const ::std::string& value) {
  set_has_passwd();
  passwd_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:C2LS_Login.passwd)
}
#if LANG_CXX11
inline void C2LS_Login::set_passwd(::std::string&& value) {
  set_has_passwd();
  passwd_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:C2LS_Login.passwd)
}
#endif
inline void C2LS_Login::set_passwd(const char* value) {
  set_has_passwd();
  passwd_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:C2LS_Login.passwd)
}
inline void C2LS_Login::set_passwd(const char* value, size_t size) {
  set_has_passwd();
  passwd_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:C2LS_Login.passwd)
}
inline ::std::string* C2LS_Login::mutable_passwd() {
  set_has_passwd();
  // @@protoc_insertion_point(field_mutable:C2LS_Login.passwd)
  return passwd_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* C2LS_Login::release_passwd() {
  // @@protoc_insertion_point(field_release:C2LS_Login.passwd)
  clear_has_passwd();
  return passwd_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void C2LS_Login::set_allocated_passwd(::std::string* passwd) {
  if (passwd != NULL) {
    set_has_passwd();
  } else {
    clear_has_passwd();
  }
  passwd_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), passwd);
  // @@protoc_insertion_point(field_set_allocated:C2LS_Login.passwd)
}

#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)


// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_NetBaseDefine_2eproto__INCLUDED