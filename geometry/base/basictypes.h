//
// Copyright 2001 - 2003 Google, Inc.
//

#ifndef _BASICTYPES_H_
#define _BASICTYPES_H_

#include "base/integral_types.h"
#include "base/casts.h"
#include "base/port.h"

// In contrast to Fingerprints, we *do* expect Hash<i> values to collide
// from time to time (although we obviously prefer them not to).  Also
// note that there is an illegal hash value for each size hash.
typedef uint32 Hash32;
typedef uint16 Hash16;
typedef unsigned char  Hash8;

const Hash32 kIllegalHash32 = static_cast<Hash32>(4294967295UL);    // 2^32-1
const Hash16 kIllegalHash16 = static_cast<Hash16>(65535U);          // 2^16-1
const Hash8  kIllegalHash8 = static_cast<Hash8>(255);               // 2^8-1

// Use these as the mlock_bytes parameter to MLock and MLockGeneral
enum { MLOCK_ALL = -1, MLOCK_NONE = 0 };

// The following enum should be used only as a constructor argument to indicate
// that the variable has static storage class, and that the constructor should
// do nothing to its state.  It indicates to the reader that it is legal to
// declare a static nistance of the class, provided the constructor is given
// the base::LINKER_INITIALIZED argument.  Normally, it is unsafe to declare a
// static variable that has a constructor or a destructor because invocation
// order is undefined.  However, IF the type can be initialized by filling with
// zeroes (which the loader does for static variables), AND the type's
// destructor does nothing to the storage, then a constructor for static initialization
// can be declared as
//       explicit MyClass(base::LinkerInitialized x) {}
// and invoked as
//       static MyClass my_variable_name(base::LINKER_INITIALIZED);
namespace base {
enum LinkerInitialized { LINKER_INITIALIZED };
}

#endif  // _BASICTYPES_H_
