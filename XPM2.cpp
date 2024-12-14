#include "XPM2.hpp"
#include<fstream>
#include<sstream>
#include<map>
#include<iostream>
#include<iomanip>
#include<vector>
using namespace std;
namespace prog {
   Image* loadFromXPM2(const std::string& file) {
    ifstream in(file);
    if (!in) {
        return nullptr;
    }

    string line;
    getline(in, line);
    getline(in,line);
    istringstream iss(line);
    int width, height, num_colors, chars_per_pixel;
    iss >> width >> height >> num_colors >> chars_per_pixel;
    map<char, Color> color_table;
    for (int i = 0; i < num_colors; i++) {
        getline(in, line);
        char c;
        char nothing;
        string color_str;
        istringstream iss(line);
        iss >> c >>nothing>>color_str;
        cout<< c<<nothing<<color_str<<endl;
        std::istringstream iss2(color_str.substr(1)); // skip the # character
        int rgb_val;
        iss2 >> std::hex >> rgb_val;
        int r = (rgb_val >> 16) & 0xFF;
        int g = (rgb_val >> 8) & 0xFF;
        int b = rgb_val & 0xFF;
        cout<<r<<g<<b<<endl;
        color_table[c] = Color(r,g,b);
    }

    Image* image = new Image(width, height);
    for (int y = 0; y < height; y++) {
        getline(in, line);
        for (int x = 0; x < width; x++) {
            char c = line[x];
            Color color = color_table[c];
            image->at(x, y) = color;
        }
    }
    return image;
}

    bool find( vector<pair<Color,char>> color_map,Color color){
        for(auto i:color_map){
            if(i.first.red()==color.red() && i.first.green()==color.green()  && i.first.blue()==color.blue()){
                return true;
            }
        }
        return false;
    }
    void saveToXPM2(const std::string& file, const Image* image) {
         std::ofstream out(file);
         int width = image->width();
         int height = image->height();
         vector<pair<Color,char>> color_map;
         for(int x=0;x<width;x++){
            for(int y=0;y<height;y++){
                  Color color = image->at(x, y);
                if (!find(color_map,color)) {
                    char new_char = 'a' + color_map.size(); 
                    color_map.push_back({color, new_char});
                }
            }  
        }
        int colors=color_map.size();
        int characters=1;
        out<<"! XMP2"<<endl;
        out<<width<<" "<<height<<" "<<colors<<" "<<characters<<endl;
        for(auto i:color_map){
            std::stringstream hex_color_stream;
hex_color_stream  << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(i.first.red())
                 << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(i.first.green())
                 << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(i.first.blue());
std::string hex_color = hex_color_stream.str();
            out<<i.second<<" "<<"c"<<" "<<"#"<<hex_color<<endl;
        }
        for (int y = 0; y<height; y++) {
            for (int x = 0; x < width; x++) {
                const Color& color = image->at(x, y);
                char c;
                for(auto i:color_map){
                    if(i.first.red()==color.red() && i.first.green()==color.green()  && i.first.blue()==color.blue()){
                        c=i.second;
                    }
                }
                out << c;
        }
        out << endl;
    }
    }
}
