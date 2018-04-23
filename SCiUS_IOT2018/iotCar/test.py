from library import *

print(temp(),humi())

# led(100,0,0)
# motor.forward(1000)
# led(0,100,0)
# motor.backward(1000)
# led(0,0,100)

# while True:
#  	for i in range(16):
#  		sleep(0.1)
#  		led((16-i)*15,i*15,0)
#  	for i in range(16):
#  		sleep(0.1)
#  		led(0,(16-i)*15,i*15)
#  	for i in range(16):
#  		sleep(0.1)
#  		led(i*15,0,(16-i)*15)

notes = "C6 C6 D6 C6 F6 E6 C6 C6 D6 C6 G6 F6 C6 C6 C6 A6 F6 E6 D6 C6 C6 B6 G6 A6 G6".split(' ')
	
for i in notes:
	sound(i,250)