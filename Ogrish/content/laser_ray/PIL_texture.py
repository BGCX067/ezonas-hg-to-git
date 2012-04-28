import Image

width = 32
max = 32
val_r = 255
val_g = 0
val_b = 0

values = []
half_range = width/2
im = Image.new("RGBA", (width, 1), (0, 0, 0, 0))


for a in range(half_range):
	values.append(a*max/half_range)

values+=reversed(values)

# print values
for a in range(width):
	c = values[a]
	im.putpixel((a,0), (val_r, val_g, val_b, c))


im.save("laser_ray.png")