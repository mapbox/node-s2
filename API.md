# API

Exposes S2 objects and methods.

# s2.Point(x:number, y:number, z:number)

# s2.LatLng(lat:number, lng:number)

Construct a new latlng object

## latLng.lat() -> number

## latLng.lng() -> number

## latLng.isValid() -> boolean

## latLng.toPoint() -> s2.Point

## latLng.normalized() -> s2.LatLng

# s2.Cell(ll:s2.LatLng)

## cell.approxArea() -> number

## cell.exactArea() -> number

## cell.averageArea(level:number) -> number

## cell.level() -> number

## cell.face() -> number

## cell.orientation() -> number

## cell.isLeaf() -> boolean

## cell.getCapBound() -> s2.Cap

# s2.CellId()

# s2.LatLngRect(ll:s2.LatLng)

## latLngRect.area() -> number

## latLngRect.center() -> latlng

## latLngRect.size() -> latlng

## latLngRect.getVertex(n:number) -> s2.LatLng

## latLngRect.getCapBound() -> s2.Cap

## latLngRect.contains(ll:latlng) -> boolean

# s2.Cap()

## cap.complement() -> s2.Cap

## cap.contains(other:s2.Cap) -> boolean

## cap.intersects(other:s2.Cap) -> boolean

## cap.getRectBound() -> s2.LatLngRect

# s2.Angle(a:s2.Point, b:s2.Point)

# s2.Interval(value:number)

## interval.length() -> number

## interval.hi() -> number

## interval.lo() -> number

## interval.complementLength() -> number
