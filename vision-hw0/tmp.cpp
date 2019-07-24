typedef struct{
    int h,w,c;
    float *data;
} image;

image im = load_image("image.jpg");

save_image(im, "output");

image im = make_image(w,h,c);

free_image(im);

make

./uwimg test

python tryit.py

float get_pixel(image im, int x, int y, int c);
void set_pixel(image im, int x, int y, int c, float v);
