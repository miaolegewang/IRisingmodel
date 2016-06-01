# import necessary modules
import matplotlib.pyplot as plt
import matplotlib.image as mp
from numpy import *
from sys import *


def str2float(img):
    return array([float(x) for x in img])


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

def numOfMiss(origin, target):
    return sum(abs(origin - target))


def main(args):
    # original black and white image
    original = mp.imread(args[1])
    original = ceil(dot(original[..., :3], [1, 1, 1]) / 3.0 / 255.0)
    print original

    # noise black and white image
    noise = mp.imread(args[2])
    noise = ceil(dot(noise[..., :3], [1, 1, 1]) / 3.0 / 255.0)

    # denoise image
    imageDir = args[3]
    f = open(imageDir, "r")
    imgArr = [str2float(line.split()) for line in f]
    f.close()
    beta = imgArr[0]
    imgArr = array(imgArr[1:])
    imgArr = datafit(imgArr, {1.: 1., -1. : 0.})
    print "Noise ratio: {}\nNumber of Miss: {}\n"\
        .format(numOfMiss(original, noise) / float(len(original)) / float(len(original[0])), numOfMiss(original, imgArr))
    mp.imsave("restore.jpg", array(imgArr), cmap = plt.get_cmap('gray'))


if __name__ == "__main__":
    main(argv)
