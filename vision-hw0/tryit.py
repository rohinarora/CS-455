from uwimg import *

# 1. Getting and setting pixels
im = load_image("data/dog.jpg")
for row in range(im.h):
    for col in range(im.w):
        set_pixel(im, col, row, 0, 0)
save_image(im, "dog_no_red")

im = load_image("data/dog.jpg")
for row in range(im.h):
    for col in range(im.w):
        set_pixel(im, col, row, 1, 0)
save_image(im, "dog_no_green")

im = load_image("data/dog.jpg")
for row in range(im.h):
    for col in range(im.w):
        set_pixel(im, col, row, 2, 0)
save_image(im, "dog_no_blue")

im = load_image("data/dog.jpg")
for row in range(im.h):
    for col in range(im.w):
        set_pixel(im, col, row, 0, 0)
        set_pixel(im, col, row, 1, 0)
save_image(im, "dog_only_blue")

im = load_image("data/dog.jpg")
for row in range(im.h):
    for col in range(im.w):
        set_pixel(im, col, row, 2, 0)
        set_pixel(im, col, row, 1, 0)
save_image(im, "dog_only_red")

im = load_image("data/dog.jpg")
for row in range(im.h):
    for col in range(im.w):
        set_pixel(im, col, row, 2, 0)
        set_pixel(im, col, row, 0, 0)
save_image(im, "dog_only_green")

# 3. Grayscale image
im = load_image("data/colorbar.png")
graybar = rgb_to_grayscale(im)
save_image(graybar, "graybar")

im = load_image("data/dog.jpg")
graybar = rgb_to_grayscale(im)
save_image(graybar, "dog_gray")

im = load_image("data/dog.jpg")
graybar = vanilla_rgb_to_grayscale(im)
save_image(graybar, "dog_vanilla_gray")

# 4. Shift Image
im = load_image("data/dog.jpg")
shift_image(im, 0, .4)
shift_image(im, 1, .4)
shift_image(im, 2, .4)
save_image(im, "overflow")

# 5. Clamp Image
clamp_image(im)
save_image(im, "doglight_fixed")

# 6-7. Colorspace and saturation
im = load_image("data/dog.jpg")
rgb_to_hsv(im)
shift_image(im, 1, .2)
clamp_image(im)
hsv_to_rgb(im)
save_image(im, "dog_saturated")


im = load_image("data/dog.jpg")
rgb_to_hsv(im)
scale_image(im, 1, 2)
clamp_image(im)
hsv_to_rgb(im)
save_image(im, "dog_scale_saturated")
