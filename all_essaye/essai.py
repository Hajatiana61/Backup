import py5


def setup():
    py5.size(200, 200)                      # ( width and height )

def draw():
     py5.background(250)
     key_pressed()

def key_pressed():
    if py5.key_code == py5.UP:
        print("Hello")

    a = -3
    b = -4

    large_Y = abs(a - b)

    print(" value: ",large_Y)
py5.run_sketch()


"""
 global COLOR, pos_x, i, diam
    py5.background(250)                     # couleur background
    py5.fill(COLOR,0,0)                       # couleur de l'objet
    py5.no_stroke()
    py5.ellipse(pos_x, py5.height/2, diam/2, diam/2 )
    pos_x = pos_x + i

    if pos_x >= py5.width :
        i = -pos_x
    if pos_x  <= ray :
        i = 2
"""
"""
    if pos_x >= py5.width - ray :
        i = -2
    if pos_x  <= ray :
        i = 2
"""
