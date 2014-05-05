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

# s2.CellId()
