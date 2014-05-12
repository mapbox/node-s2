# API

Exposes S2 objects and methods.

# s2.Point(x:number, y:number, z:number)

## point.x() -> number

## point.y() -> number

## point.z() -> number

# s2.S2LatLng(s2.Point | lat:number, lng:number)

Construct a new latlng object

## latLng.lat() -> number

## latLng.lng() -> number

## latLng.isValid() -> boolean

Return true if the latitude is between -90 and 90 degrees inclusive
and the longitude is between -180 and 180 degrees inclusive.

## latLng.toPoint() -> s2.Point

Convert a normalized S2LatLng to the equivalent unit-length vector.

## latLng.normalized() -> s2.S2LatLng

Clamps the latitude to the range [-90, 90] degrees, and adds or subtracts
a multiple of 360 degrees to the longitude if necessary to reduce it to
the range [-180, 180].

## latLng.toGeoJSON() -> GeoJSON object

Return a Point geometry of this latlng object

# s2.Cell(ll:s2.S2LatLng)

An S2Cell is an S2Region object that represents a cell.  Unlike S2CellIds,
it supports efficient containment and intersection tests.  However, it is
also a more expensive representation (currently 48 bytes rather than 8).

## cell.toGeoJSON() -> GeoJSON object

Return a Polygon geometry of this cell object

## cell.approxArea() -> number

## cell.exactArea() -> number

Return the area of this cell as accurately as possible.  This method is
more expensive but it is accurate to 6 digits of precision even for leaf
cells (whose area is approximately 1e-18).

## cell.averageArea(level:number) -> number

Return the average area of cells at this level.  This is accurate to
within a factor of 1.7 (for `S2_QUADRATIC_PROJECTION`) and is extremely
cheap to compute.

## cell.level() -> number

## cell.face() -> number

## cell.orientation() -> number

## cell.isLeaf() -> boolean

## cell.getCapBound() -> s2.S2Cap

## cell.getCenter() -> s2.S2Point

Return the direction vector corresponding to the center in (s,t)-space of
the given cell.  This is the point at which the cell is divided into four
subcells; it is not necessarily the centroid of the cell in (u,v)-space
or (x,y,z)-space.  The point returned by GetCenterRaw is not necessarily
unit length.

## cell.getVertex(n:number) -> s2.S2Point

## cell.id() -> s2.CellId

# s2.S2LatLngRect(ll:s2.S2LatLng [, ll:s2.S2LatLng])

An S2LatLngRect represents a closed latitude-longitude rectangle.  It is
capable of representing the empty and full rectangles as well as
single points.

## latLngRect.toGeoJSON() -> GeoJSON object

Return a Polygon geometry of this latlngrect object

## latLngRect.area() -> number

## latLngRect.center() -> latlng

## latLngRect.size() -> latlng

## latLngRect.getVertex(n:number) -> s2.S2LatLng

## latLngRect.getCapBound() -> s2.S2Cap

## latLngRect.contains(ll:latlng) -> boolean

## latLngRect.isEmpty() -> boolean

Return true if the rectangle is empty, i.e. it contains no points at all.

## latLngRect.isValid() -> boolean

Return true if the rectangle is valid, which essentially just means
that the latitude bounds do not exceed Pi/2 in absolute value and
the longitude bounds do not exceed Pi in absolute value.  Also, if
either the latitude or longitude bound is empty then both must be.

## latLngRect.isPoint() -> boolean

Return true if the rectangle is a point, i.e. lo() == hi()

# s2.S2Cap()

This class represents a spherical cap, i.e. a portion of a sphere cut off
by a plane.  The cap is defined by its axis and height.  This
representation has good numerical accuracy for very small caps (unlike the
(axis, min-distance-from-origin) representation), and is also efficient for
containment tests (unlike the (axis, angle) representation).

Here are some useful relationships between the cap height (h), the cap
opening angle (theta), the maximum chord length from the cap's center (d),
and the radius of cap's base (a).  All formulas assume a unit radius.

```
    h = 1 - cos(theta)
      = 2 sin^2(theta/2)
  d^2 = 2 h
      = a^2 + h^2
```

Caps may be constructed from either an axis and a height, or an axis and
an angle.  To avoid ambiguity, there are no public constructors except
the default constructor.

