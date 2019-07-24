#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "image.h"

float get_pixel(image im, int x, int y, int c)
{
  if (x<0){
    x=0;
  }
  if (y<0){
    y=0;
  }
  if (x>=im.w){
    x=im.w-1;
  }
  if (y>=im.h){
    y=im.h-1;
  }
  return im.data[x + y*im.w + c*im.w*im.h];
}

void set_pixel(image im, int x, int y, int c, float v)
{
  if ((x >= 0 && x < im.w) && (y >= 0 && y < im.h) && (c >= 0 && c < im.c)) {
    im.data[x + y*im.w + c*im.w*im.h]=v;
  }
}

image copy_image(image im)
{
  image copy = make_image(im.w, im.h, im.c);
  for (int i=0; i < (im.w * im.h * im.c); i++) {
    copy.data[i] = im.data[i];
  }
  // or memcpy(copy.data, im.data, im.w*im.h*im.c * sizeof(float));
  return copy;
}

image rgb_to_grayscale(image im)
{
  assert(im.c == 3);
  image gray = make_image(im.w, im.h, 1);
  for (int x = 0; x < (im.w); ++x) {
    for (int y = 0; y < (im.h); ++y) {
      gray.data[x + y * im.w] = 0.299 * get_pixel(im, x, y, 0) + 0.587 * get_pixel(im, x, y, 1) + 0.114 * get_pixel(im, x, y, 2);
    }
  }
  return gray;
}

image vanilla_rgb_to_grayscale(image im)
{
  assert(im.c == 3);
  image gray = make_image(im.w, im.h, 1);
  for (int x = 0; x < (im.w); ++x) {
    for (int y = 0; y < (im.h); ++y) {
      gray.data[x + y * im.w] = get_pixel(im, x, y, 0) + get_pixel(im, x, y, 1) + get_pixel(im, x, y, 2);
    }
  }
  return gray;
}

void shift_image(image im, int c, float v)
{
  for (int x = 0; x < (im.w); ++x) {
    for (int y = 0; y < (im.h); ++y) {
      int pixel=x + y * im.w+c*im.w*im.h;
      im.data[pixel]+=v;
    }
  }
}

void clamp_image(image im)
{
  for (int i=0;i<(im.c*im.h*im.w);i++){
    if (im.data[i]>1){
      im.data[i]=1;
    }else if (im.data[i]<0){
      im.data[i]=0;
    }
  }
}


// These might be handy
float three_way_max(float a, float b, float c)
{
  return (a > b) ? ( (a > c) ? a : c) : ( (b > c) ? b : c) ;
}

float three_way_min(float a, float b, float c)
{
  return (a < b) ? ( (a < c) ? a : c) : ( (b < c) ? b : c) ;
}
void rgb_to_hsv(image im)
{
  float r, g, b, min, max, c, h, s, v;
  for (int x = 0; x < im.w; x++) {
    for (int y = 0; y < im.h; y++) {
      r = get_pixel(im, x, y, 0);
      g = get_pixel(im, x, y, 1);
      b = get_pixel(im, x, y, 2);
      min = three_way_min(r, g, b);
      max = three_way_max(r, g, b);
      c = max - min;
      v = max;
      if (v != 0) {
        s = c / v;
      }
      else {
        s = 0;
      }
      if (c != 0) {
        if (v == r) {
          h = (g - b) / c;
        }
        else if (v == g) {
          h = ((b - r) / c) + 2;
        }
        else {
          h = ((r - g) / c) + 4;
        }
      }
      else {
        h = 0;
      }
      h /= 6;
      if (h < 0) {
        h++;
      }
      set_pixel(im, x, y, 0, h);
      set_pixel(im, x, y, 1, s);
      set_pixel(im, x, y, 2, v);
    }
  }
}

void hsv_to_rgb(image im)
{
  float h, s, v, c, max, min, r, g, b, h_temp;
  for (int x = 0; x < im.w; x++) {
    for (int y = 0; y < im.h; y++) {
      h = get_pixel(im, x, y, 0);
      s = get_pixel(im, x, y, 1);
      v = get_pixel(im, x, y, 2);
      c = s * v;
      max = v;
      if (v != c) {
        min = v - c;
      }
      else {
        min = 0.0;
      }
      h_temp = h * 6;
      if (c == 0) {
        r = v;
        g = v;
        b = v;
      }
      else if (h_temp > 5 && h_temp < 6) {
        r = max;
        g = min;
        b = ((((h_temp /  6) - 1) * 6 * c) - g) * -1;
      }
      else if (h_temp == 5) {
        r = max;
        g = min;
        b = max;
      }
      else if (h_temp < 5 && h_temp > 4) {
        g = min;
        r = (h_temp - 4) * c + g;
        b = max;
      }
      else if (h_temp == 4) {
        r = min;
        g = min;
        b = max;
      }
      else if (h_temp < 4 && h_temp > 3) {
        r = min;
        g = (((h_temp - 4) * c) - r) * -1;
        b = max;
      }
      else if (h_temp == 3) {
        r = min;
        g = max;
        b = max;
      }
      else if (h_temp < 3 && h_temp > 2) {
        r = min;
        g = max;
        b = ((h_temp - 2) * c) + r;
      }
      else if (h_temp == 2) {
        r = min;
        g = max;
        b = min;
      }
      else if (h_temp < 2 && h_temp > 1) {
        g = max;
        b = min;
        r = (((h_temp - 2) * c) - b) * -1;
      }
      else if (h_temp == 1) {
        r = max;
        g = max;
        b = min;
      }
      else if (h_temp < 1 && h_temp > 0) {
        r = max;
        b = min;
        g = (h_temp * c) + b;
      }
      else {
        r = max;
        g = min;
        b = min;
      }

      set_pixel(im, x, y, 0, r);
      set_pixel(im, x, y, 1, g);
      set_pixel(im, x, y, 2, b);
    }
  }
}

void scale_image(image im, int c, float v)
{
  if (c >= 0 && c < im.c) {
    for (int x = 0; x < im.w; x++) {
      for (int y = 0; y < im.h; y++) {
        im.data[x + y*im.w + c*im.w*im.h] *= v;
      }
    }
  }
}
