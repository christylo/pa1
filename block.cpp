#include "block.h"

// Returns the dimensions of the block. 
// Note that the horizontal and vertical dimensions are the same.
int Block::Dimension() const {
    return data.size();
}

// set values in data attribute, based on a dimension x dimension square region
  //   with upper-left corner at (left, upper) in the input PNG image
  // The orientation of the pixels in the data vector must match the orientation
  //   of the pixels in the PNG.
  // PRE: upper and left (and upper + dimension, left + dimension) are valid
  //        vector indices
// Completes a block’s pixel data from the square area of dimension by dimension pixels 
// in im whose upper-left corner is at position (left,upper).
void Block::Build(PNG & im, int upper, int left, int dimension) {
    
    for (int width = 0; width < dimension; width++) {
        vector <HSLAPixel> val;

        for (int height=0; height < dimension; height++) {
            HSLAPixel* pixel = im.getPixel(width + left, height + upper);
            val.push_back(*pixel);
        }
        data.push_back(val);
    }
}

// write the pixel colour data fom data attribute into im,
  //   with upper-left corner at (left, upper)
  // PRE: upper and left (and upper + dimension, left + dimension) are valid
  //        vector indices
// Draws the block at position (x,y) in im.
void Block::Render(PNG& im, int upper, int left) const {
    for (int width = 0; width < (int) data.size(); width++) {
        for (int height = 0; height < (int) data.size(); height++) {
            HSLAPixel* pixel = im.getPixel(width + left, height + upper);
            *pixel = data[width][height];
        }
    }

}

// "Reverse" the Hue and Luminance channels for each pixel in the data attribute
  //   to simulate a photo-negative effect.
  // Refer to the HSLAPixel documentation to determine an appropriate transformation
  //   for "reversing" hue and luminance.
// Reverses the hue and luminance of every pixel in the block, 
// creating a simulated photo-negative effect. It is up to you to study the HSLAPixel 
// documentation to decide what an appropriate meaning for reversing hue and luminance will be.
void Block::Negative() {
    for (int width = 0; width < (int) data.size(); width++) {
        for (int height = 0; height < (int) data.size(); height++) {
            data[width][height].h = ((int)data[width][height].h + 180) % 360;
            data[width][height].l = 1 - data[width][height].l;
        }
    }
}