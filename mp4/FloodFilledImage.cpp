#include "cs225/PNG.h"
#include <list>
#include <iostream>

#include "colorPicker/ColorPicker.h"
#include "imageTraversal/ImageTraversal.h"

#include "Point.h"
#include "Animation.h"
#include "FloodFilledImage.h"

using namespace cs225;

/**
 * Constructs a new instance of a FloodFilledImage with a image `png`.
 * 
 * @param png The starting image of a FloodFilledImage
 */
FloodFilledImage::FloodFilledImage(const PNG & png) {
  /** @todo [Part 2] */
  tra_arr.clear();
  colorP_arr.clear();
  png_ = PNG(png);
}

/**
 * Adds a flood fill operation to the FloodFillImage.  This function must store the operation,
 * which will be used by `animate`.
 * 
 * @param traversal ImageTraversal used for this FloodFill operation.
 * @param colorPicker ColorPicker used for this FloodFill operation.
 */
void FloodFilledImage::addFloodFill(ImageTraversal & traversal, ColorPicker & colorPicker) {
  /** @todo [Part 2] */
  //store info
  tra_arr.push_back(&traversal);
  colorP_arr.push_back(&colorPicker);
}

/**
 * Creates an Animation of frames from the FloodFill operations added to this object.
 * 
 * Each FloodFill operation added by `addFloodFill` is executed based on the order
 * the operation was added.  This is done by:
 * 1. Visiting pixels within the image based on the order provided by the ImageTraversal iterator and
 * 2. Updating each pixel to a new color based on the ColorPicker
 * 
 * While applying the FloodFill to the image, an Animation is created by saving the image
 * after every `frameInterval` pixels are filled.  To ensure a smooth Animation, the first
 * frame is always the starting image and the final frame is always the finished image.
 * 
 * (For example, if `frameInterval` is `4` the frames are:
 *   - The initial frame
 *   - Then after the 4th pixel has been filled
 *   - Then after the 8th pixel has been filled
 *   - ...
 *   - The final frame, after all pixels have been filed)
 */ 
Animation FloodFilledImage::animate(unsigned frameInterval) const {
  Animation animation;
  /** @todo [Part 2] */
  //add initial frame
  animation.addFrame(png_);
  // add frame every part of the traversal 
  for(unsigned i=0; i< tra_arr.size();i++)
  {
    ImageTraversal::Iterator j=tra_arr[i]->begin();
    while(j!=tra_arr[i]->end())
    {
      for(unsigned count=1;count<=frameInterval;count++)
      {
        HSLAPixel* to_change =  png_.getPixel((*j).x,(*j).y);
        *to_change = colorP_arr[i]->getColor((*j).x,(*j).y);
        ++j;
        if( !(j!=tra_arr[i]->end()))
        {
            //animation.addFrame(png_);
            break;
        }
      }
      //store the png to frame every "count" times iteration
      animation.addFrame(png_);

    }
          //animation.addFrame(png_);
    // //i is index of all operations
    // for(ImageTraversal::Iterator j=tra_arr[i]->begin();j!=tra_arr[i]->end();)
    // {
    //   for(unsigned count=1;count<=frameInterval;count++)
    //   {
    //     HSLAPixel* to_change =  png_.getPixel((*j).x,(*j).y);
    //     *to_change = colorP_arr[i]->getColor((*j).x,(*j).y);
    //     ++j;
    //   }
    //   //store the png to frame every "count" times iteration
    //   animation.addFrame(png_);
    // }    
  }
  return animation;
}
