#include "../DataStructures/GTFS/Data.h"
#include<iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>
#include <set>
#include <unordered_map>
#include "../DataStructures/Container/Map.h"
std::vector<std::string> directjourney(const GTFS::Data& gtfsdata, const std::string& sourcestopID, const std::string& deststopID, std::unordered_map<std::string, std::vector<std::string>> stopRoutes){
	std::vector<std::string> visited;
    bool directJourneyFound = false;
    for(const auto& routeid : stopRoutes[sourcestopID]){
    	for(const auto& ROUTEID : stopRoutes[deststopID]){
    		if(routeid == ROUTEID){
    			if(std::find(visited.begin(), visited.end(), routeid) != visited.end())
    			        break;
    			// std::cout << routeid << "(" << sourcestopID << " > " << deststopID << ") "<<std::endl;
    			visited.push_back(routeid);
    		}
    	}
    }
    return visited;
}
int main(int argc, char* argv[]){
	if(argc != 3){
		std::cout<< "Incorrect input"<<std::endl;
		return 1;
	}
	std::string sourcestopID = argv[1];
	std::string deststopID = argv[2];


    std::string filename = "";
    GTFS::Data gtfsdata = GTFS::Data::FromGTFS(filename);

    std::unordered_map<std::string, std::string> tripRoutes;
    for (const auto& trip : gtfsdata.trips) {
        tripRoutes[trip.tripId]= trip.routeId;
    }
    std::unordered_map<std::string, std::vector<std::string>> stopRoutes;
    for (const auto& stopTime : gtfsdata.stopTimes) {
        stopRoutes[stopTime.stopId].push_back(tripRoutes[stopTime.tripId]);
    }
    std::unordered_map<std::string, std::vector<std::string>> routeStops;
    for (const auto& stopTime : gtfsdata.stopTimes) {
    	routeStops[tripRoutes[stopTime.tripId]].push_back(stopTime.stopId);
    }

    std::cout << "Direct journeys: ";
    std::vector<std::string> visited;
    visited = directjourney(gtfsdata, sourcestopID, deststopID, stopRoutes);
    for(const auto& routeid : visited){
    	std::cout << routeid << "(" << sourcestopID << " > " << deststopID << ") "<<std::endl;
    }

    std::cout<<"Journeys with one transfer: ";
    std::vector<std::string> visited1;
    for(const auto& routeid :stopRoutes[sourcestopID]){
    	for(const auto& stopid : routeStops[routeid]){
    		if(stopid != sourcestopID && stopid != deststopID){
    	    std::vector<std::string> visited1;
    	    visited1 = directjourney(gtfsdata, stopid, deststopID, stopRoutes);
    	    if(!visited1.empty()){
    	    	for(const auto& routeID : visited1){
    	    		if(routeid != routeID)
    	    		std::cout<< routeid << "(" <<sourcestopID<<">"<<stopid<<") -"<<routeID<<"("<<stopid<<">"<< deststopID <<")"<<std::endl;
    	    	}
    	    }
    	    }
    	}
    }



    return 0;
}