#ifndef THIRD_PARTY_S2_VIEWFINDER
#define THIRD_PARTY_S2_VIEWFINDER

#include <string>
#include <vector>

int GetClosestLevel(double meters);

double DistanceBetweenLocations(double lat1, double lng1,
                                double lat2, double lng2);

std::vector<std::string> IndexCells(double lat, double lng,
                                    int min_level, int max_level);
std::vector<std::string> SearchCells(double lat, double lng, double radius,
                                     int min_level, int max_level);

#endif // THIRD_PARTY_S2_VIEWFINDER