## cap.complement() -> s2.S2Cap

## cap.contains(other:s2.S2Cap) -> boolean

## cap.intersects(other:s2.S2Cap) -> boolean

## cap.getRectBound() -> s2.S2LatLngRect

# s2.S1Angle(a:s2.Point, b:s2.Point)

This class represents a one-dimensional angle (as opposed to a
two-dimensional solid angle).  It has methods for converting angles to
or from radians, degrees, and the E5/E6/E7 representations (i.e. degrees
multiplied by 1e5/1e6/1e7 and rounded to the nearest integer).

This class has built-in support for the E5, E6, and E7
representations.  An E5 is the measure of an angle in degrees,
multiplied by `10**5`.

# s2.S1Interval(lo:number, hi:number)

An S1Interval represents a closed interval on a unit circle (also known
as a 1-dimensional sphere).  It is capable of representing the empty
interval (containing no points), the full interval (containing all
points), and zero-length intervals (containing a single point).

Points are represented by the angle they make with the positive x-axis in
the range [-Pi, Pi].  An interval is represented by its lower and upper
bounds (both inclusive, since the interval is closed).  The lower bound may
be greater than the upper bound, in which case the interval is "inverted"
(i.e. it passes through the point (-1, 0)).

Note that the point (-1, 0) has two valid representations, Pi and -Pi.
The normalized representation of this point internally is Pi, so that
endpoints of normal intervals are in the range (-Pi, Pi].  However, we
take advantage of the point -Pi to construct two special intervals:
the Full() interval is [-Pi, Pi], and the Empty() interval is [Pi, -Pi].

## interval.length() -> number

## interval.hi() -> number

## interval.lo() -> number

## interval.complementLength() -> number

# s2.CellId(s2.Point | s2.S2LatLng)

An S2CellId is a 64-bit unsigned integer that uniquely identifies a
cell in the S2 cell decomposition.  It has the following format:

```
  id = [face][face_pos]

  face:     a 3-bit number (range 0..5) encoding the cube face.

  face_pos: a 61-bit number encoding the position of the center of this
            cell along the Hilbert curve over this face (see the Wiki
            pages for details).
```

Sequentially increasing cell ids follow a continuous space-filling curve
over the entire sphere. They have the following properties:

- The id of a cell at level k consists of a 3-bit face number followed
  by k bit pairs that recursively select one of the four children of
  each cell.  The next bit is always 1, and all other bits are 0.
  Therefore, the level of a cell is determined by the position of its
  lowest-numbered bit that is turned on (for a cell at level k, this
  position is 2 * (kMaxLevel - k).)

- The id of a parent cell is at the midpoint of the range of ids spanned
  by its children (or by its descendants at any level).

Leaf cells are often used to represent points on the unit sphere, and
this class provides methods for converting directly between these two
representations.  For cells that represent 2D regions rather than
discrete point, it is better to use the S2Cell class.

## cellid.level() -> number

## cellid.toPoint() -> s2.Point

## cellid.toString() -> string

## cellid.toToken() -> string

## cellid.parent() -> s2.CellId

## cellid.prev() -> s2.CellId

## cellid.next() -> s2.CellId

## cellid.isFace() -> boolean

## cellid.rangeMin() -> s2.CellId

Methods that return the range of cell ids that are contained
within this cell (including itself).  The range is *inclusive*
(i.e. test using >= and <=) and the return values of both
methods are valid leaf cell ids.

These methods should not be used for iteration.  If you want to
iterate through all the leaf cells, call child_begin(kMaxLevel) and
child_end(kMaxLevel) instead.

It would in fact be error-prone to define a range_end() method,
because (range_max().id() + 1) is not always a valid cell id, and the
iterator would need to be tested using "<" rather that the usual "!=".

## cellid.rangeMax() -> s2.CellId

## cellid.id() -> number

The 64-bit unique identifier for this cell.

# s2.Polygon()

# s2.RegionCoverer()

# s2.getCovering(S2LatLng[], options)

Get a covering, expressed as CellIds, for a given loop of S2atLng objects.
Options is an optional object that includes:

* min: minimum level
* max: maximum level
* max_cells: max number of cells to be computed
* level_mod: modulo for skipping levels
