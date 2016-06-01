# Before actually saving the data into a dat file
#  we let 1 be the color white and 0 represents the color black
# After binarizing and adding noise to the image, we
#  save the dat file with 1 standing for white and -1 for black

# import necessary libraries
from numpy import *
import matplotlib.pyplot as plt
import matplotlib.image as mp
from sys import *
from random import random

def int2str(arr):
    return [str(i) for i in arr]


def rgb2gray(imArr, formula = [0.229, 0.587, 0.114]):
    '''
        This function convert colored image to a gray scale image using the formula
            Y = i * R + j * G + k * B
        where [i, j, k] is default to be [0.229, 0.587, 0.114]
        two arguments:
        - imArr: three dimensional image array
        - formula: array of length 3 containing the parameters i, j and k
    '''
    return dot(imArr[..., :3], formula)

def addNoise(imArr, intensity=0.2):
    '''
        This function adds noise to an image array with respect to
        the probability 'intensity'
        two arguments:
        - imArr: two dimensional image array
        - intensity: probability of flipping one cell (default: 0.2)
    '''
    for i in xrange(len(imArr)):
        for j in xrange(len(imArr[i])):
            tmp = random()
            if tmp < intensity:
                imArr[i][j] = abs(imArr[i][j] - 1.)
    return imArr


def datafit(Data, mapping):
    '''
        This function apples mapping on each element in the dictionary
        two arguments:
        - Data: two dimensional array
        - mapping: a dictionary
    '''
    for i in xrange(len(Data)):
        for j in xrange(len(Data[i])):
            Data[i][j] = mapping[Data[i][j]]
    return Data



def main(argv):
    '''
        two arguments:
        1. the path of image
        2. the rate of converting grayscale to black and white image
    '''
    imageDir = argv[1]
    rate = float(argv[2]) if len(argv) > 2 else 0.44
    img = mp.imread(imageDir)
    try:
    # len() to test if the image is colored or grayscale/binary
        len(img[0][0])
        img = rgb2gray(img)
    except:
        pass
    #mp.imsave('Gray.jpg', array(img), cmap = plt.get_cmap('gray'))
    img = [map(lambda x: 1. if x > rate else 0., line) for line in img]
    mp.imsave('BW.jpg', array(img), cmap = plt.get_cmap('gray'))

    ## add noise to image
    img = addNoise(img)
    mp.imsave('Noise.jpg', array(img), cmap = plt.get_cmap('gray'))

    ## save image data to file
    img = datafit(img, {1.: 1., 0.: -1.})
    height = len(img)
    width = len(img[0])
    f = open("noise.dat", 'w')

    f.write(str(height) + "," + str(width) + "\n")
    for line in img:
        f.write(" ".join(int2str(line)) + "\n")
    f.close()


if __name__ == "__main__":
    main(argv)
