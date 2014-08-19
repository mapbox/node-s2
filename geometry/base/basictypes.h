//
// Copyright 2001 - 2003 Google, Inc.
//

#ifndef _BASICTYPES_H_
#define _BASICTYPES_H_

#include "base/integral_types.h"
#include "base/casts.h"
#include "base/port.h"

// We *do* expect Hash<i> values to collide from time to time
// (although we obviously prefer them not to). Also
// note that there is an illegal hash value for each size hash.
typedef uint32 Hash32;
typedef uint16 Hash16;
typedef unsigned char Hash8;

const Hash32 kIllegalHash32 = static_cast<Hash32>(4294967295UL);    // 2^32-1
const Hash16 kIllegalHash16 = static_cast<Hash16>(65535U);          // 2^16-1
const Hash8  kIllegalHash8 = static_cast<Hash8>(255);               // 2^8-1

#endif  // _BASICTYPES_H_
