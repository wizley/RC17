ROBOTPATH = ./robot

ROBOTSRC = $(ROBOTPATH)/motor/motor.c
ROBOTSRC += $(ROBOTPATH)/servo/servo.c
ROBOTSRC += $(ROBOTPATH)/encoder/encoder.c
ROBOTSRC += $(ROBOTPATH)/driving.c

ROBOTINC = $(ROBOTPATH)
ROBOTINC += $(ROBOTPATH)/motor
ROBOTINC += $(ROBOTPATH)/servo
ROBOTINC += $(ROBOTPATH)/encoder