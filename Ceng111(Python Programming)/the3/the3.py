import utils

dataset = utils.load_dataset("mnist.pkl")
network1 = utils.load_network("network_3layer.pkl")
network2 = utils.load_network("network_2layer.pkl")
X_sample = dataset["X_test"][100]

import math
def forward_pass(Network, X):
    activation=X[:]
    for i in range(len(Network)):
        if "relu" in Network[i]:
            activation = relu(activation)
        elif "sigmoid" in Network[i]:
            activation = sigmoid_clipped(activation)            
        else:            
            activation = linear_layer(Network[i][1],activation)
    return activation

def linear_layer(weights,X):
    activation = [0] * len(X)

    for i in range(len(weights)):        
        for j in range(len(X)):        
            activation[i] += weights[i][j] * X[j]
    
    activation = activation[:len(weights)]
    
    return activation
    
    
def sigmoid_clipped(x):
    for i in range(len(x)):
        if x[i] <= -700:
            x[i] = 0.
        elif x[i] >= 700:
            x[i] = 1.
        else:
            x[i] =  1.0 / ( 1.0 + math.exp(-x[i]) )
    return x


def relu(x):
    for i in range(len(x)):
        x[i] = max(0,x[i])
    return x

#for j in range(900,len(dataset["X_test"])):
#    X_sample = dataset["X_test"][j]
#   utils.display_image(X_sample)
  #  print(j,":",forward_pass(network1,X_sample).index(max(forward_pass(network1,X_sample))))
print(forward_pass(network1,X_sample))
#print(utils.calculate_accuracy(dataset, network2, predictor=forward_pass))
