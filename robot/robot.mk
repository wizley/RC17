ROBOTPATH = ./robot

ROBOTSRC = $(ROBOTPATH)/motor/motor.c
ROBOTSRC += $(ROBOTPATH)/servo/servo.c
ROBOTSRC += $(ROBOTPATH)/encoder/encoder.c
#ROBOTSRC += $(ROBOTPATH)/uart_md/comm_lld.c
#ROBOTSRC += $(ROBOTPATH)/uart_md/comm.c

ROBOTINC = $(ROBOTPATH)
ROBOTINC += $(ROBOTPATH)/motor
ROBOTINC += $(ROBOTPATH)/servo
ROBOTINC += $(ROBOTPATH)/encoder
#ROBOTINC += $(ROBOTPATH)/uart_md