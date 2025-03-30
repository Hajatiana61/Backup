import py5
import time


diam = 20
rayon = diam/2
pos_x = rayon
espace = rayon
pos_y = rayon
pos_x2 = 0
pos_y2 = 0
speed = 1
espace = 0
q = 0
touch_key = "RIGHT"
tail_key = "RIGHT"
direcion ="RIGHT"

COLOR_P1 = py5.color(250)
COLOR_SEED = py5.color(255,0,0)

seed_show = True
new_ellipse = False
seed_x = py5.random_int(0,500)
seed_y = py5.random_int(0,400)

add = 0
tail_X = [0]*1
tail_Y = [0]*1

def setup():
    py5.size(500, 400)                        # ( width and height )

def draw():

    py5.background(0)
    display_hote()
    Anime_tails()
    q = 0


def key_tails():
    global add, tail_key, COLOR_P1, diam, tail_X, tail_Y, pos_x2, pos_y2, espace

    if py5.key_code == py5.UP:
        i = 0
        if add == 0:
            pass
        #COLOR_P1 = py5.color(py5.random(255), py5.random(255), py5.random(255))
        tail_key = "UP"
        while i < add:
            pos_y2 = pos_y2+espace
            tail_X[i] = pos_x2
            tail_Y[i] = pos_y2
           # py5.fill(COLOR_P1)            # couleur de l'objet
           # py5.no_stroke()
           # py5.ellipse(tail_X[i], tail_Y[i], diam/2, diam/2 )
            pos_x2 = tail_X[i]
            pos_y2 = tail_Y[i]
            i = i + 1

        add_Y_tail()

    if py5.key_code == py5.DOWN:
        i = 0
        if add == 0:
            pass
        #COLOR_P1 = py5.color(py5.random(255), py5.random(255), py5.random(255))
        tail_key = "DOWN"

        while i < add:
            pos_y2 = pos_y2-espace
            tail_X[i] = pos_x2
            tail_Y[i] = pos_y2
           # py5.fill(COLOR_P1)            # couleur de l'objet
           # py5.no_stroke()
           # py5.ellipse(tail_X[i], tail_Y[i], diam/2, diam/2 )
            pos_x2 = tail_X[i]
            pos_y2 = tail_Y[i]
            i = i + 1

        add_Y_tail()

    if py5.key_code == py5.LEFT:
        i = 0
        if add == 0:
            pass
        #COLOR = py5.color(py5.random(255), py5.random(255), py5.random(255))
        tail_key = "LEFT"

        while i < add:
            pos_x2 = pos_x2+espace
            tail_X[i] = pos_x2
            tail_Y[i] = pos_y2
           # py5.fill(COLOR_P1)            # couleur de l'objet
           # py5.no_stroke()
           # py5.ellipse(tail_X[i], tail_Y[i], diam/2, diam/2 )
            pos_x2 = tail_X[i]
            pos_y2 = tail_Y[i]
            i = i + 1

        add_X_tail()

    if py5.key_code == py5.RIGHT:
        i = 0
        if add == 0:
            pass
        #COLOR = py5.color(py5.random(255), py5.random(255), py5.random(255))
        tail_key = "RIGHT"

        while i < add:
            pos_x2 = pos_x2-espace
            tail_X[i] = pos_x2
            tail_Y[i] = pos_y2
           # py5.fill(COLOR_P1)            # couleur de l'objet
           # py5.no_stroke()
           # py5.ellipse(tail_X[i], tail_Y[i], diam/2, diam/2 )
            pos_x2 = tail_X[i]
            pos_y2 = tail_Y[i]
            i = i + 1

        add_X_tail()


def key_pressed():
    global touch_key, pos_x, pos_y, coord_X, coord_Y,direcion

    if py5.key_code == py5.UP:
        #COLOR_P1 = py5.color(py5.random(255), py5.random(255), py5.random(255))
        print("touche UP pressed")
        touch_key = "UP"
        direction = "UP"
        coord_X = pos_x
        coord_Y = pos_y
        display_Y_object()



    if py5.key_code == py5.DOWN:
        #COLOR_P1 = py5.color(py5.random(255), py5.random(255), py5.random(255))
        print("touche DOWN pressed")
        touch_key = "DOWN"
        direction = "DOWN"
        coord_X = pos_x
        coord_Y = pos_y
        display_Y_object()

    if py5.key_code == py5.LEFT:
        #COLOR = py5.color(py5.random(255), py5.random(255), py5.random(255))
        print("touche LEFT pressed")
        touch_key = "LEFT"
        direction = "LEFT"
        coord_X = pos_x
        coord_Y = pos_y
        display_X_object()

    if py5.key_code == py5.RIGHT:
        #COLOR = py5.color(py5.random(255), py5.random(255), py5.random(255))
        print("touche RIGHT pressed")
        touch_key = "RIGHT"
        direcion = "RIGHT"
        coord_X = pos_x
        coord_Y = pos_y
        display_X_object()

    else:
        print("touche unknown pressed")

