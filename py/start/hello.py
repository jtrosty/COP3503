import mymath


print("hello, world!")
myMath = mymath.MathMine 

print("1. {0}".format(myMath.add(3, 2)))
print("1. {0}".format(myMath.sub(3, 2)))
print("1. {0}".format(myMath.div(3, 2)))
print("1. {0}".format(myMath.mul(3, 2)))

# For loop
fruits = ["apple", "banana", "cherry"]
for fruit in fruits:
    print(fruit)