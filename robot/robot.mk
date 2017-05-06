ROBOTPATH = ./robot

ROBOTSRC = $(ROBOTPATH)/motor/motor.c
ROBOTSRC += $(ROBOTPATH)/servo/servo.c
ROBOTSRC += $(ROBOTPATH)/encoder/encoder.c
ROBOTSRC += $(ROBOTPATH)/linesensor/linesensor.c
ROBOTSRC += $(ROBOTPATH)/driving.c
ROBOTSRC += $(ROBOTPATH)/loop_stats.c
ROBOTSRC += $(ROBOTPATH)/common.c
ROBOTSRC += $(ROBOTPATH)/pid.c
ROBOTSRC += $(ROBOTPATH)/blue.c
ROBOTSRC += $(ROBOTPATH)/red.c
ROBOTSRC += $(ROBOTPATH)/BoardIO/boardio.c

ROBOTINC = $(ROBOTPATH)
ROBOTINC += $(ROBOTPATH)/motor
ROBOTINC += $(ROBOTPATH)/servo
ROBOTINC += $(ROBOTPATH)/encoder
ROBOTINC += $(ROBOTPATH)/linesensor
ROBOTINC += $(ROBOTPATH)/BoardIO