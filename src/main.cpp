#include <optional>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <io2d.h>
#include "route_model.h"
#include "render.h"
#include "route_planner.h"

using namespace std::experimental;
using std::string, std::cout, std::cin, std::endl;

static std::optional<std::vector<std::byte>> ReadFile(const std::string &path)
{   
    std::ifstream is{path, std::ios::binary | std::ios::ate};
    if( !is )
        return std::nullopt;
    
    auto size = is.tellg();
    std::vector<std::byte> contents(size);    
    
    is.seekg(0);
    is.read((char*)contents.data(), size);

    if( contents.empty() )
        return std::nullopt;
    return std::move(contents);
}

void get_coordinates(const string pair, float n) {
    cout << "Enter " << pair << ": ";
    cin >> n;
    while (cin.fail() || n < 0 || n > 100) {
        cout << "Invalid value. Please enter a value between 0-100.";
        cin.clear();
        cin.ignore(10000, '\n');
        cin >> n;
    }
}

int main(int argc, const char **argv)
{    
    std::string osm_data_file = "";
    if( argc > 1 ) {
        for( int i = 1; i < argc; ++i )
            if( std::string_view{argv[i]} == "-f" && ++i < argc )
                osm_data_file = argv[i];
    }
    else {
        cout << "To specify a map file use the following format: " << endl;
        cout << "Usage: [executable] [-f filename.osm]" << endl;
        osm_data_file = "../map.osm";
    }
    
    std::vector<std::byte> osm_data;
 
    if( osm_data.empty() && !osm_data_file.empty() ) {
        cout << "Reading OpenStreetMap data from the following file: " <<  osm_data_file << endl;
        auto data = ReadFile(osm_data_file);
        if( !data )
            cout << "Failed to read." << endl;
        else
            osm_data = std::move(*data);
    }

    // create coordinates
    float start_x, start_y, end_x, end_y;
    start_x = start_y = end_x = end_y = 0.0f;

    cout << "To begin, enter start coordinates and end coordinates. All values must be 0-100." << endl;
    get_coordinates("start (x)", start_x);
    get_coordinates("start (y)", start_y);
    get_coordinates("end (x)", end_x);
    get_coordinates("end (y)", end_y);

    // Build Model.
    RouteModel model{osm_data};

    // Create RoutePlanner object and perform A* search.
    RoutePlanner route_planner{model, start_x, start_y, end_x, end_y};
    route_planner.AStarSearch();

    std::cout << "Distance: " << route_planner.GetDistance() << " meters. \n";

    // Render results of search.
    Render render{model};

    auto display = io2d::output_surface{400, 400, io2d::format::argb32, io2d::scaling::none, io2d::refresh_style::fixed, 30};
    display.size_change_callback([](io2d::output_surface& surface){
        surface.dimensions(surface.display_dimensions());
    });
    display.draw_callback([&](io2d::output_surface& surface){
        render.Display(surface);
    });
    display.begin_show();
}
