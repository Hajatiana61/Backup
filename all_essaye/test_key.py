import py5


diam = 50
ray = diam/2
pos_x = ray
i = 2

COLOR = py5.color(py5.random(255), py5.random(255), py5.random(255))

def setup():
    py5.size(400, 100)                        # ( width and height )

def draw():
    py5.background(250)                       # couleur background
    display_object()

def key_pressed():
    global COLOR, i, pos_x, ray
    if py5.key_code == py5.UP:
        COLOR = py5.color(py5.random(255), py5.random(255), py5.random(255))
        pos_x = 0
        print("touche UP pressed")


    if py5.key_code == py5.DOWN:
        COLOR = py5.color(py5.random(255), py5.random(255), py5.random(255))
        print("touche DOWN pressed")

    else:
        print("touche unknown pressed")

def display_object():

    global COLOR, pos_x, i, diam
    py5.fill(COLOR)            # couleur de l'objet
    py5.no_stroke()
    py5.ellipse(pos_x, py5.height/2, diam/2, diam/2 )
    pos_x = pos_x + i

    if pos_x >= py5.width :
        i = -pos_x
    if pos_x  < py5.width :
        i = 2

py5.run_sketch()