def display_hote():
    global rayon, COLOR_P1, pos_x, pos_y, diam

    py5.fill(COLOR_P1)            # couleur de l'objet
    py5.no_stroke()
    py5.ellipse(pos_x, pos_y, diam/2, diam/2 )
    display_seed()
    key_pressed()
    goal_check()


def display_X_object():

    global touch_key, rayon, pos_x, pos_y, speed
    pos_x = pos_x + speed

    print("X:", pos_x,"/ Y:", pos_y)

    if touch_key == "RIGHT":
        print("RIGHT")
        if pos_x >= py5.width-rayon :
            speed = rayon-pos_x
        if pos_x  < py5.width-rayon :
            speed = 1

    if touch_key == "LEFT":
        print("LEFT")
        if pos_x <= rayon :
            speed = py5.width-rayon
        if pos_x  > rayon  :
            speed = -1

def display_Y_object():

    global touch_key, rayon, pos_x, pos_y, speed
    pos_y = pos_y + speed

    print("X:", pos_x,"/ Y:", pos_y)

    if touch_key == "DOWN":
        print("DOWN")
        if pos_y >= py5.height-rayon :
            speed = rayon-pos_y
        if pos_y  < py5.height-rayon :
            speed = 1

    if touch_key == "UP":
        print("UP")

        if pos_y <= rayon :
            speed = py5.height-rayon
        if pos_y  > rayon  :
            speed = -1

def display_seed():
    global COLOR_SEED, seed_x, seed_y, diam

    py5.fill(COLOR_SEED)            # couleur de l'objet
    py5.no_stroke()
    py5.ellipse(seed_x, seed_y, diam/2, diam/2 )

def goal_check():
    global seed_x, seed_y, pos_x, pos_y,rayon, add, tail_X, tail_Y, pos_x2, pos_y2
    prx = rayon-2
    large_Y = abs(seed_y - pos_y)
    large_X = abs(seed_x - pos_x)
    if large_X <= prx and large_Y <= prx :
        seed_x = py5.random_int(0,500)
        seed_y = py5.random_int(0,400)
        add = add + 1
        tail_X.append(0)
        tail_Y.append(0)
        pos_x2 = pos_x
        pos_y2 = pos_y
        key_tails()

    else:
        pass

    print("Seed: ", seed_x, "/", seed_y)


def Anime_tails():
    global add, COLOR_P1, tail_X, tail_Y, diam, q

    if add == 0 :
        pass
    else :
        while q < add:
            X = tail_X[q]
            Y = tail_Y[q]
            py5.fill(COLOR_P1)            # couleur de l'objet
            py5.no_stroke()
            py5.ellipse(X, Y, diam/2, diam/2 )
            move_tail()
            q = q + 1



def move_tail():
    add_X_tail()
    add_Y_tail()

def add_X_tail():
    global tail_key, rayon, speed, add, tail_X, coord_X, coord_Y, direction, q

    if tail_key == "RIGHT":

            tail_X[q] = tail_X[q] + speed
            if tail_X[q] >= py5.width-rayon :
                speed = rayon-tail_X[q]
            if tail_X[q]  < py5.width-rayon :
                speed = 1
            if tail_X[q] == coord_X and tail_Y[q] == coord_Y :
                tail_key = direcion
                move_tail()


    if tail_key== "LEFT":

            tail_X[q] = tail_X[q] + speed
            if tail_X[q] <= rayon :
                speed = py5.width-rayon
            if tail_X[q]  > rayon :
                speed = -1
            if tail_X[q] == coord_X and tail_Y[q] == coord_Y :
                tail_key = direcion
                move_tail()

def add_Y_tail():
    global tail_key, rayon, pos_x, speed, tail_Y, direction, q

    if tail_key == "UP":

            tail_Y[q] = tail_Y[q] + speed
            if tail_Y[q] <= rayon :
                speed = py5.height-rayon
            if tail_Y[q] > rayon :
                speed = -1
            if tail_X[q] == coord_X and tail_Y[q] == coord_Y :
                tail_key = direcion
                move_tail()


    if tail_key == "DOWN":

            tail_Y[q] = tail_Y[q] + speed
            if tail_Y[q] >= py5.height-rayon :
                speed = rayon-tail_Y[q]
            if tail_Y[q] < py5.height-rayon :
                speed = 1
            if tail_X[q] == coord_X and tail_Y[q] == coord_Y :
                tail_key = direcion
                move_tail()

py5.run_sketch()
