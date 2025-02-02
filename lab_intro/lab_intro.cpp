#include <iostream>
#include <cmath>
#include <cstdlib>

#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include "lab_intro.h"

using namespace cs225;

/**
 * Returns an image that has been transformed to grayscale.
 *
 * The saturation of every pixel is set to 0, removing any color.
 *
 * @return The grayscale image.
 */
PNG grayscale(PNG image) {
  /// This function is already written for you so you can see how to
  /// interact with our PNG class.
  for (unsigned x = 0; x < image.width(); x++) {
    for (unsigned y = 0; y < image.height(); y++) {
      HSLAPixel *pixel = image.getPixel(x, y);

      // `pixel` is a pointer to the memory stored inside of the PNG `image`,
      // which means you're changing the image directly.  No need to `set`
      // the pixel since you're directly changing the memory of the image.
      pixel->s = 0;
    }
  }

  return image;
}



/**
 * Returns an image with a spotlight centered at (`centerX`, `centerY`).
 *
 * A spotlight adjusts the luminance of a pixel based on the distance the pixel
 * is away from the center by decreasing the luminance by 0.5% per 1 pixel euclidean
 * distance away from the center.
 *
 * For example, a pixel 3 pixels above and 4 pixels to the right of the center
 * is a total of `sqrt((3 * 3) + (4 * 4)) = sqrt(25) = 5` pixels away and
 * its luminance is decreased by 2.5% (0.975x its original value).  At a
 * distance over 200 pixels away, the luminance will always 0.
 *
 * The modified PNG is then returned.
 *
 * @param image A PNG object which holds the image data to be modified.
 * @param centerX The center x coordinate of the crosshair which is to be drawn.
 * @param centerY The center y coordinate of the crosshair which is to be drawn.
 *
 * @return The image with a spotlight.
 */
PNG createSpotlight(PNG image, int centerX, int centerY) {

  //initialization
  int distance =0;

  for (unsigned x = 0; x < image.width(); x++) {
    for (unsigned y = 0; y < image.height(); y++) {
      HSLAPixel *pixel = image.getPixel(x, y);

      //calculate current distance from center
      distance = (x-centerX)*(x-centerX)+(y-centerY)*(y-centerY);
      //decrease luminance according to the distance 
      //check if the distance is farther than 200
      if(sqrt(distance)<200)
      {
      pixel->l = pixel->l*(1-sqrt(distance)*0.005);
      }
      else{pixel->l=0;}
    }
  }
  return image;
}


/**
 * Returns a image transformed to Illini colors.
 *
 * The hue of every pixel is set to the a hue value of either orange or
 * blue, based on if the pixel's hue value is closer to orange than blue.
 *
 * @param image A PNG object which holds the image data to be modified.
 *
 * @return The illinify'd image.
**/
PNG illinify(PNG image) {
  
  for (unsigned x = 0; x < image.width(); x++) {
    for (unsigned y = 0; y < image.height(); y++) {
      HSLAPixel *pixel = image.getPixel(x, y);

      //if in the range of [0,216]
      if (0 <= pixel->h && pixel->h <= 216)
      {
      //if the pixel's hue value is closer to orange than blue then orange
      if( abs(pixel->h-11) < abs(pixel->h-216))
      {
        pixel->h=11;
      }
      else{pixel->h=216;}
      }
      //if not 
      else
      {
        if(pixel->h>=294){pixel->h=11;}
        else{pixel->h=216;}
      }

    }
  }

  return image;
}


/**
* Returns an immge that has been watermarked by another image.
*
* The luminance of every pixel of the second image is checked, if that
* pixel's luminance is 1 (100%), then the pixel at the same location on
* the first image has its luminance increased by 0.2.
*
* @param firstImage  The first of the two PNGs.
* @param secondImage The second of the two PNGs.
*
* @return The watermarked image.
*/
PNG watermark(PNG firstImage, PNG secondImage) {
  //resize the two picture
  secondImage.resize(1024, 768);
  firstImage.resize(1024, 768);
  for (unsigned x = 0; x < secondImage.width(); x++) {
    for (unsigned y = 0; y < secondImage.height(); y++) {
      HSLAPixel *second_pixel = secondImage.getPixel(x, y);
      HSLAPixel *first_pixel ; 
      //if second pixel's luminance is 1, change the first image 
      if ( second_pixel->l ==1.0) 
      {
        first_pixel = firstImage.getPixel(x,y);   //get the pixel to change
        if(first_pixel->l+0.2<=1)
        {
        first_pixel->l +=0.2;
        }
        else{first_pixel->l=1;}
      }
    }
  }
  return firstImage;
}
