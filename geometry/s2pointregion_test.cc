// Copyright 2005 Google Inc. All Rights Reserved.

#include <memory>
using std::unique_ptr;

#include "s2pointregion.h"

#include "testing/base/public/gunit.h"
#include "s2cap.h"
#include "s2cell.h"
#include "s2latlngrect.h"

namespace {

TEST(S2PointRegionTest, Basic) {
  S2Point p(1, 0, 0);
  S2PointRegion r0(p);
  EXPECT_EQ(r0.point(), p);
  EXPECT_TRUE(r0.Contains(p));
  EXPECT_TRUE(r0.VirtualContainsPoint(p));
  EXPECT_TRUE(r0.VirtualContainsPoint(r0.point()));
  EXPECT_FALSE(r0.VirtualContainsPoint(S2Point(1, 0, 1)));
  testing::internal::unique_ptr<S2PointRegion> r0_clone(r0.Clone());
  EXPECT_EQ(r0_clone->point(), r0.point());
  EXPECT_EQ(r0.GetCapBound(), S2Cap::FromAxisHeight(p, 0));
  S2LatLng ll(p);
  EXPECT_EQ(r0.GetRectBound(), S2LatLngRect(ll, ll));

  // The leaf cell containing a point is still much larger than the point.
  S2Cell cell(p);
  EXPECT_FALSE(r0.Contains(cell));
  EXPECT_TRUE(r0.MayIntersect(cell));
}

}  // namespace
