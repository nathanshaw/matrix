# import sys, os
from time import sleep

# make a dict to keep track of all the values
c_info = {}

def compileConfigFile():
    with open("Configuration.h", "w") as file:
        for key, val in c_info.items():
            s = "#{} {}\n".format(key, val)
            file.write(s)
        file.close()

if __name__ == "__main__":
    print("Hello and welcome to the Matrix robotic instrument firmware guided setup script");
    sleep(0.2);
    c_info["BOT_NAME"] = str(input("Please Enter in the Name of your Bot\n"));
    print("Your robot will be called : ", c_info["BOT_NAME"]  + "\n")

    #########################
    compileConfigFile()




