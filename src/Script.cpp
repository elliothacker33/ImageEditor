#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "Script.hpp"
#include "PNG.hpp"
#include "XPM2.hpp"

using namespace std;

namespace prog {
    // Use to read color values from a script file.
    istream& operator>>(istream& input, Color& c) {
        int r, g, b;
        input >> r >> g >> b;
        c.red() = r;
        c.green() = g;
        c.blue() = b;
        return input;
    }

    Script::Script(const string& filename) :
            image(nullptr), input(filename) {

    }
    void Script::clear_image_if_any() {
        if (image != nullptr) {
            delete image;
            image = nullptr;
        }
    }
    Script::~Script() {
        clear_image_if_any();
    }

    void Script::run() {
        string command;
        while (input >> command) {
            cout << "Executing command '" << command << "' ..." << endl;
            if (command == "open") {
                open();
                continue;
            }
            if (command == "blank") {
                blank();
                continue;
            }
            // Other commands require an image to be previously loaded.
            if (command == "save") {
                save();
                continue;
            } 
            if (command == "invert"){
                invert();
                continue;
            }
            if (command == "to_gray_scale"){
                to_gray_scale();
                continue;
            }
            if (command == "replace"){
                Color r1;
                input>>r1;
                Color r2;
                input>>r2;
                replace(r1.red(),r1.green(),r1.blue(),r2.red(),r2.green(),r2.blue());
                continue;
            }
            if(command == "fill"){
                int x,y;
                input>>x>>y;
                size_t width,height;
                input>>width>>height;
                Color pixel_;
                input>>pixel_;
                fill(x,y,width,height,pixel_.red(),pixel_.green(),pixel_.blue());
                continue;
            }
            if(command == "h_mirror"){
                h_mirror();
                continue;
            }
            if(command == "v_mirror"){
                v_mirror();
                continue;
            }
            if(command == "add"){
                std::string filename;
                input>>filename;
                Color pixel;
                input>>pixel;
                int x,y;
                input>>x>>y;
                add(filename,pixel.red(),pixel.green(),pixel.blue(),x,y);
                continue;
            }
            if(command == "crop"){
                int x,y;
                input>>x>>y;
                size_t width,heigth;
                input>>width>>heigth;
                crop(x,y,width,heigth);
                continue;
            }
            if(command == "rotate_left"){
                rotate_left();
                continue;
            }
            if(command == "rotate_right"){
                rotate_right();
                continue;
            }
            if(command == "median_filter"){
                int ws;
                input>>ws;
                median_filter(ws);
                continue;
            }
            if(command == "xpm2_open"){
                clear_image_if_any();
                string filename;
                input>>filename;
                image=loadFromXPM2(filename);
                continue;
            }
            if(command == "xpm2_save"){
                string filename;
                input >> filename;
                saveToXPM2(filename, image);
                continue;
            }


        }
    }
    void Script::open() {
        // Replace current image (if any) with image read from PNG file.
        clear_image_if_any();
        string filename;
        input >> filename;
        image = loadFromPNG(filename);
    }
    void Script::blank() {
        // Replace current image (if any) with blank image.
        clear_image_if_any();
        int w, h;
        Color fill;
        input >> w >> h >> fill;
        image = new Image(w, h, fill);
    }
    void Script::save() {
        // Save current image to PNG file.
        string filename;
        input >> filename;
        saveToPNG(filename, image);
    }
    void Script::invert(){
         size_t width=image->width();
        size_t height=image->height();
        for(size_t x=0;x<width;x++){
            for(size_t y=0;y<height;y++){
                Color& pixel=image->at(x,y);
                pixel.red()=255-pixel.red();
                pixel.green()=255-pixel.green();
                pixel.blue()=255-pixel.blue();
            }
        }
    }
    void Script::to_gray_scale(){
        size_t width=image->width();
        size_t height=image->height();
        for(size_t x=0;x<width;x++){
            for(size_t y=0;y<height;y++){
                Color& pixel=image->at(x,y);
                rgb_value v=(pixel.red()+pixel.blue()+pixel.green())/3;
                pixel.red()=pixel.green()=pixel.blue()=v;
            }
        }
    }
    void Script::replace(rgb_value r1,rgb_value g1,rgb_value b1,rgb_value r2,rgb_value g2,rgb_value b2){
        size_t width=image->width();
        size_t height=image->height();
        for(size_t x=0;x<width;x++){
            for(size_t y=0;y<height;y++){
                Color& pixel=image->at(x,y);
                if(pixel.red()==r1 && pixel.green()==g1 && pixel.blue()==b1){
                    pixel.red()=r2;
                    pixel.green()=g2;
                    pixel.blue()=b2;
                }
            }
        }
    }
    void Script::fill(int x,int y,size_t width,size_t height,rgb_value r,rgb_value g,rgb_value b){
        for(size_t i=x;i<x+width;i++){
            for(size_t j=y;j<y+height;j++){
                Color& pixel= image->at(i,j);
                pixel.red()=r;
                pixel.green()=g;
                pixel.blue()=b;
            }
        }
    }
    void Script::h_mirror(){
        size_t width=image->width();
        size_t height=image->height();
        for(size_t x=0;x<(width/2);x++){
            for(size_t y=0;y<height;y++){
                Color& pixel=image->at(x,y);
                Color& pixel1=image->at(width-1-x,y);
                Color temp=pixel;
                pixel=pixel1;
                pixel1=temp;
            }
        }
    }
    void Script::v_mirror(){
        size_t width=image->width();
        size_t height=image->height();
        for(size_t x=0;x<width;x++){
            for(size_t y=0;y<(height/2);y++){
                Color& pixel=image->at(x,y);
                Color& pixel1=image->at(x,height-1-y);
                Color temp=pixel;
                pixel=pixel1;
                pixel1=temp;
            }
        }
    }
    void Script::add(const std::string &filename,rgb_value r,rgb_value g,rgb_value b,int x,int y){
        Image* image1=loadFromPNG(filename);
        size_t width=image1->width();
        size_t height=image1->height();
        for(size_t i=0;i<width;i++){
            for(size_t j=0;j<height;j++){
                Color& pixel=image1->at(i,j);
                if(pixel.red()!=r || pixel.green()!=g || pixel.blue()!=b){
                    Color& pixel1=image->at(x+i,y+j);
                    pixel1=pixel;
                }
            }
        }
        delete image1;
    }
    void Script::crop(int x, int y, size_t width, size_t height){
        Image* image1 = new Image(width, height);
            for(size_t i = 0; i < width; i++) {
                for(size_t j = 0; j < height; j++) {
                    Color& pixel = image->at(x+i, y+j);
                    Color& pixel1 = image1->at(i, j);
                    pixel1 = pixel;
                }
            }
    delete image;
    image = image1;
}
void Script::rotate_left(){
    size_t width = image->width();
    size_t height = image->height();
    Image* im = new Image(height,width);
    for(size_t x = 0; x < width; x++) {
        for(size_t y = 0; y < height; y++) {
            Color& p = image->at(x, y);
            Color& p1 = im->at(y, width-x-1);
            p1=p;
        }
    }
    delete image;
    image = im;
    }
void Script::rotate_right(){
     size_t width = image->width();
     size_t height = image->height();
     Image* im = new Image(height,width);
        for(size_t x=0;x<width;x++){
            for(size_t y=0;y<height;y++){
                Color& pixel=image->at(x,y);
                Color& pixel1=im->at(height-y-1,x);
                pixel1=Color(pixel);      
            }
         }
         delete image;
         image=im;
}

void Script::median_filter(int ws){
    int width = image->width();
    int height = image->height();
    Image* image1= new Image(width,height);
    for(int x = 0; x < width; x++) {
        for(int y = 0; y < height; y++) {
            int up = std::max(0, x - ws/2);
            int down = std::min(width - 1, x + ws/2);
            int left = std::max(0, y - ws/2);
            int right = std::min(height - 1, y + ws/2);
            std::vector<rgb_value> r_values, g_values, b_values;
            for (int k = up; k <= down; k++) {
                for (int l = left; l <= right; l++) {
                    Color& pixel = image->at(k, l);
                    r_values.push_back(pixel.red());
                    g_values.push_back(pixel.green());
                    b_values.push_back(pixel.blue());
                }
            }
            std::sort(r_values.begin(), r_values.end());
            std::sort(g_values.begin(), g_values.end());
            std::sort(b_values.begin(), b_values.end());
            Color& pixel = image1->at(x, y);
            int size = r_values.size();
            int mid = size / 2;
            if(size%2==0){
                pixel.red()=((r_values[mid]+r_values[mid-1])/2);
                pixel.green()=((g_values[mid]+g_values[mid-1])/2);
                pixel.blue()=((b_values[mid]+b_values[mid-1])/2);
            }
            else{
                pixel.red()=(r_values[mid]);
                pixel.green()=(g_values[mid]);
                pixel.blue()=(b_values[mid]);
            }
        }
    }
    delete image;
    image=image1;
}

}
