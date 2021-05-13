# -*- coding: utf-8 -*-

import random
import numpy as np
import math

# def getVector(dimension):
#     return np.random.random(dimension)

# def getBaisVectorMatrix(dimension):
#     return np.random.rand(dimension,dimension)

# def sm(baisMatrix):
#     dimension = baisMatrix.shape[0]
#     res = [( baisMatrix[0] / math.sqrt(sum(baisMatrix[0]**2)) ).tolist()];
#     for i in range(1,dimension):
#         t = baisMatrix[i]
#         for j in range(0,i):
#             phi = np.array(res[j])
#             t -=  sum(phi * t) * phi;
#         t = t / math.sqrt(sum(t**2))
#         res.append(t.tolist())
#     return res

# def signInBaisMatrix(vector,sbm):
#     res = []
#     for i in range(0,sbm.shape[0]):
#         res.append( sum(vector*sbm[i]) )
#     return res

# bais = getBaisVectorMatrix(6)
# vector = getVector(6)
# print(signInBaisMatrix(vector,bais))

class Space():
    def __init__(self,dimension):
        self.dimension = dimension
        self.baisMatrix = self.getBaisVectorMatrix()
    
    def getBaisVectorMatrix(self):
        baisMatrix = np.random.rand(self.dimension,self.dimension)
        res = [( baisMatrix[0] / math.sqrt(sum(baisMatrix[0]**2)) ).tolist()];
        for i in range(1,self.dimension):
            t = baisMatrix[i]
            for j in range(0,i):
                phi = np.array(res[j])
                t -=  sum(phi * t) * phi;
            t = t / math.sqrt(sum(t**2))
            res.append(t.tolist())
        return res
    
    def getVector(self):
        return np.random.random(self.dimension)
        
    def signInBaisMatrix(self,vector):
        res = []
        for i in range(0,self.dimension):
            res.append( sum(vector*self.baisMatrix[i]) )
        return res

space = Space(6)
print(space.signInBaisMatrix(space.getVector()))
        
    
    

