ROBOTPATH = ./robot

ROBOTSRC = $(ROBOTPATH)/motor/motor.c
ROBOTSRC += $(ROBOTPATH)/uart_md/comm_lld.c
ROBOTSRC += $(ROBOTPATH)/uart_md/comm.c

ROBOTINC = $(ROBOTPATH)/motor
ROBOTINC += $(ROBOTPATH)/uart_md