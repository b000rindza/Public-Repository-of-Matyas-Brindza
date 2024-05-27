from PIL import Image
import os



RAW_DIR = "/home/brindza/Desktop/personal_projects/Games/Space_Invaders/graphics/"
files = os.listdir(RAW_DIR+"raw/")
print(files)





def crop_dim(image):
    width, height = image.size
    color_pix, x, y = [], [], []
    for i in range(width):
        for j in range(height):
            pixel_color = image.getpixel((i, j))
            if (pixel_color!=(0,0,0)):
                color_pix.append([i, j])
                x.append(i)
                y.append(j)
                #print("Pixel color at (", i, ", ", j, ", ):", pixel_color)
#    center_x = 0
#    center_y = 0
#    for i in color_pix:
#        center_x += i[0]
#        center_y += i[1]
#    center = [center_x/len(color_pix),center_y/len(color_pix)]
    
    left = min(x)-1
    right = max(x)+1
    top = min(y)-1
    bottom = max(y)+1

#    if (left==right):
#        left += -1
#    if (top==bottom):
#        top += -1


    print(left, right, top, bottom)
    return left, right, top, bottom






# Open the image file

for file in files:
    file_new = file[0:-8:1] + ".png"
    print(file,"  --->  ", file_new)

    image = Image.open(RAW_DIR+"raw/"+file).convert("RGB")

    # Get the size of the original image
    width, height = image.size
    print(width, height)    

    # Set the crop coordinates
    left, right, top, bottom = crop_dim(image)
    print("Image mode:", image.mode)

    # Crop the image
    cropped_image = image.crop((left, top, right, bottom))

    # Save the cropped image
    cropped_image.save(RAW_DIR + "images/"+file_new)


