#!/bin/bash

rm arbre.png > /dev/null 2>&1 
dot -Tpng -o arbre.png arbre.dot
display arbre.png &