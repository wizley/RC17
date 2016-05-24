ROBOTPATH = ./robot

ROBOTSRC = $(ROBOTPATH)/motor/motor.c
ROBOTSRC += $(ROBOTPATH)/servo/servo.c
ROBOTSRC += $(ROBOTPATH)/encoder/encoder.c
ROBOTSRC += $(ROBOTPATH)/linesensor/linesensor.c
ROBOTSRC += $(ROBOTPATH)/driving.c
ROBOTSRC += $(ROBOTPATH)/loop_stats.c

ROBOTINC = $(ROBOTPATH)
ROBOTINC += $(ROBOTPATH)/motor
ROBOTINC += $(ROBOTPATH)/servo
ROBOTINC += $(ROBOTPATH)/encoder
ROBOTINC += $(ROBOTPATH)/linesensor